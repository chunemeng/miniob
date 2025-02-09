#pragma once

#include "storage/index/index.h"
#include "bplus_tree.h"
#include <immintrin.h>

// WARNING: 以下代码不支持删除和任何事务以及并发操作
enum DistanceType
{
  UNKNOWN = 0,
  L2      = 1,
  IP      = 2,
  COSINE  = 3,
};

// NOTE: 存储向量的倒排索引offset page id，到datapage中查找向量
/*    THE CLUSTER PAGE
 *   | key0, page0 | key1, page1 | ... | keyn, page1n |
 *   BUCKET PAGE
 *   | common header | prev page id | next page id |
 *   | rid0 | rid1 | ... | ridn |
 *
 */
struct IvfBucketPage
{
  PageNum next_page_num;
  int     size;
  char    data[0];
};

// this store the current end page of the bucket page
struct OffsetPage
{
  PageNum array[0];
};

class DistanceCalc
{
public:
  DistanceCalc() = default;
  explicit DistanceCalc(DistanceType type)
  {
    switch (type) {
      case DistanceType::L2: calc = l2_distance; break;
      case DistanceType::IP: calc = ip_distance; break;
      case DistanceType::COSINE: calc = cosine_distance; break;
      default: calc = l2_distance; break;
    }
  }

  void init(DistanceType type)
  {
    switch (type) {
      case DistanceType::L2: calc = l2_distance; break;
      case DistanceType::IP: calc = ip_distance; break;
      case DistanceType::COSINE: calc = cosine_distance; break;
      default: calc = l2_distance; break;
    }
  }

  float operator()(const float *a, const float *b, int size) const { return calc(a, b, size); }

  static float l2_distance(const float *a, const float *b, int size)
  {
    __m256 sum_vec = _mm256_setzero_ps();
    int    i;

    // 处理 8 个 float 数据
    for (i = 0; i <= size - 8; i += 8) {
      __m256 a_vec    = _mm256_loadu_ps(&a[i]);
      __m256 b_vec    = _mm256_loadu_ps(&b[i]);
      __m256 diff_vec = _mm256_sub_ps(a_vec, b_vec);
      sum_vec         = _mm256_add_ps(sum_vec, _mm256_mul_ps(diff_vec, diff_vec));
    }

    // 将 SIMD 结果归约
    float sum[8];
    _mm256_storeu_ps(sum, sum_vec);

    // 计算总和
    float total_sum = 0.0f;
    for (int j = 0; j < 8; j++) {
      total_sum += sum[j];
    }

    // 处理剩余的元素
    for (; i < size; i++) {
      float diff = a[i] - b[i];
      total_sum += diff * diff;
    }

    return total_sum;
  }

  static float ip_distance(const float *a, const float *b, int size)
  {
    float sum = 0;
    for (int i = 0; i < size; i++) {
      sum += a[i] * b[i];
    }
    return sum;
  }

  static float cosine_distance(const float *a, const float *b, int size)
  {
    float sum   = 0;
    float a_sum = 0;
    float b_sum = 0;
    for (int i = 0; i < size; i++) {
      sum += a[i] * b[i];
      a_sum += a[i] * a[i];
      b_sum += b[i] * b[i];
    }
    return (sum * sum) / (a_sum * b_sum);
  }

  static int compare_float(float a, float b)
  {
    float cmp = a - b;
    if (cmp > EPSILON) {
      return 1;
    }
    if (cmp < -EPSILON) {
      return -1;
    }
    return 0;
  }

  static int compare(const float *a, const float *b, int size)
  {
    for (int i = 0; i < size; i++) {
      int result = compare_float(a[i], b[i]);
      if (result != 0) {
        return result;
      }
    }
    return 0;
  }

private:
  float (*calc)(const float *a, const float *b, int size) = nullptr;
};

struct DataFileHandler
{

  DataFileHandler() = default;
  ~DataFileHandler() { close(); };

  /**
   * @brief 插入一个新的记录到指定文件中，并返回该记录的标识符
   *
   * @param data        纪录内容
   * @param record_size 记录大小
   * @param rid         返回该记录的标识符
   */
  RC insert_record(const char *data, int record_size, RID *rid);

  RC get_record(const RID &rid, Record &record);

  RC visit_record(const RID &rid, function<bool(Record &)> updater);
  /**
   * @brief 初始化
   *
   * @param buffer_pool 当前操作的是哪个文件
   */
  RC init(DiskBufferPool &buffer_pool, LogHandler &log_handler);

  RC init_free_page();

