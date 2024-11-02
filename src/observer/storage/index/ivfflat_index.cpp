#include "storage/index/ivfflat_index.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include <queue>

RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
{

  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s",
        file_name, index_meta.name());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC rc = index_handler_.create(table->db()->log_handler(), bpm, file_name, field_meta.type(), field_meta.len());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, rc:%s",
        file_name, index_meta.name(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully create index, file_name:%s, index:%s",
    file_name, index_meta.name());
  return RC::SUCCESS;
}

IndexScanner *IvfflatIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return nullptr;
}

RC IvfflatIndex::train(int lists, int probes, DistanceType distance_type)
{
  return index_handler_.train(lists, probes, distance_type);
}
RC IvfflatIndex::close() { return RC::RECORD_EOF; }

vector<RID> IvfflatIndex::ann_search(const vector<float> &base_vector, DistanceType type, size_t limit)
{
  return index_handler_.ann_search(base_vector, type, limit);
}

RC IvfflatIndex::open(
    Table *table, const char *file_name, const IndexMeta &index_meta, std::vector<const FieldMeta *> &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s",
        file_name, index_meta.name());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC                 rc  = index_handler_.open(table->db()->log_handler(), bpm, file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, rc:%s",
        file_name, index_meta.name(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully open index, file_name:%s, index:%s",
    file_name, index_meta.name());
  return RC::SUCCESS;
}

RC IvfflatIndex::open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
{
  return Index::open(table, file_name, index_meta, field_meta);
}

RC IvfflatIndex::drop() { return RC::RECORD_EOF; }

RC IvfflatIndex::create(Table *table, bool is_unqiue, const char *file_name, const IndexMeta &index_meta,
    vector<const FieldMeta *> &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s",
        file_name, index_meta.name());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC                 rc  = index_handler_.create(
      table->db()->log_handler(), is_unqiue, bpm, file_name, field_meta, table->table_meta().null_field_num());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, rc:%s",
        file_name, index_meta.name(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully create index, file_name:%s, index:%s",
    file_name, index_meta.name());
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

RC IvfflatIndexHandler::create(
    LogHandler &log_handler, BufferPoolManager &bpm, const char *file_name, AttrType attr_type, int attr_length)
{
  RC rc = bpm.create_file(file_name);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to create file. file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  LOG_INFO("Successfully create index file:%s", file_name);

  DiskBufferPool *bp = nullptr;

  rc = bpm.open_file(log_handler, file_name, bp);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to open file. file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  LOG_INFO("Successfully open index file %s.", file_name);

  rc = this->create(log_handler, *bp, attr_type, attr_length);
  if (OB_FAIL(rc)) {
    bpm.close_file(file_name);
    return rc;
  }

  LOG_INFO("Successfully create index file %s.", file_name);
  return rc;
}
RC IvfflatIndexHandler::create(
    LogHandler &log_handler, DiskBufferPool &buffer_pool, AttrType attr_type, int attr_length)
{

  log_handler_      = &log_handler;
  disk_buffer_pool_ = &buffer_pool;

  RC rc = RC::SUCCESS;

  Frame *header_frame = nullptr;

  rc = disk_buffer_pool_->allocate_page(&header_frame);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to allocate header page for bplus tree. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  char            *pdata       = header_frame->data();
  IndexFileHeader *file_header = (IndexFileHeader *)pdata;
  file_header->key_length      = attr_length + sizeof(RID);
  file_header->root_page       = BP_INVALID_PAGE_NUM;
  // 取消记录日志的原因请参考下面的sync调用的地方。
  // mtr.logger().init_header_page(header_frame, *file_header);

  header_frame->mark_dirty();

  memcpy(&file_header_, pdata, sizeof(file_header_));
  header_dirty_ = false;

  mem_pool_item_ = make_unique<common::MemPoolItem>("b+tree");
  if (mem_pool_item_->init(file_header->key_length) < 0) {
    LOG_WARN("Failed to init memory pool for index");
    close();
    return RC::NOMEM;
  }

  rc = this->sync();
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to sync index header. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  LOG_INFO("Successfully create index");
  return RC::SUCCESS;
}

