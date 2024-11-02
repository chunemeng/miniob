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

#pragma once

#include <string>

#include "sql/stmt/stmt.h"
#include "storage/index/ivfflat_index.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateIndexStmt : public Stmt
{
public:
  CreateIndexStmt(Table *table, std::vector<const FieldMeta *> &field_meta, const std::string &index_name, bool unique)
      : table_(table), index_fields_(std::move(field_meta)), index_name_(index_name), unique_(unique)
  {}

  CreateIndexStmt(Table *table, std::vector<const FieldMeta *> &field_meta, const std::string &index_name, bool unique,
      bool is_vector, int lists, int probs, DistanceType dis)
      : table_(table),
        index_fields_(std::move(field_meta)),
        index_name_(index_name),
        unique_(unique),
        is_vector_(is_vector),
        lists_(lists),
        probs_(probs),
        dis_(dis)
  {}

  virtual ~CreateIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table                          *table() const { return table_; }
  std::vector<const FieldMeta *> &index_fields() { return index_fields_; }
  const std::string              &index_name() const { return index_name_; }
  bool                            unique() const { return unique_; }
  bool                            is_vector() const { return is_vector_; }
  int                             lists() const { return lists_; }
  int                             probs() const { return probs_; }
  DistanceType                    dis() const { return dis_; }

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table                         *table_ = nullptr;
  std::vector<const FieldMeta *> index_fields_;
  std::string                    index_name_;
  bool                           unique_    = false;
  bool                           is_vector_ = false;
  int                            lists_;
  int                            probs_;
  DistanceType                   dis_;
};
