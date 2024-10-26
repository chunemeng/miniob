#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/types.h"

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(
      Table *table, std::vector<const FieldMeta *> &field_meta, std::vector<std::unique_ptr<Expression>> &expression)
      : table_(table), value_(std::move(expression)), field_meta_(field_meta)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::DELETE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table *table_ = nullptr;
  Trx   *trx_   = nullptr;

  std::vector<std::unique_ptr<Expression>> value_;

  std::vector<const FieldMeta *> field_meta_;
  std::vector<Record>            records_;
};
