/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "storage/field/field_meta.h"
#include <iostream>

class TupleCellSpec final
{
public:
  TupleCellSpec() = default;
  TupleCellSpec(const char *table_name, const char *field_name, const char *alias = nullptr);
  TupleCellSpec(const std::string &table_name, const std::string &field_name, const char *alias = nullptr);
  explicit TupleCellSpec(const char *alias);
  explicit TupleCellSpec(const std::string &alias);

  const char* table_name() const { return table_name_.c_str(); }
  const std::string &table_name_str() const { return table_name_; }
  const std::string &field_name() const { return field_name_; }
  const char        *alias() const { return alias_.c_str(); }
  const std::string &alias_str() const { return alias_; }

  bool equals(const TupleCellSpec &other) const
  {
    return table_name_ == other.table_name_ && field_name_ == other.field_name_ && alias_ == other.alias_;
  }


  bool equals_no_alias(const TupleCellSpec &other) const
  {
    return table_name_ == other.table_name_ && field_name_ == other.field_name_;
  }

private:
  std::string table_name_;
  std::string field_name_;
  std::string alias_;
};
