
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ComparisonExpr *create_comparison_expression(CompOp op,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ComparisonExpr *expr = new ComparisonExpr(op, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(AggrType aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(AggrType aggregate_name,
                                           std::vector<RelAttrSqlNode>* child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
    if (child == nullptr) {
           UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, nullptr);
          expr->set_name(token_name(sql_string, llocp));
          return expr;
    }

  if (child->size() == 1) {
    auto exp = new UnboundFieldExpr((*child)[0].relation_name,(*child)[0].attribute_name);
    UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, exp);
    delete child;
    expr->set_name(token_name(sql_string, llocp));
    return expr;
  } else {
      UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, nullptr);
      expr->set_name(token_name(sql_string, llocp));
      delete child;
      return expr;
  }
}

UnboundAggregateExpr *create_aggregate_expression(AggrType aggregate_name,
                                           std::vector<std::unique_ptr<Expression>>&& child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  if (child.size() == 1) {
    UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, std::move(child[0]));
    child.clear();
    expr->set_name(token_name(sql_string, llocp));
    return expr;
  } else {
      UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, nullptr);
      expr->set_name(token_name(sql_string, llocp));
      return expr;
  }
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        LBRACKET
        RBRACKET
        GROUP
        ORDER
        LIMIT
        HAVING
        UNIQUE
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        EXISTS
        NAMES
        DESC
        COLLATE
        ASC
        TYPE
        DISTANCE
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        VIEW
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        VECTOR_T
        TEXT_T
        STRING_T
        UTF8MB4_BIN
        DATE_T
        FLOAT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        WITH
        IVFFLAT
        LISTS
        PROBS
        FROM
        SUM
        AVG
        MAX
        MIN
        COUNT
        WHERE
        NOT
        IS
        LIKE
        AND
        OR
        SET
        ON
        IN
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        AS
        FORMAT
        INNER_PRODUCT
        INNER
        JOIN
        L2_DIST
        COS_DIST
        NULL_L
        NULL_T
        EQ
        LT
        GT
        LE
        GE
        NE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  InnerJoinSqlNode *                         inner_j;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<InnerJoinSqlNode> *            inner_join_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<float> *                       vec_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <expression>          condition
%type <vec_list>            v_list
%type <vec_list>            v_l
%type <number>              distance_type
%type <value>               value
%type <string>              as_opt
%type <number>              number
%type <number>              unique_op
%type <expression>          eq_expr
%type <sql_node>          as_select_opt
%type <number>              order_opt
%type <expression>          order_b
%type <expression>          vec_index_param
%type <expression_list>     vec_index_list
%type <expression_list>     order_by
%type <expression_list>     order_by_list
%type <expression_list>     assign_list
%type <relation_list>       view_field_list
%type <relation_list>       view_fields
%type <number>              null_t
%type <string>              relation
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <rel_attr_list>       rel_attr_list
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <inner_j>             inner_join
%type <inner_join_list>     inner_joins
%type <expression>          where
%type <expression>          having
%type <expression>          condition_list
%type <string>              storage_format
%type <rel_attr_list>       rel_list
%type <rel_attr_list>       rel_table_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            view_select_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            create_view_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-' AS ID
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | create_view_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;
unique_op:
    UNIQUE {
      $$ = 1;
    }
    | /* empty */
    {
      $$ = 0;
    }
    ;

    distance_type:
    L2_DIST {
      $$ = 1;
    }
        | INNER_PRODUCT {
          $$ = 2;
        }
    | COS_DIST {
      $$ = 3;
    }

    ;

