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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/table_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"
#include <span>

using namespace std;

RC TableScanPhysicalOperator::open(Trx *trx)
{
  RC rc        = RC::SUCCESS;
  record_size_ = table_->table_meta().record_size() - table_->table_meta().view_select_len();
  if (alias_.empty()) {
    alias_ = table_->name();
  }

  if (is_view_) {
    rc                 = children_[0]->open(trx);
    auto field_metas_p = table_->table_meta().field_metas();
    v_tuple_.set_schema(table_, {field_metas_p->data() + 1, field_metas_p->size() - 2}, alias_);
  } else {
    rc = table_->get_record_scanner(record_scanner_, trx, mode_);
    tuple_.set_schema(table_, table_->table_meta().field_metas(), alias_);
  }

  trx_ = trx;
  return rc;
}

RC TableScanPhysicalOperator::next()
{
  RC   rc            = RC::SUCCESS;
  bool filter_result = false;

  if (is_view_) [[unlikely]] {
    while (OB_SUCC(rc = children_[0]->next())) {
      v_tuple_.update_value(children_[0]->current_tuple());

      rc = filter(&v_tuple_, filter_result);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      if (filter_result) {
        sql_debug("get a tuple: %s", v_tuple_.to_string().c_str());
        break;
      } else {
        sql_debug("a tuple is filtered: %s", v_tuple_.to_string().c_str());
      }
    }
    return rc;
  }

  while (OB_SUCC(rc = record_scanner_.next(current_record_))) {
    LOG_TRACE("got a record. rid=%s", current_record_.rid().to_string().c_str());

    tuple_.set_record(&current_record_);
    rc = filter(&tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      LOG_TRACE("record filtered failed=%s", strrc(rc));
      return rc;
    }

    if (filter_result) {
      sql_debug("get a tuple: %s", tuple_.to_string().c_str());
      break;
    } else {
      sql_debug("a tuple is filtered: %s", tuple_.to_string().c_str());
    }
  }
  return rc;
}

RC TableScanPhysicalOperator::close() { return record_scanner_.close_scan(); }

Tuple *TableScanPhysicalOperator::current_tuple()
{
  if (is_view_) [[unlikely]] {
    return &v_tuple_;
  }
  tuple_.set_record(&current_record_);
  return &tuple_;
}

string TableScanPhysicalOperator::param() const { return table_->name(); }

void TableScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC TableScanPhysicalOperator::filter(Tuple *tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
