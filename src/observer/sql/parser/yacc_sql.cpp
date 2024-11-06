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
  YYSYMBOL_view_select_stmt = 114,         /* view_select_stmt  */
  YYSYMBOL_create_view_stmt = 115,         /* create_view_stmt  */
  YYSYMBOL_create_index_stmt = 116,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 117,          /* drop_index_stmt  */
  YYSYMBOL_as_select_opt = 118,            /* as_select_opt  */
  YYSYMBOL_create_table_stmt = 119,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 120,            /* attr_def_list  */
  YYSYMBOL_attr_def = 121,                 /* attr_def  */
  YYSYMBOL_number = 122,                   /* number  */
  YYSYMBOL_null_t = 123,                   /* null_t  */
  YYSYMBOL_type = 124,                     /* type  */
  YYSYMBOL_insert_stmt = 125,              /* insert_stmt  */
  YYSYMBOL_value_list = 126,               /* value_list  */
  YYSYMBOL_value = 127,                    /* value  */
  YYSYMBOL_v_list = 128,                   /* v_list  */
  YYSYMBOL_v_l = 129,                      /* v_l  */
  YYSYMBOL_storage_format = 130,           /* storage_format  */
  YYSYMBOL_delete_stmt = 131,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 132,              /* update_stmt  */
  YYSYMBOL_order_opt = 133,                /* order_opt  */
  YYSYMBOL_order_b = 134,                  /* order_b  */
  YYSYMBOL_order_by = 135,                 /* order_by  */
  YYSYMBOL_order_by_list = 136,            /* order_by_list  */
  YYSYMBOL_select_stmt = 137,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 138,                /* calc_stmt  */
  YYSYMBOL_assign_list = 139,              /* assign_list  */
  YYSYMBOL_expression_list = 140,          /* expression_list  */
  YYSYMBOL_as_opt = 141,                   /* as_opt  */
  YYSYMBOL_expression = 142,               /* expression  */
  YYSYMBOL_inner_joins = 143,              /* inner_joins  */
  YYSYMBOL_inner_join = 144,               /* inner_join  */
  YYSYMBOL_rel_attr = 145,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 146,            /* rel_attr_list  */
  YYSYMBOL_relation = 147,                 /* relation  */
  YYSYMBOL_rel_table_list = 148,           /* rel_table_list  */
  YYSYMBOL_rel_list = 149,                 /* rel_list  */
  YYSYMBOL_having = 150,                   /* having  */
  YYSYMBOL_where = 151,                    /* where  */
  YYSYMBOL_condition_list = 152,           /* condition_list  */
  YYSYMBOL_eq_expr = 153,                  /* eq_expr  */
  YYSYMBOL_condition = 154,                /* condition  */
  YYSYMBOL_comp_op = 155,                  /* comp_op  */
  YYSYMBOL_group_by = 156,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 157,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 158,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 159,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 160             /* opt_semicolon  */
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
#define YYLAST   455

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  180
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  356

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
       0,   305,   305,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   337,   343,   348,   354,   360,   366,
     372,   379,   385,   392,   396,   402,   405,   408,   415,   421,
     426,   431,   439,   443,   454,   462,   473,   489,   504,   514,
     517,   521,   527,   556,   579,   582,   595,   614,   630,   634,
     637,   641,   645,   649,   656,   657,   658,   659,   660,   661,
     664,   681,   684,   695,   699,   703,   707,   711,   716,   722,
     730,   735,   739,   743,   747,   756,   759,   766,   777,   791,
     794,   798,   805,   810,   817,   822,   835,   838,   845,   884,
     892,   901,   909,   918,   926,   929,   933,   940,   956,   961,
     966,   969,   972,   975,   978,   981,   985,   989,   993,   996,
    1002,  1006,  1010,  1014,  1017,  1020,  1023,  1026,  1029,  1032,
    1036,  1040,  1044,  1048,  1058,  1061,  1072,  1086,  1103,  1108,
    1119,  1122,  1127,  1139,  1145,  1160,  1183,  1192,  1208,  1211,
    1219,  1222,  1228,  1231,  1234,  1240,  1249,  1256,  1260,  1264,
    1268,  1275,  1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,
    1284,  1285,  1290,  1293,  1298,  1311,  1319,  1327,  1334,  1341,
    1342
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
  "vec_index_param", "vec_index_list", "view_select_stmt",
  "create_view_stmt", "create_index_stmt", "drop_index_stmt",
  "as_select_opt", "create_table_stmt", "attr_def_list", "attr_def",
  "number", "null_t", "type", "insert_stmt", "value_list", "value",
  "v_list", "v_l", "storage_format", "delete_stmt", "update_stmt",
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

