#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator();
  explicit OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>> &condition) : expressions(std::move(condition)) {}

  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::NESTED_LOOP_JOIN; }

  RC     open(Trx *trx) override;
  RC     next() override;
  RC     close() override;
  Tuple *current_tuple() override;

private:
  Trx                 *trx_ = nullptr;
  std::vector<Tuple *> tuples_;
  int                  index_ = 0;

  std::vector<std::unique_ptr<Expression>> expressions;
};
