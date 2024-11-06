/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "storage/index/ivfflat_index.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  if (temp_buffer_pool_ != nullptr) {
    temp_buffer_pool_->close_file();
    temp_buffer_pool_ = nullptr;
  }

  for (vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name().c_str());
}

RC Table::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
    span<const AttrInfoSqlNode> attributes, StorageFormat storage_format, bool is_view)
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  const vector<FieldMeta> *trx_fields = db->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attributes, storage_format, is_view)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  string             data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = db->buffer_pool_manager();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }
  int start = table_meta_.sys_field_num();
  for (int i = start; i < table_meta_.field_num(); ++i) {
    auto type = table_meta_.field(i)->type();
    if (type == AttrType::TEXTS || type == AttrType::HIGH_DIMS) {
      std::string tem = table_temp_file(base_dir, name);
      rc              = bpm.create_file(tem.c_str());
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", tem.c_str());
        return rc;
      }
      rc = bpm.open_file(db_->log_handler(), tem.c_str(), temp_buffer_pool_);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", tem.c_str(), rc, strrc(rc));
        return rc;
      }
      break;
    }
  }

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop(const char *meta_file)
{
  if (common::is_blank(meta_file)) {
    LOG_WARN("Invalid arguments. meta_file=%s", meta_file);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  // 删除表文件
  if (remove(meta_file) != 0) {
    LOG_ERROR("Failed to remove table file. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::INTERNAL;
  }

  string             data_file = table_data_file(base_dir_.c_str(), table_meta_.name());
  BufferPoolManager &bpm       = db()->buffer_pool_manager();
  rc                           = bpm.remove_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  data_buffer_pool_ = nullptr;

  temp_buffer_pool_ = nullptr;

  delete record_handler_;
  record_handler_ = nullptr;

  for (Index *index : indexes_) {
    index->drop();
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Successfully drop table:%s", meta_file);
  return rc;
}

RC Table::open(Db *db, const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta               *index_meta = table_meta_.index(i);
    std::vector<const FieldMeta *> field_meta;
    for (const auto &field_name : index_meta->field()) {
      const FieldMeta *field = table_meta_.field(field_name.c_str());
      if (field == nullptr) {
        LOG_ERROR("Failed to open index. table=%s, index=%s, field=%s",
                  name().c_str(), index_meta->name(), field_name.c_str());
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::INTERNAL;
      }
      field_meta.push_back(field);
    }
    if (field_meta.empty()) {
      LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s",
                name().c_str(), index_meta->name());
      // skip cleanup
      //  do all cleanup action in destructive Table function
      return RC::INTERNAL;
    }

    Index *index = nullptr;

    if (index_meta->type() == IndexType::BTREE) {
      index = new BplusTreeIndex();
    } else if (index_meta->type() == IndexType::IVF) {
      index = new IvfflatIndex();
    } else {
      LOG_ERROR("Failed to open index. table=%s, index=%s, type=%d",
                name().c_str(), index_meta->name(), index_meta->type());
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return RC::INTERNAL;
    }

    string index_file = table_index_file(base_dir, name(), index_meta->name());

    rc = index->open(this, index_file.c_str(), *index_meta, field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name().c_str(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  int start = table_meta_.sys_field_num();
  for (int i = start; i < table_meta_.field_num(); ++i) {
    auto type = table_meta_.field(i)->type();
    if (type == AttrType::TEXTS || type == AttrType::HIGH_DIMS) {
      BufferPoolManager &bpm = db_->buffer_pool_manager();
      std::string        tem = table_temp_file(base_dir, table_meta_.name());
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", tem.c_str());
        return rc;
      }
      rc = bpm.open_file(db_->log_handler(), tem.c_str(), temp_buffer_pool_);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", tem.c_str(), rc, strrc(rc));
        return rc;
      }
      break;
    }
  }

  return rc;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    if (rc == RC::RECORD_DUPLICATE_KEY_UNIQUE) {
      record_handler_->delete_record(&record.rid());
      return rc;
    }

    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    }
  }
  return rc;
}

