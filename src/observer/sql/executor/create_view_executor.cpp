#include "sql/executor/create_view_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "storage/db/db.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/optimizer/rewriter.h"
#include "sql/operator/insert_physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/expr/expression_tuple.h"
#include "sql/stmt/create_view_stmt.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();

  CreateViewStmt *create_table_stmt = static_cast<CreateViewStmt *>(stmt);

  std::vector<AttrInfoSqlNode> attr_infos;

  auto &exprs = create_table_stmt->select_stmt()->query_expressions();

  auto &column_names = create_table_stmt->column_names();

  if (!column_names.empty() && exprs.size() != create_table_stmt->column_names().size()) {
    LOG_ERROR("create table failed, no attributes");
    return RC::INVALID_ARGUMENT;
  }
  bool has_column_names = !column_names.empty();

  for (int i = 0; i < exprs.size(); i++) {
    AttrInfoSqlNode attr_info;
    if (has_column_names) {
      attr_info.name = column_names[i];
    } else {
      attr_info.name = exprs[i]->name();
    }
    attr_info.type     = exprs[i]->value_type();
    attr_info.length   = exprs[i]->value_length();
    attr_info.nullable = true;
    attr_infos.emplace_back(attr_info);
  }

  AttrInfoSqlNode attr_info;
  attr_info.name   = "__view_table";
  attr_info.type   = AttrType::CHARS;
  attr_info.length = create_table_stmt->select_str().length() + 1;
  attr_infos.emplace_back(attr_info);

  const char *table_name = create_table_stmt->table_name().c_str();
  RC          rc         = session->get_current_db()->create_view(
      table_name, attr_infos, create_table_stmt->select_str(), create_table_stmt->storage_format());

  if (rc != RC::SUCCESS) {
    LOG_ERROR("create table failed, table name: %s", table_name);
    return rc;
  }

  return rc;
}
