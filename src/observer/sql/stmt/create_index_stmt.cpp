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
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/stmt/create_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/expr/expression.h"
#include "storage/index/ivfflat_index.h"

using namespace std;
using namespace common;

RC CreateIndexStmt::create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt)
{
  stmt = nullptr;

  const char *table_name = create_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_index.index_name.c_str()) || create_index.attribute_list.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index name=%s",
        db, table_name, create_index.index_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  Index *index = table->find_index(create_index.index_name.c_str());
  if (nullptr != index) {
    LOG_WARN("index with name(%s) already exists. table name=%s", create_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }

  std::vector<const FieldMeta *> index_fields;
  const auto                    &table_meta = table->table_meta();
  // NOTE:SHOULD reserve one more space for the NULL FIELD
  index_fields.reserve(create_index.attribute_list.size() + table_meta.null_field_num());
  for (int i = 0; i < table_meta.null_field_num(); ++i) {
    index_fields.push_back(table_meta.field(i));
  }

  for (const auto &attr : create_index.attribute_list) {
    const FieldMeta *field_meta = table->table_meta().field(attr.attribute_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", db->name(), table_name, attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    index_fields.push_back(field_meta);
  }
  if (create_index.is_vector) {
    int          lists = 0, probs = 0;
    DistanceType type = UNKNOWN;
    if (create_index.expressions.size() != 4) {
      LOG_WARN("invalid expression size. size=%d", create_index.expressions.size());
      return RC::INVALID_ARGUMENT;
    }
    for (auto &expr : create_index.expressions) {
      if (expr->type() != ExprType::COMPARISON) {
        LOG_WARN("invalid expression type. type=%d", expr->type());
        return RC::INVALID_ARGUMENT;
      }
      auto *comp_expr = dynamic_cast<ComparisonExpr *>(expr.get());
      if (comp_expr->comp() != CompOp::EQUAL_TO) {
        LOG_WARN("invalid expression op. op=%d", comp_expr->comp());
        return RC::INVALID_ARGUMENT;
      }

      auto left = dynamic_cast<ValueExpr *>(comp_expr->left().get());
      switch (left->get_value().get_int()) {
        case 1:
          if (lists != 0) {
            LOG_WARN("invalid expression value. value=%d", left->get_value().get_int());
            return RC::INVALID_ARGUMENT;
          }
          lists = dynamic_cast<ValueExpr *>(comp_expr->right().get())->get_value().get_int();
          break;
        case 2:
          if (probs != 0) {
            LOG_WARN("invalid expression value. value=%d", left->get_value().get_int());
            return RC::INVALID_ARGUMENT;
          }
          probs = dynamic_cast<ValueExpr *>(comp_expr->right().get())->get_value().get_int();
          break;
        case 3:
          if (type != UNKNOWN) {
            LOG_WARN("invalid expression value. value=%d", left->get_value().get_int());
            return RC::INVALID_ARGUMENT;
          }
          type = static_cast<DistanceType>(dynamic_cast<ValueExpr *>(comp_expr->right().get())->get_value().get_int());
          break;
        case 4: {
          auto right = dynamic_cast<ValueExpr *>(comp_expr->right().get());
          if (right == nullptr) {
            LOG_WARN("invalid expression value. value=");
            return RC::INVALID_ARGUMENT;
          }
          if (right->get_value().get_int() != 1) {
            LOG_WARN("invalid expression value. value=%d", right->get_value().get_int());
            return RC::INVALID_ARGUMENT;
          }
        } break;
        default: return RC::INVALID_ARGUMENT;
      }
    }
    stmt = new CreateIndexStmt(
        table, index_fields, create_index.index_name, create_index.unique, true, lists, probs, type);

  } else {
    stmt = new CreateIndexStmt(table, index_fields, create_index.index_name, create_index.unique);
  }

  return RC::SUCCESS;
}