RC Table::update_record(Record &record, const FieldMeta *field_meta, Value &value)
{
  RC rc = RC::SUCCESS;

  auto data = new char[table_meta_.record_size()];
  memcpy(data, record.data(), table_meta_.record_size());
  auto null_map          = reinterpret_cast<int *>(data + table_meta_.field(table_meta_.null_field_offset())->offset());
  const FieldMeta *field = field_meta;

  // TODO: optimize this
  if (value.attr_type() == AttrType::NULLS) {
    null_map[0] |= (1 << (field->field_id()));
  } else {
    if (field->type() != value.attr_type()) {
      Value real_value;
      rc = Value::cast_to(value, field->type(), real_value);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name().c_str(), value.to_string().c_str());
      }
      rc = set_value_to_record(data, real_value, field);
    } else {
      rc = set_value_to_record(data, value, field);
    }
  }

  Record new_record;
  new_record.set_data(data, table_meta_.record_size());
  new_record.set_rid(record.rid());

  if (OB_FAIL(rc)) {
    LOG_WARN("failed to update record. table name:%s", table_meta_.name());
    return rc;
  }

  RC rc2 = delete_record(record);
  if (rc2 != RC::SUCCESS) {
    LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
  }

  rc2 = insert_record(new_record);
  if (rc2 != RC::SUCCESS) {
    LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
  }

  return rc;
}

