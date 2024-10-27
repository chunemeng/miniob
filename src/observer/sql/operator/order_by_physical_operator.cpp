#include "order_by_physical_operator.h"

RC OrderByPhysicalOperator::open(Trx *trx)
{
  trx_        = trx;
  RC    rc    = RC::SUCCESS;
  auto &child = children_[0];
  child->open(trx);
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    tuples_.emplace_back(std::move(tuple));
  }

  if (rc != RC::RECORD_EOF) {
    return rc;
  }

  child->close();

  if (expressions.empty()) {
    return RC::SUCCESS;
  }
  std::vector<int> cell_indexs;

  for (auto &node : expressions) {
    auto expr  = dynamic_cast<OrderByExpr *>(node.get());
    int  index = 0;
    rc         = tuples_[0]->find_cell_index(TupleCellSpec(expr->table_name(), expr->field_name()), index);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to find cell index: %s", strrc(rc));
      return rc;
    }
  }
  try {
    std::sort(tuples_.begin(), tuples_.end(), [&](Tuple *a, Tuple *b) {
      int   result = 0;
      Value left, right;
      Value desc;
      for (size_t i = 0; i < cell_indexs.size(); i++) {
        rc = a->cell_at(cell_indexs[i], left);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get cell value: %s", strrc(rc));
          throw std::runtime_error(strrc(rc));
        }
        rc = b->cell_at(cell_indexs[i], right);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get cell value: %s", strrc(rc));
          throw std::runtime_error(strrc(rc));
        }
        result = left.compare(right);

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
  } catch (const std::exception &e) {
    LOG_WARN("failed to sort tuples: %s", e.what());
    return RC::INTERNAL;
  }

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
  if (++index_ >= tuples_.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() { return RC::RECORD_EOF; }

Tuple *OrderByPhysicalOperator::current_tuple() { return tuples_[index_]; }
