#include "common/type/vector_type.h"
#include "common/value.h"
#include <cmath>
#include <iomanip>
#include <cmath>

float round_f(float var)
{
  float int_part;
  float frac_part = std::modf(var, &int_part);
  return int_part + std::round(frac_part * 100) / 100.0f;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }
  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto   left_vec   = l.get_vector();
  auto   right_vec  = r.get_vector();
  float *result_vec = new float[len];
  for (int i = 0; i < len; i++) {
    result_vec[i] = round_f(left_vec[i] + right_vec[i]);
  }
  result.set_vector(result_vec, len);

  return RC::SUCCESS;
}
RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }
  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto left_vec   = l.get_vector();
  auto right_vec  = r.get_vector();
  auto result_vec = new float[len];

  for (int i = 0; i < len; i++) {
    result_vec[i] = round_f(left_vec[i] - right_vec[i]);
  }
  result.set_vector(result_vec, len);

  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto   left_vec   = l.get_vector();
  auto   right_vec  = r.get_vector();
  float *result_vec = new float[len];
  for (int i = 0; i < len; i++) {
    result_vec[i] = round_f(left_vec[i] * right_vec[i]);
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
      ss << ",";
    }
  }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}
RC VectorType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::VECTORS: {
      result.ref_vector(val);
    } break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}
RC VectorType::l2_distance(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto  left_vec  = l.get_vector();
  auto  right_vec = r.get_vector();
  float sum       = l2_norm_helper(left_vec, right_vec, len);
  result.set_float(round_f(std::sqrt(sum)));
  return RC::SUCCESS;
}

float VectorType::l2_norm_helper(const float *left, const float *right, int len) const
{
  float sum = 0;
  for (int i = 0; i < len; i++) {
    sum += (left[i] - right[i]) * (left[i] - right[i]);
  }
  return sum;
}
RC VectorType::cosine_distance(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto  left_vec   = l.get_vector();
  auto  right_vec  = r.get_vector();
  float inner_prod = inner_product_helper(left_vec, right_vec, len);
  float left_norm  = inner_product_helper(left_vec, left_vec, len);
  float right_norm = inner_product_helper(right_vec, right_vec, len);
  float sum        = round_f(1 - inner_prod / (std::sqrt(left_norm) * std::sqrt(right_norm)));

  result.set_float(sum);
  return RC::SUCCESS;
}
RC VectorType::inner_product(const Value &left, const Value &right, Value &result) const
{
  int   len;
  Value l, r;
  RC    rc = Value::cast_to(left, AttrType::VECTORS, l);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Value::cast_to(right, AttrType::VECTORS, r);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  if ((len = l.length_) != r.length_) {
    return RC::INVALID_ARGUMENT;
  }
  auto  left_vec  = l.get_vector();
  auto  right_vec = r.get_vector();
  float sum       = inner_product_helper(left_vec, right_vec, len);

  result.set_float(round_f(sum));
  return RC::SUCCESS;
}
float VectorType::inner_product_helper(const float *left, const float *right, int len) const
{
  float sum = 0;
  for (int i = 0; i < len; i++) {
    sum += left[i] * right[i];
  }
  return sum;
}
RC VectorType::set_value_from_str(Value &val, const string &data) const
{
  Value tmp;

  tmp.set_string(data.c_str() + 1, data.length() - 2);
  Value::cast_to(tmp, AttrType::VECTORS, val);

  return RC::SUCCESS;
}
