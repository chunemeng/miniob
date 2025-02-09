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

#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/create_table_stmt.h"
#include "event/sql_debug.h"
#include "sql/parser/expression_binder.h"

RC CreateTableStmt::create(Db *db, CreateTableSqlNode &create_table, Stmt *&stmt)
{
  StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT;
  if (create_table.storage_format.length() == 0) {
    storage_format = StorageFormat::ROW_FORMAT;
  } else {
    storage_format = get_storage_format(create_table.storage_format.c_str());
  }
  if (storage_format == StorageFormat::UNKNOWN_FORMAT) {
    return RC::INVALID_ARGUMENT;
  }

  SelectStmt *select_stmt = nullptr;
  if (create_table.select != nullptr) {
    Stmt *select_stmt_t = nullptr;
    RC    rc            = SelectStmt::create(db, *create_table.select, select_stmt_t);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    select_stmt = dynamic_cast<SelectStmt *>(select_stmt_t);
    if (create_table.attr_infos.empty()) {
      rc = select_stmt->get_attr_infos(create_table.attr_infos);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos, select_stmt, storage_format);
  return RC::SUCCESS;
}

StorageFormat CreateTableStmt::get_storage_format(const char *format_str)
{
  StorageFormat format = StorageFormat::UNKNOWN_FORMAT;
  if (0 == strcasecmp(format_str, "ROW")) {
    format = StorageFormat::ROW_FORMAT;
  } else if (0 == strcasecmp(format_str, "PAX")) {
    format = StorageFormat::PAX_FORMAT;
  } else {
    format = StorageFormat::UNKNOWN_FORMAT;
  }
  return format;
}