  /**
   * @brief 关闭，做一些资源清理的工作
   */
  void close();

  PageNum         current_page_num_ = 0;
  int             dim_;
  StorageFormat   storage_format_;
  LogHandler     *log_handler_      = nullptr;  /// 日志处理器
  DiskBufferPool *disk_buffer_pool_ = nullptr;  /// 磁盘缓冲池
};

class DataFileScanner
{
public:
  DataFileScanner() = default;
  ~DataFileScanner();

  /**
   * @brief 打开一个文件扫描。
   * @param mode             当前是否只读操作。访问数据时，需要对页面加锁。比如
   *                         删除时也需要遍历找到数据，然后删除，这时就需要加写锁
   * @param condition_filter 做一些初步过滤操作
   */
  RC open_scan(DiskBufferPool &buffer_pool, LogHandler &log_handler, ReadWriteMode mode);

  /**
   * @brief 关闭一个文件扫描，释放相应的资源
   */
  RC close_scan();

  /**
   * @brief 获取下一条记录
   *
   * @param record 返回的下一条记录
   */
  RC next(Record &record);

  RC update_current(const Record &record);

private:
  /**
   * @brief 获取该文件中的下一条记录
   */
  RC fetch_next_record();

  /**
   * @brief 获取一个页面内的下一条记录
   */
  RC fetch_next_record_in_page();

private:
  DiskBufferPool *disk_buffer_pool_ = nullptr;  ///< 当前访问的文件
  LogHandler     *log_handler_      = nullptr;
  ReadWriteMode   rw_mode_ = ReadWriteMode::READ_WRITE;  ///< 遍历出来的数据，是否可能对它做修改

  BufferPoolIterator bp_iterator_;                    ///< 遍历buffer pool的所有页面
  RecordPageHandler *record_page_handler_ = nullptr;  ///< 处理文件某页面的记录
  RecordPageIterator record_page_iterator_;           ///< 遍历某个页面上的所有record
  Record             next_record_;                    ///< 获取的记录放在这里缓存起来
};

struct IvfFileHandler
{

  IvfFileHandler() = default;
  ~IvfFileHandler() { close(); };

  RC insert_cluster_record(std::vector<std::vector<float>> &data);

  /**
   * @brief 插入一个新的记录到指定文件中，并返回该记录的标识符
   *
   * @param data        纪录内容
   * @param record_size 记录大小
   * @param rid         返回该记录的标识符
   */
  RC insert_record_into_bucket(const Record &record, int offset);

  std::vector<RID> ann_search(const vector<float> &base_vector, DistanceType type, size_t limit);
  std::vector<RID> ann_search_p(const float *base_vector, DistanceType type, size_t limit);

  std::vector<Record> ann_search_cached(const float *base_vector, DistanceType type, size_t limit);
  /**
   * @brief 初始化
   *
   * @param buffer_pool 当前操作的是哪个文件
   */
  RC init(DiskBufferPool &buffer_pool, LogHandler &log_handler);

  RC init_vec_info(int dim, int lists, int probes, DistanceType distance_type, DataFileHandler &data_file_handler);

  /**
   * @brief 关闭，做一些资源清理的工作
   */
  void close()
  {
    log_handler_ = nullptr;
    if (disk_buffer_pool_ != nullptr) {
      disk_buffer_pool_->close_file();
    }

    for (auto &cluster : cluster_cache_) {
      delete[] cluster;
    }
  }

  int                  list_;
  int                  dim_;
  int                  probes_;
  PageNum              offset_page_num_         = 0;
  int                  cluster_record_per_page_ = 0;
  int                  data_offset_             = 0;
  int                  record_size_             = 0;
  int                  bucket_size_             = 0;
  bool                 is_cached_all_           = false;
  DistanceCalc         dis_calc_;
  StorageFormat        storage_format_;
  std::vector<float *> cluster_cache_;
  LogHandler          *log_handler_       = nullptr;  /// 日志处理器
  DiskBufferPool      *disk_buffer_pool_  = nullptr;  /// 磁盘缓冲池
  DataFileHandler     *data_file_handler_ = nullptr;
};

// NOTE: 数据页，用于存储所有的数据
struct DataPage
{
  PageNum next_page_num;
  int     size;
  char    data[0];
};

struct IvfIndexFileHeader : public IndexFileHeader
{
  IvfIndexFileHeader() { root_page = BP_INVALID_PAGE_NUM; }