RC IvfflatIndexHandler::sync()
{
  if (header_dirty_) {
    Frame *frame = nullptr;

    RC rc = disk_buffer_pool_->get_this_page(FIRST_INDEX_PAGE, &frame);
    if (OB_SUCC(rc) && frame != nullptr) {
      char *pdata = frame->data();
      memcpy(pdata, &file_header_, sizeof(file_header_));
      frame->mark_dirty();
      disk_buffer_pool_->unpin_page(frame);
      header_dirty_ = false;
    } else {
      LOG_WARN("failed to sync index header file. file_desc=%d, rc=%s", disk_buffer_pool_->file_desc(), strrc(rc));
      // TODO: ingore?
    }
  }
  return disk_buffer_pool_->flush_all_pages();
}

RC IvfflatIndexHandler::close()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
    log_handler_      = nullptr;
  }
  return RC::SUCCESS;
}

RC IvfflatIndexHandler::train(int lists, int probes, DistanceType distance_type)
{
  const auto &info   = file_header_.attr_info[file_header_.null_field_num];
  int         offset = info.offset;
  int         len    = info.length;
  int         dim    = len / static_cast<int>(sizeof(float));

  Frame *frame = nullptr;

  disk_buffer_pool_->get_this_page(FIRST_INDEX_PAGE, &frame);

  IvfIndexFileHeader *file_header = reinterpret_cast<IvfIndexFileHeader *>(frame->data());
  file_header->lists_             = lists;
  file_header->probes_            = probes;
  file_header->distance_type_     = distance_type;
  file_header->dim_               = dim;
  file_header_.lists_             = lists;
  file_header_.probes_            = probes;
  file_header_.distance_type_     = distance_type;
  file_header_.dim_               = dim;
  header_dirty_                   = true;
  frame->mark_dirty();

  ivf_file_handler_.init_vec_info(dim, lists, probes, distance_type, data_file_handler_);

  std::vector<std::vector<float>> last(lists, std::vector<float>(dim, 0));
  std::vector<std::vector<float>> cur(lists, std::vector<float>(dim, 0));
  std::vector<int>                num(lists, 0);

  dis_calc_.init(distance_type);

  int             times = 6;
  DataFileScanner scanner;
  int             init = 0;
  for (int ii = 0; ii < times; ii++) {
    RC rc = scanner.open_scan(*disk_buffer_pool_, *log_handler_, ReadWriteMode::READ_ONLY);

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open scan. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    Record record;
    while (OB_SUCC(rc = scanner.next(record))) {
      auto data = reinterpret_cast<float *>(record.data() + offset);
      if (init < lists) {
        memcpy(last[init].data(), data, len);
        memcpy(cur[init].data(), data, len);
        num[init]++;
        init++;
      } else {
        float dis = std::numeric_limits<float>::max();
        int   off = 0;
        for (int i = 0; i < lists; i++) {
          float new_dis = dis_calc_(last[i].data(), data, dim);
          if (new_dis < dis) {
            dis = new_dis;
            off = i;
          }
        }
        if (num[off] == 0) {
          memcpy(cur[off].data(), data, len);
        } else {
          for (int i = 0; i < dim; i++) {
            cur[off][i] += (data[i] - cur[off][i]) / static_cast<float>(num[off] + 1);
          }
        }

        num[off]++;
      }
    }
    last.swap(cur);
    num.assign(lists, 0);

    scanner.close_scan();
  }

  RC rc = ivf_file_handler_.insert_cluster_record(last);

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open scan. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  rc = scanner.open_scan(*disk_buffer_pool_, *log_handler_, ReadWriteMode::READ_ONLY);

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open scan. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    auto  data = reinterpret_cast<float *>(record.data() + offset);
    float dis  = std::numeric_limits<float>::max();
    int   off  = 0;
    for (int i = 0; i < lists; i++) {
      float new_dis = dis_calc_(last[i].data(), data, dim);
      if (new_dis < dis) {
        dis = new_dis;
        off = i;
      }
    }
    rc = ivf_file_handler_.insert_record_into_bucket(&record.rid(), off);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into bucket. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("failed to scan all records. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  LOG_INFO("Successfully train index.");

  return RC::SUCCESS;
}

RC IvfflatIndexHandler::create(LogHandler &log_handler, bool is_unqiue, DiskBufferPool &buffer_pool,
    DiskBufferPool &ivf, std::vector<const FieldMeta *> &field_metas, int null_field_num)
{
  std::vector<AttrTypeInfo> attr_type_infos;

  for (const FieldMeta *field_meta : field_metas) {
    int len = field_meta->len();
    attr_type_infos.emplace_back(field_meta->type(), len, field_meta->offset(), field_meta->field_id());
  }
  auto &attr_type_info = field_metas[field_metas.size() - 1];
  int   attr_length    = attr_type_info->len() + attr_type_info->offset();

  log_handler_      = &log_handler;
  disk_buffer_pool_ = &buffer_pool;
  ivf_buffer_pool_  = &ivf;
  data_file_handler_.init(buffer_pool, log_handler);
  ivf_file_handler_.init(ivf, log_handler);

  RC rc = RC::SUCCESS;

  Frame *header_frame = nullptr;

  rc = disk_buffer_pool_->allocate_page(&header_frame);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to allocate header page for bplus tree. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  if (header_frame->page_num() != FIRST_INDEX_PAGE) {
    LOG_WARN("header page num should be %d but got %d. is it a new file",
            FIRST_INDEX_PAGE, header_frame->page_num());
    return RC::INTERNAL;
  }

  char               *pdata       = header_frame->data();
  IvfIndexFileHeader *file_header = (IvfIndexFileHeader *)pdata;
  file_header->key_length         = attr_length + sizeof(RID);
  file_header->root_page          = BP_INVALID_PAGE_NUM;
  file_header->attr_size          = field_metas.size();
  file_header->attr_length        = attr_length;
  file_header->null_field_num     = null_field_num;
  file_header->is_unique          = is_unqiue;

  for (size_t i = 0; i < field_metas.size(); i++) {
    file_header->attr_info[i] = attr_type_infos[i];
  }

  // 取消记录日志的原因请参考下面的sync调用的地方。
  // mtr.logger().init_header_page(header_frame, *file_header);

  header_frame->mark_dirty();

  memcpy(&file_header_, pdata, sizeof(file_header_));
  header_dirty_ = false;

  mem_pool_item_ = make_unique<common::MemPoolItem>("IVF");
  if (mem_pool_item_->init(file_header->key_length) < 0) {
    LOG_WARN("Failed to init memory pool for index");
    close();
    return RC::NOMEM;
  }

  rc = this->sync();
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to sync index header. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  LOG_INFO("Successfully create index");
  return RC::SUCCESS;
}

RC IvfflatIndexHandler::create(LogHandler &log_handler, bool is_unqiue, BufferPoolManager &bpm, const char *file_name,
    vector<const FieldMeta *> &field_metas, int null_field_num)
{
  RC rc = bpm.create_file(file_name);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to create file. file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  LOG_INFO("Successfully create index file:%s", file_name);

  DiskBufferPool *bp = nullptr;

  rc = bpm.open_file(log_handler, file_name, bp);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to open file. file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  LOG_INFO("Successfully open index file %s.", file_name);

  std::string file_name_ivf = std::string(file_name) + "_ivf";

  rc = bpm.create_file(file_name_ivf.c_str());
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to create file. file name=%s, rc=%d:%s", file_name_ivf.c_str(), rc, strrc(rc));
    return rc;
  }

  DiskBufferPool *ivf = nullptr;

  rc = bpm.open_file(log_handler, file_name_ivf.c_str(), ivf);
  LOG_INFO("Successfully create index file:%s", file_name_ivf.c_str());

  rc = this->create(log_handler, is_unqiue, *bp, *ivf, field_metas, null_field_num);
  if (OB_FAIL(rc)) {
    bpm.close_file(file_name);
    return rc;
  }

  LOG_INFO("Successfully create index file %s.", file_name);
  return rc;
}
RC IvfflatIndexHandler::insert_entry(const char *user_key, const RID *rid)
{
  if (user_key == nullptr || rid == nullptr) {
    LOG_WARN("Invalid arguments, key is empty or rid is empty");
    return RC::INVALID_ARGUMENT;
  }

  common::MemPoolItem::item_unique_ptr pkey = make_key(user_key, *rid);
  if (pkey == nullptr) {
    LOG_WARN("Failed to alloc memory for key.");
    return RC::NOMEM;
  }

  char *key = static_cast<char *>(pkey.get());

  RID record{};
  RC  rc = data_file_handler_.insert_record(key, file_header_.key_length, &record);

  return rc;
}
common::MemPoolItem::item_unique_ptr IvfflatIndexHandler::make_key(const char *user_key, const RID &rid)
{
  common::MemPoolItem::item_unique_ptr key = mem_pool_item_->alloc_unique_ptr();
  if (key == nullptr) {
    LOG_WARN("Failed to alloc memory for key.");
    return nullptr;
  }
  memcpy(static_cast<char *>(key.get()), user_key, file_header_.attr_length);
  memcpy(static_cast<char *>(key.get()) + file_header_.attr_length, &rid, sizeof(rid));
  return key;
}
RC IvfflatIndexHandler::open(LogHandler &log_handler, BufferPoolManager &bpm, const char *file_name)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_WARN("%s has been opened before index.open.", file_name);
    return RC::RECORD_OPENNED;
  }

  DiskBufferPool *disk_buffer_pool = nullptr;

  RC rc = bpm.open_file(log_handler, file_name, disk_buffer_pool);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to open file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  std::string     file_name_ivf = std::string(file_name) + "_ivf";
  DiskBufferPool *ivf           = nullptr;
  rc                            = bpm.open_file(log_handler, file_name_ivf.c_str(), ivf);

  rc = this->open(log_handler, *disk_buffer_pool, *ivf);
  if (OB_SUCC(rc)) {
    LOG_INFO("open ivf success. filename=%s", file_name);
  }
  return rc;
}
RC IvfflatIndexHandler::open(LogHandler &log_handler, DiskBufferPool &buffer_pool, DiskBufferPool &ivf)
{

  if (disk_buffer_pool_ != nullptr) {
    LOG_WARN("ivf has been opened before index.open.");
    return RC::RECORD_OPENNED;
  }

  RC rc = RC::SUCCESS;

  Frame *frame = nullptr;
  rc           = buffer_pool.get_this_page(FIRST_INDEX_PAGE, &frame);
  if (OB_FAIL(rc)) {
    LOG_WARN("Failed to get first page, rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  char *pdata = frame->data();
  memcpy(&file_header_, pdata, sizeof(IvfIndexFileHeader));
  header_dirty_     = false;
  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;

  data_file_handler_.init(buffer_pool, log_handler);
  ivf_file_handler_.init(ivf, log_handler);

  mem_pool_item_ = make_unique<common::MemPoolItem>("b+tree");
  if (mem_pool_item_->init(file_header_.key_length) < 0) {
    LOG_WARN("Failed to init memory pool for index");
    close();
    return RC::NOMEM;
  }

  // close old page_handle
  buffer_pool.unpin_page(frame);

  std::vector<AttrTypeInfo> attr_type_infos;
  for (int i = 0; i < file_header_.attr_size; i++) {
    attr_type_infos.emplace_back(
        file_header_.attr_info[i].type, file_header_.attr_info[i].length, file_header_.attr_info[i].offset);
  }

  dis_calc_.init(static_cast<DistanceType>(file_header_.distance_type_));
  ivf_file_handler_.init_vec_info(file_header_.dim_,
      file_header_.lists_,
      file_header_.probes_,
      static_cast<DistanceType>(file_header_.distance_type_),
      data_file_handler_);

  LOG_INFO("Successfully open index");
  return RC::SUCCESS;
}

std::vector<RID> IvfflatIndexHandler::ann_search(const vector<float> &base_vector, DistanceType type, size_t limit)
{
  return ivf_file_handler_.ann_search(base_vector, type, limit);
}

RC DataFileHandler::init(DiskBufferPool &buffer_pool, LogHandler &log_handler)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_ERROR("record file handler has been openned.");
    return RC::RECORD_OPENNED;
  }

  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;
  storage_format_   = StorageFormat::ROW_FORMAT;

  return init_free_page();
}

