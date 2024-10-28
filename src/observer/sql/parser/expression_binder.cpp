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

#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/expression_binder.h"
#include "sql/expr/expression_iterator.h"

using namespace std;
using namespace common;

Table *BinderContext::find_table(const string &table_name) const
{
  auto alias_iter = alias_map_.find(table_name);
  if (alias_iter != alias_map_.end()) {
    auto table_iter = table_map_.find(alias_iter->second);
    return table_iter == table_map_.end() ? nullptr : table_iter->second;
  }
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
static void wildcard_fields(Table *table, vector<unique_ptr<Expression>> &expressions, bool should_alis)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Field      field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    if (should_alis) {
      field_expr->set_name(field.table_name() + "." + field.field_name());
    } else {
      field_expr->set_name(field.field_name());
    }
    expressions.emplace_back(field_expr);
  }
}

RC ExpressionBinder::bind_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions, bool should_alis)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  switch (expr->type()) {
    case ExprType::STAR: {
      return bind_star_expression(expr, bound_expressions, should_alis);
    } break;

    case ExprType::UNBOUND_FIELD: {
      return bind_unbound_field_expression(expr, bound_expressions, should_alis);
    } break;

    case ExprType::UNBOUND_AGGREGATION: {
      return bind_aggregate_expression(expr, bound_expressions);
    } break;
    case ExprType::VALUE_LIST: {
      return bind_valuelist_expression(expr, bound_expressions);
    } break;
    case ExprType::SUBQUERY: {
      return bind_subquery_expression(expr, bound_expressions);
    } break;

    case ExprType::FIELD: {
      return bind_field_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::CAST: {
      return bind_cast_expression(expr, bound_expressions);
    } break;

    case ExprType::COMPARISON: {
      return bind_comparison_expression(expr, bound_expressions);
    } break;

    case ExprType::CONJUNCTION: {
      return bind_conjunction_expression(expr, bound_expressions);
    } break;

    case ExprType::ARITHMETIC: {
      return bind_arithmetic_expression(expr, bound_expressions);
    } break;

    case ExprType::AGGREGATION: {
      ASSERT(false, "shouldn't be here");
    } break;
    case ExprType::ORDER_BY: {
      return bind_order_by_expression(expr, bound_expressions);
    } break;

    default: {
      LOG_WARN("unknown expression type: %d", static_cast<int>(expr->type()));
      return RC::INTERNAL;
    }
  }
  return RC::INTERNAL;
}