vec_index_param:
    DISTANCE EQ  distance_type{
    Value val((int)($3));
                Value valf((int)3);

      $$ = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &@$);
    }
    | LISTS EQ number {
        Value val((int)($3));
            Value valf((int)1);
        $$ = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &@$);
    }
    | PROBS EQ number {
       Value val((int)($3));
        Value valf((int)2);
        $$ = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &@$);
    }
    | TYPE EQ IVFFLAT {
        Value valf((int)4);
        Value val((int)(1));
        $$ = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &@$);
    }
    ;

    vec_index_list:
    vec_index_param {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | vec_index_param COMMA vec_index_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    ;

view_fields:
    ID {
      $$ = new std::vector<std::string>();
        $$->insert($$->begin(), $1);
      free($1);
    }
    | ID COMMA view_fields {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->insert($$->begin(), $1);
      free($1);
    }
    ;

view_field_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | LBRACE view_fields RBRACE {
      $$ = $2;
    }
    ;


view_select_stmt:
    AS select_stmt {
          delete $2;
          $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
          $$->create_view.select_stmt = std::move(token_name(sql_string, &@$));
    }
    ;

create_view_stmt:
    CREATE VIEW ID view_field_list view_select_stmt storage_format{
        $$ = $5;
        $$->create_view.relation_name = $3;
        if ($4 != nullptr) {
            $$->create_view.alias.swap(*$4);
            delete $4;
        }
        if ($6 != nullptr) {
          $$->create_view.storage_format = $6;
          free($6);
        }
        free($3);
    };

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE vec_index_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = false;
      create_index.is_vector = true;
      create_index.attribute_list = std::move(*$8);
      create_index.expressions = std::move(*$12);
      free($4);
      free($6);
      delete($8);
      delete($12);
    }

    | CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = $2;
      create_index.attribute_list = std::move(*$8);
      free($4);
      free($6);
      delete($8);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
as_select_opt:
    select_stmt {
      $$ = $1;
    }
    | AS select_stmt {
      $$ = $2;
    }
    | /* empty */
    {
      $$ = nullptr;
    }
    ;

create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format
    {
        LOG_INFO("%s",token_name(sql_string, &@$).c_str());
      auto node = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = node->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.select = std::make_unique<SelectSqlNode>(std::move(($8->selection)));
        delete $8;
      }

      $$ = node;

      if ($9 != nullptr) {
        create_table.storage_format = $9;
        free($9);
      }
    }
    |CREATE TABLE ID as_select_opt storage_format
     {
       auto node = new ParsedSqlNode(SCF_CREATE_TABLE);
       CreateTableSqlNode &create_table = node->create_table;
       create_table.relation_name = $3;
       free($3);

       if ($4 != nullptr) {
         create_table.select = std::make_unique<SelectSqlNode>(std::move(($4->selection)));
         delete $4;
       }

       $$ = node;

       if ($5 != nullptr) {
         create_table.storage_format = $5;
         free($5);
       }
     }

    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE null_t
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if ($$->type == AttrType::VECTORS) {
         $$->length = $4 * sizeof(float);
         if ($$->length > BP_PAGE_DATA_SIZE) {
            $$->type = AttrType::HIGH_DIMS;
            $$->length = $4;
         }
      } else {
            $$->length = ($4);
      }


      $$->nullable = $6;
      free($1);
    }
    | ID type null_t
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if ($$->type == AttrType::TEXTS) {
        $$->length = ((65535 + BP_PAGE_DATA_SIZE - 1) / BP_PAGE_DATA_SIZE + 1) * sizeof(int);
      } else {
            $$->length = 4;
      }

      $$->nullable = $3;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
null_t:
    /* empty */
    {
      $$ = 0;
    }
    | NULL_L
    {
      $$ = 1;
    }
    | NULL_T
    {
      $$ = 1;
    }
    | NOT NULL_T
    {
      $$ = 0;
    }
    | NOT NULL_L
    {
      $$ = 0;
    }
    ;

