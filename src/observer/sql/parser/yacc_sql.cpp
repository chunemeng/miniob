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
  YYSYMBOL_RBRACE = 32,                    /* RBRACE  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 34,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 35,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 36,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 37,                     /* INT_T  */
  YYSYMBOL_VECTOR_T = 38,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 39,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 40,                  /* STRING_T  */
  YYSYMBOL_UTF8MB4_BIN = 41,               /* UTF8MB4_BIN  */
  YYSYMBOL_DATE_T = 42,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 43,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 44,                      /* HELP  */
  YYSYMBOL_EXIT = 45,                      /* EXIT  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_INTO = 47,                      /* INTO  */
  YYSYMBOL_VALUES = 48,                    /* VALUES  */
  YYSYMBOL_WITH = 49,                      /* WITH  */
  YYSYMBOL_IVFFLAT = 50,                   /* IVFFLAT  */
  YYSYMBOL_LISTS = 51,                     /* LISTS  */
  YYSYMBOL_PROBS = 52,                     /* PROBS  */
  YYSYMBOL_FROM = 53,                      /* FROM  */
  YYSYMBOL_SUM = 54,                       /* SUM  */
  YYSYMBOL_AVG = 55,                       /* AVG  */
  YYSYMBOL_MAX = 56,                       /* MAX  */
  YYSYMBOL_MIN = 57,                       /* MIN  */
  YYSYMBOL_COUNT = 58,                     /* COUNT  */
  YYSYMBOL_WHERE = 59,                     /* WHERE  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_IS = 61,                        /* IS  */
  YYSYMBOL_LIKE = 62,                      /* LIKE  */
  YYSYMBOL_AND = 63,                       /* AND  */
  YYSYMBOL_OR = 64,                        /* OR  */
  YYSYMBOL_SET = 65,                       /* SET  */
  YYSYMBOL_ON = 66,                        /* ON  */
  YYSYMBOL_IN = 67,                        /* IN  */
  YYSYMBOL_LOAD = 68,                      /* LOAD  */
  YYSYMBOL_DATA = 69,                      /* DATA  */
  YYSYMBOL_INFILE = 70,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 71,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 72,                   /* STORAGE  */
  YYSYMBOL_AS = 73,                        /* AS  */
  YYSYMBOL_FORMAT = 74,                    /* FORMAT  */
  YYSYMBOL_INNER_PRODUCT = 75,             /* INNER_PRODUCT  */
  YYSYMBOL_INNER = 76,                     /* INNER  */
  YYSYMBOL_JOIN = 77,                      /* JOIN  */
  YYSYMBOL_L2_DIST = 78,                   /* L2_DIST  */
  YYSYMBOL_COS_DIST = 79,                  /* COS_DIST  */
  YYSYMBOL_NULL_L = 80,                    /* NULL_L  */
  YYSYMBOL_NULL_T = 81,                    /* NULL_T  */
  YYSYMBOL_EQ = 82,                        /* EQ  */
  YYSYMBOL_LT = 83,                        /* LT  */
  YYSYMBOL_GT = 84,                        /* GT  */
  YYSYMBOL_LE = 85,                        /* LE  */
  YYSYMBOL_GE = 86,                        /* GE  */
  YYSYMBOL_NE = 87,                        /* NE  */
  YYSYMBOL_NUMBER = 88,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 89,                     /* FLOAT  */
  YYSYMBOL_ID = 90,                        /* ID  */
  YYSYMBOL_SSS = 91,                       /* SSS  */
  YYSYMBOL_92_ = 92,                       /* '+'  */
  YYSYMBOL_93_ = 93,                       /* '-'  */
  YYSYMBOL_94_ = 94,                       /* '*'  */
  YYSYMBOL_95_ = 95,                       /* '/'  */
  YYSYMBOL_UMINUS = 96,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_commands = 98,                  /* commands  */
  YYSYMBOL_command_wrapper = 99,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 100,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 101,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 102,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 103,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 104,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 105,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 106,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 107,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 108,          /* desc_table_stmt  */
  YYSYMBOL_unique_op = 109,                /* unique_op  */
  YYSYMBOL_distance_type = 110,            /* distance_type  */
  YYSYMBOL_vec_index_param = 111,          /* vec_index_param  */
  YYSYMBOL_vec_index_list = 112,           /* vec_index_list  */
  YYSYMBOL_create_index_stmt = 113,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 114,          /* drop_index_stmt  */
  YYSYMBOL_as_select_opt = 115,            /* as_select_opt  */
  YYSYMBOL_create_table_stmt = 116,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 117,            /* attr_def_list  */
  YYSYMBOL_attr_def = 118,                 /* attr_def  */
  YYSYMBOL_number = 119,                   /* number  */
  YYSYMBOL_null_t = 120,                   /* null_t  */
  YYSYMBOL_type = 121,                     /* type  */
  YYSYMBOL_insert_stmt = 122,              /* insert_stmt  */
  YYSYMBOL_value_list = 123,               /* value_list  */
  YYSYMBOL_value = 124,                    /* value  */
  YYSYMBOL_v_list = 125,                   /* v_list  */
  YYSYMBOL_v_l = 126,                      /* v_l  */
  YYSYMBOL_storage_format = 127,           /* storage_format  */
  YYSYMBOL_delete_stmt = 128,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 129,              /* update_stmt  */
  YYSYMBOL_order_opt = 130,                /* order_opt  */
  YYSYMBOL_order_b = 131,                  /* order_b  */
  YYSYMBOL_order_by = 132,                 /* order_by  */
  YYSYMBOL_order_by_list = 133,            /* order_by_list  */
  YYSYMBOL_select_stmt = 134,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 135,                /* calc_stmt  */
  YYSYMBOL_assign_list = 136,              /* assign_list  */
  YYSYMBOL_expression_list = 137,          /* expression_list  */
  YYSYMBOL_as_opt = 138,                   /* as_opt  */
  YYSYMBOL_expression = 139,               /* expression  */
  YYSYMBOL_inner_joins = 140,              /* inner_joins  */
  YYSYMBOL_inner_join = 141,               /* inner_join  */
  YYSYMBOL_rel_attr = 142,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 143,            /* rel_attr_list  */
  YYSYMBOL_relation = 144,                 /* relation  */
  YYSYMBOL_rel_table_list = 145,           /* rel_table_list  */
  YYSYMBOL_rel_list = 146,                 /* rel_list  */
  YYSYMBOL_having = 147,                   /* having  */
  YYSYMBOL_where = 148,                    /* where  */
  YYSYMBOL_condition_list = 149,           /* condition_list  */
  YYSYMBOL_eq_expr = 150,                  /* eq_expr  */
  YYSYMBOL_condition = 151,                /* condition  */
  YYSYMBOL_comp_op = 152,                  /* comp_op  */
  YYSYMBOL_group_by = 153,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 154,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 155,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 156,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 157             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  349

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   347


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
       2,     2,    94,    92,     2,    93,     2,    95,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   302,   302,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   333,   339,   344,   350,   356,   362,   368,
     375,   381,   388,   392,   398,   401,   404,   411,   417,   422,
     427,   435,   439,   452,   468,   483,   493,   496,   500,   506,
     534,   557,   560,   573,   592,   608,   612,   615,   619,   623,
     627,   634,   635,   636,   637,   638,   639,   642,   659,   662,
     673,   677,   681,   685,   689,   694,   700,   708,   713,   717,
     721,   725,   734,   737,   744,   755,   769,   772,   776,   783,
     788,   795,   800,   813,   816,   823,   862,   870,   879,   887,
     896,   904,   907,   911,   918,   934,   939,   944,   947,   950,
     953,   956,   959,   963,   967,   971,   974,   980,   984,   988,
     992,   995,   998,  1001,  1004,  1007,  1010,  1014,  1018,  1022,
    1026,  1036,  1039,  1050,  1064,  1081,  1086,  1097,  1100,  1105,
    1117,  1123,  1138,  1161,  1170,  1186,  1189,  1197,  1200,  1206,
    1209,  1212,  1218,  1227,  1234,  1238,  1242,  1246,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1268,
    1271,  1276,  1289,  1297,  1305,  1312,  1319,  1320
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
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "VECTOR_T", "TEXT_T",
  "STRING_T", "UTF8MB4_BIN", "DATE_T", "FLOAT_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "WITH", "IVFFLAT", "LISTS", "PROBS", "FROM", "SUM",
  "AVG", "MAX", "MIN", "COUNT", "WHERE", "NOT", "IS", "LIKE", "AND", "OR",
  "SET", "ON", "IN", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "AS",
  "FORMAT", "INNER_PRODUCT", "INNER", "JOIN", "L2_DIST", "COS_DIST",
  "NULL_L", "NULL_T", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER",
  "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "unique_op", "distance_type",
  "vec_index_param", "vec_index_list", "create_index_stmt",
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

