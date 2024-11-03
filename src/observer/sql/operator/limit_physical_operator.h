#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class LimitPhysicalOperator : public PhysicalOperator
{
public:
  LimitPhysicalOperator();
  explicit LimitPhysicalOperator(size_t limit) : limit_(limit) {}

  virtual ~LimitPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::LIMIT; }

  RC open(Trx *trx) override
  {
    trx_ = trx;
    return children_[0]->open(trx);
  }
  RC next() override
  {
    if (limit_ == 0) {
      return RC::RECORD_EOF;
    }
    RC rc = children_[0]->next();
    if (rc == RC::RECORD_EOF) {
      return RC::RECORD_EOF;
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }
    limit_--;
    return RC::SUCCESS;
  }
  RC     close() override { return children_[0]->close(); }
  Tuple *current_tuple() override { return children_[0]->current_tuple(); }

private:
  Trx   *trx_   = nullptr;
  size_t limit_ = 0;
};
