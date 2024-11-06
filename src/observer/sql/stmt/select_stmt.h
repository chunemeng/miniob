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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;
class BinderContext;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);
  static RC create(BinderContext &binder_context, SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }
  FilterStmt                 *having_stmt() const { return having_stmt_; }
  static RC                   create_select_from_str(Table *table, Stmt *&stmt);

  std::vector<std::unique_ptr<Expression>>  &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>>  &group_by() { return group_by_; }
  std::vector<std::unique_ptr<Expression>>  &order_by() { return order_by_; }
  std::unordered_map<Table *, SelectStmt *> &view_map() { return view_map_; }

  RC get_attr_infos(std::vector<AttrInfoSqlNode> &field_meta);

  bool is_vector_scanner() const { return is_vector_scanner_; }

private:
  std::vector<std::unique_ptr<Expression>>  query_expressions_;
  std::vector<Table *>                      tables_;
  FilterStmt                               *filter_stmt_ = nullptr;
  FilterStmt                               *having_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>>  order_by_;
  std::vector<std::unique_ptr<Expression>>  group_by_;
  std::unordered_map<Table *, SelectStmt *> view_map_;
  bool                                      is_vector_scanner_ = false;
};