#define YYPACT_NINF (-312)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     333,    10,    21,   208,   208,   -53,    30,  -312,     6,     5,
     -21,  -312,  -312,  -312,  -312,  -312,    -7,    20,   333,    92,
     105,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,    29,    34,   111,   145,    89,    90,   -62,
     165,    70,   138,   151,   153,   154,   159,   163,   170,  -312,
    -312,  -312,   155,  -312,   254,  -312,  -312,  -312,  -312,    38,
     -52,   152,  -312,  -312,   116,   117,   144,   -11,   129,   143,
    -312,  -312,  -312,  -312,    15,   139,   127,   128,  -312,   167,
     206,   212,   224,   209,   215,   -18,   208,   208,   208,   208,
     208,   208,   208,   208,    35,  -312,  -312,  -312,   208,   161,
    -312,   208,   208,   208,   208,   162,  -312,  -312,   171,   201,
     216,   208,  -312,  -312,    25,   183,   178,   261,   207,  -312,
     261,   207,   214,   219,   191,   -62,   -62,  -312,  -312,  -312,
    -312,   258,     0,   259,   260,   263,   271,   272,   274,   275,
     287,   296,   177,   281,   290,  -312,  -312,  -312,  -312,    40,
      40,  -312,  -312,  -312,  -312,   -52,   217,   283,    97,  -312,
     216,   142,   298,    56,  -312,   289,   278,   301,  -312,   265,
    -312,  -312,  -312,   250,   251,  -312,  -312,  -312,  -312,   256,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,   208,
     208,   208,   318,   279,   216,   217,    25,   208,   334,   335,
    -312,  -312,    98,  -312,   208,   208,  -312,  -312,   342,  -312,
    -312,  -312,  -312,  -312,  -312,    78,   178,   325,   282,   336,
     349,   319,   339,  -312,    -8,    47,   104,   171,   291,   378,
    -312,   355,   232,   208,   -13,   340,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,   208,    97,    97,   232,  -312,   303,   306,
      85,  -312,  -312,  -312,   301,    26,   309,   171,   171,   313,
    -312,  -312,  -312,  -312,   -52,   402,   395,    25,   375,   232,
    -312,  -312,  -312,   232,  -312,  -312,  -312,  -312,   377,  -312,
    -312,  -312,   207,  -312,   379,   381,   382,   344,   208,    97,
     406,   355,  -312,    42,  -312,   171,   362,  -312,    97,  -312,
    -312,   413,  -312,  -312,  -312,  -312,   393,  -312,   198,    16,
    -312,  -312,  -312,   394,   398,  -312,    44,   350,   351,   352,
     353,   403,   405,   208,   198,  -312,  -312,  -312,   376,    68,
     306,   306,    16,  -312,   297,  -312,  -312,  -312,  -312,  -312,
    -312,   208,   135,   428,   306,  -312
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     179,    23,    22,    14,    16,    17,    18,     9,    10,    11,
      15,    12,    13,     8,     5,     7,     6,     4,     3,    19,
      20,    21,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
      73,    75,   138,    78,     0,   123,   119,    79,    99,   103,
     104,     0,    32,    31,     0,     0,     0,     0,     0,     0,
     175,     1,   180,     2,    51,     0,     0,     0,    30,     0,
      83,    82,     0,     0,     0,     0,   140,   140,   140,   140,
     140,     0,     0,     0,     0,    73,    75,   118,     0,     0,
     108,     0,     0,     0,     0,     0,   106,   107,     0,     0,
     150,     0,   178,   177,     0,     0,     0,     0,    85,    49,
       0,    85,     0,     0,     0,     0,     0,    80,   120,   121,
     117,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   139,   122,   102,   109,   110,
     111,   112,   113,   105,   143,   104,   134,     0,   152,    87,
     150,     0,   101,     0,   176,     0,     0,    54,    50,     0,
      53,    44,    45,     0,     0,    48,    84,    81,   130,   140,
     125,   131,   126,   132,   127,   133,   128,   129,   124,     0,
       0,     0,   144,     0,   150,   134,     0,     0,     0,     0,
     151,   160,   153,    88,     0,     0,    74,    76,     0,    64,
      68,    69,    65,    66,    67,    59,     0,     0,     0,     0,
       0,   138,   141,   142,     0,     0,     0,     0,     0,   172,
     135,    71,   158,     0,     0,   167,   169,   170,   161,   162,
     163,   164,   165,     0,   152,   152,   156,   100,     0,     0,
       0,    60,    61,    57,    54,    51,     0,     0,     0,     0,
     116,   114,   115,   145,   104,     0,   148,     0,     0,   159,
     168,   171,   166,   157,   154,   155,   174,    58,     0,    63,
      62,    55,    85,    86,   146,     0,     0,   137,     0,   152,
      96,    71,    70,    59,    52,     0,     0,    47,   152,   173,
     149,     0,    98,    72,    56,   147,     0,   136,     0,     0,
      36,    35,    37,     0,    94,    97,    91,     0,     0,     0,
       0,    42,     0,     0,     0,    90,    89,    92,     0,     0,
       0,     0,     0,    46,     0,    95,    41,    38,    39,    40,
      43,     0,     0,     0,     0,    93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -312,  -312,   422,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,   102,  -312,   100,  -312,  -312,  -312,  -312,
     179,  -312,   181,   220,  -311,   140,  -312,  -312,   146,  -107,
    -312,    39,  -121,  -312,  -312,  -312,  -312,   114,  -312,   -48,
    -312,   234,    -3,  -161,   -50,   245,  -312,   -91,   -79,  -115,
     218,  -257,  -312,  -144,  -197,  -109,  -312,  -312,  -312,  -312,
    -312,  -312,  -312
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    46,   323,   331,   332,   131,    30,    31,    32,
     128,    33,   227,   177,   288,   263,   225,    34,   278,    66,
      67,    92,   180,    35,    36,   337,   324,   325,   312,    37,
      38,   170,    68,   117,    69,   204,   205,    70,   143,   294,
     166,   295,   300,   169,   210,   211,   212,   253,   276,    39,
      40,    41,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      95,    71,    93,   165,   202,   142,   142,   142,   142,   142,
     182,   296,   172,    77,   107,   140,   108,   174,   145,   147,
     149,   151,   115,    42,    43,   270,   213,    90,    91,   348,
     349,   122,    49,     4,   189,    47,   129,    48,    72,   116,
     327,   328,    44,   355,     4,    73,   126,    94,   315,    45,
     280,   152,   153,   154,    74,   281,   109,   284,   285,    75,
     239,   159,   160,   161,   162,   335,   109,   336,   329,   330,
      76,   171,   108,   110,   115,   111,   112,   113,   114,   178,
     271,   123,   181,   110,    78,   111,   112,   113,   114,   127,
      79,   116,    81,   141,   144,   146,   148,   150,   232,   241,
     127,    96,   310,   260,    49,   157,   172,    59,    82,   259,
     233,   317,   109,   297,    60,    61,   207,    63,   209,   173,
      84,   109,   165,   261,   262,    85,   155,    86,    50,   110,
     156,   111,   112,   113,   114,   113,   114,   272,   110,   260,
     111,   112,   113,   114,   320,   216,   217,   321,   322,   234,
     235,   236,    51,    52,    53,    54,    55,   242,   208,   261,
     262,    87,   254,   255,   256,   171,   289,   290,   353,    97,
     301,   304,    49,    56,   186,   187,    57,    58,   109,    59,
      88,    89,    98,     4,    99,   100,    60,    61,    62,    63,
     101,    64,    65,   279,   102,   110,    50,   111,   112,   113,
     114,   103,   104,   283,   209,   209,   118,   119,   120,   109,
     121,   199,   124,   130,   125,    49,   109,   129,   132,   133,
      51,    52,    53,    54,    55,   214,   110,   326,   111,   112,
     113,   114,   137,   110,   134,   111,   112,   113,   114,    50,
     135,    56,   138,   326,    57,    58,   136,    59,   139,   209,
     167,   109,   158,   163,    60,    61,    62,    63,   209,    64,
      65,    49,   164,    51,    52,    53,    54,    55,   110,   176,
     111,   112,   113,   114,   320,   175,   168,   321,   322,     4,
     179,   183,   185,   344,    56,    50,   184,    57,    58,   231,
      59,   188,   190,   191,   203,   309,   192,    60,    61,    62,
      63,   352,    64,    65,   193,   194,   109,   195,   196,    51,
      52,    53,    54,    55,   206,   200,   219,   220,   221,   222,
     197,   223,   224,   110,   201,   111,   112,   113,   114,   198,
      56,   351,   215,    57,    58,   226,    59,   218,     1,     2,
     228,   229,   230,   105,   106,    62,    63,   231,    64,    65,
       3,     4,   237,   243,     5,   109,   258,   238,   265,     6,
       7,     8,     9,    10,   109,   266,   269,   267,    11,    12,
      13,   109,   110,   189,   111,   112,   113,   114,    14,    15,
     268,   110,   274,   111,   112,   113,   114,   275,   110,   277,
     111,   112,   113,   114,   286,   287,   244,   245,   246,    16,
     293,   282,    17,   247,   155,    18,   298,   299,   302,   109,
     303,   308,   316,   305,   306,   307,   311,   318,   214,   248,
     249,   250,   251,   252,   319,   333,   110,   346,   111,   112,
     113,   114,   334,   338,   339,   340,   341,   342,   343,   354,
      80,   347,   350,   314,   292,   291,   264,   313,   345,   257,
     240,     0,     0,     0,     0,   273
};

