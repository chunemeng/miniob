#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(
      Table *table, std::vector<const FieldMeta *> &field_meta, std::vector<std::unique_ptr<Expression>> &expression)
      : table_(table), value_(std::move(expression)), field_meta_(std::move(field_meta))
  {}
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType                       type() const override { return LogicalOperatorType::UPDATE; }
  Table                                    *table() const { return table_; }
  std::vector<const FieldMeta *>           &field_meta() { return field_meta_; }
  std::vector<std::unique_ptr<Expression>> &values() { return value_; }

private:
  Table *table_ = nullptr;

  std::vector<std::unique_ptr<Expression>> value_;

  std::vector<const FieldMeta *> field_meta_;
};