type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATES); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | TEXT_T   { $$ = static_cast<int>(AttrType::TEXTS); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID view_field_list VALUES LBRACE value value_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;

      if ($4 != nullptr) {
        $$->insertion.columns.swap(*$4);
        delete $4;
      }

      if ($8 != nullptr) {
        $$->insertion.values.swap(*$8);
        delete $8;
      }
      $$->insertion.values.emplace_back(*$7);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $7;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    | '-' NUMBER {
      $$ = new Value((int)-$2);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    | '-' FLOAT {
      $$ = new Value((float)-$2);
      @$ = @1;
    }
    | NULL_T {
        $$ = new Value();
        $$->set_null();
        @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | v_list {
      std::reverse($1->begin(), $1->end());
      $$ = new Value(*$1);

      delete $1;
    }
    ;
    v_list:
    LBRACKET v_l RBRACKET {
      $$ = $2;
    }
    ;
    v_l:
    FLOAT COMMA v_l {
      $$ = $3;
      $$->push_back($1);
    }
    | FLOAT {
      $$ = new std::vector<float>;
      $$->push_back($1);
    }
    | NUMBER {
      $$ = new std::vector<float>;
      $$->push_back($1);
    }
    | NUMBER COMMA v_l {
      $$ = $3;
      $$->push_back($1);
    }
    ;


storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions = $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET assign_list where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.expressions = std::move(*$4);
      if ($5 != nullptr) {
        $$->update.conditions  = $5 ;
      }
      delete $4;
      free($2);
    }
    ;

  order_opt:
    ASC {
      $$ = 0;
    }
    | DESC {
      $$ = 1;
    }
    | /* empty */
    {
      $$ = 0;
    }
    ;


order_b:
    rel_attr order_opt
    {
      $$ = new OrderByExpr($1->relation_name, $1->attribute_name, $2);
      delete $1;
    }
    | distance_type LBRACE expression COMMA expression RBRACE LIMIT number
    {
      $$ = new VecOrderByExpr($3,$5,$1, $8);
    }
    ;

order_by:
    order_b
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | order_b COMMA order_by
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->insert($$->begin(),std::unique_ptr<Expression>($1));
    }
    ;

order_by_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by
    {
      $$ = $3;
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if ($5 != nullptr) {
        $$->selection.inner_joins.swap(*$5);
        std::reverse($$->selection.inner_joins.begin(),$$->selection.inner_joins.end());
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.conditions = $6;
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }

      if ($8 != nullptr) {
        $$->selection.having_cond = $8;
      }

      if ($9 != nullptr) {
        $$->selection.order_bys.swap(*$9);
        delete $9;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;
    assign_list:
    eq_expr COMMA assign_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    | eq_expr
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    ;

expression_list:
    expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    | expression
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    ;
as_opt:
    /* empty */
    {
      $$ = nullptr;
    }
    | AS ID
    {
      $$ = $2;
    }
    | ID
    {
      $$ = $1;
    }
    ;

expression:
    rel_attr  {
                RelAttrSqlNode *node = $1;
                UnboundFieldExpr * ex = new UnboundFieldExpr(node->relation_name, node->attribute_name);



                ex->set_name(token_name(sql_string, &@$));


                $$ = ex;
                delete $1;
              }

    | expression ID {
            $$ = $1;
             if ($$->type() == ExprType::UNBOUND_FIELD)    {
                auto ex = dynamic_cast<UnboundFieldExpr*>($$);
                 ex->set_alias(true);
             }
            $$->set_name($2);
            free($2);
    }
   | expression AS ID {
            $$ = $1;
            if ($$->type() == ExprType::UNBOUND_FIELD)    {
                            auto ex = dynamic_cast<UnboundFieldExpr*>($$);

                             ex->set_alias(true);
            }
            $$->set_name($3);
            free($3);
    }
    | expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | L2_DIST LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, $3, $5, sql_string, &@$);
    }
    | COS_DIST LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, $3, $5, sql_string, &@$);
    }

    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, $3, $5, sql_string, &@$);
    }

    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }

    | LBRACE select_stmt RBRACE {
       $$ = new SubQueryExpr(std::move($2->selection));
       delete $2;
    }
    | LBRACE expression_list RBRACE {
       $$ = new ValueListExpr(std::move(*$2));
       delete $2;
    }
    | ID DOT '*' {
      $$ = new StarExpr($1);
      free($1);
    }
    | '*' {
      $$ = new StarExpr();
    }
    | COUNT LBRACE rel_attr_list RBRACE {
      $$ = create_aggregate_expression(AggrType::COUNT, $3, sql_string, &@$);
    }
    | SUM LBRACE rel_attr_list RBRACE {
      $$ = create_aggregate_expression(AggrType::SUM, $3, sql_string, &@$);
    }
    | AVG LBRACE rel_attr_list RBRACE {
      $$ = create_aggregate_expression(AggrType::AVG, $3, sql_string, &@$);
    }
    | MAX LBRACE rel_attr_list RBRACE {
      $$ = create_aggregate_expression(AggrType::MAX, $3, sql_string, &@$);
    }
    | MIN LBRACE rel_attr_list RBRACE {
      $$ = create_aggregate_expression(AggrType::MIN, $3, sql_string, &@$);
    }
    | COUNT LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression(AggrType::COUNT, std::move(*$3), sql_string, &@$);
      delete $3;
    }
    | SUM LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression(AggrType::SUM, std::move(*$3), sql_string, &@$);
      delete $3;
    }
    | AVG LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression(AggrType::AVG, std::move(*$3), sql_string, &@$);
      delete $3;
    }
    | MAX LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression(AggrType::MAX, std::move(*$3), sql_string, &@$);
      delete $3;
    }
    | MIN LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression(AggrType::MIN, std::move(*$3), sql_string, &@$);
      delete $3;
    }


    // your code here
    ;

