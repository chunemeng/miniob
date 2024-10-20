#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const FieldMeta *field_meta, Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount), field_meta_(field_meta){};