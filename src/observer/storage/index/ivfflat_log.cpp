//#include "ivfflat_log.h"
//
//
/////////////////////////////////////////////////////////////////////////////////
//// class IvfflatLogger
//IvfflatLogger::IvfflatLogger(LogHandler &log_handler, int32_t buffer_pool_id)
//    : log_handler_(log_handler), buffer_pool_id_(buffer_pool_id)
//{}
//
//IvfflatLogger::~IvfflatLogger() { commit(); }
//
//RC IvfflatLogger::init_header_page(Frame *frame, const IndexFileHeader &header)
//{
//  return append_log_entry(make_unique<InitHeaderPageLogEntryHandler>(frame, header));
//}
//
//RC IvfflatLogger::update_root_page(Frame *frame, PageNum root_page_num, PageNum old_page_num)
//{
//  return append_log_entry(make_unique<UpdateRootPageLogEntryHandler>(frame, root_page_num, old_page_num));
//}
//
//RC IvfflatLogger::leaf_init_empty(IndexNodeHandler &node_handler)
//{
//  return append_log_entry(make_unique<LeafInitEmptyLogEntryHandler>(node_handler.frame()));
//}
//
//RC IvfflatLogger::node_insert_items(IndexNodeHandler &node_handler, int index, span<const char> items, int item_num)
//{
//  return append_log_entry(make_unique<NormalOperationLogEntryHandler>(
//      node_handler.frame(), LogOperation::Type::NODE_INSERT, index, items, item_num));
//}
//
//RC IvfflatLogger::node_remove_items(IndexNodeHandler &node_handler, int index, span<const char> items, int item_num)
//{
//  return append_log_entry(make_unique<NormalOperationLogEntryHandler>(
//      node_handler.frame(), LogOperation::Type::NODE_REMOVE, index, items, item_num));
//}
//
//RC IvfflatLogger::leaf_set_next_page(IndexNodeHandler &node_handler, PageNum page_num, PageNum old_page_num)
//{
//  return append_log_entry(make_unique<LeafSetNextPageLogEntryHandler>(node_handler.frame(), page_num, old_page_num));
//}
//
//RC IvfflatLogger::internal_init_empty(IndexNodeHandler &node_handler)
//{
//  return append_log_entry(make_unique<InternalInitEmptyLogEntryHandler>(node_handler.frame()));
//}
//
//RC IvfflatLogger::internal_create_new_root(
//    IndexNodeHandler &node_handler, PageNum first_page_num, span<const char> key, PageNum page_num)
//{
//  return append_log_entry(
//      make_unique<InternalCreateNewRootLogEntryHandler>(node_handler.frame(), first_page_num, key, page_num));
//}
//
//RC IvfflatLogger::internal_update_key(
//    IndexNodeHandler &node_handler, int index, span<const char> key, span<const char> old_key)
//{
//  return append_log_entry(make_unique<InternalUpdateKeyLogEntryHandler>(node_handler.frame(), index, key, old_key));
//}
//
//RC IvfflatLogger::set_parent_page(IndexNodeHandler &node_handler, PageNum page_num, PageNum old_page_num)
//{
//  return append_log_entry(make_unique<SetParentPageLogEntryHandler>(node_handler.frame(), page_num, old_page_num));
//}
//
//RC IvfflatLogger::append_log_entry(unique_ptr<bplus_tree::LogEntryHandler> entry)
//{
//  if (!need_log_) {
//    return RC::SUCCESS;
//  }
//
//  entries_.push_back(std::move(entry));
//  return RC::SUCCESS;
//}
//
//RC IvfflatLogger::commit()
//{
//  if (entries_.empty()) {
//    return RC::SUCCESS;
//  }
//
//  LSN        lsn = 0;
//  Serializer buffer;
//  buffer.write_int32(buffer_pool_id_);
//
//  for (auto &entry : entries_) {
//    entry->serialize(buffer);
//  }
//
//  Serializer::BufferType &buffer_data = buffer.data();
//
//  RC rc = log_handler_.append(lsn, LogModule::Id::BPLUS_TREE, std::move(buffer_data));
//  if (RC::SUCCESS != rc) {
//    LOG_WARN("failed to append log entry. rc=%s", strrc(rc));
//    return rc;
//  }
//
//  for (auto &entry : entries_) {
//    entry->frame()->set_lsn(lsn);
//  }
//
//  entries_.clear();
//  return RC::SUCCESS;
//}
//
//RC IvfflatLogger::rollback(BplusTreeMiniTransaction &mtr, BplusTreeHandler &tree_handler)
//{
//  need_log_ = false;
//
//  for (auto iter = entries_.rbegin(), itend = entries_.rend(); iter != itend; ++iter) {
//    auto &entry = *iter;
//    entry->rollback(mtr, tree_handler);
//  }
//
//  entries_.clear();
//  need_log_ = true;
//  return RC::SUCCESS;
//}
//
//RC IvfflatLogger::redo(BufferPoolManager &bpm, const LogEntry &entry)
//{
//  ASSERT(entry.module().id() == LogModule::Id::BPLUS_TREE, "invalid log entry: %s", entry.to_string().c_str());
//
//  Deserializer buffer(entry.data(), entry.payload_size());
//  int32_t      buffer_pool_id = -1;
//  int          ret            = buffer.read_int32(buffer_pool_id);
//  if (ret != 0) {
//    LOG_ERROR("failed to read buffer pool id. ret=%d", ret);
//    return RC::IOERR_READ;
//  }
//
//  DiskBufferPool *buffer_pool = nullptr;
//  RC              rc          = bpm.get_buffer_pool(buffer_pool_id, buffer_pool);
//  if (OB_FAIL(rc) || buffer_pool == nullptr) {
//    LOG_WARN("failed to get buffer pool. rc=%s, buffer_pool_id=%d", strrc(rc), buffer_pool_id);
//    return rc;
//  }
//
//  VacuousLogHandler log_handler;
//  BplusTreeHandler  tree_handler;
//  rc = tree_handler.open(log_handler, *buffer_pool);
//  if (OB_FAIL(rc)) {
//    LOG_WARN("failed to open bplus tree handler. rc=%s", strrc(rc));
//    return rc;
//  }
//
//  BplusTreeMiniTransaction mtr(tree_handler);
//  rc = mtr.logger().__redo(entry.lsn(), mtr, tree_handler, buffer);
//  if (OB_FAIL(rc)) {
//    LOG_WARN("failed to redo log entry. rc=%s", strrc(rc));
//    return rc;
//  }
//
//  ASSERT(mtr.logger().entries_.empty(), "entries should be empty after redo");
//  return rc;
//}
//
//RC IvfflatLogger::__redo(LSN lsn, BplusTreeMiniTransaction &mtr, BplusTreeHandler &tree_handler, Deserializer &redo_buffer)
//{
//  need_log_ = false;
//
//  DEFER(need_log_ = true);
//
//  RC rc = RC::SUCCESS;
//  vector<Frame *> frames;
//  while (redo_buffer.remain() > 0) {
//    unique_ptr<LogEntryHandler> entry;
//
//    rc = LogEntryHandler::from_buffer(tree_handler.buffer_pool(), redo_buffer, entry);
//    if (OB_FAIL(rc)) {
//      LOG_WARN("failed to deserialize log entry. rc=%s", strrc(rc));
//      break;
//    }
//    Frame *frame = entry->frame();
//    if (frame != nullptr) {
//      if (frame->lsn() >= lsn) {
//        LOG_TRACE("no need to redo. frame=%p:%s, redo lsn=%ld", frame, frame->to_string().c_str(), lsn);
//        frame->unpin();
//        continue;
//      } else {
//        frames.push_back(frame);
//      }
//    } else {
//      LOG_TRACE("frame is null, skip the redo action");
//      continue;
//    }
//
//    rc = entry->redo(mtr, tree_handler);
//    if (OB_FAIL(rc)) {
//      LOG_WARN("failed to redo log entry. rc=%s, lsn=%d, entry=%s", strrc(rc), lsn, entry->to_string().c_str());
//      break;
//    }
//
//    // 在这里能设置frame的LSN，因为一个页面可能会有多个操作
//    // frame->set_lsn(lsn);
//  }
//
//  if (OB_SUCC(rc)) {
//    for (Frame *frame : frames) {
//      frame->set_lsn(lsn);
//      frame->unpin();
//    }
//  }
//
//  return RC::SUCCESS;
//}
//
//string IvfflatLogger::log_entry_to_string(const LogEntry &entry)
//{
//  stringstream ss;
//  Deserializer buffer(entry.data(), entry.payload_size());
//  int32_t      buffer_pool_id = -1;
//  int          ret            = buffer.read_int32(buffer_pool_id);
//  if (ret != 0) {
//    LOG_ERROR("failed to read buffer pool id. ret=%d", ret);
//    return ss.str();
//  }
//
//  ss << "buffer_pool_id:" << buffer_pool_id;
//  while (buffer.remain() > 0) {
//    unique_ptr<LogEntryHandler> entry;
//
//    RC rc = LogEntryHandler::from_buffer(buffer, entry);
//    if (RC::SUCCESS != rc) {
//      LOG_WARN("failed to deserialize log entry. rc=%s", strrc(rc));
//      return ss.str();
//    }
//
//    ss << ",";
//    ss << entry->to_string();
//  }
//  return ss.str();
//}
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// class IvfflatMiniTransaction
//
//IvfflatMiniTransaction::~IvfflatMiniTransaction()
//{
//  if (nullptr == operation_result_) {
//    return;
//  }
//
//  if (OB_SUCC(*operation_result_)) {
//    commit();
//  } else {
//    rollback();
//  }
//}
//
//RC IvfflatMiniTransaction::commit() { return logger_.commit(); }
//
//RC IvfflatMiniTransaction::rollback() { return logger_.rollback(*this, tree_handler_); }
