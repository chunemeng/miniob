/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/type/data_type.h"

/**
 * @brief 向量类型
 * @ingroup DataType
 */
class VectorType : public DataType
{
private:
  float l2_norm_helper(const float *left, const float *right, int len) const;

  float inner_product_helper(const float *left, const float *right, int len) const;

public:
  VectorType() : DataType(AttrType::VECTORS) {}
  ~VectorType() override = default;

  int compare(const Value &left, const Value &right) const override;

  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC l2_distance(const Value &left, const Value &right, Value &result) const override;

  RC cosine_distance(const Value &left, const Value &right, Value &result) const override;

  RC inner_product(const Value &left, const Value &right, Value &result) const override;

  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  RC to_string(const Value &val, string &result) const override;
};