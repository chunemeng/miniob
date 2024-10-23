#pragma once

#include "common/type/data_type.h"

/**
 * @brief NULL类型
 * @ingroup DataType
 */
class NULLType : public DataType
{
public:
  NULLType() : DataType(AttrType::NULLS) {}
  virtual ~NULLType() {}

  int cast_cost(AttrType type) override { return INT32_MAX; }

  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;
  RC divide(const Value &left, const Value &right, Value &result) const override;
  int compare(const Value &left, const Value &right) const override;

  RC to_string(const Value &val, string &result) const override;
};