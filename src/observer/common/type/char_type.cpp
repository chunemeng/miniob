/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"
#include "common/time/datetime.h"

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC parser_str_to_float(const char *input, int len, std::vector<float> &array)
{
  std::string_view content(input + 1, len - 2);

  std::string buffer;
  size_t      start = 0;
  size_t      end;
  while ((end = content.find(',', start)) != std::string_view::npos) {
    char *endptr;
    auto  item  = content.substr(start, end - start);
    float value = strtof(item.data(), &endptr);
    if (endptr == item.data()) {
      // Conversion failed
      return RC::INVALID_ARGUMENT;
    }
    array.emplace_back(value);

    start = end + 1;
  }

  if (start < content.size()) {
    char *endptr;
    auto  item  = content.substr(start, end - start);
    float value = strtof(item.data(), &endptr);
    if (endptr == item.data()) {
      // Conversion failed
      return RC::INVALID_ARGUMENT;
    }
    array.push_back(value);
  }
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::FLOATS: {
      result.attr_type_ = AttrType::FLOATS;

      result.set_float(val.get_float());
    } break;
    case AttrType::INTS: {
      result.attr_type_ = AttrType::INTS;

      result.set_int(val.get_int());
    } break;
    case AttrType::DATES:
      int y, m, d;
      if (sscanf(val.value_.pointer_value_, "%d-%d-%d", &y, &m, &d) != 3) {
        LOG_WARN("invalid date format", val.value_.pointer_value_);
        return RC::INVALID_ARGUMENT;
      }
      if (!common::check_date(y, m, d)) {
        LOG_WARN("invalid date value", val.value_.pointer_value_);
        return RC::INVALID_ARGUMENT;
      }
      result.set_date(y, m, d);
      break;
    case AttrType::VECTORS: {
      result.attr_type_ = AttrType::VECTORS;
      std::vector<float> vec;
      RC                 rc = parser_str_to_float(val.value_.pointer_value_, val.length_, vec);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_vector(vec);
      break;
    }
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  switch (type) {
    case AttrType::CHARS: return 0;
    case AttrType::INTS:
    case AttrType::FLOATS:
    case AttrType::DATES: return 1;
    case AttrType::VECTORS: return 2;
    default: return INT32_MAX;
  }
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}
RC CharType::add(const Value &left, const Value &right, Value &result) const
{
  switch (right.attr_type_) {
    case AttrType::INTS: {
      result.set_int(left.get_int() + right.get_int());
    } break;

    case AttrType::FLOATS: {
      result.set_float(left.get_float() + right.get_float());
    } break;
    case AttrType::VECTORS: {
      return Value::add(right, left, result);
    }
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

RC CharType::subtract(const Value &left, const Value &right, Value &result) const
{
  switch (right.attr_type_) {
    case AttrType::INTS: {
      result.set_int(left.get_int() - right.get_int());
    } break;

    case AttrType::FLOATS: {
      result.set_float(left.get_float() - right.get_float());
    } break;
    case AttrType::VECTORS: {
      return Value::subtract(right, left, result);
    }
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}
RC CharType::multiply(const Value &left, const Value &right, Value &result) const
{
  switch (right.attr_type_) {
    case AttrType::INTS: {
      result.set_int(left.get_int() * right.get_int());
    } break;

    case AttrType::FLOATS: {
      result.set_float(left.get_float() * right.get_float());
    } break;
    case AttrType::VECTORS: {
      return Value::multiply(right, left, result);
    }
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}
RC CharType::divide(const Value &left, const Value &right, Value &result) const
{
  switch (right.attr_type_) {
    case AttrType::FLOATS: {
      Value temp;
      temp.set_float(left.get_float());
      return Value::divide(temp, right, result);
    } break;
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}
