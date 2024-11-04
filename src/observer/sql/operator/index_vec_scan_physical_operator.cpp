
#include "sql/operator/index_vec_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

RC IndexVecScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }

  IvfflatIndex *index = dynamic_cast<IvfflatIndex *>(index_);

  if (nullptr == index) {
    return RC::INTERNAL;
  }

  std::vector<float> value;
  Value              v;
  Value::cast_to(value_, AttrType::VECTORS, v);

  rids_ = index->ann_search_p(reinterpret_cast<const float *>(v.data()), type_, limit_);

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    return RC::INTERNAL;
  }

  tuple_.set_schema(table_, table_->table_meta().field_metas());

  trx_ = trx;
  return RC::SUCCESS;
}

RC IndexVecScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (n >= rids_.size()) {
    return RC::RECORD_EOF;
  }

  rc = record_handler_->get_record(rids_[n], current_record_);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to get record. rid=%s, rc=%s", rids_[n].to_string().c_str(), strrc(rc));
    return rc;
  }

  tuple_.set_record(&current_record_);

  n++;
  return rc;
}

RC IndexVecScanPhysicalOperator::close() { return RC::SUCCESS; }

Tuple *IndexVecScanPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

void IndexVecScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC IndexVecScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}

std::string IndexVecScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
IndexVecScanPhysicalOperator::IndexVecScanPhysicalOperator(
    Table *table, Index *index, ReadWriteMode mode, const Value *value, DistanceType type, size_t limit)
    : table_(table), index_(index), mode_(mode), limit_(limit), type_(type)
{
  if (nullptr != value) {
    value_ = *value;
  }
}