RC Table::visit_record(const RID &rid, function<bool(Record &)> visitor)
{
  return record_handler_->visit_record(rid, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  RC rc = record_handler_->get_record(rid, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name().c_str(), strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const std::string &Table::name() const { return table_meta_.name_str(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  RC rc = RC::SUCCESS;
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  // 复制所有字段的值
  int   record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  memset(record_data, 0, record_size);

  auto null_map = reinterpret_cast<int *>(record_data + table_meta_.field(table_meta_.null_field_offset())->offset());

  for (int i = 0; i < value_num && OB_SUCC(rc); i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value     &value = values[i];

    // TODO: optimize this
    if (value.attr_type() == AttrType::NULLS) {
      ASSERT(value_num <= 32, "can't support more than 32 fields");
      null_map[0] |= (1 << i);
      if (field->type() == AttrType::TEXTS) {
        auto bp  = reinterpret_cast<int *>(record_data + field->offset());
        int  len = field->len() / static_cast<int>(sizeof(int));
        for (int j = 0; j < len; j++) {
          bp[j] = BP_INVALID_PAGE_NUM;
        }
        bp[len - 1] = 0;
      } else if (field->type() == AttrType::HIGH_DIMS) {
        auto bp  = reinterpret_cast<int *>(record_data + field->offset());
        int  len = field->len() / static_cast<int>(sizeof(int));
        for (int j = 0; j < len; j++) {
          bp[j] = BP_INVALID_PAGE_NUM;
        }
      }
    } else {
      if (field->type() != value.attr_type()) {
        int         len = value.length();
        std::string tmp;
        switch (field->type()) {
          case AttrType::HIGH_DIMS: {
            if (value.attr_type() != AttrType::VECTORS && value.attr_type() != AttrType::CHARS) {
              LOG_INFO("field type: %d, value type: %d", field->type(), value.attr_type());
              return RC::INVALID_ARGUMENT;
            }
            Value        cast_value;
            const Value *real_value = &value;
            if (value.attr_type() == AttrType::CHARS) {
              rc = Value::cast_to(value, AttrType::VECTORS, cast_value);
              if (OB_FAIL(rc)) {
                LOG_WARN("failed to cast value.field name:%s",field->name().c_str());
              }
              real_value = &cast_value;
            }
            if (real_value->length() != field->real_len()) {
              LOG_INFO("value dim: %d, field dim: %d", real_value->length(), field->real_len());
              return RC::INVALID_ARGUMENT;
            }
            int pages = field->len() / static_cast<int>(sizeof(int));
            len       = real_value->length() * sizeof(float);
            LOG_INFO("field len: %d, value len: %d field real_len", field->len(), len, field->real_len());
            auto bp = std::launder(reinterpret_cast<int *>(record_data + field->offset()));
            for (int j = 0; j < pages; j++) {
              Frame *frame = nullptr;
              temp_buffer_pool_->allocate_page(&frame);
              if (frame == nullptr) {
                LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                            table_meta_.name(), field->name().c_str());
                rc = RC::INTERNAL;
                break;
              }
              bp[j]      = frame->page_num();
              Page &page = frame->page();
              memcpy(page.data,
                  real_value->data() + j * BP_PAGE_DATA_SIZE,
                  min(len - j * BP_PAGE_DATA_SIZE, BP_PAGE_DATA_SIZE));
              frame->mark_dirty();
              frame->unpin();
            }
          } break;
          case AttrType::TEXTS: {
            const char *v_data = value.data();
            if (value.attr_type() != AttrType::CHARS) {
              LOG_INFO("field type: %d, value type: %d", field->type(), value.attr_type());
              return RC::INVALID_ARGUMENT;
            }

            if (len > 65535) {
              LOG_INFO("field len: %d, value len: %d", field->len(), len);
              return RC::INVALID_ARGUMENT;
            }

            int pages     = (len + BP_PAGE_DATA_SIZE - 1) / BP_PAGE_DATA_SIZE;
            int max_pages = field->len() / static_cast<int>(sizeof(int));
            if (pages >= max_pages) {
              LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                                table_meta_.name(), field->name().c_str());
              rc = RC::INTERNAL;
              break;
            }
            auto bp = std::launder(reinterpret_cast<int *>(record_data + field->offset()));
            for (int j = 0; j < pages; j++) {
              Frame *frame = nullptr;
              temp_buffer_pool_->allocate_page(&frame);
              if (frame == nullptr) {
                LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                            table_meta_.name(), field->name().c_str());
                rc = RC::INTERNAL;
                break;
              }
              bp[j]      = frame->page_num();
              Page &page = frame->page();
              memcpy(page.data, v_data + j * BP_PAGE_DATA_SIZE, min(len - j * BP_PAGE_DATA_SIZE, BP_PAGE_DATA_SIZE));
              frame->mark_dirty();
              frame->unpin();
            }
            for (int j = pages; j < max_pages; j++) {
              bp[j] = BP_INVALID_PAGE_NUM;
            }
            bp[max_pages - 1] = len;
          } break;
          default: {
            Value real_value;
            rc = Value::cast_to(value, field->type(), real_value);
            if (real_value.attr_type() == AttrType::VECTORS &&
                (real_value.length() * sizeof(float)) != static_cast<size_t>(field->len())) {
              LOG_INFO("field len: %d, value len: %d", field->len(), real_value.length());
              return RC::INVALID_ARGUMENT;
            }

            if (OB_FAIL(rc)) {
              LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name().c_str(), value.to_string().c_str());
              break;
            }
            rc = set_value_to_record(record_data, real_value, field);
          }
        }
      } else {
        rc = set_value_to_record(record_data, value, field);
      }
    }
  }

  if (OB_FAIL(rc)) {
    LOG_WARN("failed to make record. table name:%s", table_meta_.name());
    free(record_data);
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::set_value_to_record(char *record_data, const Value &value, const FieldMeta *field)
{
  size_t       copy_len = field->len();
  const size_t data_len = value.length();
  if (field->type() == AttrType::CHARS) {
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
  if (field->type() == AttrType::VECTORS) {
    copy_len = data_len * sizeof(float);
  }
  memcpy(record_data + field->offset(), value.data(), copy_len);
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  string data_file = table_data_file(base_dir, table_meta_.name());

  BufferPoolManager &bpm = db_->buffer_pool_manager();
  RC                 rc  = bpm.open_file(db_->log_handler(), data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler(table_meta_.storage_format());

  rc = record_handler_->init(*data_buffer_pool_, db_->log_handler(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, db_->log_handler(), mode, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan_chunk(this, *data_buffer_pool_, db_->log_handler(), mode);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(Trx *trx, std::vector<const FieldMeta *> &field_meta, const char *index_name, bool is_unique)
{
  if (common::is_blank(index_name) || field_meta.empty()) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name().c_str());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta new_index_meta;

  RC rc = new_index_meta.init(index_name, field_meta, is_unique, IndexType::BTREE);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s",
             name().c_str(), index_name);
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  string          index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, is_unique, index_file.c_str(), new_index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s",
             name().c_str(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name().c_str(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name().c_str(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name().c_str(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name().c_str(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name().c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name().c_str());
  return rc;
}

RC Table::delete_record(const RID &rid)
{
  RC     rc = RC::SUCCESS;
  Record record;
  rc = get_record(rid, record);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return delete_record(record);
}

RC Table::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record.data(), &record.rid());
    ASSERT(RC::SUCCESS == rc, 
           "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
           name(), index->index_meta().name(), record.rid().to_string().c_str(), strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_DUPLICATE_KEY && index->index_meta().is_unique()) {
        rc = RC::RECORD_DUPLICATE_KEY_UNIQUE;
      }
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  // TODO:FIX THIS
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name().c_str(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }

  rc = data_buffer_pool_->flush_all_pages();
  LOG_INFO("Sync table over. table=%s", name().c_str());
  if (temp_buffer_pool_ != nullptr) {
    rc = temp_buffer_pool_->flush_all_pages();
    LOG_INFO("Sync table over. table=%s", name().c_str());
  }
  return rc;
}
RC Table::update_record(Record &record, vector<const FieldMeta *> &field_meta, vector<Value> &values)
{
  RC rc = RC::SUCCESS;

  auto data = new char[table_meta_.record_size()];
  memcpy(data, record.data(), table_meta_.record_size());
  auto null_map = reinterpret_cast<int *>(data + table_meta_.field(table_meta_.null_field_offset())->offset());

  for (size_t i = 0; i < field_meta.size(); i++) {
    const FieldMeta *field = field_meta[i];
    const Value     &value = values[i];

    // TODO: optimize this
    if (value.attr_type() == AttrType::NULLS) {
      null_map[0] |= (1 << (field->field_id()));
    } else {
      if (field->type() != value.attr_type()) {
        Value real_value;
        rc = Value::cast_to(value, field->type(), real_value);
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name().c_str(), value.to_string().c_str());
        }
        rc = set_value_to_record(data, real_value, field);
      } else {
        rc = set_value_to_record(data, value, field);
      }
    }
  }

  Record new_record;
  new_record.set_data(data, table_meta_.record_size());
  new_record.set_rid(record.rid());

  if (OB_FAIL(rc)) {
    LOG_WARN("failed to update record. table name:%s", table_meta_.name());
    return rc;
  }

  RC rc2 = delete_record(record);
  if (rc2 != RC::SUCCESS) {
    LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    return rc2;
  }

  rc2 = insert_record(new_record);
  if (rc2 != RC::SUCCESS) {
    LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name().c_str(), rc2, strrc(rc2));
    return rc2;
  }

  return rc;
}
RC Table::make_record(
    const Record &record, vector<const FieldMeta *> &field_meta, vector<Value> &values, Record &new_record)
{
  RC rc = RC::SUCCESS;

  auto data = new char[table_meta_.record_size()];
  memcpy(data, record.data(), table_meta_.record_size());
  auto null_map = reinterpret_cast<int *>(data + table_meta_.field(table_meta_.null_field_offset())->offset());

  for (size_t i = 0; i < field_meta.size(); i++) {
    const FieldMeta *field = field_meta[i];
    const Value     &value = values[i];
    LOG_INFO("field name:%s, value:%s", field->name().c_str(), value.to_string().c_str());
    // TODO: optimize this
    if (value.attr_type() == AttrType::NULLS) {
      null_map[0] |= (1 << (field->field_id()));
      if (field->type() == AttrType::TEXTS) {
        auto bp  = reinterpret_cast<int *>(data + field->offset());
        int  len = field->len() / static_cast<int>(sizeof(int));
        for (int j = 0; j < len - 1; j++) {
          if (bp[j] != BP_INVALID_PAGE_NUM) {
            temp_buffer_pool_->dispose_page(bp[j]);
          }
          bp[j] = BP_INVALID_PAGE_NUM;
        }
        bp[len - 1] = 0;
      } else if (field->type() == AttrType::HIGH_DIMS) {
        auto bp  = reinterpret_cast<int *>(data + field->offset());
        int  len = field->len() / static_cast<int>(sizeof(int));
        for (int j = 0; j < len; j++) {
          if (bp[j] != BP_INVALID_PAGE_NUM) {
            temp_buffer_pool_->dispose_page(bp[j]);
          }
          bp[j] = BP_INVALID_PAGE_NUM;
        }
      }

    } else {
      if (field->type() != value.attr_type()) {
        int         len = value.length();
        std::string tmp;
        switch (field->type()) {
          case AttrType::HIGH_DIMS: {
            if (value.attr_type() != AttrType::VECTORS && value.attr_type() != AttrType::CHARS) {
              LOG_INFO("field type: %d, value type: %d", field->type(), value.attr_type());
              return RC::INVALID_ARGUMENT;
            }
            Value        cast_value;
            const Value *real_value = &value;
            if (value.attr_type() == AttrType::CHARS) {
              rc = Value::cast_to(value, AttrType::VECTORS, cast_value);
              if (OB_FAIL(rc)) {
                LOG_WARN("failed to cast value.field name:%s",field->name().c_str());
              }
              real_value = &cast_value;
            }
            if (real_value->length() != field->real_len()) {
              LOG_INFO("value dim: %d, field dim: %d", real_value->length(), field->real_len());
              return RC::INVALID_ARGUMENT;
            }
            int pages = field->len() / static_cast<int>(sizeof(int));
            len       = real_value->length() * sizeof(float);
            auto bp   = reinterpret_cast<int *>(data + field->offset());
            for (int j = 0; j < pages; j++) {
              Frame *frame = nullptr;
              temp_buffer_pool_->allocate_page(&frame);
              if (frame == nullptr) {
                LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                            table_meta_.name(), field->name().c_str());
                rc = RC::INTERNAL;
                break;
              }
              bp[j]      = frame->page_num();
              Page &page = frame->page();
              memcpy(page.data,
                  real_value->data() + j * BP_PAGE_DATA_SIZE,
                  min(len - j * BP_PAGE_DATA_SIZE, BP_PAGE_DATA_SIZE));
              frame->mark_dirty();
              frame->unpin();
            }
          } break;
          case AttrType::TEXTS: {
            const char *v_data = value.data();
            if (value.attr_type() != AttrType::CHARS) {
              LOG_INFO("field type: %d, value type: %d", field->type(), value.attr_type());
              return RC::INVALID_ARGUMENT;
            }

            if (len > 65535) {
              LOG_INFO("field len: %d, value len: %d", field->len(), len);
              return RC::INVALID_ARGUMENT;
            }

            int pages     = (len + BP_PAGE_DATA_SIZE - 1) / BP_PAGE_DATA_SIZE;
            int max_pages = field->len() / static_cast<int>(sizeof(int));
            if (pages >= max_pages) {
              LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                                table_meta_.name(), field->name().c_str());
              rc = RC::INTERNAL;
              break;
            }
            auto bp = reinterpret_cast<int *>(data + field->offset());
            for (int j = 0; j < pages; j++) {
              Frame *frame = nullptr;
              temp_buffer_pool_->allocate_page(&frame);
              if (frame == nullptr) {
                LOG_ERROR("Failed to allocate page for text field. table name:%s, field name:%s",
                            table_meta_.name(), field->name().c_str());
                rc = RC::INTERNAL;
                break;
              }
              bp[j]      = frame->page_num();
              Page &page = frame->page();
              memcpy(page.data, v_data + j * BP_PAGE_DATA_SIZE, min(len - j * BP_PAGE_DATA_SIZE, BP_PAGE_DATA_SIZE));
              frame->mark_dirty();
              frame->unpin();
            }
            for (int j = pages; j < max_pages - 1; j++) {
              if (bp[j] != BP_INVALID_PAGE_NUM) {
                temp_buffer_pool_->dispose_page(bp[j]);
              }
              bp[j] = BP_INVALID_PAGE_NUM;
            }
            bp[max_pages - 1] = len;
          } break;
          default: {
            Value real_value;
            rc = Value::cast_to(value, field->type(), real_value);
            if (real_value.attr_type() == AttrType::VECTORS &&
                (real_value.length() * sizeof(float)) != static_cast<size_t>(field->len())) {
              LOG_INFO("field type: %d, value type: %d", field->type(), value.attr_type());
              return RC::INVALID_ARGUMENT;
            }

            if (OB_FAIL(rc)) {
              LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name().c_str(), value.to_string().c_str());
              break;
            }
            rc = set_value_to_record(data, real_value, field);
          }
        }
      } else {
        rc = set_value_to_record(data, value, field);
      }
    }
  }

  new_record.set_data(data, table_meta_.record_size());
  new_record.set_rid(record.rid());

  if (OB_FAIL(rc)) {
    LOG_WARN("failed to update record. table name:%s", table_meta_.name());
    return rc;
  }
  return rc;
}

RC Table::read_from_big_page(char *data, int len, int *page_nums, int page_num) const
{
  for (int i = 0; i < page_num; i++) {
    Frame *frame;
    RC     rc = temp_buffer_pool_->get_this_page(page_nums[i], &frame);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to get page for text field. table name:%s",
                        table_meta_.name());
      return rc;
    }
    Page &page = frame->page();
    memcpy(data + i * BP_PAGE_DATA_SIZE, page.data, std::min(len - i * BP_PAGE_DATA_SIZE, BP_PAGE_DATA_SIZE));
  }
  return RC::SUCCESS;
}
RC Table::create_vector_index(Trx *trx, int lists, int probs, DistanceType type, vector<const FieldMeta *> &field_meta,
    const char *index_name, bool is_unique)
{
  if (common::is_blank(index_name) || field_meta.empty()) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name().c_str());
    return RC::INVALID_ARGUMENT;
  }
  ASSERT(static_cast<int>(field_meta.size()) == 1 + table_meta_.null_field_num(), "field_meta size should be 1");

  IndexMeta new_index_meta;

  RC rc = new_index_meta.init(index_name, field_meta, is_unique, IndexType::IVF);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s",
             name().c_str(), index_name);
    return rc;
  }

  // 创建索引相关数据
  auto   index      = new IvfflatIndex();
  string index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, is_unique, index_file.c_str(), new_index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s",
             name().c_str(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name().c_str(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name().c_str(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name().c_str(), index_name);

  rc = index->train(lists, probs, type);

  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to train index. table=%s, index=%s, rc=%d:%s",
              name().c_str(), index_name, rc, strrc(rc));
    return rc;
  }

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name().c_str(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name().c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name().c_str());
  return rc;
}

Index *Table::find_index(const string &index_name) const
{
  for (Index *index : indexes_) {
    auto meta = index->index_meta();
    if (meta.field().size() == 2) {
      if (meta.field()[1] == index_name) {
        return index;
      }
    }
  }
  return nullptr;
}