void DataFileHandler::close()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
    log_handler_      = nullptr;
  }
}

RC DataFileHandler::insert_record(const char *data, int record_size, RID *rid)
{
  RC ret = RC::SUCCESS;

  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));

  ret = record_page_handler->init(*disk_buffer_pool_, *log_handler_, current_page_num_, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(ret)) {
    LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num_, ret, strrc(ret));
    return ret;
  }

  if (record_page_handler->is_full()) {
    record_page_handler->cleanup();
    // 找不到就分配一个新的页面
    Frame *frame = nullptr;
    if ((ret = disk_buffer_pool_->allocate_page(&frame)) != RC::SUCCESS) {
      LOG_ERROR("Failed to allocate page while inserting record. ret:%d", ret);
      return ret;
    }

    current_page_num_ = frame->page_num();

    ret = record_page_handler->init_empty_page(
        *disk_buffer_pool_, *log_handler_, current_page_num_, record_size, nullptr);
    if (OB_FAIL(ret)) {
      frame->unpin();
      LOG_ERROR("Failed to init empty page. ret:%d", ret);
      // this is for allocate_page
      return ret;
    }

    // frame 在allocate_page的时候，是有一个pin的，在init_empty_page时又会增加一个，所以这里手动释放一个
    frame->unpin();
  }

  // 找到空闲位置
  return record_page_handler->insert_record(data, rid);
}
RC DataFileHandler::get_record(const RID &rid, Record &record)
{
  unique_ptr<RecordPageHandler> page_handler(RecordPageHandler::create(storage_format_));

  RC rc = page_handler->init(*disk_buffer_pool_, *log_handler_, rid.page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init record page handler.page number=%d", rid.page_num);
    return rc;
  }

  Record inplace_record;
  rc = page_handler->get_record(rid, inplace_record);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get record from record page handle. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
    return rc;
  }

  record.copy_data(inplace_record.data(), inplace_record.len());
  record.set_rid(rid);
  return rc;
}
RC DataFileHandler::visit_record(const RID &rid, function<bool(Record &)> updater)
{
  unique_ptr<RecordPageHandler> page_handler(RecordPageHandler::create(storage_format_));

  RC rc = page_handler->init(*disk_buffer_pool_, *log_handler_, rid.page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init record page handler.page number=%d", rid.page_num);
    return rc;
  }

  Record inplace_record;
  rc = page_handler->get_record(rid, inplace_record);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get record from record page handle. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
    return rc;
  }

  // 需要将数据复制出来再修改，否则update_record调用失败但是实际上数据却更新成功了，
  // 会导致数据库状态不正确
  Record record;
  record.copy_data(inplace_record.data(), inplace_record.len());
  record.set_rid(rid);

  bool updated = updater(record);
  if (updated) {
    rc = page_handler->update_record(rid, record.data());
  }
  return rc;
}
RC DataFileHandler::init_free_page()
{

  RC rc = RC::SUCCESS;

  BufferPoolIterator bp_iterator;
  bp_iterator.init(*disk_buffer_pool_, 1);
  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));
  PageNum                       current_page_num = 0;

  while (bp_iterator.has_next()) {
    current_page_num = bp_iterator.next();

    rc = record_page_handler->init(*disk_buffer_pool_, *log_handler_, current_page_num, ReadWriteMode::READ_ONLY);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num, rc, strrc(rc));
      return rc;
    }

    if (!record_page_handler->is_full()) {
      current_page_num_ = current_page_num;
      record_page_handler->cleanup();
    }
    record_page_handler->cleanup();
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