#define YYPACT_NINF (-250)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     342,    15,    42,   212,   212,   -42,    29,  -250,    25,    23,
     -10,  -250,  -250,  -250,  -250,  -250,    -7,    45,   342,    85,
      93,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,     8,    90,    95,    26,    38,    52,   171,   103,
     107,   112,   127,   130,   133,   137,   138,  -250,  -250,  -250,
     108,  -250,   264,  -250,  -250,  -250,  -250,   190,   -43,   122,
    -250,  -250,    89,    91,   115,   -20,   101,   120,  -250,  -250,
    -250,  -250,     1,   102,   111,  -250,   142,   144,   160,   195,
     179,   188,    -6,   212,   212,   212,   212,   212,   212,   212,
     212,   -57,  -250,  -250,  -250,   212,   131,  -250,   212,   212,
     212,   212,   132,  -250,  -250,   140,   184,   178,   212,  -250,
    -250,    16,   147,   149,   223,   170,  -250,   181,   182,   155,
      52,    52,  -250,  -250,  -250,  -250,   219,    -9,   224,   225,
     226,   241,   242,   243,   244,   245,   247,   221,   239,   302,
    -250,  -250,  -250,  -250,   -54,   -54,  -250,  -250,  -250,  -250,
     -43,   205,   255,   116,  -250,   178,   326,   222,    60,  -250,
     250,   403,   256,  -250,   218,  -250,   208,   209,  -250,  -250,
    -250,  -250,   214,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,   212,   212,   212,   274,   231,   178,   205,    16,
     212,   290,   344,  -250,  -250,    87,  -250,   212,   212,  -250,
    -250,   296,  -250,  -250,  -250,  -250,  -250,  -250,    82,   149,
     285,   246,   292,   293,   279,   294,  -250,    27,    37,    92,
     140,   236,   321,  -250,   303,   141,   212,     6,   277,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,   212,   116,   116,   141,
    -250,   248,   252,    76,  -250,  -250,  -250,   256,     2,   254,
     140,   140,   259,  -250,  -250,  -250,  -250,   -43,   346,   334,
      16,   319,   141,  -250,  -250,  -250,   141,  -250,  -250,  -250,
    -250,   324,  -250,  -250,  -250,   170,  -250,   328,   330,   332,
     299,   212,   116,   356,   303,  -250,   -38,  -250,   140,   318,
    -250,   116,  -250,  -250,   369,  -250,  -250,  -250,  -250,   343,
    -250,   -44,    14,  -250,  -250,  -250,   348,   347,  -250,    56,
     300,   301,   306,   307,   351,   353,   212,   -44,  -250,  -250,
    -250,   340,    58,   252,   252,    14,  -250,   308,  -250,  -250,
    -250,  -250,  -250,  -250,   212,   123,   380,   252,  -250
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     176,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    74,    70,    72,
     135,    75,     0,   120,   116,    76,    96,   100,   101,     0,
      31,    30,     0,     0,     0,     0,     0,     0,   172,     1,
     177,     2,    48,     0,     0,    29,     0,    80,    79,     0,
       0,     0,     0,   137,   137,   137,   137,   137,     0,     0,
       0,     0,    70,    72,   115,     0,     0,   105,     0,     0,
       0,     0,     0,   103,   104,     0,     0,   147,     0,   175,
     174,     0,     0,     0,     0,    82,    46,     0,     0,     0,
       0,     0,    77,   117,   118,   114,     0,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   119,    99,   106,   107,   108,   109,   110,   102,   140,
     101,   131,     0,   149,    84,   147,     0,    98,     0,   173,
       0,     0,    51,    47,     0,    50,     0,     0,    45,    81,
      78,   127,   137,   122,   128,   123,   129,   124,   130,   125,
     126,   121,     0,     0,     0,   141,     0,   147,   131,     0,
       0,     0,     0,   148,   157,   150,    85,     0,     0,    71,
      73,     0,    61,    65,    66,    62,    63,    64,    56,     0,
       0,     0,     0,     0,   135,   138,   139,     0,     0,     0,
       0,     0,   169,   132,    68,   155,     0,     0,   164,   166,
     167,   158,   159,   160,   161,   162,     0,   149,   149,   153,
      97,     0,     0,     0,    57,    58,    54,    51,    48,     0,
       0,     0,     0,   113,   111,   112,   142,   101,     0,   145,
       0,     0,   156,   165,   168,   163,   154,   151,   152,   171,
      55,     0,    60,    59,    52,    82,    83,   143,     0,     0,
     134,     0,   149,    93,    68,    67,    56,    49,     0,     0,
      44,   149,   170,   146,     0,    95,    69,    53,   144,     0,
     133,     0,     0,    35,    34,    36,     0,    91,    94,    88,
       0,     0,     0,     0,    41,     0,     0,     0,    87,    86,
      89,     0,     0,     0,     0,     0,    43,     0,    92,    40,
      37,    38,    39,    42,     0,     0,     0,     0,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,   375,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,    77,  -250,    79,  -250,  -250,   154,  -250,
     158,   203,  -208,   128,  -250,  -250,   129,  -117,  -250,    36,
     148,  -250,  -250,  -250,  -250,    98,  -250,   -46,  -250,   227,
      -3,  -155,   -48,   234,  -250,   -87,   -79,  -112,   217,  -249,
    -250,  -140,  -193,  -107,  -250,  -250,  -250,  -250,  -250,  -250,
    -250
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    44,   316,   324,   325,    30,    31,   125,    32,
     220,   172,   281,   256,   218,    33,   271,    64,    65,    89,
     175,    34,    35,   330,   317,   318,   305,    36,    37,   165,
      66,   114,    67,   197,   198,    68,   138,   287,   161,   288,
     293,   164,   203,   204,   205,   246,   269,    38,    39,    40,
      81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    69,    90,   160,   169,   195,   137,   137,   137,   137,
     137,   167,   289,    75,   104,   140,   142,   144,   146,     4,
       4,   119,   253,    47,   182,   206,   135,   105,    41,    42,
     112,   313,   123,   150,   314,   315,   126,   151,   320,   321,
     110,   111,   254,   255,    71,    91,   224,   113,    70,   308,
     147,   148,   149,    43,   277,   278,    45,   232,    46,   263,
     154,   155,   156,   157,   112,   322,   323,   106,   273,   264,
     166,   120,    72,   274,   124,   124,    73,   328,   173,   329,
      74,   113,   234,    76,   107,    79,   108,   109,   110,   111,
     136,   139,   141,   143,   145,   225,    80,    57,    82,   303,
     106,   167,   152,   226,    58,    59,    83,    61,   310,   168,
     106,    84,   290,   252,    77,   202,    85,   107,   160,   108,
     109,   110,   111,    47,   265,   341,   342,   107,    86,   108,
     109,   110,   111,   313,    93,   200,   314,   315,    94,   348,
      87,    88,   253,    95,   227,   228,   229,    48,   209,   210,
     247,   248,   235,   294,   101,   346,   282,   283,    96,   249,
     166,    97,   254,   255,    98,   106,   179,   180,    99,   100,
      49,    50,    51,    52,    53,   115,   201,   130,    47,   116,
     118,   117,   107,   121,   108,   109,   110,   111,   272,     4,
     122,    54,   127,   131,    55,    56,   106,    57,   276,   202,
     202,   128,    48,   132,    58,    59,    60,    61,   129,    62,
      63,   133,   126,   107,   106,   108,   109,   110,   111,    47,
     134,   153,   158,   105,   319,    49,    50,    51,    52,    53,
     159,   107,   162,   108,   109,   110,   111,   163,   170,   171,
     319,     4,   174,    48,   202,   178,    54,   176,   177,    55,
      56,   181,    57,   202,   192,   208,   183,   184,   185,    58,
      59,    60,    61,   106,    62,    63,    49,    50,    51,    52,
      53,    47,   193,   186,   187,   188,   189,   190,   337,   191,
     107,   196,   108,   109,   110,   111,   199,    54,   302,   219,
      55,    56,   221,    57,   106,    48,   345,   211,   222,   223,
      58,    59,    60,    61,   224,    62,    63,   230,   231,   236,
     251,   107,   106,   108,   109,   110,   111,   258,    49,    50,
      51,    52,    53,   260,   261,   262,   267,   182,   259,   107,
     268,   108,   109,   110,   111,   194,   270,   275,   279,    54,
     280,   344,    55,    56,   286,    57,   292,     1,     2,   150,
     291,   295,   102,   103,    60,    61,   296,    62,    63,     3,
       4,   298,   299,     5,   300,   301,   304,   309,     6,     7,
       8,     9,    10,   311,   312,   106,    11,    12,    13,   326,
     327,   106,   331,   332,   335,   336,    14,    15,   333,   334,
     339,   347,   107,    78,   108,   109,   110,   111,   107,   106,
     108,   109,   110,   111,   237,   238,   239,    16,   207,   340,
      17,   240,   285,    18,   343,   284,   107,   106,   108,   109,
     110,   111,   257,   306,   307,   338,   207,   241,   242,   243,
     244,   245,   233,   297,   107,   250,   108,   109,   110,   111,
     212,   213,   214,   215,     0,   216,   217,   266
};