RC ExpressionBinder::bind_star_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions, bool should_alis)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto star_expr = static_cast<StarExpr *>(expr.get());

  const auto &table_name = star_expr->table_name();
  if (!is_blank(table_name) && table_name != "*") {
    Table *table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    wildcard_fields(table, bound_expressions, should_alis);
  } else {
    auto &all_tables = context_.table_ordered();
    // don't change it to auto, because it may lose const & in std::string!!!

    for (auto table : all_tables) {
      wildcard_fields(table, bound_expressions, should_alis);
    }
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_unbound_field_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions, bool should_alis)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

  const auto &table_name = unbound_field_expr->table_name();
  const auto &field_name = unbound_field_expr->field_name();

  Table *table = nullptr;
  if (is_blank(table_name)) {
    if (context_.table_map().size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table = context_.table_map().begin()->second;
  } else {
    table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }

  if (field_name == "*") {
    wildcard_fields(table, bound_expressions, should_alis);
  } else {
    const FieldMeta *field_meta = table->table_meta().field(field_name.c_str());
    if (nullptr == field_meta) {
      LOG_INFO("no such field in table: %s.%s", table_name.c_str(), field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    Field      field(table, field_meta);
    FieldExpr *field_expr = new FieldExpr(field);
    if (unbound_field_expr->is_alias()) {
      field_expr->set_name(unbound_field_expr->name());
    } else if (should_alis) {
      field_expr->set_name(table_name + "." + field_name);
    } else {
      field_expr->set_name(field_name);
    }

    bound_expressions.emplace_back(field_expr);
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_field_expression(
    unique_ptr<Expression> &field_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(field_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_value_expression(
    unique_ptr<Expression> &value_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_cast_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto cast_expr = static_cast<CastExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &child_expr = cast_expr->child();

  RC rc = bind_expression(child_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid children number of cast expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &child = child_bound_expressions[0];
  if (child.get() == child_expr.get()) {
    return RC::SUCCESS;
  }

  child_expr.reset(child.release());
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

static int implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC ExpressionBinder::bind_comparison_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = comparison_expr->left();
  unique_ptr<Expression>        &right_expr = comparison_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  if (comparison_expr->comp() == EXISTS_C || comparison_expr->comp() == NOT_EXISTS) {
    if (left_expr->type() != ExprType::VALUE_LIST) {
      LOG_WARN("right expression should be null for exists or not exists");
      return RC::INVALID_ARGUMENT;
    }
    bound_expressions.emplace_back(std::move(expr));
    return RC::SUCCESS;
  }

  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }

  if (comparison_expr->comp() == IN_OP || comparison_expr->comp() == NOT_IN) {
    if (right_expr->type() != ExprType::VALUE_LIST) {
      return RC::INVALID_ARGUMENT;
    }
    bound_expressions.emplace_back(std::move(expr));
    return RC::SUCCESS;
  }

  AttrType left_attr_type  = left_expr->value_type();
  AttrType right_attr_type = right_expr->value_type();

  if (left_attr_type == AttrType::NULLS || right_attr_type == AttrType::NULLS) {
    bound_expressions.emplace_back(std::move(expr));
    return RC::SUCCESS;
  }

  if (left_attr_type != right_attr_type) {
    auto left_to_right_cost = implicit_cast_cost(left_attr_type, right_attr_type);
    auto right_to_left_cost = implicit_cast_cost(right_attr_type, left_attr_type);
    if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
      ExprType left_type = left_expr->type();
      auto     cast_expr = make_unique<CastExpr>(std::move(left_expr), right_attr_type);
      if (left_type == ExprType::VALUE) {
        Value left_val;
        if (OB_FAIL(rc = cast_expr->try_get_value(left_val))) {
          LOG_WARN("failed to get value from left child", strrc(rc));
          return rc;
        }
        left_expr = make_unique<ValueExpr>(left_val);
      } else {
        left_expr = std::move(cast_expr);
      }
    } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
      ExprType right_type = right_expr->type();
      auto     cast_expr  = make_unique<CastExpr>(std::move(right_expr), left_attr_type);
      if (right_type == ExprType::VALUE) {
        Value right_val;
        if (OB_FAIL(rc = cast_expr->try_get_value(right_val))) {
          LOG_WARN("failed to get value from right child", strrc(rc));
          return rc;
        }
        right_expr = make_unique<ValueExpr>(right_val);
      } else {
        right_expr = std::move(cast_expr);
      }

    } else {
      rc = RC::UNSUPPORTED;
      LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left_attr_type), attr_type_to_string(right_attr_type));
      return rc;
    }
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_conjunction_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());

  vector<unique_ptr<Expression>>  child_bound_expressions;
  vector<unique_ptr<Expression>> &children = conjunction_expr->children();

  for (unique_ptr<Expression> &child_expr : children) {
    child_bound_expressions.clear();

    RC rc = bind_expression(child_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of conjunction expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &child = child_bound_expressions[0];
    if (child.get() != child_expr.get()) {
      child_expr.reset(child.release());
    }
  }

  bound_expressions.emplace_back(std::move(expr));

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_arithmetic_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = arithmetic_expr->left();
  unique_ptr<Expression>        &right_expr = arithmetic_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();

  if (right_expr) {
    rc = bind_expression(right_expr, child_bound_expressions);
    if (OB_FAIL(rc)) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &right = child_bound_expressions[0];
    if (right.get() != right_expr.get()) {
      right_expr.reset(right.release());
    }
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC check_aggregate_expression(AggregateExpr &expression)
{
  // 必须有一个子表达式
  Expression *child_expression = expression.child().get();
  if (nullptr == child_expression) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  // 校验数据类型与聚合类型是否匹配
  AggrType aggregate_type   = expression.aggregate_type();
  AttrType child_value_type = child_expression->value_type();
  switch (aggregate_type) {
    case AggrType::SUM:
    case AggrType::AVG: {
      // 仅支持数值类型
      if (child_value_type != AttrType::INTS && child_value_type != AttrType::FLOATS &&
          child_value_type != AttrType::NULLS) {
        LOG_WARN("invalid child value type for aggregate expression: %d", static_cast<int>(child_value_type));
        return RC::INVALID_ARGUMENT;
      }
    } break;

    case AggrType::COUNT:
    case AggrType::MAX:
    case AggrType::MIN: {
      // 任何类型都支持
    } break;
  }

  // 子表达式中不能再包含聚合表达式
  function<RC(std::unique_ptr<Expression> &)> check_aggregate_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      LOG_WARN("aggregate expression cannot be nested");
      return RC::INVALID_ARGUMENT;
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, check_aggregate_expr);
    return rc;
  };

  RC rc = ExpressionIterator::iterate_child_expr(expression, check_aggregate_expr);

  return rc;
}

RC ExpressionBinder::bind_aggregate_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_aggregate_expr = static_cast<UnboundAggregateExpr *>(expr.get());
  if (unbound_aggregate_expr->child() == nullptr) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  auto aggregate_type = unbound_aggregate_expr->aggregate_name();
  RC   rc             = RC::SUCCESS;

  unique_ptr<Expression>        &child_expr = unbound_aggregate_expr->child();
  vector<unique_ptr<Expression>> child_bound_expressions;

  if (child_expr->type() == ExprType::STAR && aggregate_type == AggrType::COUNT) {
    ValueExpr *value_expr = new ValueExpr(Value(1));
    child_expr.reset(value_expr);
  } else {
    rc = bind_expression(child_expr, child_bound_expressions);
    if (OB_FAIL(rc)) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of aggregate expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    if (child_bound_expressions[0].get() != child_expr.get()) {
      child_expr.reset(child_bound_expressions[0].release());
    }
  }

  auto aggregate_expr = make_unique<AggregateExpr>(aggregate_type, std::move(child_expr));
  aggregate_expr->set_name(unbound_aggregate_expr->name());
  rc = check_aggregate_expression(*aggregate_expr);
  if (OB_FAIL(rc)) {
    return rc;
  }

  bound_expressions.emplace_back(std::move(aggregate_expr));
  return RC::SUCCESS;
}
RC ExpressionBinder::bind_subquery_expression(
    unique_ptr<Expression> &expr, vector<std::unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto subquery_expr = static_cast<SubQueryExpr *>(expr.get());
  RC   rc            = subquery_expr->create_select(context_);
  if (OB_FAIL(rc)) {
    return rc;
  }
  auto value_list_expr = std::make_unique<ValueListExpr>(std::move(expr));
  rc                   = value_list_expr->init();
  if (OB_FAIL(rc)) {
    return rc;
  }

  bound_expressions.emplace_back(std::move(value_list_expr));
  return RC::SUCCESS;
}
RC ExpressionBinder::bind_valuelist_expression(
    unique_ptr<Expression> &value_expr, vector<std::unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == value_expr) {
    return RC::SUCCESS;
  }
  auto value_list_expr = static_cast<ValueListExpr *>(value_expr.get());
  RC   rc              = value_list_expr->init();
  if (OB_FAIL(rc)) {
    return rc;
  }
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}
RC ExpressionBinder::bind_order_by_expression(
    unique_ptr<Expression> &order_by_expr, vector<std::unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == order_by_expr) {
    return RC::SUCCESS;
  }

  auto expr = static_cast<OrderByExpr *>(order_by_expr.get());

  auto       &table_name = expr->get_table_name();
  const auto &field_name = expr->field_name();

  if (is_blank(table_name)) {
    if (context_.table_map().size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table_name = context_.table_map().begin()->first;
  }
  bound_expressions.emplace_back(std::move(order_by_expr));
  return RC::SUCCESS;
}
