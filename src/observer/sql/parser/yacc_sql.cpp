/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 178 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_LBRACKET = 7,                   /* LBRACKET  */
  YYSYMBOL_RBRACKET = 8,                   /* RBRACKET  */
  YYSYMBOL_GROUP = 9,                      /* GROUP  */
  YYSYMBOL_ORDER = 10,                     /* ORDER  */
  YYSYMBOL_LIMIT = 11,                     /* LIMIT  */
  YYSYMBOL_HAVING = 12,                    /* HAVING  */
  YYSYMBOL_UNIQUE = 13,                    /* UNIQUE  */
  YYSYMBOL_TABLE = 14,                     /* TABLE  */
  YYSYMBOL_TABLES = 15,                    /* TABLES  */
  YYSYMBOL_INDEX = 16,                     /* INDEX  */
  YYSYMBOL_CALC = 17,                      /* CALC  */
  YYSYMBOL_SELECT = 18,                    /* SELECT  */
  YYSYMBOL_EXISTS = 19,                    /* EXISTS  */
  YYSYMBOL_NAMES = 20,                     /* NAMES  */
  YYSYMBOL_DESC = 21,                      /* DESC  */
  YYSYMBOL_COLLATE = 22,                   /* COLLATE  */
  YYSYMBOL_ASC = 23,                       /* ASC  */
  YYSYMBOL_TYPE = 24,                      /* TYPE  */
  YYSYMBOL_DISTANCE = 25,                  /* DISTANCE  */
  YYSYMBOL_SHOW = 26,                      /* SHOW  */
  YYSYMBOL_SYNC = 27,                      /* SYNC  */
  YYSYMBOL_INSERT = 28,                    /* INSERT  */
  YYSYMBOL_DELETE = 29,                    /* DELETE  */
  YYSYMBOL_UPDATE = 30,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 31,                    /* LBRACE  */
  YYSYMBOL_VIEW = 32,                      /* VIEW  */
  YYSYMBOL_RBRACE = 33,                    /* RBRACE  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 35,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 36,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 37,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 38,                     /* INT_T  */
  YYSYMBOL_VECTOR_T = 39,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 40,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 41,                  /* STRING_T  */
  YYSYMBOL_UTF8MB4_BIN = 42,               /* UTF8MB4_BIN  */
  YYSYMBOL_DATE_T = 43,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 44,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 45,                      /* HELP  */
  YYSYMBOL_EXIT = 46,                      /* EXIT  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_INTO = 48,                      /* INTO  */
  YYSYMBOL_VALUES = 49,                    /* VALUES  */
  YYSYMBOL_WITH = 50,                      /* WITH  */
  YYSYMBOL_IVFFLAT = 51,                   /* IVFFLAT  */
  YYSYMBOL_LISTS = 52,                     /* LISTS  */
  YYSYMBOL_PROBS = 53,                     /* PROBS  */
  YYSYMBOL_FROM = 54,                      /* FROM  */
  YYSYMBOL_SUM = 55,                       /* SUM  */
  YYSYMBOL_AVG = 56,                       /* AVG  */
  YYSYMBOL_MAX = 57,                       /* MAX  */
  YYSYMBOL_MIN = 58,                       /* MIN  */
  YYSYMBOL_COUNT = 59,                     /* COUNT  */
  YYSYMBOL_WHERE = 60,                     /* WHERE  */
  YYSYMBOL_NOT = 61,                       /* NOT  */
  YYSYMBOL_IS = 62,                        /* IS  */
  YYSYMBOL_LIKE = 63,                      /* LIKE  */
  YYSYMBOL_AND = 64,                       /* AND  */
  YYSYMBOL_OR = 65,                        /* OR  */
  YYSYMBOL_SET = 66,                       /* SET  */
  YYSYMBOL_ON = 67,                        /* ON  */
  YYSYMBOL_IN = 68,                        /* IN  */
  YYSYMBOL_LOAD = 69,                      /* LOAD  */
  YYSYMBOL_DATA = 70,                      /* DATA  */
  YYSYMBOL_INFILE = 71,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 72,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 73,                   /* STORAGE  */
  YYSYMBOL_AS = 74,                        /* AS  */
  YYSYMBOL_FORMAT = 75,                    /* FORMAT  */
  YYSYMBOL_INNER_PRODUCT = 76,             /* INNER_PRODUCT  */
  YYSYMBOL_INNER = 77,                     /* INNER  */
  YYSYMBOL_JOIN = 78,                      /* JOIN  */
  YYSYMBOL_L2_DIST = 79,                   /* L2_DIST  */
  YYSYMBOL_COS_DIST = 80,                  /* COS_DIST  */
  YYSYMBOL_NULL_L = 81,                    /* NULL_L  */
  YYSYMBOL_NULL_T = 82,                    /* NULL_T  */
  YYSYMBOL_EQ = 83,                        /* EQ  */
  YYSYMBOL_LT = 84,                        /* LT  */
  YYSYMBOL_GT = 85,                        /* GT  */
  YYSYMBOL_LE = 86,                        /* LE  */
  YYSYMBOL_GE = 87,                        /* GE  */
  YYSYMBOL_NE = 88,                        /* NE  */
  YYSYMBOL_NUMBER = 89,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 90,                     /* FLOAT  */
  YYSYMBOL_ID = 91,                        /* ID  */
  YYSYMBOL_SSS = 92,                       /* SSS  */
  YYSYMBOL_93_ = 93,                       /* '+'  */
  YYSYMBOL_94_ = 94,                       /* '-'  */
  YYSYMBOL_95_ = 95,                       /* '*'  */
  YYSYMBOL_96_ = 96,                       /* '/'  */
  YYSYMBOL_UMINUS = 97,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_commands = 99,                  /* commands  */
  YYSYMBOL_command_wrapper = 100,          /* command_wrapper  */
  YYSYMBOL_exit_stmt = 101,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 102,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 103,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 104,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 105,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 106,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 107,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 108,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 109,          /* desc_table_stmt  */
  YYSYMBOL_unique_op = 110,                /* unique_op  */
  YYSYMBOL_distance_type = 111,            /* distance_type  */
  YYSYMBOL_vec_index_param = 112,          /* vec_index_param  */
  YYSYMBOL_vec_index_list = 113,           /* vec_index_list  */
  YYSYMBOL_view_fields = 114,              /* view_fields  */
  YYSYMBOL_view_field_list = 115,          /* view_field_list  */
  YYSYMBOL_view_select_stmt = 116,         /* view_select_stmt  */
  YYSYMBOL_create_view_stmt = 117,         /* create_view_stmt  */
  YYSYMBOL_create_index_stmt = 118,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 119,          /* drop_index_stmt  */
  YYSYMBOL_as_select_opt = 120,            /* as_select_opt  */
  YYSYMBOL_create_table_stmt = 121,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 122,            /* attr_def_list  */
  YYSYMBOL_attr_def = 123,                 /* attr_def  */
  YYSYMBOL_number = 124,                   /* number  */
  YYSYMBOL_null_t = 125,                   /* null_t  */
  YYSYMBOL_type = 126,                     /* type  */
  YYSYMBOL_insert_stmt = 127,              /* insert_stmt  */
  YYSYMBOL_value_list = 128,               /* value_list  */
  YYSYMBOL_value = 129,                    /* value  */
  YYSYMBOL_v_list = 130,                   /* v_list  */
  YYSYMBOL_v_l = 131,                      /* v_l  */
  YYSYMBOL_storage_format = 132,           /* storage_format  */
  YYSYMBOL_delete_stmt = 133,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 134,              /* update_stmt  */
  YYSYMBOL_order_opt = 135,                /* order_opt  */
  YYSYMBOL_order_b = 136,                  /* order_b  */
  YYSYMBOL_order_by = 137,                 /* order_by  */
  YYSYMBOL_order_by_list = 138,            /* order_by_list  */
  YYSYMBOL_select_stmt = 139,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 140,                /* calc_stmt  */
  YYSYMBOL_assign_list = 141,              /* assign_list  */
  YYSYMBOL_expression_list = 142,          /* expression_list  */
  YYSYMBOL_as_opt = 143,                   /* as_opt  */
  YYSYMBOL_expression = 144,               /* expression  */
  YYSYMBOL_inner_joins = 145,              /* inner_joins  */
  YYSYMBOL_inner_join = 146,               /* inner_join  */
  YYSYMBOL_rel_attr = 147,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 148,            /* rel_attr_list  */
  YYSYMBOL_relation = 149,                 /* relation  */
  YYSYMBOL_rel_table_list = 150,           /* rel_table_list  */
  YYSYMBOL_rel_list = 151,                 /* rel_list  */
  YYSYMBOL_having = 152,                   /* having  */
  YYSYMBOL_where = 153,                    /* where  */
  YYSYMBOL_condition_list = 154,           /* condition_list  */
  YYSYMBOL_eq_expr = 155,                  /* eq_expr  */
  YYSYMBOL_condition = 156,                /* condition  */
  YYSYMBOL_comp_op = 157,                  /* comp_op  */
  YYSYMBOL_group_by = 158,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 159,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 160,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 161,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 162             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   459

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  184
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  362

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    95,    93,     2,    94,     2,    96,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    97
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   307,   307,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   339,   345,   350,   356,   362,   368,
     374,   381,   387,   394,   398,   404,   407,   410,   417,   423,
     428,   433,   441,   445,   456,   461,   474,   477,   484,   492,
     507,   523,   538,   548,   551,   555,   561,   590,   613,   616,
     629,   648,   664,   668,   671,   675,   679,   683,   690,   691,
     692,   693,   694,   695,   698,   715,   718,   729,   733,   737,
     741,   745,   750,   756,   764,   769,   773,   777,   781,   790,
     793,   800,   811,   825,   828,   832,   839,   844,   851,   856,
     869,   872,   879,   918,   926,   935,   943,   952,   960,   963,
     967,   974,   987,   996,  1006,  1009,  1012,  1015,  1018,  1021,
    1025,  1029,  1033,  1036,  1042,  1046,  1050,  1054,  1057,  1060,
    1063,  1066,  1069,  1072,  1076,  1080,  1084,  1088,  1099,  1102,
    1113,  1127,  1144,  1149,  1160,  1163,  1168,  1180,  1186,  1201,
    1224,  1233,  1249,  1252,  1260,  1263,  1269,  1272,  1275,  1281,
    1290,  1297,  1301,  1305,  1309,  1316,  1317,  1318,  1319,  1320,
    1321,  1322,  1323,  1324,  1325,  1326,  1331,  1334,  1339,  1352,
    1360,  1368,  1375,  1382,  1383
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "LBRACKET", "RBRACKET", "GROUP", "ORDER", "LIMIT",
  "HAVING", "UNIQUE", "TABLE", "TABLES", "INDEX", "CALC", "SELECT",
  "EXISTS", "NAMES", "DESC", "COLLATE", "ASC", "TYPE", "DISTANCE", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "VIEW", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "VECTOR_T",
  "TEXT_T", "STRING_T", "UTF8MB4_BIN", "DATE_T", "FLOAT_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "WITH", "IVFFLAT", "LISTS", "PROBS", "FROM",
  "SUM", "AVG", "MAX", "MIN", "COUNT", "WHERE", "NOT", "IS", "LIKE", "AND",
  "OR", "SET", "ON", "IN", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE",
  "AS", "FORMAT", "INNER_PRODUCT", "INNER", "JOIN", "L2_DIST", "COS_DIST",
  "NULL_L", "NULL_T", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER",
  "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "unique_op", "distance_type",
  "vec_index_param", "vec_index_list", "view_fields", "view_field_list",
  "view_select_stmt", "create_view_stmt", "create_index_stmt",
  "drop_index_stmt", "as_select_opt", "create_table_stmt", "attr_def_list",
  "attr_def", "number", "null_t", "type", "insert_stmt", "value_list",
  "value", "v_list", "v_l", "storage_format", "delete_stmt", "update_stmt",
  "order_opt", "order_b", "order_by", "order_by_list", "select_stmt",
  "calc_stmt", "assign_list", "expression_list", "as_opt", "expression",
  "inner_joins", "inner_join", "rel_attr", "rel_attr_list", "relation",
  "rel_table_list", "rel_list", "having", "where", "condition_list",
  "eq_expr", "condition", "comp_op", "group_by", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-307)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     305,    35,    57,   183,   183,   -61,    23,  -307,    24,    38,
      26,  -307,  -307,  -307,  -307,  -307,   -14,    43,   305,   118,
     116,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,    31,    33,   109,   110,    36,    41,   -32,
     136,    97,    98,   102,   103,   114,   115,   119,   120,  -307,
    -307,  -307,    93,  -307,   226,  -307,  -307,  -307,  -307,   285,
    -307,    88,  -307,  -307,    61,    62,    89,   -27,    75,    92,
    -307,  -307,  -307,  -307,    -5,   137,    82,    85,  -307,   112,
     143,   150,   178,   154,   155,    87,   183,   183,   183,   183,
     183,   183,   183,   183,   -52,  -307,  -307,  -307,   183,   105,
    -307,   183,   183,   183,   183,   106,   140,   139,   183,  -307,
    -307,    18,   108,   122,   185,   128,  -307,   126,   145,   144,
     153,   130,   -32,   -32,  -307,  -307,  -307,  -307,   190,   195,
     191,   199,   201,   203,   204,   210,   211,   212,   213,   294,
     309,   318,  -307,  -307,  -307,  -307,   -13,   -13,  -307,  -307,
    -307,   -41,   170,   217,    80,  -307,   139,   175,   216,     1,
    -307,   205,   355,   218,  -307,   179,  -307,   222,   227,   185,
     128,   176,   188,  -307,  -307,  -307,  -307,   189,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,   183,   183,   183,
     196,  -307,   242,   214,   139,   170,    18,   183,   269,   363,
    -307,  -307,    37,  -307,   183,   183,  -307,  -307,   247,  -307,
    -307,  -307,  -307,  -307,  -307,    -2,   122,   257,   208,   126,
    -307,  -307,  -307,   263,   265,   246,   195,  -307,   111,   253,
     262,  -307,   106,   206,   289,  -307,   266,   345,   183,   -26,
     238,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   183,    80,
      80,   345,  -307,   221,   220,    22,  -307,  -307,  -307,   218,
       4,   223,  -307,   106,   106,   233,  -307,  -307,  -307,  -307,
     -41,   299,   301,    18,   292,   345,  -307,  -307,  -307,   345,
    -307,  -307,  -307,  -307,   296,  -307,  -307,  -307,   128,  -307,
     303,   297,   306,   287,   183,    80,   328,   266,  -307,   -37,
    -307,   106,   310,  -307,    80,  -307,  -307,   359,  -307,  -307,
    -307,  -307,   338,  -307,   -45,     3,  -307,  -307,  -307,   339,
     341,  -307,    65,   290,   308,   314,   323,   348,   351,   183,
     -45,  -307,  -307,  -307,   321,     5,   220,   220,     3,  -307,
     327,  -307,  -307,  -307,  -307,  -307,  -307,   183,   271,   375,
     220,  -307
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     183,    23,    22,    14,    16,    17,    18,     9,    10,    11,
      15,    12,    13,     8,     5,     7,     6,     4,     3,    19,
      20,    21,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      77,    79,   142,    82,     0,   127,   123,    83,   103,   107,
     111,     0,    32,    31,     0,     0,     0,     0,     0,     0,
     179,     1,   184,     2,    55,    46,     0,     0,    30,     0,
      87,    86,     0,     0,     0,     0,   144,   144,   144,   144,
     144,     0,     0,     0,     0,    77,    79,   122,     0,     0,
     112,     0,     0,     0,     0,     0,     0,   154,     0,   182,
     181,     0,     0,     0,     0,    89,    53,     0,     0,     0,
       0,     0,     0,     0,    84,   124,   125,   121,     0,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   126,   106,   113,   114,   115,   116,   117,
     147,   108,   138,     0,   156,    91,   154,     0,   105,     0,
     180,     0,     0,    58,    54,     0,    57,    44,     0,     0,
      89,     0,     0,    52,    88,    85,   134,   144,   129,   135,
     130,   136,   131,   137,   132,   133,   128,     0,     0,     0,
       0,   110,   148,     0,   154,   138,     0,     0,     0,     0,
     155,   164,   157,    92,     0,     0,    78,    80,     0,    68,
      72,    73,    69,    70,    71,    63,     0,     0,     0,     0,
      47,    48,    49,     0,     0,   142,   145,   146,     0,     0,
       0,   109,     0,     0,   176,   139,    75,   162,     0,     0,
     171,   173,   174,   165,   166,   167,   168,   169,     0,   156,
     156,   160,   104,     0,     0,     0,    64,    65,    61,    58,
      55,     0,    45,     0,     0,     0,   120,   118,   119,   149,
     108,     0,   152,     0,     0,   163,   172,   175,   170,   161,
     158,   159,   178,    62,     0,    67,    66,    59,    89,    90,
     150,     0,     0,   141,     0,   156,   100,    75,    74,    63,
      56,     0,     0,    51,   156,   177,   153,     0,   102,    76,
      60,   151,     0,   140,     0,     0,    36,    35,    37,     0,
      98,   101,    95,     0,     0,     0,     0,    42,     0,     0,
       0,    94,    93,    96,     0,     0,     0,     0,     0,    50,
       0,    99,    41,    38,    39,    40,    43,     0,     0,     0,
       0,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,   389,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,    63,  -307,    67,   181,  -307,  -307,  -307,
    -307,  -307,   146,  -307,   148,   202,  -306,   121,  -307,  -307,
     125,  -117,  -307,   -17,  -175,  -307,  -307,  -307,  -307,    94,
    -307,   -48,  -307,   228,    -3,   147,   -50,   224,  -307,   -89,
     -81,  -112,   193,  -251,  -307,  -134,  -239,  -106,  -307,  -307,
    -307,  -307,  -307,  -307,  -307
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    46,   329,   337,   338,   178,   128,   180,    30,
      31,    32,   125,    33,   227,   173,   294,   268,   225,    34,
     284,    66,    67,    92,   176,    35,    36,   343,   330,   331,
     318,    37,    38,   166,    68,   202,    69,   204,   205,    70,
     140,   300,   162,   301,   306,   165,   210,   211,   212,   258,
     282,    39,    40,    41,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      95,    71,    93,   161,   170,   232,    77,   139,   139,   139,
     139,   139,   168,     4,   107,   119,   142,   144,   146,   148,
     290,   291,     4,   302,   265,    49,   123,   333,   334,   264,
      72,   326,   213,   200,   327,   328,   126,   286,    73,   152,
     354,   355,   287,   153,   266,   267,   235,    94,    42,    43,
     201,   149,   150,   151,   361,   335,   336,    90,    91,   265,
     321,   156,   157,   158,   159,   120,   316,    44,   167,   124,
     244,    47,    74,    48,    45,   323,   174,    78,   124,   266,
     267,   326,   113,   114,   327,   328,   341,    49,   342,   246,
     216,   217,    75,   138,   141,   143,   145,   147,   236,   207,
      59,   259,   260,   295,   296,   154,   237,    60,    61,   168,
      63,    50,   169,    79,   209,   184,   185,    76,    81,    82,
     137,   108,    84,   310,    85,    86,    87,    88,    96,    97,
     161,   231,    89,    98,    99,    51,    52,    53,    54,    55,
     104,   208,   115,    49,   276,   100,   101,   238,   239,   240,
     102,   103,   116,   117,     4,   118,    56,   247,   121,    57,
      58,   109,    59,   122,   261,   167,   307,    50,   127,    60,
      61,    62,    63,   129,    64,    65,   130,   132,   110,   131,
     111,   112,   113,   114,   133,   109,   134,   135,   136,   163,
      49,    51,    52,    53,    54,    55,   155,   160,   285,   164,
     171,   175,   110,     4,   111,   112,   113,   114,   289,   209,
     209,   181,    56,   172,    50,    57,    58,   177,    59,   179,
     182,   183,   126,   186,   188,    60,    61,    62,    63,   187,
      64,    65,   189,    49,   190,   332,   191,   192,    51,    52,
      53,    54,    55,   193,   194,   195,   196,   203,   206,   109,
     215,   332,   226,   218,   228,   209,   229,    50,   214,    56,
     230,   263,    57,    58,   209,    59,   110,   233,   111,   112,
     113,   114,    60,    61,    62,    63,   242,    64,    65,   234,
     235,    51,    52,    53,    54,    55,   277,   241,   248,   350,
     270,   271,   243,   275,   273,   278,   274,   280,   281,   288,
     283,   315,    56,   304,   359,    57,    58,   358,    59,   293,
       1,     2,   292,   305,   299,   105,   106,    62,    63,   108,
      64,    65,     3,     4,   152,   308,     5,   109,   197,   309,
     312,     6,     7,     8,     9,    10,   109,   311,   317,   313,
      11,    12,    13,   198,   110,   109,   111,   112,   113,   114,
      14,    15,   199,   110,   314,   111,   112,   113,   114,   109,
     322,   357,   110,   324,   111,   112,   113,   114,   109,   325,
     339,    16,   352,   344,    17,   340,   110,    18,   111,   112,
     113,   114,   348,   109,   349,   110,   360,   111,   112,   113,
     114,   345,   109,   219,   220,   221,   222,   346,   223,   224,
     110,   109,   111,   112,   113,   114,   347,    80,   353,   110,
     272,   111,   112,   113,   114,   356,   298,   297,   110,   109,
     111,   112,   113,   114,   249,   250,   251,   303,   269,   245,
     320,   252,   319,     0,   351,   279,   110,   109,   111,   112,
     113,   114,     0,   262,     0,     0,   214,   253,   254,   255,
     256,   257,     0,     0,   110,     0,   111,   112,   113,   114
};

