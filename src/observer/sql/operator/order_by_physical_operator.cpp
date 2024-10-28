#include "order_by_physical_operator.h"

RC OrderByPhysicalOperator::open(Trx *trx)
{
  trx_        = trx;
  RC    rc    = RC::SUCCESS;
  auto &child = children_[0];
  child->open(trx);

  std::vector<int> cell_indexs;
  cell_indexs.resize(expressions.size());

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    if (index_ != -1) {
      for (size_t i = 0; i < expressions.size(); i++) {
        auto expr = dynamic_cast<OrderByExpr *>(expressions[i].get());
        rc        = tuple->find_cell_index(TupleCellSpec(expr->table_name(), expr->field_name()), cell_indexs[i]);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to find cell index: %s", strrc(rc));
          return rc;
        }
      }
      std::vector<TupleCellSpec> cell;
      cell.resize(tuple->cell_num());
      for (int i = 0; i < tuple->cell_num(); i++) {
        rc = tuple->spec_at(i, cell[i]);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get cell spec: %s", strrc(rc));
          return rc;
        }
      }
      tuple_.set_names(std::move(cell));
      index_ = -1;
    }

    std::vector<Value> values;
    values.resize(tuple->cell_num());
    for (int i = 0; i < tuple->cell_num(); i++) {
      rc = tuple->cell_at(i, values[i]);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get cell value: %s", strrc(rc));
        return rc;
      }
    }
    tuple_in_value.emplace_back(std::move(values));
  }

  if (rc != RC::RECORD_EOF) {
    return rc;
  }

  child->close();

  if (expressions.empty()) {
    return RC::SUCCESS;
  }

  std::sort(
      tuple_in_value.begin(), tuple_in_value.end(), [&](const std::vector<Value> &a, const std::vector<Value> &b) {
        int   result = 0;
        Value desc;
        for (size_t i = 0; i < cell_indexs.size(); i++) {
          const Value &left  = a[cell_indexs[i]];
          const Value &right = b[cell_indexs[i]];
          result             = left.compare(right);
          if (left.attr_type() == AttrType::NULLS) {
            if (right.attr_type() == AttrType::NULLS) {
              continue;
            }
            return true;
          }
          if (right.attr_type() == AttrType::NULLS) {
            return false;
          }

          if (result != 0) {
            expressions[i]->try_get_value(desc);
            if (desc.get_boolean()) {
              return result > 0;
            }
            return result < 0;
          }
        }
        return false;
      });

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
  if (static_cast<size_t>(++index_) >= tuple_in_value.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() { return RC::RECORD_EOF; }

Tuple *OrderByPhysicalOperator::current_tuple()
{
  tuple_.set_cells(std::move(tuple_in_value[index_]));
  return &tuple_;
}
