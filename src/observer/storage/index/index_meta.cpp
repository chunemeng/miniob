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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta *> &fields)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for (const FieldMeta *field : fields) {
    field_.push_back(field->name());
  }

  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  Json::Value fields_value;
  for (const auto &field : field_) {
    fields_value.append(field);
  }

  json_value[FIELD_FIELD_NAME] = std::move(fields_value);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value  = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.empty()) {
    if (!field_value.isArray()) {
      LOG_ERROR("Invalid table meta. indexes is not array, json value=%s", field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }

    const int                index_num = field_value.size();
    std::vector<std::string> fields;
    fields.reserve(index_num);
    for (int i = 0; i < index_num; i++) {
      fields.emplace_back(field_value[i].asString());
      const FieldMeta *field = table.field(fields[i].c_str());
      if (nullptr == field) {
        LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    return index.init(name_value.asCString(), fields);
  }

  return RC::INTERNAL;
}

const char *IndexMeta::name() const { return name_.c_str(); }

const std::vector<std::string> &IndexMeta::field() const { return field_; }

void IndexMeta::desc(ostream &os) const
{
  os << "index name=" << name_ << ", field=";
  for (const auto &field : field_) {
    os << field << ", ";
  }
}
RC IndexMeta::init(const char *name, vector<std::string> &fields)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  field_ = std::move(fields);
  return RC::SUCCESS;
}
