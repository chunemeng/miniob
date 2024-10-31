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
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/executor/create_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_table_stmt.h"
#include "storage/db/db.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/optimizer/rewriter.h"
#include "sql/operator/insert_physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/expr/expression_tuple.h"

RC CreateTableExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type()));
  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);

  const char *table_name = create_table_stmt->table_name().c_str();
  RC          rc         = session->get_current_db()->create_table(
      table_name, create_table_stmt->attr_infos(), create_table_stmt->storage_format());

  if (rc != RC::SUCCESS) {
    LOG_ERROR("create table failed, table name: %s", table_name);
    return rc;
  }

  if (create_table_stmt->select_stmt() != nullptr) {
    LOG_INFO("create table with select");
    LogicalPlanGenerator  logical_plan_generator_;   ///< 根据SQL生成逻辑计划
    PhysicalPlanGenerator physical_plan_generator_;  ///< 根据逻辑计划生成物理计划
    Rewriter              rewriter_;                 ///< 逻辑计划改写

    std::unique_ptr<LogicalOperator> logical_operator;
    rc = logical_plan_generator_.create(create_table_stmt->select_stmt(), logical_operator);
    LOG_INFO("create logical plan");

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create logical plan. rc=%s", strrc(rc));
      return rc;
    }

    if (logical_operator == nullptr) {
      LOG_WARN("logical operator is null");
      return RC::SUCCESS;
    }

    bool change_made = false;
    do {
      change_made = false;
      rc          = rewriter_.rewrite(logical_operator, change_made);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to do expression rewrite on logical plan in subquery. rc=%s", strrc(rc));
        return rc;
      }
    } while (change_made);

    std::unique_ptr<PhysicalOperator> oper;
    rc = physical_plan_generator_.create(*logical_operator, oper);
    if (rc != RC::SUCCESS || oper == nullptr || oper->type() != PhysicalOperatorType::PROJECT) {
      LOG_WARN("failed to create physical operator in subquery. rc=%s", strrc(rc));
      return rc;
    }

    rc = oper->open(session->current_trx());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open physical operator in subquery. rc=%s", strrc(rc));
      return rc;
    }
    Table *table = session->get_current_db()->find_table(table_name);
    if (table == nullptr) {
      LOG_WARN("no such table. table_name=%s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    Trx *trx = session->current_trx();
    std::vector<Value> values_;
    values_.resize(create_table_stmt->attr_infos().size());

    while (OB_SUCC(rc = oper->next())) {
      LOG_INFO("get next record");
      Tuple *tuple = oper->current_tuple();
      for (size_t i = 0; i < values_.size(); ++i) {
        tuple->cell_at(static_cast<int>(i), values_[i]);
      }

      Record record;
      rc = table->make_record(static_cast<int>(values_.size()), values_.data(), record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
      }

      rc = trx->insert_record(table, record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      }
    }

    if (rc != RC::RECORD_EOF) {
      LOG_WARN("failed to get next record. rc=%s", strrc(rc));
      return rc;
    }
    rc = oper->close();
  }

  return rc;
}