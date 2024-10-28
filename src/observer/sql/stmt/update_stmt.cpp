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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<std::unique_ptr<Expression>> &value,
    std::vector<const FieldMeta *> &field_meta, FilterStmt *filter_stmt)
    : table_(table), filter_stmt_(filter_stmt), field_meta_(std::move(field_meta)), values_(std::move(value))
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{

  auto table_name = update.relation_name;
  if (nullptr == db || table_name.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name.c_str());
    return RC::INVALID_ARGUMENT;
  }
  BinderContext binder_context;
  binder_context.set_db(db);

  // check whether the table exists
  Table *table = db->find_table(table_name.c_str());
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  ExpressionBinder binder(binder_context);
  const auto      &table_meta = table->table_meta();
  auto            &exprs      = update.expressions;

  std::vector<std::unique_ptr<Expression>> expr;
  expr.reserve(exprs.size());
  std::vector<const FieldMeta *> fields;
  fields.reserve(exprs.size());

  RC rc = RC::SUCCESS;

  for (size_t i = 0; i < exprs.size(); ++i) {
    if (exprs[i]->type() != ExprType::COMPARISON) {
      LOG_WARN("invalid update expr type.");
      return RC::INVALID_ARGUMENT;
    }
    auto expr_tmp = dynamic_cast<ComparisonExpr *>(exprs[i].get());
    if (expr_tmp->left()->type() != ExprType::UNBOUND_FIELD) {
      LOG_WARN("invalid update expr op.");
      return RC::INVALID_ARGUMENT;
    }
    const FieldMeta *field_meta =
        table_meta.field(dynamic_cast<UnboundFieldExpr *>(expr_tmp->left().get())->field_name());
    if (nullptr == field_meta) {
      LOG_WARN("no such field in table. db=%s, table=%s",
          db->name(), table_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    fields.emplace_back(field_meta);

    rc = binder.bind_expression(expr_tmp->right(), expr);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to bind expression. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
  }

  ASSERT(expr.size() == fields.size(), "expr size should be equal to fields size");

  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(table, update.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, expr, fields, filter_stmt);

  return rc;
}