inner_joins:
    /* empty */
    {
      $$ = nullptr;
    }
    | inner_join inner_joins {
      if ($2 != nullptr) {
         $$ = $2;
      } else {
         $$ = new std::vector<InnerJoinSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
inner_join:
    INNER JOIN ID as_opt ON condition_list {
      $$ = new InnerJoinSqlNode();
      RelAttrSqlNode node;
      if ($4 != nullptr) {
        node.attribute_name = $4;
        node.relation_name = $3;
        free($4);
      } else {
        node.relation_name = $3;
      }
        $$->table_name = node;
      $$->conditions = $6;
      free($3);
    }
    | INNER JOIN ID as_opt {
      $$ = new InnerJoinSqlNode();
        RelAttrSqlNode node;
        if ($4 != nullptr) {
          node.attribute_name = $4;
          node.relation_name = $3;
          free($4);
        } else {
          node.relation_name = $3;
        }

      $$->table_name = node;
      free($3);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

rel_attr_list:
    /* empty */
    {
       $$ = nullptr;
    }
    | rel_attr {
      $$ = new std::vector<RelAttrSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | rel_attr COMMA rel_attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;

rel_table_list:
    relation as_opt {
      $$ = new std::vector<RelAttrSqlNode>();
      if ($2 != nullptr) {
        RelAttrSqlNode node;
        node.relation_name = $1;
        node.attribute_name = $2;
        $$->push_back(node);
        free($2);
      } else {
        RelAttrSqlNode node;
        node.relation_name = $1;
        $$->push_back(node);
      }
      free($1);
    }
    | relation as_opt COMMA rel_table_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<RelAttrSqlNode>();
      }
      if ($2 != nullptr) {
        RelAttrSqlNode node;
        node.relation_name = $1;
        node.attribute_name = $2;
        $$->insert($$->begin(), node);
        free($2);
      } else {
        RelAttrSqlNode node;
        node.relation_name = $1;
        $$->insert($$->begin(), node);
      }
      free($1);
    }
    ;


rel_list:
    relation {
      $$ = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = $1;
        $$->push_back(node);

      free($1);
    }
    | relation COMMA rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>();
      }

        RelAttrSqlNode node;
        node.attribute_name = $1;
        $$->insert($$->begin(), node);

      free($1);
    }
    ;
having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list {
      $$ = $2;
    }
    ;


where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = $1;
    }
    | condition AND condition_list {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back($1);
      tmp.emplace_back($3);
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
    | condition OR condition_list {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back($1);
      tmp.emplace_back($3);
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }

    ;
eq_expr:
    expression EQ expression
    {
      $$ = create_comparison_expression(EQUAL_TO, $1, $3, sql_string, &@$);
    }
    ;

condition:
    expression comp_op expression
    {
      $$ = create_comparison_expression($2, $1, $3, sql_string, &@$);
    }
    | EXISTS expression
    {
      $$ = create_comparison_expression(EXISTS_C, $2, nullptr, sql_string, &@$);
    }
    | NOT EXISTS expression
    {
      $$ = create_comparison_expression(NOT_EXISTS, $3, nullptr, sql_string, &@$);
    }
    | eq_expr
    {
      $$ = $1;
    }
    ;

comp_op:
    LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS NOT {$$ = IS_NOT_C;}
    | IS { $$ = IS_C;}
    | NOT LIKE  { $$ = NOT_LIKE; }
    | LIKE { $$ = LIKE_OP; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN; }
    ;

group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list {
      $$ = $3;
    }
    ;
load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    |SET NAMES SSS
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name = "NAMES";
      $$->set_variable.value = Value($3);
      free($3);
    }
    | SET NAMES UTF8MB4_BIN
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name = "NAMES";
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
