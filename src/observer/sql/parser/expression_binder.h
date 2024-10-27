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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include <vector>

#include "sql/expr/expression.h"

class BinderContext
{
public:
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  bool add_table(const std::string &name, Table *table)
  {
    auto iter = table_map_.emplace(name, table);
    if (!iter.second) {
      return false;
    }
    table_ordered_.emplace_back(table);
    return true;
  }

  int &real_table_num() { return real_table_num_; }

  void set_db(Db *db) { this->db_ = db; }

  Table *find_table(const std::string &table_name) const;

  std::unordered_map<std::string, Table *> &table_map() { return table_map_; }
  std::vector<Table *>                     &table_ordered() { return table_ordered_; }
  Db                                       *get_db() const { return db_; }

private:
  Db                                      *db_             = nullptr;
  int                                      real_table_num_ = 0;
  std::unordered_map<std::string, Table *> table_map_;
  // use for output the table in order
  std::vector<Table *> table_ordered_;
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions,
      bool should_alis = false);

private:
  RC bind_subquery_expression(
      std::unique_ptr<Expression> &subquery_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_star_expression(std::unique_ptr<Expression> &star_expr,
      std::vector<std::unique_ptr<Expression>> &bound_expressions, bool should_alis = false);
  RC bind_unbound_field_expression(std::unique_ptr<Expression> &unbound_field_expr,
      std::vector<std::unique_ptr<Expression>> &bound_expressions, bool should_alis = false);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_valuelist_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  BinderContext &context_;
};