static const yytype_int16 yycheck[] =
{
      48,     4,    48,   115,   121,   160,    93,    94,    95,    96,
      97,   118,   261,    20,    62,    94,    95,    96,    97,    18,
      18,    41,    60,     7,    33,   165,    32,    33,    13,    14,
      73,    75,    31,    90,    78,    79,    82,    94,    24,    25,
      94,    95,    80,    81,    15,    48,    90,    90,    90,   298,
      98,    99,   100,    38,   247,   248,    14,   197,    16,    32,
     108,   109,   110,   111,    73,    51,    52,    73,    62,    32,
     118,    91,    47,    67,    73,    73,    53,    21,   124,    23,
      90,    90,   199,    90,    90,     0,    92,    93,    94,    95,
      93,    94,    95,    96,    97,   182,     3,    81,    90,   292,
      73,   208,   105,   182,    88,    89,    16,    91,   301,    93,
      73,    16,   267,    31,    69,   163,    90,    90,   230,    92,
      93,    94,    95,     7,    32,   333,   334,    90,    90,    92,
      93,    94,    95,    75,    31,    19,    78,    79,    31,   347,
      88,    89,    60,    31,   192,   193,   194,    31,    88,    89,
      63,    64,   200,   270,    46,    32,    80,    81,    31,   207,
     208,    31,    80,    81,    31,    73,   130,   131,    31,    31,
      54,    55,    56,    57,    58,    53,    60,    33,     7,    90,
      65,    90,    90,    82,    92,    93,    94,    95,   236,    18,
      70,    75,    90,    33,    78,    79,    73,    81,   246,   247,
     248,    90,    31,     8,    88,    89,    90,    91,    66,    93,
      94,    32,   258,    90,    73,    92,    93,    94,    95,     7,
      32,    90,    90,    33,   311,    54,    55,    56,    57,    58,
      90,    90,    48,    92,    93,    94,    95,    59,    91,    90,
     327,    18,    72,    31,   292,    90,    75,    66,    66,    78,
      79,    32,    81,   301,    33,    33,    32,    32,    32,    88,
      89,    90,    91,    73,    93,    94,    54,    55,    56,    57,
      58,     7,    33,    32,    32,    32,    32,    32,   326,    32,
      90,    76,    92,    93,    94,    95,    31,    75,   291,    33,
      78,    79,    74,    81,    73,    31,   344,    47,    90,    90,
      88,    89,    90,    91,    90,    93,    94,    33,    77,    19,
      14,    90,    73,    92,    93,    94,    95,    32,    54,    55,
      56,    57,    58,    31,    31,    46,    90,    33,    82,    90,
       9,    92,    93,    94,    95,    33,    33,    60,    90,    75,
      88,    33,    78,    79,    90,    81,    12,     5,     6,    90,
       4,    32,    88,    89,    90,    91,    32,    93,    94,    17,
      18,    33,    32,    21,    32,    66,    10,    49,    26,    27,
      28,    29,    30,     4,    31,    73,    34,    35,    36,    31,
      33,    73,    82,    82,    33,    32,    44,    45,    82,    82,
      50,    11,    90,    18,    92,    93,    94,    95,    90,    73,
      92,    93,    94,    95,    60,    61,    62,    65,    82,   332,
      68,    67,   258,    71,   335,   257,    90,    73,    92,    93,
      94,    95,   219,   294,   296,   327,    82,    83,    84,    85,
      86,    87,   198,   285,    90,   208,    92,    93,    94,    95,
      37,    38,    39,    40,    -1,    42,    43,   230
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    17,    18,    21,    26,    27,    28,    29,
      30,    34,    35,    36,    44,    45,    65,    68,    71,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     113,   114,   116,   122,   128,   129,   134,   135,   154,   155,
     156,    13,    14,    38,   109,    14,    16,     7,    31,    54,
      55,    56,    57,    58,    75,    78,    79,    81,    88,    89,
      90,    91,    93,    94,   124,   125,   137,   139,   142,   137,
      90,    15,    47,    53,    90,    20,    90,    69,    99,     0,
       3,   157,    90,    16,    16,    90,    90,    88,    89,   126,
     134,   137,   139,    31,    31,    31,    31,    31,    31,    31,
      31,    46,    88,    89,   139,    33,    73,    90,    92,    93,
      94,    95,    73,    90,   138,    53,    90,    90,    65,    41,
      91,    82,    70,    31,    73,   115,   134,    90,    90,    66,
      33,    33,     8,    32,    32,    32,   137,   142,   143,   137,
     143,   137,   143,   137,   143,   137,   143,   139,   139,   139,
      90,    94,   137,    90,   139,   139,   139,   139,    90,    90,
     144,   145,    48,    59,   148,   136,   139,   150,    93,   124,
      91,    90,   118,   134,    72,   127,    66,    66,    90,   126,
     126,    32,    33,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    33,    33,    33,   138,    76,   140,   141,    31,
      19,    60,   139,   149,   150,   151,   148,    82,    33,    88,
      89,    47,    37,    38,    39,    40,    42,    43,   121,    33,
     117,    74,    90,    90,    90,   142,   143,   139,   139,   139,
      33,    77,   148,   140,   124,   139,    19,    60,    61,    62,
      67,    83,    84,    85,    86,    87,   152,    63,    64,   139,
     136,    14,    31,    60,    80,    81,   120,   118,    32,    82,
      31,    31,    46,    32,    32,    32,   145,    90,     9,   153,
      33,   123,   139,    62,    67,    60,   139,   149,   149,    90,
      88,   119,    80,    81,   117,   115,    90,   144,   146,   146,
     138,     4,    12,   147,   124,    32,    32,   127,    33,    32,
      32,    66,   137,   149,    10,   133,   123,   120,   146,    49,
     149,     4,    31,    75,    78,    79,   110,   131,   132,   142,
      24,    25,    51,    52,   111,   112,    31,    33,    21,    23,
     130,    82,    82,    82,    82,    33,    32,   139,   132,    50,
     110,   119,   119,   112,    33,   139,    32,    11,   119
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   109,   110,   110,   110,   111,   111,   111,
     111,   112,   112,   113,   113,   114,   115,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   120,   120,   120,   120,
     120,   121,   121,   121,   121,   121,   121,   122,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   126,
     126,   126,   127,   127,   128,   129,   130,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   135,   136,   136,   137,
     137,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   143,   143,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   150,   151,   151,   151,   151,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   154,   155,   156,   156,   156,   157,   157
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     0,     1,     1,     1,     3,     3,     3,
       3,     1,     3,    13,     9,     5,     1,     2,     0,     9,
       5,     0,     3,     6,     3,     1,     0,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       1,     2,     1,     2,     1,     1,     1,     3,     3,     1,
       1,     3,     0,     4,     4,     5,     1,     1,     0,     2,
       8,     1,     3,     0,     3,     9,     2,     3,     1,     3,
       1,     0,     2,     1,     2,     2,     3,     3,     3,     3,
       3,     6,     6,     6,     3,     2,     1,     3,     3,     3,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     0,     2,     6,     4,     1,     3,     0,     1,     3,
       1,     2,     4,     1,     3,     0,     2,     0,     2,     0,
       1,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     1,     2,     0,
       3,     7,     2,     4,     3,     3,     0,     1
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
#line 303 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1998 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 333 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 339 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 344 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2023 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 350 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 356 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 362 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2047 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 368 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2057 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 375 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2065 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 381 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2075 "yacc_sql.cpp"
    break;

  case 32: /* unique_op: UNIQUE  */
#line 388 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2083 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: %empty  */
#line 392 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2091 "yacc_sql.cpp"
    break;

  case 34: /* distance_type: L2_DIST  */
#line 398 "yacc_sql.y"
            {
      (yyval.number) = 1;
    }
#line 2099 "yacc_sql.cpp"
    break;

  case 35: /* distance_type: INNER_PRODUCT  */
#line 401 "yacc_sql.y"
                        {
          (yyval.number) = 2;
        }
#line 2107 "yacc_sql.cpp"
    break;

  case 36: /* distance_type: COS_DIST  */
#line 404 "yacc_sql.y"
               {
      (yyval.number) = 3;
    }
#line 2115 "yacc_sql.cpp"
    break;

  case 37: /* vec_index_param: DISTANCE EQ distance_type  */
#line 411 "yacc_sql.y"
                              {
    Value val((int)((yyvsp[0].number)));
                Value valf((int)3);

      (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2126 "yacc_sql.cpp"
    break;

  case 38: /* vec_index_param: LISTS EQ number  */
#line 417 "yacc_sql.y"
                      {
        Value val((int)((yyvsp[0].number)));
            Value valf((int)1);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2136 "yacc_sql.cpp"
    break;

  case 39: /* vec_index_param: PROBS EQ number  */
#line 422 "yacc_sql.y"
                      {
       Value val((int)((yyvsp[0].number)));
        Value valf((int)2);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 40: /* vec_index_param: TYPE EQ IVFFLAT  */
#line 427 "yacc_sql.y"
                      {
        Value valf((int)4);
        Value val((int)(1));
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2156 "yacc_sql.cpp"
    break;

  case 41: /* vec_index_list: vec_index_param  */
#line 435 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2165 "yacc_sql.cpp"
    break;

  case 42: /* vec_index_list: vec_index_param COMMA vec_index_list  */
#line 439 "yacc_sql.y"
                                           {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 43: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE vec_index_list RBRACE  */
#line 453 "yacc_sql.y"
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
#line 2197 "yacc_sql.cpp"
    break;

  case 44: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 469 "yacc_sql.y"
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
#line 2213 "yacc_sql.cpp"
    break;

  case 45: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 484 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 46: /* as_select_opt: select_stmt  */
#line 493 "yacc_sql.y"
                {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 47: /* as_select_opt: AS select_stmt  */
#line 496 "yacc_sql.y"
                     {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 48: /* as_select_opt: %empty  */
#line 500 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 2249 "yacc_sql.cpp"
    break;

  case 49: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format  */
#line 507 "yacc_sql.y"
    {
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
#line 2281 "yacc_sql.cpp"
    break;

  case 50: /* create_table_stmt: CREATE TABLE ID as_select_opt storage_format  */
#line 535 "yacc_sql.y"
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
#line 2304 "yacc_sql.cpp"
    break;

  case 51: /* attr_def_list: %empty  */
#line 557 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2312 "yacc_sql.cpp"
    break;

  case 52: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 561 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 53: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 574 "yacc_sql.y"
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
#line 2349 "yacc_sql.cpp"
    break;

  case 54: /* attr_def: ID type null_t  */
#line 593 "yacc_sql.y"
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
#line 2367 "yacc_sql.cpp"
    break;

  case 55: /* number: NUMBER  */
#line 608 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2373 "yacc_sql.cpp"
    break;

  case 56: /* null_t: %empty  */
#line 612 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 57: /* null_t: NULL_L  */
#line 616 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 58: /* null_t: NULL_T  */
#line 620 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 59: /* null_t: NOT NULL_T  */
#line 624 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 60: /* null_t: NOT NULL_L  */
#line 628 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2413 "yacc_sql.cpp"
    break;

  case 61: /* type: INT_T  */
#line 634 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2419 "yacc_sql.cpp"
    break;

  case 62: /* type: STRING_T  */
#line 635 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2425 "yacc_sql.cpp"
    break;

  case 63: /* type: DATE_T  */
#line 636 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2431 "yacc_sql.cpp"
    break;

  case 64: /* type: FLOAT_T  */
#line 637 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2437 "yacc_sql.cpp"
    break;

  case 65: /* type: VECTOR_T  */
#line 638 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2443 "yacc_sql.cpp"
    break;

  case 66: /* type: TEXT_T  */
#line 639 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2449 "yacc_sql.cpp"
    break;

  case 67: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 643 "yacc_sql.y"
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
#line 2466 "yacc_sql.cpp"
    break;

  case 68: /* value_list: %empty  */
#line 659 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 69: /* value_list: COMMA value value_list  */
#line 662 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2488 "yacc_sql.cpp"
    break;

  case 70: /* value: NUMBER  */
#line 673 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 71: /* value: '-' NUMBER  */
#line 677 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 72: /* value: FLOAT  */
#line 681 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 73: /* value: '-' FLOAT  */
#line 685 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 74: /* value: NULL_T  */
#line 689 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 75: /* value: SSS  */
#line 694 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 76: /* value: v_list  */
#line 700 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2556 "yacc_sql.cpp"
    break;

  case 77: /* v_list: LBRACKET v_l RBRACKET  */
#line 708 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2564 "yacc_sql.cpp"
    break;

  case 78: /* v_l: FLOAT COMMA v_l  */
#line 713 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 79: /* v_l: FLOAT  */
#line 717 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 80: /* v_l: NUMBER  */
#line 721 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 81: /* v_l: NUMBER COMMA v_l  */
#line 725 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 82: /* storage_format: %empty  */
#line 734 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2608 "yacc_sql.cpp"
    break;

  case 83: /* storage_format: STORAGE FORMAT EQ ID  */
#line 738 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 84: /* delete_stmt: DELETE FROM ID where  */
#line 745 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2629 "yacc_sql.cpp"
    break;

  case 85: /* update_stmt: UPDATE ID SET assign_list where  */
#line 756 "yacc_sql.y"
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
#line 2644 "yacc_sql.cpp"
    break;

  case 86: /* order_opt: ASC  */
#line 769 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 87: /* order_opt: DESC  */
#line 772 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 88: /* order_opt: %empty  */
#line 776 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 89: /* order_b: rel_attr order_opt  */
#line 784 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 90: /* order_b: distance_type LBRACE expression COMMA expression RBRACE LIMIT number  */
#line 789 "yacc_sql.y"
    {
      (yyval.expression) = new VecOrderByExpr((yyvsp[-5].expression),(yyvsp[-3].expression),(yyvsp[-7].number), (yyvsp[0].number));
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 91: /* order_by: order_b  */
#line 796 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 92: /* order_by: order_b COMMA order_by  */
#line 801 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 93: /* order_by_list: %empty  */
#line 813 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 94: /* order_by_list: ORDER BY order_by  */
#line 817 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 95: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 824 "yacc_sql.y"
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
#line 2764 "yacc_sql.cpp"
    break;

  case 96: /* calc_stmt: CALC expression_list  */
#line 863 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 97: /* assign_list: eq_expr COMMA assign_list  */
#line 871 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2787 "yacc_sql.cpp"
    break;

  case 98: /* assign_list: eq_expr  */
#line 880 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 99: /* expression_list: expression COMMA expression_list  */
#line 888 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 100: /* expression_list: expression  */
#line 897 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 101: /* as_opt: %empty  */
#line 904 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 102: /* as_opt: AS ID  */
#line 908 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 103: /* as_opt: ID  */
#line 912 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2842 "yacc_sql.cpp"
    break;

  case 104: /* expression: rel_attr as_opt  */
#line 918 "yacc_sql.y"
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
#line 2863 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression ID  */
#line 934 "yacc_sql.y"
                    {
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression AS ID  */
#line 939 "yacc_sql.y"
                      {
            (yyval.expression) = (yyvsp[-2].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2883 "yacc_sql.cpp"
    break;

  case 107: /* expression: expression '+' expression  */
#line 944 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2891 "yacc_sql.cpp"
    break;

  case 108: /* expression: expression '-' expression  */
#line 947 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 109: /* expression: expression '*' expression  */
#line 950 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 110: /* expression: expression '/' expression  */
#line 953 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 111: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 956 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 112: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 959 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 113: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 963 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 114: /* expression: LBRACE expression RBRACE  */
#line 967 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 115: /* expression: '-' expression  */
#line 971 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 116: /* expression: value  */
#line 974 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 117: /* expression: LBRACE select_stmt RBRACE  */
#line 980 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 118: /* expression: LBRACE expression_list RBRACE  */
#line 984 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 119: /* expression: ID DOT '*'  */
#line 988 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 120: /* expression: '*'  */
#line 992 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 121: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 995 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 122: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 998 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 123: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 1001 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 124: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 1004 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 125: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 1007 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 126: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 1010 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3050 "yacc_sql.cpp"
    break;

  case 127: /* expression: SUM LBRACE expression_list RBRACE  */
#line 1014 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 128: /* expression: AVG LBRACE expression_list RBRACE  */
#line 1018 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 129: /* expression: MAX LBRACE expression_list RBRACE  */
#line 1022 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3077 "yacc_sql.cpp"
    break;

  case 130: /* expression: MIN LBRACE expression_list RBRACE  */
#line 1026 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3086 "yacc_sql.cpp"
    break;

  case 131: /* inner_joins: %empty  */
#line 1036 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3094 "yacc_sql.cpp"
    break;

  case 132: /* inner_joins: inner_join inner_joins  */
#line 1039 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 133: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 1050 "yacc_sql.y"
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
#line 3127 "yacc_sql.cpp"
    break;

  case 134: /* inner_join: INNER JOIN ID as_opt  */
#line 1064 "yacc_sql.y"
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
#line 3146 "yacc_sql.cpp"
    break;

  case 135: /* rel_attr: ID  */
#line 1081 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3156 "yacc_sql.cpp"
    break;

  case 136: /* rel_attr: ID DOT ID  */
#line 1086 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3168 "yacc_sql.cpp"
    break;

  case 137: /* rel_attr_list: %empty  */
#line 1097 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 3176 "yacc_sql.cpp"
    break;

  case 138: /* rel_attr_list: rel_attr  */
#line 1100 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 3186 "yacc_sql.cpp"
    break;

  case 139: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 1105 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 3200 "yacc_sql.cpp"
    break;

  case 140: /* relation: ID  */
#line 1117 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3208 "yacc_sql.cpp"
    break;

  case 141: /* rel_table_list: relation as_opt  */
#line 1123 "yacc_sql.y"
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
#line 3228 "yacc_sql.cpp"
    break;

  case 142: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 1138 "yacc_sql.y"
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
#line 3252 "yacc_sql.cpp"
    break;

  case 143: /* rel_list: relation  */
#line 1161 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3266 "yacc_sql.cpp"
    break;

  case 144: /* rel_list: relation COMMA rel_list  */
#line 1170 "yacc_sql.y"
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
#line 3284 "yacc_sql.cpp"
    break;

  case 145: /* having: %empty  */
#line 1186 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3292 "yacc_sql.cpp"
    break;

  case 146: /* having: HAVING condition_list  */
#line 1189 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3300 "yacc_sql.cpp"
    break;

  case 147: /* where: %empty  */
#line 1197 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3308 "yacc_sql.cpp"
    break;

  case 148: /* where: WHERE condition_list  */
#line 1200 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3316 "yacc_sql.cpp"
    break;

  case 149: /* condition_list: %empty  */
#line 1206 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3324 "yacc_sql.cpp"
    break;

  case 150: /* condition_list: condition  */
#line 1209 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 151: /* condition_list: condition AND condition_list  */
#line 1212 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: condition OR condition_list  */
#line 1218 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3354 "yacc_sql.cpp"
    break;

  case 153: /* eq_expr: expression EQ expression  */
#line 1228 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3362 "yacc_sql.cpp"
    break;

  case 154: /* condition: expression comp_op expression  */
#line 1235 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3370 "yacc_sql.cpp"
    break;

  case 155: /* condition: EXISTS expression  */
#line 1239 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3378 "yacc_sql.cpp"
    break;

  case 156: /* condition: NOT EXISTS expression  */
#line 1243 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3386 "yacc_sql.cpp"
    break;

  case 157: /* condition: eq_expr  */
#line 1247 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3394 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: LT  */
#line 1253 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3400 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: GT  */
#line 1254 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3406 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: LE  */
#line 1255 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3412 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: GE  */
#line 1256 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3418 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NE  */
#line 1257 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3424 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: IS NOT  */
#line 1258 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3430 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: IS  */
#line 1259 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3436 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: NOT LIKE  */
#line 1260 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3442 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: LIKE  */
#line 1261 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3448 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: IN  */
#line 1262 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3454 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NOT IN  */
#line 1263 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3460 "yacc_sql.cpp"
    break;

  case 169: /* group_by: %empty  */
#line 1268 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3468 "yacc_sql.cpp"
    break;

  case 170: /* group_by: GROUP BY expression_list  */
#line 1271 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3476 "yacc_sql.cpp"
    break;

  case 171: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1277 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3490 "yacc_sql.cpp"
    break;

  case 172: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1290 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3499 "yacc_sql.cpp"
    break;

  case 173: /* set_variable_stmt: SET ID EQ value  */
#line 1298 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3511 "yacc_sql.cpp"
    break;

  case 174: /* set_variable_stmt: SET NAMES SSS  */
#line 1306 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
      (yyval.sql_node)->set_variable.value = Value((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3522 "yacc_sql.cpp"
    break;

  case 175: /* set_variable_stmt: SET NAMES UTF8MB4_BIN  */
#line 1313 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name = "NAMES";
    }
#line 3531 "yacc_sql.cpp"
    break;


#line 3535 "yacc_sql.cpp"

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

#line 1322 "yacc_sql.y"

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
