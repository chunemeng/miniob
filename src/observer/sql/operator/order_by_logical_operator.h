#pragma once

#include "sql/operator/logical_operator.h"

class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(std::vector<std::unique_ptr<Expression>> &order_by_expressions)
      : order_by_expressions_(std::move(order_by_expressions)){};
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  auto &order_by_expressions() { return order_by_expressions_; }

private:
  std::vector<std::unique_ptr<Expression>> order_by_expressions_;
};
