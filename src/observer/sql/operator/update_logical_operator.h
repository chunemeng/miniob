#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const FieldMeta *field_meta, Expression* expression);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType          type() const override { return LogicalOperatorType::UPDATE; }
  Table                       *table() const { return table_; }
  const FieldMeta             *field_meta() const { return field_meta_; }
  std::unique_ptr<Expression> &values() { return value_; }

private:
  Table *table_ = nullptr;

  std::unique_ptr<Expression> value_;

  const FieldMeta *field_meta_;
};
