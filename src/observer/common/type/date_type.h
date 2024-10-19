#pragma once

#include "common/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 固定长度的字符串类型
 * @ingroup DataType
 */
class DateType : public DataType
{
public:
  DateType() : DataType(AttrType::DATES) {}

  virtual ~DateType() = default;

  int compare(const Value &left, const Value &right) const override;

  int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;
};