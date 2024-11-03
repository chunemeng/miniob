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

  std::vector<std::unique_ptr<Expression>> conditions;

  for (auto &node : select_sql.inner_joins) {
    conditions.emplace_back(node.conditions);

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
    LOG_INFO("table_name_r.attribute_name %s", table_name_r.attribute_name.c_str());
    if (!table_name_r.attribute_name.empty() &&
        !binder_context.add_alias(table_name_r.attribute_name, table_name_r.relation_name)) {
      LOG_WARN("alias name already exists. alias=%s, table_name=%s", table_name_r.attribute_name.c_str(), table_name_r.relation_name.c_str());
      return RC::SCHEMA_ALIAS_NAME_REPEAT;
    }
  }

  if (!conditions.empty()) {
    if (select_sql.conditions != nullptr) {
      conditions.emplace_back(select_sql.conditions);
    }
    select_sql.conditions = new ConjunctionExpr(ConjunctionExpr::Type::AND, conditions);
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
  bool is_vector_scanner = false;
  if (order_by_expressions.size() == 1 && order_by_expressions[0]->type() == ExprType::VEC_ORDER_BY) {
    auto                   &expr              = order_by_expressions[0];
    VecOrderByExpr         *vec_order_by_expr = dynamic_cast<VecOrderByExpr *>(expr.get());
    unique_ptr<Expression> &left_expr         = vec_order_by_expr->left();
    unique_ptr<Expression> &right_expr        = vec_order_by_expr->right();
    auto                   &tables            = binder_context.table_ordered();
    // 左右比较的一边最少是一个值
    if ((left_expr->type() != ExprType::VALUE && right_expr->type() != ExprType::VALUE) && tables.size() != 1) {
      return RC::INVALID_ARGUMENT;
    }

    FieldExpr *field_expr = nullptr;
    if (left_expr->type() == ExprType::FIELD) {
      ASSERT(right_expr->type() == ExprType::VALUE, "right expr should be a value expr while left is field expr");
      field_expr = static_cast<FieldExpr *>(left_expr.get());
    } else if (right_expr->type() == ExprType::FIELD) {
      ASSERT(left_expr->type() == ExprType::VALUE, "left expr should be a value expr while right is a field expr");
      field_expr = static_cast<FieldExpr *>(right_expr.get());
      left_expr.swap(right_expr);
    }
    const Field &field = field_expr->field();
    Index       *index = tables[0]->find_index_by_field(field.field_name().c_str());

    is_vector_scanner = index != nullptr && index->index_meta().type() == IndexType::IVF;
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(expression_binder, select_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  FilterStmt *having_stmt = nullptr;
  rc                      = FilterStmt::create(expression_binder, select_sql.having_cond, having_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(binder_context.table_ordered());
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  select_stmt->is_vector_scanner_ = is_vector_scanner;
  stmt                            = select_stmt;
  return RC::SUCCESS;
}
RC SelectStmt::create(BinderContext &binder_context, SelectSqlNode &select_sql, Stmt *&stmt)
{
  Db *db = binder_context.get_db();
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

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
      std::string alias = binder_context.get_alias_back(table_name.attribute_name);
      if (alias == table_name.relation_name) {
        LOG_WARN("alias name already exists. alias=%s, table_name=%s", table_name.attribute_name.c_str(), table_name.relation_name.c_str());
        return RC::SCHEMA_ALIAS_NAME_REPEAT;
      }
      binder_context.add_alias_subquery(table_name.attribute_name, table_name.relation_name);
    }
  }

  bool                                     should_alis = !select_sql.inner_joins.empty();
  std::vector<std::unique_ptr<Expression>> conditions;

  for (auto &node : select_sql.inner_joins) {
    conditions.emplace_back(node.conditions);

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
      std::string alias = binder_context.get_alias_back(table_name_r.attribute_name);
      if (alias == table_name_r.relation_name) {
        LOG_WARN("alias name already exists. alias=%s, table_name=%s", table_name_r.attribute_name.c_str(), table_name_r.relation_name.c_str());
        return RC::SCHEMA_ALIAS_NAME_REPEAT;
      }
      binder_context.add_alias_subquery(table_name_r.attribute_name, table_name_r.relation_name);
    }
  }

  if (!conditions.empty()) {
    if (select_sql.conditions != nullptr) {
      conditions.emplace_back(select_sql.conditions);
    }
    select_sql.conditions = new ConjunctionExpr(ConjunctionExpr::Type::AND, conditions);
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
  LOG_INFO("bound_expressions size %d", bound_expressions.size());

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
  RC          rc          = FilterStmt::create(expression_binder, select_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  FilterStmt *having_stmt = nullptr;
  rc                      = FilterStmt::create(expression_binder, select_sql.having_cond, having_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(binder_context.table_ordered());
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  stmt = select_stmt;
  return RC::SUCCESS;
}
RC SelectStmt::get_attr_infos(vector<AttrInfoSqlNode> &field_meta)
{
  for (const unique_ptr<Expression> &expression : query_expressions_) {
    AttrInfoSqlNode attr_info;
    switch (expression->type()) {
      case ExprType::FIELD: {
        FieldExpr *field_expr = dynamic_cast<FieldExpr *>(expression.get());
        auto       field      = field_expr->field().meta();
        attr_info.type        = field->type();
        attr_info.name        = field->name();
        attr_info.nullable    = field->nullable();
        attr_info.length      = field->len();
      } break;
      case ExprType::ARITHMETIC: {
        attr_info.type     = expression->value_type();
        attr_info.name     = expression->name();
        attr_info.length   = expression->value_length();
        attr_info.nullable = true;
      } break;
      case ExprType::VALUE: {
        attr_info.type     = expression->value_type();
        attr_info.name     = expression->name();
        attr_info.length   = expression->value_length();
        attr_info.nullable = true;
      } break;
      default: LOG_WARN("invalid expression type. type=%d", expression->type()); return RC::INVALID_ARGUMENT;
    }
    field_meta.emplace_back(attr_info);
  }
  return RC::SUCCESS;
}
