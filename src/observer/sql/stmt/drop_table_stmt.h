#pragma once

#include "sql/stmt/stmt.h"

/**
 * @brief Exit 语句，表示断开连接，现在什么成员都没有
 * @ingroup Statement
 */
class DropTableStmt : public Stmt
{
public:
  DropTableStmt(const std::string &table_name) : table_name_(table_name) {}
  virtual ~DropTableStmt() = default;

  StmtType type() const override { return StmtType::DROP_TABLE; }

  const std::string &table_name() const { return table_name_; }

  static RC create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt);

private:
  std::string                  table_name_;
  std::vector<AttrInfoSqlNode> attr_infos_;
};