  int  lists_         = 1;
  int  probes_        = 1;
  int  dim_           = 1;
  int  distance_type_ = 0;  ///< distance type
  bool whole_cached_  = false;
};

#define FIRST_INDEX_PAGE 1

class IvfflatIndexHandler
{
public:
  /**
   * @brief 创建一个B+树
   * @param log_handler 记录日志
   * @param bpm 缓冲池管理器
   * @param file_name 文件名
   * @param attr_type 属性类型
   * @param attr_length 属性长度
   * @param internal_max_size 内部节点最大大小
   * @param leaf_max_size 叶子节点最大大小
   */
  RC create(
      LogHandler &log_handler, BufferPoolManager &bpm, const char *file_name, AttrType attr_type, int attr_length);
  RC create(LogHandler &log_handler, DiskBufferPool &buffer_pool, AttrType attr_type, int attr_length);

  RC create(LogHandler &log_handler, bool is_unqiue, BufferPoolManager &bpm, const char *file_name,
      std::vector<const FieldMeta *> &field_metas, int null_field_num);

  RC create(LogHandler &log_handler, bool is_unqiue, DiskBufferPool &bpm, DiskBufferPool &ivf,
      std::vector<const FieldMeta *> &field_metas, int null_field_num);

  std::vector<RID> ann_search_p(const float *base_vector, DistanceType type, size_t limit);

  std::vector<RID> ann_search(const vector<float> &base_vector, DistanceType type, size_t limit);

  std::vector<Record> ann_search_cached(const float *base_vector, DistanceType type, size_t limit);

  RC open(LogHandler &log_handler, BufferPoolManager &bpm, const char *file_name);
  RC open(LogHandler &log_handler, DiskBufferPool &buffer_pool, DiskBufferPool &ivf);

  void set_cached() { whole_cached_ = true; }

  /**
   * 关闭句柄indexHandle对应的索引文件
   */
  RC close();

  /**
   * @brief 此函数向IndexHandle对应的索引中插入一个索引项。
   * @details 参数user_key指向要插入的属性值，参数rid标识该索引项对应的元组，
   * 即向索引中插入一个值为（user_key，rid）的键值对
   * @note 这里假设user_key的内存大小与attr_length 一致
   */
  RC insert_entry(const char *user_key, const RID *rid);

  RC sync();

public:
  const IvfIndexFileHeader &file_header() const { return file_header_; }
  DiskBufferPool           &buffer_pool() const { return *disk_buffer_pool_; }
  LogHandler               &log_handler() const { return *log_handler_; }

public:
  RC train(int lists, int probes, DistanceType distance_type);

private:
  common::MemPoolItem::item_unique_ptr make_key(const char *user_key, const RID &rid);

private:
  LogHandler        *log_handler_      = nullptr;  /// 日志处理器
  DiskBufferPool    *disk_buffer_pool_ = nullptr;  /// 磁盘缓冲池
  DiskBufferPool    *ivf_buffer_pool_  = nullptr;  /// 磁盘缓冲池
  bool               header_dirty_     = false;    /// 是否需要更新头页面
  IvfIndexFileHeader file_header_;
  DataFileHandler    data_file_handler_;
  IvfFileHandler     ivf_file_handler_;
  bool               whole_cached_ = false;

  DistanceCalc                    dis_calc_;
  unique_ptr<common::MemPoolItem> mem_pool_item_;
};

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  IvfflatIndex()                   = default;
  virtual ~IvfflatIndex() noexcept = default;

  RC train(int lists, int probes, DistanceType distance_type);

  int get_dim() const { return index_handler_.file_header().dim_; }

  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) override;
  RC create(Table *table, bool is_unqiue, const char *file_name, const IndexMeta &index_meta,
      std::vector<const FieldMeta *> &field_meta) override;

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta,
      std::vector<const FieldMeta *> &field_meta) override;

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) override;

  RC drop() override;

  vector<RID>    ann_search(const vector<float> &base_vector, DistanceType type, size_t limit);
  vector<RID>    ann_search_p(const float *base_vector, DistanceType type, size_t limit);
  vector<Record> ann_search_cached(const float *base_vector, DistanceType type, size_t limit);

  RC close();

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override;

  RC insert_entry(const char *record, const RID *rid) override { return index_handler_.insert_entry(record, rid); };
  RC delete_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; };

  RC sync() override { return index_handler_.sync(); };

  bool is_cached() const { return index_handler_.file_header().whole_cached_; }

private:
  bool                inited_ = false;
  Table              *table_  = nullptr;
  IvfflatIndexHandler index_handler_;
};
