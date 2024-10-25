#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const FieldMeta *field_meta, Expression *value)
    : table_(table), value_(value){};