DataFileScanner::~DataFileScanner() { close_scan(); }

RC DataFileScanner::open_scan(DiskBufferPool &buffer_pool, LogHandler &log_handler, ReadWriteMode mode)
{
  close_scan();

  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;
  rw_mode_          = mode;

  RC rc = bp_iterator_.init(buffer_pool, 1);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to init bp iterator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  record_page_handler_ = new RowRecordPageHandler();

  return rc;
}

/**
 * @brief 从当前位置开始找到下一条有效的记录
 *
 * 如果当前页面还有记录没有访问，就遍历当前的页面。
 * 当前页面遍历完了，就遍历下一个页面，然后找到有效的记录
 */
RC DataFileScanner::fetch_next_record()
{
  RC rc = RC::SUCCESS;
  if (record_page_iterator_.is_valid()) {
    // 当前页面还是有效的，尝试看一下是否有有效记录
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 上个页面遍历完了，或者还没有开始遍历某个页面，那么就从一个新的页面开始遍历查找
  while (bp_iterator_.has_next()) {
    PageNum page_num = bp_iterator_.next();
    record_page_handler_->cleanup();
    rc = record_page_handler_->init(*disk_buffer_pool_, *log_handler_, page_num, rw_mode_);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to init record page handler. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    record_page_iterator_.init(record_page_handler_);
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 所有的页面都遍历完了，没有数据了
  next_record_.rid().slot_num = -1;
  record_page_handler_->cleanup();
  return RC::RECORD_EOF;
}

/**
 * @brief 遍历当前页面，尝试找到一条有效的记录
 */
RC DataFileScanner::fetch_next_record_in_page()
{
  RC rc = RC::SUCCESS;
  while (record_page_iterator_.has_next()) {
    rc = record_page_iterator_.next(next_record_);
    if (rc != RC::SUCCESS) {
      const auto page_num = record_page_handler_->get_page_num();
      LOG_TRACE("failed to get next record from page. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    return rc;
  }

  next_record_.rid().slot_num = -1;
  return RC::RECORD_EOF;
}

RC DataFileScanner::close_scan()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
  }

  if (record_page_handler_ != nullptr) {
    record_page_handler_->cleanup();
    delete record_page_handler_;
    record_page_handler_ = nullptr;
  }

  return RC::SUCCESS;
}

RC DataFileScanner::next(Record &record)
{
  RC rc = fetch_next_record();
  if (OB_FAIL(rc)) {
    return rc;
  }

  record = next_record_;
  return RC::SUCCESS;
}

RC DataFileScanner::update_current(const Record &record)
{
  if (record.rid() != next_record_.rid()) {
    return RC::INVALID_ARGUMENT;
  }

  return record_page_handler_->update_record(record.rid(), record.data());
}

RC IvfFileHandler::insert_cluster_record(std::vector<std::vector<float>> &data)
{
  int record_size          = dim_ * sizeof(float);
  cluster_record_per_page_ = (BP_PAGE_DATA_SIZE) / record_size;

  int page_num = (list_ + cluster_record_per_page_ - 1) / cluster_record_per_page_;

  for (int i = 0; i < page_num; ++i) {
    Frame *frame = nullptr;
    RC     rc    = disk_buffer_pool_->allocate_page(&frame);
    ASSERT(frame->page_num() == FIRST_INDEX_PAGE + i, "page num is not correct");
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to allocate page while inserting record. ret:%d", rc);
      return rc;
    }

    for (int j = 0; j < cluster_record_per_page_; ++j) {
      if (i * cluster_record_per_page_ + j >= list_) {
        break;
      }
      char *pdata = frame->data() + j * record_size;
      memcpy(pdata, data[i * cluster_record_per_page_ + j].data(), record_size);
    }
    frame->mark_dirty();
    frame->unpin();
  }

  int end_page_size = BP_PAGE_DATA_SIZE / sizeof(int);

  int end_page_num = (list_ + end_page_size - 1) / end_page_size;

  offset_page_num_ = FIRST_INDEX_PAGE + page_num;

  for (int i = 0; i < end_page_num; ++i) {
    Frame *frame = nullptr;
    RC     rc    = disk_buffer_pool_->allocate_page(&frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
      return rc;
    }

    OffsetPage *pdata = reinterpret_cast<OffsetPage *>(frame->data());

    for (int j = 0; j < end_page_size; ++j) {
      if (i * end_page_size + j >= list_) {
        break;
      }

      Frame *tmp_frame = nullptr;
      rc               = disk_buffer_pool_->allocate_page(&tmp_frame);
      if (rc != RC::SUCCESS) {
        LOG_WARN("Failed to allocate page while inserting record. ret:%d", rc);
        return rc;
      }

      pdata->array[j] = tmp_frame->page_num();

      IvfBucketPage *bucket = reinterpret_cast<IvfBucketPage *>(tmp_frame->data());
      bucket->size          = 0;

      tmp_frame->mark_dirty();
      tmp_frame->unpin();
    }
    frame->mark_dirty();
    frame->unpin();
  }

  return RC::SUCCESS;
}
RC IvfFileHandler::insert_record_into_bucket(const RID *rid, int offset)
{
  Frame *frame           = nullptr;
  int    offset_per_page = BP_PAGE_DATA_SIZE / sizeof(int);

  // NOTE: offset_page_num_ 是第一个offset page的page number, *2 是因为分配时与数据页是交替分配的
  RC rc = disk_buffer_pool_->get_this_page(offset_page_num_ + (offset / offset_per_page) * 2, &frame);
  if (rc != RC::SUCCESS) {
    LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
    return rc;
  }
  OffsetPage *pdata = reinterpret_cast<OffsetPage *>(frame->data());
  PageNum     page  = pdata->array[offset % offset_per_page];
  frame->unpin();

  rc = disk_buffer_pool_->get_this_page(page, &frame);
  if (rc != RC::SUCCESS) {
    LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
    return rc;
  }

  IvfBucketPage *bucket = reinterpret_cast<IvfBucketPage *>(frame->data());
  if (bucket->size >= IvfBucketPage::BUCKET_SIZE) {
    frame->unpin();
    Frame *offset_frame = nullptr;
    rc = disk_buffer_pool_->get_this_page(offset_page_num_ + (offset / offset_per_page) * 2, &offset_frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
      return rc;
    }

    rc = disk_buffer_pool_->allocate_page(&frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to allocate page while inserting record. ret:%d", rc);
      return rc;
    }

    OffsetPage *offset_p                      = reinterpret_cast<OffsetPage *>(offset_frame->data());
    offset_p->array[offset % offset_per_page] = frame->page_num();
    offset_frame->mark_dirty();
    offset_frame->unpin();
    bucket       = reinterpret_cast<IvfBucketPage *>(frame->data());
    bucket->size = 0;
  }

  bucket->data[bucket->size] = *rid;
  bucket->size++;

  frame->mark_dirty();
  frame->unpin();
  return RC::SUCCESS;
}

RC IvfFileHandler::init(DiskBufferPool &buffer_pool, LogHandler &log_handler)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_ERROR("record file handler has been openned.");
    return RC::RECORD_OPENNED;
  }

  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;
  storage_format_   = StorageFormat::ROW_FORMAT;

  return RC::SUCCESS;
}

