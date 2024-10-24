#include "common/type/vector_type.h"
#include "common/value.h"
#include <iomanip>
#include <cmath>

float round(float var)
{
  float int_part;
  float frac_part = std::modf(var, &int_part);
  return int_part + std::round(frac_part * 100) / 100.0f;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  int len;
  if (right.attr_type() == AttrType::CHARS) {
    Value::cast_to(right, AttrType::VECTORS, result);
    if ((len = left.length_) != result.length_) {
      return RC::INVALID_ARGUMENT;
    }
    auto left_vec   = left.get_vector();
    auto right_vec  = result.get_vector();
    auto result_vec = result.get_vector();
    for (int i = 0; i < len; i++) {
      result_vec[i] = round(left_vec[i] + right_vec[i]);
    }

    return RC::SUCCESS;
  }

  if ((len = left.length_) != right.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto   left_vec   = left.get_vector();
  auto   right_vec  = right.get_vector();
  float *result_vec = new float[len];
  for (int i = 0; i < len; i++) {
    result_vec[i] = round(left_vec[i] + right_vec[i]);
  }
  result.set_vector(result_vec, len);

  return RC::SUCCESS;
}
RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  int len;
  if (right.attr_type() == AttrType::CHARS) {
    Value::cast_to(right, AttrType::VECTORS, result);
    if ((len = left.length_) != result.length_) {
      return RC::INVALID_ARGUMENT;
    }
    auto left_vec   = left.get_vector();
    auto right_vec  = result.get_vector();
    auto result_vec = result.get_vector();
    for (int i = 0; i < len; i++) {
      result_vec[i] = round(left_vec[i] - right_vec[i]);
    }

    return RC::SUCCESS;
  }

  if ((len = left.length_) != right.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto left_vec  = left.get_vector();
  auto right_vec = right.get_vector();

  auto result_vec = result.get_vector();

  for (int i = 0; i < len; i++) {
    result_vec[i] = round(left_vec[i] - right_vec[i]);
  }

  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  int len;
  if (right.attr_type() == AttrType::CHARS) {
    Value::cast_to(right, AttrType::VECTORS, result);
    if ((len = left.length_) != result.length_) {
      return RC::INVALID_ARGUMENT;
    }
    auto left_vec   = left.get_vector();
    auto right_vec  = result.get_vector();
    auto result_vec = result.get_vector();

    for (int i = 0; i < len; i++) {
      result_vec[i] = round(left_vec[i] * right_vec[i]);
    }

    return RC::SUCCESS;
  }

  if ((len = left.length_) != right.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto   left_vec   = left.get_vector();
  auto   right_vec  = right.get_vector();
  float *result_vec = new float[len];
  for (int i = 0; i < len; i++) {
    result_vec[i] = round(left_vec[i] * right_vec[i]);
  }
  result.set_vector(result_vec, len);

  return RC::SUCCESS;
}

int VectorType::compare(const Value &left, const Value &right) const
{
  if (right.attr_type() != AttrType::VECTORS) {
    return INT32_MAX;
  }
  if (left.length_ != right.length_) {
    return INT32_MAX;
  }
  int  len       = left.length_;
  auto left_vec  = left.get_vector();
  auto right_vec = right.get_vector();
  for (int i = 0; i < len; i++) {
    float cmp = left_vec[i] - right_vec[i];
    if (cmp > EPSILON) {
      return 1;
    }
    if (cmp < -EPSILON) {
      return -1;
    }
  }

  return 0;
}
RC VectorType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << "[";
  auto vec = val.get_vector();
  for (int i = 0; i < val.length_; i++) {
    // NOTE: THIS WILL IGNORE THE TRAILING ZEROS
    ss << vec[i];
    if (i != val.length_ - 1) {
      ss << ", ";
    }
  }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}
