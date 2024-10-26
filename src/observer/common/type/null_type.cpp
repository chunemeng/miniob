#include "common/type/null_type.h"
#include "common/value.h"

RC NULLType::to_string(const Value &val, string &result) const
{
  result = "NULL";
  return RC::SUCCESS;
}
RC NULLType::add(const Value &left, const Value &right, Value &result) const
{
  result.set_null();
  return RC::SUCCESS;
}
RC NULLType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_null();
  return RC::SUCCESS;
}
RC NULLType::multiply(const Value &left, const Value &right, Value &result) const
{
  result.set_null();
  return RC::SUCCESS;
}
RC NULLType::divide(const Value &left, const Value &right, Value &result) const
{
  result.set_null();
  return RC::SUCCESS;
}
int NULLType::compare(const Value &left, const Value &right) const {
  if (right.attr_type() == AttrType::NULLS) {
    return 0;
  }
  return left.attr_type() == AttrType::NULLS ? 1 : -1;
}
