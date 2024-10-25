#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include <iomanip>

int DateType::compare(const Value &left, const Value &right) const
{
  return common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
}

int DateType::cast_cost(AttrType type)
{
  if (type == AttrType::DATES) {
    return 0;
  }
  return INT32_MAX;
}

RC DateType::to_string(const Value &val, string &result) const
{
  stringstream ss;

  auto date_int = val.value_.int_value_;
  auto day      = date_int % 100;
  auto month    = (date_int / 100) % 100;
  auto year     = date_int / 10000;

  ss << std::setw(4) << std::setfill('0') << year << "-"
     << std::setw(2) << std::setfill('0') << month << "-"
     << std::setw(2) << std::setfill('0') << day;
  result = ss.str();
  return RC::SUCCESS;
}