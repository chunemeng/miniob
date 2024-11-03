#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse.h"

class LimitLogicalOperator : public LogicalOperator
{
public:
  explicit LimitLogicalOperator(size_t limit) : limit_(limit) {}

  virtual ~LimitLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::LIMIT; }

  size_t limit() const { return limit_; }

private:
  size_t limit_ = 0;
};
