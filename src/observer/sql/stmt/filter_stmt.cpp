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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

RC FilterStmt::create(Table *default_table, Expression *expr, FilterStmt *&stmt)
{
  BinderContext binder_context;
  binder_context.add_table(default_table->name(), default_table);
  ExpressionBinder binder(binder_context);
  return create(binder, expr, stmt);
}

RC FilterStmt::create(ExpressionBinder &binder, Expression *expr, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();

  std::unique_ptr<Expression> filter_unit(expr);
  if (nullptr == filter_unit) {
    stmt = tmp_stmt;
    return RC::SUCCESS;
  }

  std::vector<std::unique_ptr<Expression>> units;
  rc = binder.bind_expression(filter_unit, units, false, true);
  if (rc != RC::SUCCESS) {
    delete tmp_stmt;
    LOG_WARN("failed to create filter unit. condition index=%d");
    return rc;
  }
  if (units.empty()) {
    delete tmp_stmt;
    LOG_WARN("empty filter unit");
    return RC::INVALID_ARGUMENT;
  }

  tmp_stmt->filter_units_ = std::move(units[0]);
  stmt                    = tmp_stmt;
  return rc;
}
