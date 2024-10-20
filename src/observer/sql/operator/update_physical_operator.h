#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/types.h"

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const FieldMeta *field_meta, Value *values, int value_amount)
      : table_(table), field_meta_(field_meta), values_(values), value_amount(value_amount)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::DELETE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table           *table_      = nullptr;
  const FieldMeta *field_meta_ = nullptr;
  Trx             *trx_        = nullptr;
  Value           *values_     = nullptr;

  int                 value_amount;
  std::vector<Record> records_;
};
