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
// Created by Wangyunlai on 2022/12/30.
//

#include "sql/optimizer/predicate_pushdown_rewriter.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include <queue>

RC push_predicate_to_child(std::unordered_map<std::string, std::unique_ptr<Expression>> &pushdown_exprs,
    std::map<std::pair<std::string, std::string>, std::unique_ptr<Expression>>          &pushdown_join_exprs,
    JoinLogicalOperator                                                                 *join_oper)
{
  // 对JOIN算子，进行层状遍历，将谓词下推到最底层的TableGet算子，同时将JOIN算子的谓词下推到JOIN算子
  if (join_oper->children().size() != 2) {
    return RC::INVALID_ARGUMENT;
  }

  RC                            rc = RC::SUCCESS;
  std::queue<LogicalOperator *> q;
  JoinLogicalOperator          *current    = join_oper;
  JoinLogicalOperator          *child_join = nullptr;

  int pos = -1;
  q.emplace(current->children()[0].get());
  q.emplace(current->children()[1].get());
  LogicalOperator *child = nullptr;

  while (!q.empty()) {
    child = q.front();
    q.pop();
    pos = (pos + 1) & 1;

    if (child->type() == LogicalOperatorType::JOIN) {
      child_join = dynamic_cast<JoinLogicalOperator *>(child);
      q.emplace(child_join->children()[0].get());
      q.emplace(child_join->children()[1].get());
    } else if (child->type() == LogicalOperatorType::TABLE_GET) {
      auto ch1  = dynamic_cast<TableGetLogicalOperator *>(child);
      auto name = ch1->table()->name();
      LOG_INFO("push predicate to table get operator %s", name.c_str());
      auto  iter      = pushdown_exprs.find(name);
      auto &predicate = ch1->predicates();
      while (iter != pushdown_exprs.end()) {
        predicate.emplace_back(std::move(iter->second));
        pushdown_exprs.erase(iter);
        iter = pushdown_exprs.find(name);
      }
      if (current->type() != LogicalOperatorType::JOIN) {
        rc = RC::INVALID_ARGUMENT;
        return rc;
      }
      if (pushdown_join_exprs.empty()) {
        continue;
      }
      auto &pushdown_join_predicate = current->expressions();
      auto  lower_bound             = pushdown_join_exprs.lower_bound({name, ""});
      auto  it                      = lower_bound;
      for (; it != pushdown_join_exprs.end() && it->first.first == name; ++it) {
        LOG_INFO("push  %s", it->first.first.c_str());
        pushdown_join_predicate.emplace_back(std::move(it->second));
      }

      for (auto it2 = pushdown_join_exprs.begin(); it2 != lower_bound;) {
        auto iterrr = it2;
        ++it2;
        if (iterrr->first.second == name) {
          LOG_INFO("push  %s", iterrr->first.second.c_str());

          pushdown_join_predicate.emplace_back(std::move(iterrr->second));
          pushdown_join_exprs.erase(iterrr);
        }
      }

      pushdown_join_exprs.erase(lower_bound, it);
      LOG_INFO("push predicate to join operator %d", pushdown_join_exprs.size());
    }

    LOG_INFO("pos %d", pos);
    if (pos) {
      current = child_join;
    }
  }

  return rc;
}

