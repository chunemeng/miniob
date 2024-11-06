#include "sql/stmt/create_view_stmt.h"
#include "sql/parser/parse.h"
#include "sql/expr/expression.h"

RC CreateViewStmt::create(Db *db, CreateViewSqlNode &create_table, Stmt *&stmt)
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

  if (create_table.select_stmt.length() <= 2) {
    return RC::INVALID_ARGUMENT;
  }
  std::string s;
  s = create_table.select_stmt.substr(2, create_table.select_stmt.length() - 2);

  ParsedSqlResult sql_node;
  parse(s.c_str(), &sql_node);

  if (sql_node.sql_nodes().size() != 1) {
    return RC::INVALID_ARGUMENT;
  }

  SelectSqlNode select      = std::move(sql_node.sql_nodes()[0]->selection);
  Stmt         *select_stmt = nullptr;
  RC            rc          = SelectStmt::create(db, select, select_stmt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  stmt = new CreateViewStmt(
      create_table.relation_name, s, static_cast<SelectStmt *>(select_stmt), create_table.alias, storage_format);
  return RC::SUCCESS;
}

StorageFormat CreateViewStmt::get_storage_format(const char *format_str)
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