static const yytype_int16 yycheck[] =
{
      50,     4,    50,   115,   121,   180,    20,    96,    97,    98,
      99,   100,   118,    18,    64,    42,    97,    98,    99,   100,
     259,   260,    18,   274,    61,     7,    31,    24,    25,    31,
      91,    76,   166,    74,    79,    80,    84,    63,    15,    91,
     346,   347,    68,    95,    81,    82,    91,    50,    13,    14,
      91,   101,   102,   103,   360,    52,    53,    89,    90,    61,
     311,   111,   112,   113,   114,    92,   305,    32,   118,    74,
     204,    14,    48,    16,    39,   314,   124,    91,    74,    81,
      82,    76,    95,    96,    79,    80,    21,     7,    23,   206,
      89,    90,    54,    96,    97,    98,    99,   100,   187,    19,
      82,    64,    65,    81,    82,   108,   187,    89,    90,   215,
      92,    31,    94,    70,   164,   132,   133,    91,     0,     3,
      33,    34,    91,   298,    91,    16,    16,    91,    31,    31,
     242,   179,    91,    31,    31,    55,    56,    57,    58,    59,
      47,    61,    54,     7,    33,    31,    31,   197,   198,   199,
      31,    31,    91,    91,    18,    66,    76,   207,    83,    79,
      80,    74,    82,    71,   214,   215,   283,    31,    31,    89,
      90,    91,    92,    91,    94,    95,    91,    34,    91,    67,
      93,    94,    95,    96,    34,    74,     8,    33,    33,    49,
       7,    55,    56,    57,    58,    59,    91,    91,   248,    60,
      92,    73,    91,    18,    93,    94,    95,    96,   258,   259,
     260,    67,    76,    91,    31,    79,    80,    91,    82,    74,
      67,    91,   270,    33,    33,    89,    90,    91,    92,    34,
      94,    95,    33,     7,    33,   324,    33,    33,    55,    56,
      57,    58,    59,    33,    33,    33,    33,    77,    31,    74,
      34,   340,    34,    48,    75,   305,    34,    31,    83,    76,
      33,    14,    79,    80,   314,    82,    91,    91,    93,    94,
      95,    96,    89,    90,    91,    92,    34,    94,    95,    91,
      91,    55,    56,    57,    58,    59,    33,    91,    19,   339,
      33,    83,    78,    47,    31,    33,    31,    91,     9,    61,
      34,   304,    76,     4,    33,    79,    80,   357,    82,    89,
       5,     6,    91,    12,    91,    89,    90,    91,    92,    34,
      94,    95,    17,    18,    91,    33,    21,    74,    34,    33,
      33,    26,    27,    28,    29,    30,    74,    34,    10,    33,
      35,    36,    37,    34,    91,    74,    93,    94,    95,    96,
      45,    46,    34,    91,    67,    93,    94,    95,    96,    74,
      50,    34,    91,     4,    93,    94,    95,    96,    74,    31,
      31,    66,    51,    83,    69,    34,    91,    72,    93,    94,
      95,    96,    34,    74,    33,    91,    11,    93,    94,    95,
      96,    83,    74,    38,    39,    40,    41,    83,    43,    44,
      91,    74,    93,    94,    95,    96,    83,    18,   345,    91,
     229,    93,    94,    95,    96,   348,   270,   269,    91,    74,
      93,    94,    95,    96,    61,    62,    63,   280,   226,   205,
     309,    68,   307,    -1,   340,   242,    91,    74,    93,    94,
      95,    96,    -1,   215,    -1,    -1,    83,    84,    85,    86,
      87,    88,    -1,    -1,    91,    -1,    93,    94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    17,    18,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    45,    46,    66,    69,    72,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     117,   118,   119,   121,   127,   133,   134,   139,   140,   159,
     160,   161,    13,    14,    32,    39,   110,    14,    16,     7,
      31,    55,    56,    57,    58,    59,    76,    79,    80,    82,
      89,    90,    91,    92,    94,    95,   129,   130,   142,   144,
     147,   142,    91,    15,    48,    54,    91,    20,    91,    70,
     100,     0,     3,   162,    91,    91,    16,    16,    91,    91,
      89,    90,   131,   139,   142,   144,    31,    31,    31,    31,
      31,    31,    31,    31,    47,    89,    90,   144,    34,    74,
      91,    93,    94,    95,    96,    54,    91,    91,    66,    42,
      92,    83,    71,    31,    74,   120,   139,    31,   115,    91,
      91,    67,    34,    34,     8,    33,    33,    33,   142,   147,
     148,   142,   148,   142,   148,   142,   148,   142,   148,   144,
     144,   144,    91,    95,   142,    91,   144,   144,   144,   144,
      91,   149,   150,    49,    60,   153,   141,   144,   155,    94,
     129,    92,    91,   123,   139,    73,   132,    91,   114,    74,
     116,    67,    67,    91,   131,   131,    33,    34,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    34,    34,    34,
      74,    91,   143,    77,   145,   146,    31,    19,    61,   144,
     154,   155,   156,   153,    83,    34,    89,    90,    48,    38,
      39,    40,    41,    43,    44,   126,    34,   122,    75,    34,
      33,   139,   132,    91,    91,    91,   147,   148,   144,   144,
     144,    91,    34,    78,   153,   145,   129,   144,    19,    61,
      62,    63,    68,    84,    85,    86,    87,    88,   157,    64,
      65,   144,   141,    14,    31,    61,    81,    82,   125,   123,
      33,    83,   114,    31,    31,    47,    33,    33,    33,   150,
      91,     9,   158,    34,   128,   144,    63,    68,    61,   144,
     154,   154,    91,    89,   124,    81,    82,   122,   120,    91,
     149,   151,   151,   143,     4,    12,   152,   129,    33,    33,
     132,    34,    33,    33,    67,   142,   154,    10,   138,   128,
     125,   151,    50,   154,     4,    31,    76,    79,    80,   111,
     136,   137,   147,    24,    25,    52,    53,   112,   113,    31,
      34,    21,    23,   135,    83,    83,    83,    83,    34,    33,
     144,   137,    51,   111,   124,   124,   113,    34,   144,    33,
      11,   124
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   110,   111,   111,   111,   112,   112,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   117,
     118,   118,   119,   120,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   125,   125,   125,   125,   125,   126,   126,
     126,   126,   126,   126,   127,   128,   128,   129,   129,   129,
     129,   129,   129,   129,   130,   131,   131,   131,   131,   132,
     132,   133,   134,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   140,   141,   141,   142,   142,   143,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     146,   146,   147,   147,   148,   148,   148,   149,   150,   150,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   154,
     155,   156,   156,   156,   156,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   158,   158,   159,   160,
     161,   161,   161,   162,   162
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     1,     0,     1,     1,     1,     3,     3,
       3,     3,     1,     3,     1,     3,     0,     3,     2,     6,
      13,     9,     5,     1,     2,     0,     9,     5,     0,     3,
       6,     3,     1,     0,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     8,     0,     3,     1,     2,     1,
       2,     1,     1,     1,     3,     3,     1,     1,     3,     0,
       4,     4,     5,     1,     1,     0,     2,     8,     1,     3,
       0,     3,     9,     2,     3,     1,     3,     1,     0,     2,
       1,     1,     2,     3,     3,     3,     3,     3,     6,     6,
       6,     3,     2,     1,     3,     3,     3,     1,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     0,     2,
       6,     4,     1,     3,     0,     1,     3,     1,     2,     4,
       1,     3,     0,     2,     0,     2,     0,     1,     3,     3,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     2,     0,     3,     7,     2,
       4,     3,     3,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 308 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2015 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 339 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 345 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2032 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 350 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2040 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 356 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2048 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 362 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2056 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 368 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 374 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 381 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2082 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 387 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: UNIQUE  */
#line 394 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2100 "yacc_sql.cpp"
    break;

  case 34: /* unique_op: %empty  */
#line 398 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 35: /* distance_type: L2_DIST  */
#line 404 "yacc_sql.y"
            {
      (yyval.number) = 1;
    }
#line 2116 "yacc_sql.cpp"
    break;

  case 36: /* distance_type: INNER_PRODUCT  */
#line 407 "yacc_sql.y"
                        {
          (yyval.number) = 2;
        }
#line 2124 "yacc_sql.cpp"
    break;

  case 37: /* distance_type: COS_DIST  */
#line 410 "yacc_sql.y"
               {
      (yyval.number) = 3;
    }
#line 2132 "yacc_sql.cpp"
    break;

  case 38: /* vec_index_param: DISTANCE EQ distance_type  */
#line 417 "yacc_sql.y"
                              {
    Value val((int)((yyvsp[0].number)));
                Value valf((int)3);

      (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 39: /* vec_index_param: LISTS EQ number  */
#line 423 "yacc_sql.y"
                      {
        Value val((int)((yyvsp[0].number)));
            Value valf((int)1);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 40: /* vec_index_param: PROBS EQ number  */
#line 428 "yacc_sql.y"
                      {
       Value val((int)((yyvsp[0].number)));
        Value valf((int)2);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 41: /* vec_index_param: TYPE EQ IVFFLAT  */
#line 433 "yacc_sql.y"
                      {
        Value valf((int)4);
        Value val((int)(1));
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 42: /* vec_index_list: vec_index_param  */
#line 441 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 43: /* vec_index_list: vec_index_param COMMA vec_index_list  */
#line 445 "yacc_sql.y"
                                           {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 44: /* view_fields: ID  */
#line 456 "yacc_sql.y"
       {
      (yyval.relation_list) = new std::vector<std::string>();
        (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 45: /* view_fields: ID COMMA view_fields  */
#line 461 "yacc_sql.y"
                           {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2219 "yacc_sql.cpp"
    break;

  case 46: /* view_field_list: %empty  */
#line 474 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2227 "yacc_sql.cpp"
    break;

  case 47: /* view_field_list: LBRACE view_fields RBRACE  */
#line 477 "yacc_sql.y"
                                {
      (yyval.relation_list) = (yyvsp[-1].relation_list);
    }
#line 2235 "yacc_sql.cpp"
    break;

  case 48: /* view_select_stmt: AS select_stmt  */
#line 484 "yacc_sql.y"
                   {
          delete (yyvsp[0].sql_node);
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
          (yyval.sql_node)->create_view.select_stmt = std::move(token_name(sql_string, &(yyloc)));
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 49: /* create_view_stmt: CREATE VIEW ID view_field_list view_select_stmt storage_format  */
#line 492 "yacc_sql.y"
                                                                  {
        (yyval.sql_node) = (yyvsp[-1].sql_node);
        (yyval.sql_node)->create_view.relation_name = (yyvsp[-3].string);
        if ((yyvsp[-2].relation_list) != nullptr) {
            (yyval.sql_node)->create_view.alias.swap(*(yyvsp[-2].relation_list));
            delete (yyvsp[-2].relation_list);
        }
        if ((yyvsp[0].string) != nullptr) {
          (yyval.sql_node)->create_view.storage_format = (yyvsp[0].string);
          free((yyvsp[0].string));
        }
        free((yyvsp[-3].string));
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 50: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE vec_index_list RBRACE  */
#line 508 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-9].string);
      create_index.relation_name = (yyvsp[-7].string);
      create_index.unique = false;
      create_index.is_vector = true;
      create_index.attribute_list = std::move(*(yyvsp[-5].rel_attr_list));
      create_index.expressions = std::move(*(yyvsp[-1].expression_list));
      free((yyvsp[-9].string));
      free((yyvsp[-7].string));
      delete((yyvsp[-5].rel_attr_list));
      delete((yyvsp[-1].expression_list));
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 51: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 524 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = (yyvsp[-7].number);
      create_index.attribute_list = std::move(*(yyvsp[-1].rel_attr_list));
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      delete((yyvsp[-1].rel_attr_list));
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 52: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 539 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 53: /* as_select_opt: select_stmt  */
#line 548 "yacc_sql.y"
                {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 54: /* as_select_opt: AS select_stmt  */
#line 551 "yacc_sql.y"
                     {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 55: /* as_select_opt: %empty  */
#line 555 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 2334 "yacc_sql.cpp"
    break;

  case 56: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format  */
#line 562 "yacc_sql.y"
    {
        LOG_INFO("%s",token_name(sql_string, &(yyloc)).c_str());
      auto node = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = node->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].sql_node) != nullptr) {
        create_table.select = std::make_unique<SelectSqlNode>(std::move(((yyvsp[-1].sql_node)->selection)));
        delete (yyvsp[-1].sql_node);
      }

      (yyval.sql_node) = node;

      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 57: /* create_table_stmt: CREATE TABLE ID as_select_opt storage_format  */
#line 591 "yacc_sql.y"
     {
       auto node = new ParsedSqlNode(SCF_CREATE_TABLE);
       CreateTableSqlNode &create_table = node->create_table;
       create_table.relation_name = (yyvsp[-2].string);
       free((yyvsp[-2].string));

       if ((yyvsp[-1].sql_node) != nullptr) {
         create_table.select = std::make_unique<SelectSqlNode>(std::move(((yyvsp[-1].sql_node)->selection)));
         delete (yyvsp[-1].sql_node);
       }

       (yyval.sql_node) = node;

       if ((yyvsp[0].string) != nullptr) {
         create_table.storage_format = (yyvsp[0].string);
         free((yyvsp[0].string));
       }
     }
#line 2390 "yacc_sql.cpp"
    break;

  case 58: /* attr_def_list: %empty  */
#line 613 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 59: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 617 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2412 "yacc_sql.cpp"
    break;

  case 60: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 630 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      if ((yyval.attr_info)->type == AttrType::VECTORS) {
         (yyval.attr_info)->length = (yyvsp[-2].number) * sizeof(float);
         if ((yyval.attr_info)->length > BP_PAGE_DATA_SIZE) {
            (yyval.attr_info)->type = AttrType::HIGH_DIMS;
            (yyval.attr_info)->length = (yyvsp[-2].number);
         }
      } else {
            (yyval.attr_info)->length = ((yyvsp[-2].number));
      }


      (yyval.attr_info)->nullable = (yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 61: /* attr_def: ID type null_t  */
#line 649 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if ((yyval.attr_info)->type == AttrType::TEXTS) {
        (yyval.attr_info)->length = ((65535 + BP_PAGE_DATA_SIZE - 1) / BP_PAGE_DATA_SIZE + 1) * sizeof(int);
      } else {
            (yyval.attr_info)->length = 4;
      }

      (yyval.attr_info)->nullable = (yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 62: /* number: NUMBER  */
#line 664 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2459 "yacc_sql.cpp"
    break;

  case 63: /* null_t: %empty  */
#line 668 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 64: /* null_t: NULL_L  */
#line 672 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 65: /* null_t: NULL_T  */
#line 676 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 66: /* null_t: NOT NULL_T  */
#line 680 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 67: /* null_t: NOT NULL_L  */
#line 684 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 68: /* type: INT_T  */
#line 690 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2505 "yacc_sql.cpp"
    break;

  case 69: /* type: STRING_T  */
#line 691 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2511 "yacc_sql.cpp"
    break;

  case 70: /* type: DATE_T  */
#line 692 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2517 "yacc_sql.cpp"
    break;

  case 71: /* type: FLOAT_T  */
#line 693 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2523 "yacc_sql.cpp"
    break;

  case 72: /* type: VECTOR_T  */
#line 694 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2529 "yacc_sql.cpp"
    break;

  case 73: /* type: TEXT_T  */
#line 695 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2535 "yacc_sql.cpp"
    break;

  case 74: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 699 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 75: /* value_list: %empty  */
#line 715 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2560 "yacc_sql.cpp"
    break;

  case 76: /* value_list: COMMA value value_list  */
#line 718 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 77: /* value: NUMBER  */
#line 729 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 78: /* value: '-' NUMBER  */
#line 733 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 79: /* value: FLOAT  */
#line 737 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 80: /* value: '-' FLOAT  */
#line 741 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2610 "yacc_sql.cpp"
    break;

  case 81: /* value: NULL_T  */
#line 745 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 82: /* value: SSS  */
#line 750 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 83: /* value: v_list  */
#line 756 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2642 "yacc_sql.cpp"
    break;

  case 84: /* v_list: LBRACKET v_l RBRACKET  */
#line 764 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2650 "yacc_sql.cpp"
    break;

  case 85: /* v_l: FLOAT COMMA v_l  */
#line 769 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 86: /* v_l: FLOAT  */
#line 773 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 87: /* v_l: NUMBER  */
#line 777 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 88: /* v_l: NUMBER COMMA v_l  */
#line 781 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 89: /* storage_format: %empty  */
#line 790 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 90: /* storage_format: STORAGE FORMAT EQ ID  */
#line 794 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 91: /* delete_stmt: DELETE FROM ID where  */
#line 801 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 92: /* update_stmt: UPDATE ID SET assign_list where  */
#line 812 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.expressions = std::move(*(yyvsp[-1].expression_list));
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions  = (yyvsp[0].expression) ;
      }
      delete (yyvsp[-1].expression_list);
      free((yyvsp[-3].string));
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 93: /* order_opt: ASC  */
#line 825 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 94: /* order_opt: DESC  */
#line 828 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 95: /* order_opt: %empty  */
#line 832 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2754 "yacc_sql.cpp"
    break;

  case 96: /* order_b: rel_attr order_opt  */
#line 840 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 97: /* order_b: distance_type LBRACE expression COMMA expression RBRACE LIMIT number  */
#line 845 "yacc_sql.y"
    {
      (yyval.expression) = new VecOrderByExpr((yyvsp[-5].expression),(yyvsp[-3].expression),(yyvsp[-7].number), (yyvsp[0].number));
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 98: /* order_by: order_b  */
#line 852 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 99: /* order_by: order_b COMMA order_by  */
#line 857 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 100: /* order_by_list: %empty  */
#line 869 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 101: /* order_by_list: ORDER BY order_by  */
#line 873 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 102: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 880 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].rel_attr_list));
        delete (yyvsp[-5].rel_attr_list);
      }

      if ((yyvsp[-4].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.inner_joins.swap(*(yyvsp[-4].inner_join_list));
        std::reverse((yyval.sql_node)->selection.inner_joins.begin(),(yyval.sql_node)->selection.inner_joins.end());
        delete (yyvsp[-4].inner_join_list);
      }

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-3].expression);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_cond = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.order_bys.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 103: /* calc_stmt: CALC expression_list  */
#line 919 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 104: /* assign_list: eq_expr COMMA assign_list  */
#line 927 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 105: /* assign_list: eq_expr  */
#line 936 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2882 "yacc_sql.cpp"
    break;

  case 106: /* expression_list: expression COMMA expression_list  */
#line 944 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 107: /* expression_list: expression  */
#line 953 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 108: /* as_opt: %empty  */
#line 960 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 109: /* as_opt: AS ID  */
#line 964 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 110: /* as_opt: ID  */
#line 968 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 111: /* expression: rel_attr  */
#line 974 "yacc_sql.y"
              {
                RelAttrSqlNode *node = (yyvsp[0].rel_attr);
                UnboundFieldExpr * ex = new UnboundFieldExpr(node->relation_name, node->attribute_name);



                ex->set_name(token_name(sql_string, &(yyloc)));


                (yyval.expression) = ex;
                delete (yyvsp[0].rel_attr);
              }
#line 2945 "yacc_sql.cpp"
    break;

  case 112: /* expression: expression ID  */
#line 987 "yacc_sql.y"
                    {
            (yyval.expression) = (yyvsp[-1].expression);
             if ((yyval.expression)->type() == ExprType::UNBOUND_FIELD)    {
                auto ex = dynamic_cast<UnboundFieldExpr*>((yyval.expression));
                 ex->set_alias(true);
             }
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 113: /* expression: expression AS ID  */
#line 996 "yacc_sql.y"
                      {
            (yyval.expression) = (yyvsp[-2].expression);
            if ((yyval.expression)->type() == ExprType::UNBOUND_FIELD)    {
                            auto ex = dynamic_cast<UnboundFieldExpr*>((yyval.expression));

                             ex->set_alias(true);
            }
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 114: /* expression: expression '+' expression  */
#line 1006 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2982 "yacc_sql.cpp"
    break;

  case 115: /* expression: expression '-' expression  */
#line 1009 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2990 "yacc_sql.cpp"
    break;

  case 116: /* expression: expression '*' expression  */
#line 1012 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 117: /* expression: expression '/' expression  */
#line 1015 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 118: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 1018 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 119: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 1021 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3022 "yacc_sql.cpp"
    break;

  case 120: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1025 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3030 "yacc_sql.cpp"
    break;

  case 121: /* expression: LBRACE expression RBRACE  */
#line 1029 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 122: /* expression: '-' expression  */
#line 1033 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3047 "yacc_sql.cpp"
    break;

  case 123: /* expression: value  */
#line 1036 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3057 "yacc_sql.cpp"
    break;

  case 124: /* expression: LBRACE select_stmt RBRACE  */
#line 1042 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 3066 "yacc_sql.cpp"
    break;

  case 125: /* expression: LBRACE expression_list RBRACE  */
#line 1046 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 126: /* expression: ID DOT '*'  */
#line 1050 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 127: /* expression: '*'  */
#line 1054 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 128: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 1057 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3100 "yacc_sql.cpp"
    break;

  case 129: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 1060 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 130: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 1063 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3116 "yacc_sql.cpp"
    break;

  case 131: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 1066 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3124 "yacc_sql.cpp"
    break;

  case 132: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 1069 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3132 "yacc_sql.cpp"
    break;

  case 133: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 1072 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3141 "yacc_sql.cpp"
    break;

  case 134: /* expression: SUM LBRACE expression_list RBRACE  */
#line 1076 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 135: /* expression: AVG LBRACE expression_list RBRACE  */
#line 1080 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3159 "yacc_sql.cpp"
    break;

  case 136: /* expression: MAX LBRACE expression_list RBRACE  */
#line 1084 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3168 "yacc_sql.cpp"
    break;

  case 137: /* expression: MIN LBRACE expression_list RBRACE  */
#line 1088 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3177 "yacc_sql.cpp"
    break;

  case 138: /* inner_joins: %empty  */
#line 1099 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 139: /* inner_joins: inner_join inner_joins  */
#line 1102 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 140: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 1113 "yacc_sql.y"
                                           {
      (yyval.inner_j) = new InnerJoinSqlNode();
      RelAttrSqlNode node;
      if ((yyvsp[-2].string) != nullptr) {
        node.attribute_name = (yyvsp[-2].string);
        node.relation_name = (yyvsp[-3].string);
        free((yyvsp[-2].string));
      } else {
        node.relation_name = (yyvsp[-3].string);
      }
        (yyval.inner_j)->table_name = node;
      (yyval.inner_j)->conditions = (yyvsp[0].expression);
      free((yyvsp[-3].string));
    }
#line 3218 "yacc_sql.cpp"
    break;

  case 141: /* inner_join: INNER JOIN ID as_opt  */
#line 1127 "yacc_sql.y"
                           {
      (yyval.inner_j) = new InnerJoinSqlNode();
        RelAttrSqlNode node;
        if ((yyvsp[0].string) != nullptr) {
          node.attribute_name = (yyvsp[0].string);
          node.relation_name = (yyvsp[-1].string);
          free((yyvsp[0].string));
        } else {
          node.relation_name = (yyvsp[-1].string);
        }

      (yyval.inner_j)->table_name = node;
      free((yyvsp[-1].string));
    }
#line 3237 "yacc_sql.cpp"
    break;

  case 142: /* rel_attr: ID  */
#line 1144 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3247 "yacc_sql.cpp"
    break;

  case 143: /* rel_attr: ID DOT ID  */
#line 1149 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 144: /* rel_attr_list: %empty  */
#line 1160 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 3267 "yacc_sql.cpp"
    break;

  case 145: /* rel_attr_list: rel_attr  */
#line 1163 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 3277 "yacc_sql.cpp"
    break;

  case 146: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 1168 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 3291 "yacc_sql.cpp"
    break;

  case 147: /* relation: ID  */
#line 1180 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3299 "yacc_sql.cpp"
    break;

  case 148: /* rel_table_list: relation as_opt  */
#line 1186 "yacc_sql.y"
                    {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();
      if ((yyvsp[0].string) != nullptr) {
        RelAttrSqlNode node;
        node.relation_name = (yyvsp[-1].string);
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);
        free((yyvsp[0].string));
      } else {
        RelAttrSqlNode node;
        node.relation_name = (yyvsp[-1].string);
        (yyval.rel_attr_list)->push_back(node);
      }
      free((yyvsp[-1].string));
    }
#line 3319 "yacc_sql.cpp"
    break;

  case 149: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 1201 "yacc_sql.y"
                                           {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();
      }
      if ((yyvsp[-2].string) != nullptr) {
        RelAttrSqlNode node;
        node.relation_name = (yyvsp[-3].string);
        node.attribute_name = (yyvsp[-2].string);
        (yyval.rel_attr_list)->insert((yyval.rel_attr_list)->begin(), node);
        free((yyvsp[-2].string));
      } else {
        RelAttrSqlNode node;
        node.relation_name = (yyvsp[-3].string);
        (yyval.rel_attr_list)->insert((yyval.rel_attr_list)->begin(), node);
      }
      free((yyvsp[-3].string));
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 150: /* rel_list: relation  */
#line 1224 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3357 "yacc_sql.cpp"
    break;

  case 151: /* rel_list: relation COMMA rel_list  */
#line 1233 "yacc_sql.y"
                              {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();
      }

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[-2].string);
        (yyval.rel_attr_list)->insert((yyval.rel_attr_list)->begin(), node);

      free((yyvsp[-2].string));
    }
#line 3375 "yacc_sql.cpp"
    break;

  case 152: /* having: %empty  */
#line 1249 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3383 "yacc_sql.cpp"
    break;

  case 153: /* having: HAVING condition_list  */
#line 1252 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 154: /* where: %empty  */
#line 1260 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3399 "yacc_sql.cpp"
    break;

  case 155: /* where: WHERE condition_list  */
#line 1263 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3407 "yacc_sql.cpp"
    break;

  case 156: /* condition_list: %empty  */
#line 1269 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3415 "yacc_sql.cpp"
    break;

  case 157: /* condition_list: condition  */
#line 1272 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3423 "yacc_sql.cpp"
    break;

  case 158: /* condition_list: condition AND condition_list  */
#line 1275 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3434 "yacc_sql.cpp"
    break;

  case 159: /* condition_list: condition OR condition_list  */
#line 1281 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3445 "yacc_sql.cpp"
    break;

  case 160: /* eq_expr: expression EQ expression  */
#line 1291 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3453 "yacc_sql.cpp"
    break;

  case 161: /* condition: expression comp_op expression  */
#line 1298 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3461 "yacc_sql.cpp"
    break;

  case 162: /* condition: EXISTS expression  */
#line 1302 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3469 "yacc_sql.cpp"
    break;

  case 163: /* condition: NOT EXISTS expression  */
#line 1306 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3477 "yacc_sql.cpp"
    break;

  case 164: /* condition: eq_expr  */
#line 1310 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3485 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: LT  */
#line 1316 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3491 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: GT  */
#line 1317 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3497 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: LE  */
#line 1318 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3503 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: GE  */
#line 1319 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3509 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: NE  */
#line 1320 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3515 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: IS NOT  */
#line 1321 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3521 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: IS  */
#line 1322 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3527 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: NOT LIKE  */
#line 1323 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3533 "yacc_sql.cpp"
    break;

  case 173: /* comp_op: LIKE  */
#line 1324 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3539 "yacc_sql.cpp"
    break;

  case 174: /* comp_op: IN  */
#line 1325 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3545 "yacc_sql.cpp"
    break;

  case 175: /* comp_op: NOT IN  */
#line 1326 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3551 "yacc_sql.cpp"
    break;

  case 176: /* group_by: %empty  */
#line 1331 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3559 "yacc_sql.cpp"
    break;

  case 177: /* group_by: GROUP BY expression_list  */
#line 1334 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3567 "yacc_sql.cpp"
    break;

  case 178: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1340 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3581 "yacc_sql.cpp"
    break;

  case 179: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1353 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3590 "yacc_sql.cpp"
    break;

  case 180: /* set_variable_stmt: SET ID EQ value  */
#line 1361 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3602 "yacc_sql.cpp"
    break;

  case 181: /* set_variable_stmt: SET NAMES SSS  */
#line 1369 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
      (yyval.sql_node)->set_variable.value = Value((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3613 "yacc_sql.cpp"
    break;

  case 182: /* set_variable_stmt: SET NAMES UTF8MB4_BIN  */
#line 1376 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
    }
#line 3622 "yacc_sql.cpp"
    break;


#line 3626 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1385 "yacc_sql.y"

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