RC PredicatePushdownRewriter::rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made)
{
  RC rc = RC::SUCCESS;
  if (oper->type() != LogicalOperatorType::PREDICATE) {
    return rc;
  }

  std::unique_ptr<LogicalOperator> &child_oper = oper->children().front();
  if (child_oper->type() != LogicalOperatorType::TABLE_GET) {
    if (child_oper->type() != LogicalOperatorType::JOIN) {
      return rc;
    }
    auto table_get_oper = dynamic_cast<JoinLogicalOperator *>(child_oper.get());

    std::vector<std::unique_ptr<Expression>> &predicate_oper_exprs = oper->expressions();
    if (predicate_oper_exprs.size() != 1) {
      return rc;
    }

    std::unique_ptr<Expression> &predicate_expr = predicate_oper_exprs.front();

    PUSH_JOIN_EXPRS_TYPE                                         pushdown_join_exprs;
    std::unordered_map<std::string, std::unique_ptr<Expression>> pushdown_exprs;

    rc = get_exprs_can_pushdown(predicate_expr, pushdown_exprs, pushdown_join_exprs);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get exprs can pushdown. rc=%s", strrc(rc));
      return rc;
    }

    if (!predicate_expr || is_empty_predicate(predicate_expr)) {
      // 所有的表达式都下推到了下层算子
      // 这个predicate operator其实就可以不要了。但是这里没办法删除，弄一个空的表达式吧
      LOG_TRACE("all expressions of predicate operator were pushdown to table get operator, then make a fake one");

      Value value((bool)true);
      predicate_expr = std::unique_ptr<Expression>(new ValueExpr(value));
    }

    if (!pushdown_exprs.empty() || !pushdown_join_exprs.empty()) {
      change_made = true;
      // the child of join operator is table get operator or another join operator
      push_predicate_to_child(pushdown_exprs, pushdown_join_exprs, table_get_oper);
      ASSERT(pushdown_exprs.empty() && pushdown_join_exprs.empty(), "pushdown_exprs should be empty");
    }
    return rc;
  }

  if (oper->children().size() != 1) {
    return rc;
  }

  auto table_get_oper = dynamic_cast<TableGetLogicalOperator *>(child_oper.get());

  std::vector<std::unique_ptr<Expression>> &predicate_oper_exprs = oper->expressions();
  if (predicate_oper_exprs.size() != 1) {
    return rc;
  }

  std::unique_ptr<Expression>             &predicate_expr = predicate_oper_exprs.front();
  std::vector<std::unique_ptr<Expression>> pushdown_exprs;
  rc = get_exprs_can_pushdown(predicate_expr, pushdown_exprs);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get exprs can pushdown. rc=%s", strrc(rc));
    return rc;
  }

  if (!predicate_expr || is_empty_predicate(predicate_expr)) {
    // 所有的表达式都下推到了下层算子
    // 这个predicate operator其实就可以不要了。但是这里没办法删除，弄一个空的表达式吧
    LOG_TRACE("all expressions of predicate operator were pushdown to table get operator, then make a fake one");

    Value value((bool)true);
    predicate_expr = std::unique_ptr<Expression>(new ValueExpr(value));
  }

  if (!pushdown_exprs.empty()) {
    change_made = true;
    table_get_oper->set_predicates(std::move(pushdown_exprs));
  }

  // NOTE: 此时不再需要递归调用, 因为TableGetLogicalOperator是最底层的operator
  return rc;
}

bool PredicatePushdownRewriter::is_empty_predicate(std::unique_ptr<Expression> &expr)
{
  bool bool_ret = false;
  if (!expr) {
    return true;
  }

  if (expr->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr *conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());
    if (conjunction_expr->children().empty()) {
      bool_ret = true;
    }
  }

  return bool_ret;
}

/**
 * 查看表达式是否可以直接下放到table get算子的filter
 * @param expr 是当前的表达式。如果可以下放给table get 算子，执行完成后expr就失效了
 * @param pushdown_exprs 当前所有要下放给table get 算子的filter。此函数执行多次，
 *                       pushdown_exprs 只会增加，不要做清理操作
 */
RC PredicatePushdownRewriter::get_exprs_can_pushdown(
    std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &pushdown_exprs)
{
  RC rc = RC::SUCCESS;
  if (expr->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr *conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());
    // 或 操作的比较，太复杂，现在不考虑
    if (conjunction_expr->conjunction_type() == ConjunctionExpr::Type::OR) {
      LOG_WARN("unsupported or operation");
      rc = RC::SUCCESS;
      return rc;
    }

    std::vector<std::unique_ptr<Expression>> &child_exprs = conjunction_expr->children();
    for (auto iter = child_exprs.begin(); iter != child_exprs.end();) {
      // 对每个子表达式，判断是否可以下放到table get 算子
      // 如果可以的话，就从当前孩子节点中删除他
      rc = get_exprs_can_pushdown(*iter, pushdown_exprs);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get pushdown expressions. rc=%s", strrc(rc));
        return rc;
      }

      if (!*iter) {
        child_exprs.erase(iter);
      } else {
        ++iter;
      }
    }
  } else if (expr->type() == ExprType::COMPARISON) {
    // 如果是比较操作，并且比较的左边或右边是表某个列值，那么就下推下去
    auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

    std::unique_ptr<Expression> &left_expr  = comparison_expr->left();
    std::unique_ptr<Expression> &right_expr = comparison_expr->right();
    // 比较操作的左右两边只要有一个是取列字段值的并且另一边也是取字段值或常量，就pushdown
    if (left_expr->type() != ExprType::FIELD && right_expr->type() != ExprType::FIELD) {
      return rc;
    }
    if (left_expr->type() != ExprType::FIELD && left_expr->type() != ExprType::VALUE &&
        right_expr->type() != ExprType::FIELD && right_expr->type() != ExprType::VALUE) {
      return rc;
    }

    pushdown_exprs.emplace_back(std::move(expr));
  }
  return rc;
}

