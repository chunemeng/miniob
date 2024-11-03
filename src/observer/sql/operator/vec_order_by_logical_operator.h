#pragma once

#include "sql/operator/logical_operator.h"

class VecOrderByLogicalOperator : public LogicalOperator
{
public:
  VecOrderByLogicalOperator(std::vector<std::unique_ptr<Expression>> &order_by_expressions, DistanceType distance_type)
      : order_by_expressions_(std::move(order_by_expressions)), distance_type_(distance_type){};
  virtual ~VecOrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::VEC_ORDER_BY; }

  auto        &order_by_expressions() { return order_by_expressions_; }
  DistanceType distance_type() const { return distance_type_; }

private:
  std::vector<std::unique_ptr<Expression>> order_by_expressions_;
  DistanceType                             distance_type_;
};
