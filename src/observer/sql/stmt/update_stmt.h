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

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  ~UpdateStmt() override;
  UpdateStmt(Table *table, std::vector<std::unique_ptr<Expression>> &value, std::vector<const FieldMeta *> &,
      FilterStmt *filter_stmt);

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table                                    *table() const { return table_; }
  std::vector<std::unique_ptr<Expression>> &values() { return values_; }
  FilterStmt                               *filter_stmt() const { return filter_stmt_; }
  std::vector<const FieldMeta *>           &field_meta() { return field_meta_; }

  StmtType type() const override { return StmtType::UPDATE; }

private:
  Table      *table_       = nullptr;
  FilterStmt *filter_stmt_ = nullptr;

  std::vector<const FieldMeta *>           field_meta_;
  std::vector<std::unique_ptr<Expression>> values_;
};
