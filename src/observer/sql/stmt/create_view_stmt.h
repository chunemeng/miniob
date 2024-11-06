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

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(std::string &table_name, std::string &select, SelectStmt *stmt, std::vector<std::string> &alias,
      StorageFormat storage_format)
      : select_str_(select),
        table_name_(table_name),
        select_stmt_(stmt),
        column_names_(std::move(alias)),
        storage_format_(storage_format)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string        &table_name() const { return table_name_; }
  const StorageFormat       storage_format() const { return storage_format_; }
  SelectStmt               *select_stmt() { return select_stmt_; }
  std::string              &select_str() { return select_str_; }
  std::vector<std::string> &column_names() { return column_names_; }

  static RC            create(Db *db, CreateViewSqlNode &create_table, Stmt *&stmt);
  static StorageFormat get_storage_format(const char *format_str);

private:
  std::string              select_str_;
  std::string              table_name_;
  SelectStmt              *select_stmt_;
  std::vector<std::string> column_names_;
  StorageFormat            storage_format_;
};