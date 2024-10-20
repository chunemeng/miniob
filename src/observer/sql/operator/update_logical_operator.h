#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const FieldMeta *field_meta, Value *values, int value_amount);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  const FieldMeta    *field_meta() const { return field_meta_; }
  Value              *values() const { return values_; }
  int                 value_amount() const { return value_amount_; }

private:
  Table *table_        = nullptr;
  Value *values_       = nullptr;
  int    value_amount_ = 0;

  const FieldMeta *field_meta_;
};
