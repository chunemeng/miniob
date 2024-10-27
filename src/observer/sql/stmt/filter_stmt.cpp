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

FilterStmt::~FilterStmt() { filter_units_.clear(); }

RC FilterStmt::create(Table *default_table, const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  BinderContext binder_context;
  binder_context.add_table(default_table->name(), default_table);
  binder_context.real_table_num()++;
  ExpressionBinder binder(binder_context);
  return create(binder, conditions, condition_num, stmt);
}

RC FilterStmt::create(ExpressionBinder &binder, const ConditionSqlNode *conditions,
    int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();

  std::vector<std::unique_ptr<Expression>> units;
  for (int i = 0; i < condition_num; i++) {
    std::unique_ptr<Expression> filter_unit(conditions[i].condition);
    rc = binder.bind_expression(filter_unit, units);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
  }

  tmp_stmt->filter_units_ = std::move(units);
  stmt                    = tmp_stmt;
  return rc;
}
