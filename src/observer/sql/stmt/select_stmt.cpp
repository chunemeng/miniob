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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;
  binder_context.set_db(db);

  // collect tables in `from` statement
  vector<Table *> tables;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const auto &table_name = select_sql.relations[i];
    if (table_name.relation_name.empty()) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name.relation_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table_name.relation_name, table);
    if (!table_name.attribute_name.empty() &&
        !binder_context.add_alias(table_name.attribute_name, table_name.relation_name)) {
      LOG_WARN("alias name already exists. alias=%s, table_name=%s", table_name.attribute_name.c_str(), table_name.relation_name.c_str());
      return RC::SCHEMA_ALIAS_NAME_REPEAT;
    }
  }
  bool should_alis = !select_sql.inner_joins.empty();

  for (auto &node : select_sql.inner_joins) {
    for (auto &cond : node.conditions) {
      select_sql.conditions.emplace_back(cond);
    }

    const auto &table_name_r = node.table_name;
    if (table_name_r.relation_name.empty()) {
      LOG_WARN("invalid argument. relation name is null.");
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name_r.relation_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name_r.relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table_name_r.relation_name, table);
    if (!table_name_r.attribute_name.empty() &&
        !binder_context.add_alias(table_name_r.attribute_name, table_name_r.relation_name)) {
      LOG_WARN("alias name already exists. alias=%s, table_name=%s", table_name_r.attribute_name.c_str(), table_name_r.relation_name.c_str());
      return RC::SCHEMA_ALIAS_NAME_REPEAT;
    }
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder               expression_binder(binder_context);

  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions, should_alis);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions, should_alis);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  std::vector<unique_ptr<Expression>> order_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.order_bys) {
    RC rc = expression_binder.bind_expression(expression, order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      expression_binder, select_sql.conditions.data(), static_cast<int>(select_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(binder_context.table_ordered());
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  stmt = select_stmt;
  return RC::SUCCESS;
}
