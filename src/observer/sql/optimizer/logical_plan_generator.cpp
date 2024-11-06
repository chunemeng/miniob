/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/vec_order_by_logical_operator.h"
#include "sql/operator/limit_logical_operator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression_iterator.h"
#include "sql/operator/update_logical_operator.h"

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{

  unique_ptr<LogicalOperator>  table_oper(nullptr);
  unique_ptr<LogicalOperator> *last_oper = &table_oper;

  const auto &tables = select_stmt->tables();
  bool        once   = true;
  for (auto table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table->table_meta().is_view()) [[unlikely]] {
      unique_ptr<LogicalOperator> view_oper;
      auto                        iter = select_stmt->view_map().find(table);
      if (iter == select_stmt->view_map().end()) {
        LOG_WARN("view not found");
        return RC::NOT_EXIST;
      }
      RC rc = create(iter->second, view_oper);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create view logical plan. rc=%s", strrc(rc));
        return rc;
      }
      table_get_oper->add_child(std::move(view_oper));
    }

    if (select_stmt->is_vector_scanner() && once) {
      auto ptr = dynamic_cast<TableGetLogicalOperator *>(table_get_oper.get());
      ptr->set_vector_scanner(true);
      ptr->set_vector_scan_expr(std::move(select_stmt->order_by()[0]));
      once = false;
      select_stmt->order_by().clear();
    }
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  unique_ptr<LogicalOperator> predicate_oper_having;

  rc = create_plan(select_stmt->having_stmt(), predicate_oper_having);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper_having) {
    if (*last_oper) {
      predicate_oper_having->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper_having;
  }

  std::unique_ptr<LogicalOperator> order_by_oper;
  std::unique_ptr<LogicalOperator> limit_oper;
  if (!select_stmt->order_by().empty()) {
    if (select_stmt->order_by().size() == 1 && select_stmt->order_by()[0]->type() == ExprType::VEC_ORDER_BY) {
      auto vec_order = dynamic_cast<VecOrderByExpr *>(select_stmt->order_by()[0].get());
      std::vector<std::unique_ptr<Expression>> order_by_exprs;
      order_by_exprs.emplace_back(std::move(vec_order->left()));
      order_by_exprs.emplace_back(std::move(vec_order->right()));
      order_by_oper = std::make_unique<VecOrderByLogicalOperator>(order_by_exprs, vec_order->distance_type());

      if (*last_oper) {
        LOG_INFO("add order by oper");
        order_by_oper->add_child(std::move(*last_oper));
      }
      limit_oper = std::make_unique<LimitLogicalOperator>(vec_order->limit());
      limit_oper->add_child(std::move(order_by_oper));
      last_oper = &limit_oper;
    } else {
      order_by_oper = std::make_unique<OrderByLogicalOperator>(select_stmt->order_by());
      if (*last_oper) {
        LOG_INFO("add order by oper");
        order_by_oper->add_child(std::move(*last_oper));
      }
      last_oper = &order_by_oper;
    }
  }

  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC                           rc           = RC::SUCCESS;
  std::unique_ptr<Expression> &filter_units = filter_stmt->filter_units();

  unique_ptr<PredicateLogicalOperator> predicate_oper;

  if (filter_units != nullptr) {
    predicate_oper = std::make_unique<PredicateLogicalOperator>(std::move(filter_units));
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();

  if (table->table_meta().is_view()) {
    Stmt *select_stmt = nullptr;
    RC    rc          = SelectStmt::create_select_from_str(table, select_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create select stmt from view. rc=%s", strrc(rc));
      return rc;
    }
    SelectStmt *select_stmt_cast = static_cast<SelectStmt *>(select_stmt);

    const auto                     &tables = select_stmt_cast->tables();
    auto                           &values = insert_stmt->values();
    std::vector<std::vector<Value>> new_values(select_stmt_cast->tables().size());
    for (int i = 0; i < tables.size(); i++) {
      auto  table_meta = tables[i]->table_meta();
      Value v;
      v.set_null_chars();
      new_values[i].resize(table_meta.field_num() - table_meta.sys_field_num(), v);
    }

    for (int i = 0; i < values.size(); i++) {
      auto &value = values[i];
      auto &expr  = select_stmt_cast->query_expressions()[i];
      if (expr->type() == ExprType::FIELD) {
        auto field_expr = dynamic_cast<FieldExpr *>(expr.get());
        auto table_name = field_expr->table_name();
        auto field_name = field_expr->field_name();
        for (int j = 0; j < tables.size(); j++) {
          if (tables[j]->name() == table_name) {
            auto field_meta = tables[j]->table_meta().field(field_name);
            if (field_meta == nullptr) {
              continue;
            }
            new_values[j][field_meta->field_id()] = value;
            break;
          }
        }
      }
    }
    InsertLogicalOperator *last_insert_operator;
    for (int i = 0; i < tables.size(); i++) {
      InsertLogicalOperator *insert_operator = new InsertLogicalOperator(tables[i], new_values[i]);
      if (i == 0) {
        last_insert_operator = insert_operator;
      } else {
        last_insert_operator->add_child(std::unique_ptr<LogicalOperator>(insert_operator));
        last_insert_operator = insert_operator;
      }
    }
    logical_operator.reset(last_insert_operator);
    return RC::SUCCESS;
  }

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, insert_stmt->values());
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = update_stmt->table();
  FilterStmt                 *filter_stmt = update_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(table, update_stmt->field_meta(), update_stmt->values()));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>>             &group_by_expressions = select_stmt->group_by();
  vector<Expression *>                        aggregate_expressions;
  vector<unique_ptr<Expression>>             &query_expressions = select_stmt->query_expressions();
  function<RC(std::unique_ptr<Expression> &)> collector         = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression> &)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(static_cast<int>(i));
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

  bool                                        found_unbound_column = false;
  function<RC(std::unique_ptr<Expression> &)> find_unbound_column  = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    } else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  auto &having_stmt = select_stmt->having_stmt()->filter_units();

  if (having_stmt != nullptr) {
    bind_group_by_expr(having_stmt);

    find_unbound_column(having_stmt);

    collector(having_stmt);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper =
      make_unique<GroupByLogicalOperator>(std::move(group_by_expressions), std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}