static const yytype_int16 yycheck[] =
{
      50,     4,    50,   118,   165,    96,    97,    98,    99,   100,
     131,   268,   121,    20,    64,    33,    34,   124,    97,    98,
      99,   100,    74,    13,    14,    33,   170,    89,    90,   340,
     341,    42,     7,    18,    34,    14,    84,    16,    91,    91,
      24,    25,    32,   354,    18,    15,    31,    50,   305,    39,
      63,   101,   102,   103,    48,    68,    74,   254,   255,    54,
     204,   111,   112,   113,   114,    21,    74,    23,    52,    53,
      91,   121,    34,    91,    74,    93,    94,    95,    96,   127,
      33,    92,   130,    91,    91,    93,    94,    95,    96,    74,
      70,    91,     0,    96,    97,    98,    99,   100,   189,   206,
      74,    31,   299,    61,     7,   108,   215,    82,     3,    31,
     189,   308,    74,   274,    89,    90,    19,    92,   168,    94,
      91,    74,   237,    81,    82,    91,    91,    16,    31,    91,
      95,    93,    94,    95,    96,    95,    96,    33,    91,    61,
      93,    94,    95,    96,    76,    89,    90,    79,    80,   199,
     200,   201,    55,    56,    57,    58,    59,   207,    61,    81,
      82,    16,    64,    65,   214,   215,    81,    82,    33,    31,
     277,   292,     7,    76,   135,   136,    79,    80,    74,    82,
      91,    91,    31,    18,    31,    31,    89,    90,    91,    92,
      31,    94,    95,   243,    31,    91,    31,    93,    94,    95,
      96,    31,    47,   253,   254,   255,    54,    91,    91,    74,
      66,    34,    83,    74,    71,     7,    74,   265,    91,    91,
      55,    56,    57,    58,    59,    83,    91,   318,    93,    94,
      95,    96,     8,    91,    67,    93,    94,    95,    96,    31,
      34,    76,    33,   334,    79,    80,    34,    82,    33,   299,
      49,    74,    91,    91,    89,    90,    91,    92,   308,    94,
      95,     7,    91,    55,    56,    57,    58,    59,    91,    91,
      93,    94,    95,    96,    76,    92,    60,    79,    80,    18,
      73,    67,    91,   333,    76,    31,    67,    79,    80,    91,
      82,    33,    33,    33,    77,   298,    33,    89,    90,    91,
      92,   351,    94,    95,    33,    33,    74,    33,    33,    55,
      56,    57,    58,    59,    31,    34,    38,    39,    40,    41,
      33,    43,    44,    91,    34,    93,    94,    95,    96,    33,
      76,    34,    34,    79,    80,    34,    82,    48,     5,     6,
      75,    91,    91,    89,    90,    91,    92,    91,    94,    95,
      17,    18,    34,    19,    21,    74,    14,    78,    33,    26,
      27,    28,    29,    30,    74,    83,    47,    31,    35,    36,
      37,    74,    91,    34,    93,    94,    95,    96,    45,    46,
      31,    91,    91,    93,    94,    95,    96,     9,    91,    34,
      93,    94,    95,    96,    91,    89,    61,    62,    63,    66,
      91,    61,    69,    68,    91,    72,     4,    12,    33,    74,
      33,    67,    50,    34,    33,    33,    10,     4,    83,    84,
      85,    86,    87,    88,    31,    31,    91,    51,    93,    94,
      95,    96,    34,    83,    83,    83,    83,    34,    33,    11,
      18,   339,   342,   303,   265,   264,   226,   301,   334,   215,
     205,    -1,    -1,    -1,    -1,   237
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    17,    18,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    45,    46,    66,    69,    72,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     115,   116,   117,   119,   125,   131,   132,   137,   138,   157,
     158,   159,    13,    14,    32,    39,   110,    14,    16,     7,
      31,    55,    56,    57,    58,    59,    76,    79,    80,    82,
      89,    90,    91,    92,    94,    95,   127,   128,   140,   142,
     145,   140,    91,    15,    48,    54,    91,    20,    91,    70,
     100,     0,     3,   160,    91,    91,    16,    16,    91,    91,
      89,    90,   129,   137,   140,   142,    31,    31,    31,    31,
      31,    31,    31,    31,    47,    89,    90,   142,    34,    74,
      91,    93,    94,    95,    96,    74,    91,   141,    54,    91,
      91,    66,    42,    92,    83,    71,    31,    74,   118,   137,
      74,   114,    91,    91,    67,    34,    34,     8,    33,    33,
      33,   140,   145,   146,   140,   146,   140,   146,   140,   146,
     140,   146,   142,   142,   142,    91,    95,   140,    91,   142,
     142,   142,   142,    91,    91,   147,   148,    49,    60,   151,
     139,   142,   153,    94,   127,    92,    91,   121,   137,    73,
     130,   137,   130,    67,    67,    91,   129,   129,    33,    34,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    34,
      34,    34,   141,    77,   143,   144,    31,    19,    61,   142,
     152,   153,   154,   151,    83,    34,    89,    90,    48,    38,
      39,    40,    41,    43,    44,   124,    34,   120,    75,    91,
      91,    91,   145,   146,   142,   142,   142,    34,    78,   151,
     143,   127,   142,    19,    61,    62,    63,    68,    84,    85,
      86,    87,    88,   155,    64,    65,   142,   139,    14,    31,
      61,    81,    82,   123,   121,    33,    83,    31,    31,    47,
      33,    33,    33,   148,    91,     9,   156,    34,   126,   142,
      63,    68,    61,   142,   152,   152,    91,    89,   122,    81,
      82,   120,   118,    91,   147,   149,   149,   141,     4,    12,
     150,   127,    33,    33,   130,    34,    33,    33,    67,   140,
     152,    10,   136,   126,   123,   149,    50,   152,     4,    31,
      76,    79,    80,   111,   134,   135,   145,    24,    25,    52,
      53,   112,   113,    31,    34,    21,    23,   133,    83,    83,
      83,    83,    34,    33,   142,   135,    51,   111,   122,   122,
     113,    34,   142,    33,    11,   122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   110,   111,   111,   111,   112,   112,
     112,   112,   113,   113,   114,   115,   116,   116,   117,   118,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   123,
     123,   123,   123,   123,   124,   124,   124,   124,   124,   124,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     128,   129,   129,   129,   129,   130,   130,   131,   132,   133,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   138,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   143,   143,   144,   144,   145,   145,
     146,   146,   146,   147,   148,   148,   149,   149,   150,   150,
     151,   151,   152,   152,   152,   152,   153,   154,   154,   154,
     154,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   156,   156,   157,   158,   159,   159,   159,   160,
     160
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     1,     0,     1,     1,     1,     3,     3,
       3,     3,     1,     3,     2,     5,    13,     9,     5,     1,
       2,     0,     9,     5,     0,     3,     6,     3,     1,     0,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     2,     1,     2,     1,     1,     1,
       3,     3,     1,     1,     3,     0,     4,     4,     5,     1,
       1,     0,     2,     8,     1,     3,     0,     3,     9,     2,
       3,     1,     3,     1,     0,     2,     1,     2,     2,     3,
       3,     3,     3,     3,     6,     6,     6,     3,     2,     1,
       3,     3,     3,     1,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     0,     2,     6,     4,     1,     3,
       0,     1,     3,     1,     2,     4,     1,     3,     0,     2,
       0,     2,     0,     1,     3,     3,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     2,     0,     3,     7,     2,     4,     3,     3,     0,
       1
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
#line 306 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2010 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 337 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 343 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2027 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 348 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 354 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 360 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 366 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 372 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2069 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 379 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2077 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 385 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: UNIQUE  */
#line 392 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 34: /* unique_op: %empty  */
#line 396 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 35: /* distance_type: L2_DIST  */
#line 402 "yacc_sql.y"
            {
      (yyval.number) = 1;
    }
#line 2111 "yacc_sql.cpp"
    break;

  case 36: /* distance_type: INNER_PRODUCT  */
#line 405 "yacc_sql.y"
                        {
          (yyval.number) = 2;
        }
#line 2119 "yacc_sql.cpp"
    break;

  case 37: /* distance_type: COS_DIST  */
#line 408 "yacc_sql.y"
               {
      (yyval.number) = 3;
    }
#line 2127 "yacc_sql.cpp"
    break;

  case 38: /* vec_index_param: DISTANCE EQ distance_type  */
#line 415 "yacc_sql.y"
                              {
    Value val((int)((yyvsp[0].number)));
                Value valf((int)3);

      (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 39: /* vec_index_param: LISTS EQ number  */
#line 421 "yacc_sql.y"
                      {
        Value val((int)((yyvsp[0].number)));
            Value valf((int)1);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2148 "yacc_sql.cpp"
    break;

  case 40: /* vec_index_param: PROBS EQ number  */
#line 426 "yacc_sql.y"
                      {
       Value val((int)((yyvsp[0].number)));
        Value valf((int)2);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 41: /* vec_index_param: TYPE EQ IVFFLAT  */
#line 431 "yacc_sql.y"
                      {
        Value valf((int)4);
        Value val((int)(1));
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2168 "yacc_sql.cpp"
    break;

  case 42: /* vec_index_list: vec_index_param  */
#line 439 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2177 "yacc_sql.cpp"
    break;

  case 43: /* vec_index_list: vec_index_param COMMA vec_index_list  */
#line 443 "yacc_sql.y"
                                           {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2190 "yacc_sql.cpp"
    break;

  case 44: /* view_select_stmt: AS select_stmt  */
#line 454 "yacc_sql.y"
                   {
          delete (yyvsp[0].sql_node);
          (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
          (yyval.sql_node)->create_view.select_stmt = std::move(token_name(sql_string, &(yyloc)));
    }
#line 2200 "yacc_sql.cpp"
    break;

  case 45: /* create_view_stmt: CREATE VIEW ID view_select_stmt storage_format  */
#line 462 "yacc_sql.y"
                                                  {
        (yyval.sql_node) = (yyvsp[-1].sql_node);
        (yyval.sql_node)->create_view.relation_name = (yyvsp[-2].string);
        if ((yyvsp[0].string) != nullptr) {
          (yyval.sql_node)->create_view.storage_format = (yyvsp[0].string);
          free((yyvsp[0].string));
        }
        free((yyvsp[-2].string));
    }
#line 2214 "yacc_sql.cpp"
    break;

  case 46: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE vec_index_list RBRACE  */
#line 474 "yacc_sql.y"
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
#line 2233 "yacc_sql.cpp"
    break;

  case 47: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 490 "yacc_sql.y"
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
#line 2249 "yacc_sql.cpp"
    break;

  case 48: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 505 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2261 "yacc_sql.cpp"
    break;

  case 49: /* as_select_opt: select_stmt  */
#line 514 "yacc_sql.y"
                {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2269 "yacc_sql.cpp"
    break;

  case 50: /* as_select_opt: AS select_stmt  */
#line 517 "yacc_sql.y"
                     {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2277 "yacc_sql.cpp"
    break;

  case 51: /* as_select_opt: %empty  */
#line 521 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 52: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format  */
#line 528 "yacc_sql.y"
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
#line 2318 "yacc_sql.cpp"
    break;

  case 53: /* create_table_stmt: CREATE TABLE ID as_select_opt storage_format  */
#line 557 "yacc_sql.y"
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
#line 2341 "yacc_sql.cpp"
    break;

  case 54: /* attr_def_list: %empty  */
#line 579 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 55: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 583 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 56: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 596 "yacc_sql.y"
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
#line 2386 "yacc_sql.cpp"
    break;

  case 57: /* attr_def: ID type null_t  */
#line 615 "yacc_sql.y"
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
#line 2404 "yacc_sql.cpp"
    break;

  case 58: /* number: NUMBER  */
#line 630 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2410 "yacc_sql.cpp"
    break;

  case 59: /* null_t: %empty  */
#line 634 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2418 "yacc_sql.cpp"
    break;

  case 60: /* null_t: NULL_L  */
#line 638 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2426 "yacc_sql.cpp"
    break;

  case 61: /* null_t: NULL_T  */
#line 642 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2434 "yacc_sql.cpp"
    break;

  case 62: /* null_t: NOT NULL_T  */
#line 646 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2442 "yacc_sql.cpp"
    break;

  case 63: /* null_t: NOT NULL_L  */
#line 650 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2450 "yacc_sql.cpp"
    break;

  case 64: /* type: INT_T  */
#line 656 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2456 "yacc_sql.cpp"
    break;

  case 65: /* type: STRING_T  */
#line 657 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2462 "yacc_sql.cpp"
    break;

  case 66: /* type: DATE_T  */
#line 658 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2468 "yacc_sql.cpp"
    break;

  case 67: /* type: FLOAT_T  */
#line 659 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2474 "yacc_sql.cpp"
    break;

  case 68: /* type: VECTOR_T  */
#line 660 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2480 "yacc_sql.cpp"
    break;

  case 69: /* type: TEXT_T  */
#line 661 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2486 "yacc_sql.cpp"
    break;

  case 70: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 665 "yacc_sql.y"
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
#line 2503 "yacc_sql.cpp"
    break;

  case 71: /* value_list: %empty  */
#line 681 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2511 "yacc_sql.cpp"
    break;

  case 72: /* value_list: COMMA value value_list  */
#line 684 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2525 "yacc_sql.cpp"
    break;

  case 73: /* value: NUMBER  */
#line 695 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 74: /* value: '-' NUMBER  */
#line 699 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2543 "yacc_sql.cpp"
    break;

  case 75: /* value: FLOAT  */
#line 703 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 76: /* value: '-' FLOAT  */
#line 707 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 77: /* value: NULL_T  */
#line 711 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 78: /* value: SSS  */
#line 716 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 79: /* value: v_list  */
#line 722 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 80: /* v_list: LBRACKET v_l RBRACKET  */
#line 730 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 81: /* v_l: FLOAT COMMA v_l  */
#line 735 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2610 "yacc_sql.cpp"
    break;

  case 82: /* v_l: FLOAT  */
#line 739 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2619 "yacc_sql.cpp"
    break;

  case 83: /* v_l: NUMBER  */
#line 743 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 84: /* v_l: NUMBER COMMA v_l  */
#line 747 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 85: /* storage_format: %empty  */
#line 756 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 86: /* storage_format: STORAGE FORMAT EQ ID  */
#line 760 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 87: /* delete_stmt: DELETE FROM ID where  */
#line 767 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2666 "yacc_sql.cpp"
    break;

  case 88: /* update_stmt: UPDATE ID SET assign_list where  */
#line 778 "yacc_sql.y"
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
#line 2681 "yacc_sql.cpp"
    break;

  case 89: /* order_opt: ASC  */
#line 791 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2689 "yacc_sql.cpp"
    break;

  case 90: /* order_opt: DESC  */
#line 794 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 91: /* order_opt: %empty  */
#line 798 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 92: /* order_b: rel_attr order_opt  */
#line 806 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 93: /* order_b: distance_type LBRACE expression COMMA expression RBRACE LIMIT number  */
#line 811 "yacc_sql.y"
    {
      (yyval.expression) = new VecOrderByExpr((yyvsp[-5].expression),(yyvsp[-3].expression),(yyvsp[-7].number), (yyvsp[0].number));
    }
#line 2722 "yacc_sql.cpp"
    break;

  case 94: /* order_by: order_b  */
#line 818 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 95: /* order_by: order_b COMMA order_by  */
#line 823 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 96: /* order_by_list: %empty  */
#line 835 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 97: /* order_by_list: ORDER BY order_by  */
#line 839 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 98: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 846 "yacc_sql.y"
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
#line 2801 "yacc_sql.cpp"
    break;

  case 99: /* calc_stmt: CALC expression_list  */
#line 885 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 100: /* assign_list: eq_expr COMMA assign_list  */
#line 893 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2824 "yacc_sql.cpp"
    break;

  case 101: /* assign_list: eq_expr  */
#line 902 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2833 "yacc_sql.cpp"
    break;

  case 102: /* expression_list: expression COMMA expression_list  */
#line 910 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 103: /* expression_list: expression  */
#line 919 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 104: /* as_opt: %empty  */
#line 926 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 105: /* as_opt: AS ID  */
#line 930 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2871 "yacc_sql.cpp"
    break;

  case 106: /* as_opt: ID  */
#line 934 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 107: /* expression: rel_attr as_opt  */
#line 940 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      UnboundFieldExpr * ex = new UnboundFieldExpr(node->relation_name, node->attribute_name);


      if ((yyvsp[0].string) != nullptr) {
        ex->set_name((yyvsp[0].string));
        ex->set_alias(true);
        free((yyvsp[0].string));
      } else {
        ex->set_name(token_name(sql_string, &(yyloc)));
      }

      (yyval.expression) = ex;
      delete (yyvsp[-1].rel_attr);
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 108: /* expression: expression ID  */
#line 956 "yacc_sql.y"
                    {
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 109: /* expression: expression AS ID  */
#line 961 "yacc_sql.y"
                      {
            (yyval.expression) = (yyvsp[-2].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 110: /* expression: expression '+' expression  */
#line 966 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 111: /* expression: expression '-' expression  */
#line 969 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 112: /* expression: expression '*' expression  */
#line 972 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 113: /* expression: expression '/' expression  */
#line 975 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2952 "yacc_sql.cpp"
    break;

  case 114: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 978 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2960 "yacc_sql.cpp"
    break;

  case 115: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 981 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 116: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 985 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 117: /* expression: LBRACE expression RBRACE  */
#line 989 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2985 "yacc_sql.cpp"
    break;

  case 118: /* expression: '-' expression  */
#line 993 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 119: /* expression: value  */
#line 996 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3003 "yacc_sql.cpp"
    break;

  case 120: /* expression: LBRACE select_stmt RBRACE  */
#line 1002 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 3012 "yacc_sql.cpp"
    break;

  case 121: /* expression: LBRACE expression_list RBRACE  */
#line 1006 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 122: /* expression: ID DOT '*'  */
#line 1010 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 3030 "yacc_sql.cpp"
    break;

  case 123: /* expression: '*'  */
#line 1014 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3038 "yacc_sql.cpp"
    break;

  case 124: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 1017 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 125: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 1020 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3054 "yacc_sql.cpp"
    break;

  case 126: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 1023 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 127: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 1026 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 128: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 1029 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3078 "yacc_sql.cpp"
    break;

  case 129: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 1032 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 130: /* expression: SUM LBRACE expression_list RBRACE  */
#line 1036 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 131: /* expression: AVG LBRACE expression_list RBRACE  */
#line 1040 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3105 "yacc_sql.cpp"
    break;

  case 132: /* expression: MAX LBRACE expression_list RBRACE  */
#line 1044 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 133: /* expression: MIN LBRACE expression_list RBRACE  */
#line 1048 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3123 "yacc_sql.cpp"
    break;

  case 134: /* inner_joins: %empty  */
#line 1058 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3131 "yacc_sql.cpp"
    break;

  case 135: /* inner_joins: inner_join inner_joins  */
#line 1061 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 3145 "yacc_sql.cpp"
    break;

  case 136: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 1072 "yacc_sql.y"
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
#line 3164 "yacc_sql.cpp"
    break;

  case 137: /* inner_join: INNER JOIN ID as_opt  */
#line 1086 "yacc_sql.y"
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
#line 3183 "yacc_sql.cpp"
    break;

  case 138: /* rel_attr: ID  */
#line 1103 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3193 "yacc_sql.cpp"
    break;

  case 139: /* rel_attr: ID DOT ID  */
#line 1108 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 140: /* rel_attr_list: %empty  */
#line 1119 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 141: /* rel_attr_list: rel_attr  */
#line 1122 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 3223 "yacc_sql.cpp"
    break;

  case 142: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 1127 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 3237 "yacc_sql.cpp"
    break;

  case 143: /* relation: ID  */
#line 1139 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3245 "yacc_sql.cpp"
    break;

  case 144: /* rel_table_list: relation as_opt  */
#line 1145 "yacc_sql.y"
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
#line 3265 "yacc_sql.cpp"
    break;

  case 145: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 1160 "yacc_sql.y"
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
#line 3289 "yacc_sql.cpp"
    break;

  case 146: /* rel_list: relation  */
#line 1183 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3303 "yacc_sql.cpp"
    break;

  case 147: /* rel_list: relation COMMA rel_list  */
#line 1192 "yacc_sql.y"
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
#line 3321 "yacc_sql.cpp"
    break;

  case 148: /* having: %empty  */
#line 1208 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3329 "yacc_sql.cpp"
    break;

  case 149: /* having: HAVING condition_list  */
#line 1211 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3337 "yacc_sql.cpp"
    break;

  case 150: /* where: %empty  */
#line 1219 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3345 "yacc_sql.cpp"
    break;

  case 151: /* where: WHERE condition_list  */
#line 1222 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3353 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: %empty  */
#line 1228 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3361 "yacc_sql.cpp"
    break;

  case 153: /* condition_list: condition  */
#line 1231 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3369 "yacc_sql.cpp"
    break;

  case 154: /* condition_list: condition AND condition_list  */
#line 1234 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3380 "yacc_sql.cpp"
    break;

  case 155: /* condition_list: condition OR condition_list  */
#line 1240 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 156: /* eq_expr: expression EQ expression  */
#line 1250 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3399 "yacc_sql.cpp"
    break;

  case 157: /* condition: expression comp_op expression  */
#line 1257 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3407 "yacc_sql.cpp"
    break;

  case 158: /* condition: EXISTS expression  */
#line 1261 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3415 "yacc_sql.cpp"
    break;

  case 159: /* condition: NOT EXISTS expression  */
#line 1265 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3423 "yacc_sql.cpp"
    break;

  case 160: /* condition: eq_expr  */
#line 1269 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3431 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: LT  */
#line 1275 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3437 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: GT  */
#line 1276 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3443 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: LE  */
#line 1277 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3449 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: GE  */
#line 1278 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3455 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: NE  */
#line 1279 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3461 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: IS NOT  */
#line 1280 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3467 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: IS  */
#line 1281 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3473 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NOT LIKE  */
#line 1282 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3479 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: LIKE  */
#line 1283 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3485 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: IN  */
#line 1284 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3491 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: NOT IN  */
#line 1285 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3497 "yacc_sql.cpp"
    break;

  case 172: /* group_by: %empty  */
#line 1290 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3505 "yacc_sql.cpp"
    break;

  case 173: /* group_by: GROUP BY expression_list  */
#line 1293 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3513 "yacc_sql.cpp"
    break;

  case 174: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1299 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3527 "yacc_sql.cpp"
    break;

  case 175: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1312 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3536 "yacc_sql.cpp"
    break;

  case 176: /* set_variable_stmt: SET ID EQ value  */
#line 1320 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3548 "yacc_sql.cpp"
    break;

  case 177: /* set_variable_stmt: SET NAMES SSS  */
#line 1328 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
      (yyval.sql_node)->set_variable.value = Value((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3559 "yacc_sql.cpp"
    break;

  case 178: /* set_variable_stmt: SET NAMES UTF8MB4_BIN  */
#line 1335 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
    }
#line 3568 "yacc_sql.cpp"
    break;


#line 3572 "yacc_sql.cpp"

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

#line 1344 "yacc_sql.y"

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