RC IvfFileHandler::init_vec_info(int dim, int lists, int probes, DistanceType distance_type, DataFileHandler &handler)
{
  dim_                     = dim;
  list_                    = lists;
  probes_                  = probes;
  data_file_handler_       = &handler;
  int record_size          = dim_ * sizeof(float);
  cluster_record_per_page_ = (BP_PAGE_DATA_SIZE) / record_size;

  int page_num = (list_ + cluster_record_per_page_ - 1) / cluster_record_per_page_;

  offset_page_num_         = FIRST_INDEX_PAGE + page_num;
  cluster_record_per_page_ = (BP_PAGE_DATA_SIZE) / record_size;

  dis_calc_.init(distance_type);
  return RC::SUCCESS;
}

std::vector<RID> IvfFileHandler::ann_search(const vector<float> &base_vector, DistanceType type, size_t limit)
{
  std::vector<RID> result;

  struct Node
  {
    float dis;
    int   offset;
    Node(float dis, int offset) : dis(dis), offset(offset) {}
    bool operator<(const Node &node) const { return dis < node.dis; }
  };
  std::priority_queue<Node> q;

  DistanceCalc dis_calc;
  dis_calc.init(type);

  for (int i = 0; i < list_; i++) {
    Frame *frame = nullptr;
    RC     rc    = disk_buffer_pool_->get_this_page(FIRST_INDEX_PAGE + i / cluster_record_per_page_, &frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
      return result;
    }
    char *pdata = frame->data() + (i % cluster_record_per_page_) * dim_ * sizeof(float);

    float dis = dis_calc(base_vector.data(), reinterpret_cast<const float *>(pdata), dim_);
    if (q.size() < probes_) {
      q.emplace(dis, i);
    } else {
      if (dis < q.top().dis) {
        q.pop();
        q.emplace(dis, i);
      }
    }
    frame->unpin();
  }

  struct RIDNode
  {
    RID   rid;
    float dis;
    RIDNode(RID rid, float dis) : rid(rid), dis(dis) {}
    bool operator<(const RIDNode &node) const { return dis < node.dis; }
  };

  std::priority_queue<RIDNode> result_q;
  int                          offset_per_page = BP_PAGE_DATA_SIZE / sizeof(int);

  int offset = 0;
  while (!q.empty()) {
    Record record;
    Frame *frame = nullptr;
    RC     rc    = disk_buffer_pool_->get_this_page(offset_page_num_ + q.top().offset / offset_per_page * 2, &frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
      return result;
    }
    OffsetPage *offset_page = reinterpret_cast<OffsetPage *>(frame->data());
    PageNum     page        = offset_page->array[q.top().offset % offset_per_page];
    frame->unpin();
    rc = disk_buffer_pool_->get_this_page(page, &frame);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to get page while inserting record. ret:%d", rc);
      return result;
    }
    IvfBucketPage *bucket = reinterpret_cast<IvfBucketPage *>(frame->data());
    for (int i = 0; i < bucket->size; i++) {
      rc = data_file_handler_->get_record(bucket->data[i], record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("Failed to get record while inserting record. ret:%d", rc);
        return result;
      }
      offset = record.len() - sizeof(RID) - dim_ * sizeof(float);

      float dis = dis_calc(base_vector.data(), reinterpret_cast<const float *>(record.data() + offset), dim_);
      RID  *rid = reinterpret_cast<RID *>(record.data() + record.len() - sizeof(RID));
      if (result_q.size() < limit) {
        result_q.emplace(*rid, dis);
      } else {
        if (dis < result_q.top().dis) {
          result_q.pop();
          result_q.emplace(*rid, dis);
        }
      }
    }
    frame->unpin();
    q.pop();
  }

  for (int i = 0; i < limit; i++) {
    if (result_q.empty()) {
      break;
    }
    result.push_back(result_q.top().rid);
    result_q.pop();
  }
  return result;
}