RC PredicatePushdownRewriter::get_exprs_can_pushdown(unique_ptr<Expression> &expr,
    std::unordered_map<std::string, std::unique_ptr<Expression>>            &pushdown_exprs,
    PUSH_JOIN_EXPRS_TYPE                                                    &pushdown_join_exprs)
{
  // NOTE: THIS IS A PIECE OF SHIT
  RC rc = RC::SUCCESS;
  if (expr->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr *conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());
    // 或 操作的比较，太复杂，现在不考虑
    if (conjunction_expr->conjunction_type() == ConjunctionExpr::Type::OR) {
      LOG_WARN("unsupported or operation");
      rc = RC::SUCCESS;
      return rc;
    }

    std::vector<std::unique_ptr<Expression>> &child_exprs = conjunction_expr->children();
    for (auto iter = child_exprs.begin(); iter != child_exprs.end();) {
      // 对每个子表达式，判断是否可以下放到table get 算子
      // 如果可以的话，就从当前孩子节点中删除他
      rc = get_exprs_can_pushdown(*iter, pushdown_exprs, pushdown_join_exprs);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get pushdown expressions. rc=%s", strrc(rc));
        return rc;
      }

      if (!*iter) {
        child_exprs.erase(iter);
      } else {
        ++iter;
      }
    }
  } else if (expr->type() == ExprType::COMPARISON) {
    // 如果是比较操作，并且比较的左边或右边是表某个列值，那么就下推下去
    auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

    std::unique_ptr<Expression> &left_expr      = comparison_expr->left();
    std::unique_ptr<Expression> &right_expr     = comparison_expr->right();
    bool                         is_left_field  = left_expr->type() == ExprType::FIELD;
    bool                         is_right_field = right_expr->type() == ExprType::FIELD;

    // 比较操作的左右两边只要有一个是取列字段值的并且另一边也是取字段值或常量，就pushdown
    if (is_left_field && is_right_field) {
      auto left_name  = dynamic_cast<FieldExpr *>(left_expr.get())->table_name();
      auto right_name = dynamic_cast<FieldExpr *>(right_expr.get())->table_name();
      if (left_name == right_name) {
        return rc;
      }
      if (left_name > right_name) {
        pushdown_join_exprs.emplace(std::make_pair(right_name, left_name), std::move(expr));
      } else {
        pushdown_join_exprs.emplace(std::make_pair(left_name, right_name), std::move(expr));
      }
      return rc;
    }
    if (!is_left_field && right_expr->type() != ExprType::FIELD) {
      return rc;
    }
    if (left_expr->type() != ExprType::FIELD && left_expr->type() != ExprType::VALUE &&
        right_expr->type() != ExprType::FIELD && right_expr->type() != ExprType::VALUE) {
      return rc;
    }

    // NOTE: 防止把实际两侧都是FIELD的表达式 推到了TABLE GET算子 而不是JOIN算子
    if (left_expr->type() == ExprType::CAST || right_expr->type() == ExprType::CAST) {
      return rc;
    }

    auto name =
        (is_left_field ? dynamic_cast<FieldExpr *>(left_expr.get()) : dynamic_cast<FieldExpr *>(right_expr.get()))
            ->table_name();
    pushdown_exprs.emplace(name, std::move(expr));
  }
  return rc;
}
