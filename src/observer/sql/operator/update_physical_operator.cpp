#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open update operator");
  if (children_.empty()) {
    LOG_INFO("no child operator");
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  // Collect records before updating
  while (OB_SUCC(rc = child->next())) {
    LOG_INFO("get next record %d", child->type());
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();

  rc = RC::SUCCESS;

  std::vector<Value> values(field_meta_.size());

  for (size_t i = 0; i < field_meta_.size(); ++i) {
    rc = value_[i]->try_get_value(values[i]);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to evaluate expression: %s", strrc(rc));
      return rc;
    }
  }

  for (Record &record : records_) {
    Record new_record;
    rc = table_->make_record(record, field_meta_, values, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
    rc = trx_->update_record(table_, record, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }

  return rc;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
