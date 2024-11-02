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
  YYSYMBOL_DESC = 20,                      /* DESC  */
  YYSYMBOL_ASC = 21,                       /* ASC  */
  YYSYMBOL_TYPE = 22,                      /* TYPE  */
  YYSYMBOL_DISTANCE = 23,                  /* DISTANCE  */
  YYSYMBOL_SHOW = 24,                      /* SHOW  */
  YYSYMBOL_SYNC = 25,                      /* SYNC  */
  YYSYMBOL_INSERT = 26,                    /* INSERT  */
  YYSYMBOL_DELETE = 27,                    /* DELETE  */
  YYSYMBOL_UPDATE = 28,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 29,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 30,                    /* RBRACE  */
  YYSYMBOL_COMMA = 31,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 32,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 33,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 34,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 35,                     /* INT_T  */
  YYSYMBOL_VECTOR_T = 36,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 37,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 38,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 39,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 40,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 41,                      /* HELP  */
  YYSYMBOL_EXIT = 42,                      /* EXIT  */
  YYSYMBOL_DOT = 43,                       /* DOT  */
  YYSYMBOL_INTO = 44,                      /* INTO  */
  YYSYMBOL_VALUES = 45,                    /* VALUES  */
  YYSYMBOL_WITH = 46,                      /* WITH  */
  YYSYMBOL_IVFFLAT = 47,                   /* IVFFLAT  */
  YYSYMBOL_LISTS = 48,                     /* LISTS  */
  YYSYMBOL_PROBS = 49,                     /* PROBS  */
  YYSYMBOL_FROM = 50,                      /* FROM  */
  YYSYMBOL_SUM = 51,                       /* SUM  */
  YYSYMBOL_AVG = 52,                       /* AVG  */
  YYSYMBOL_MAX = 53,                       /* MAX  */
  YYSYMBOL_MIN = 54,                       /* MIN  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_WHERE = 56,                     /* WHERE  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_IS = 58,                        /* IS  */
  YYSYMBOL_LIKE = 59,                      /* LIKE  */
  YYSYMBOL_AND = 60,                       /* AND  */
  YYSYMBOL_OR = 61,                        /* OR  */
  YYSYMBOL_SET = 62,                       /* SET  */
  YYSYMBOL_ON = 63,                        /* ON  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_LOAD = 65,                      /* LOAD  */
  YYSYMBOL_DATA = 66,                      /* DATA  */
  YYSYMBOL_INFILE = 67,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 68,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 69,                   /* STORAGE  */
  YYSYMBOL_AS = 70,                        /* AS  */
  YYSYMBOL_FORMAT = 71,                    /* FORMAT  */
  YYSYMBOL_INNER_PRODUCT = 72,             /* INNER_PRODUCT  */
  YYSYMBOL_INNER = 73,                     /* INNER  */
  YYSYMBOL_JOIN = 74,                      /* JOIN  */
  YYSYMBOL_L2_DIST = 75,                   /* L2_DIST  */
  YYSYMBOL_COS_DIST = 76,                  /* COS_DIST  */
  YYSYMBOL_NULL_L = 77,                    /* NULL_L  */
  YYSYMBOL_NULL_T = 78,                    /* NULL_T  */
  YYSYMBOL_EQ = 79,                        /* EQ  */
  YYSYMBOL_LT = 80,                        /* LT  */
  YYSYMBOL_GT = 81,                        /* GT  */
  YYSYMBOL_LE = 82,                        /* LE  */
  YYSYMBOL_GE = 83,                        /* GE  */
  YYSYMBOL_NE = 84,                        /* NE  */
  YYSYMBOL_NUMBER = 85,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 86,                     /* FLOAT  */
  YYSYMBOL_ID = 87,                        /* ID  */
  YYSYMBOL_SSS = 88,                       /* SSS  */
  YYSYMBOL_89_ = 89,                       /* '+'  */
  YYSYMBOL_90_ = 90,                       /* '-'  */
  YYSYMBOL_91_ = 91,                       /* '*'  */
  YYSYMBOL_92_ = 92,                       /* '/'  */
  YYSYMBOL_UMINUS = 93,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_commands = 95,                  /* commands  */
  YYSYMBOL_command_wrapper = 96,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 97,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 98,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 99,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 100,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 101,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 102,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 103,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 104,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 105,          /* desc_table_stmt  */
  YYSYMBOL_unique_op = 106,                /* unique_op  */
  YYSYMBOL_distance_type = 107,            /* distance_type  */
  YYSYMBOL_vec_index_param = 108,          /* vec_index_param  */
  YYSYMBOL_vec_index_list = 109,           /* vec_index_list  */
  YYSYMBOL_create_index_stmt = 110,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 111,          /* drop_index_stmt  */
  YYSYMBOL_as_select_opt = 112,            /* as_select_opt  */
  YYSYMBOL_create_table_stmt = 113,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 114,            /* attr_def_list  */
  YYSYMBOL_attr_def = 115,                 /* attr_def  */
  YYSYMBOL_number = 116,                   /* number  */
  YYSYMBOL_null_t = 117,                   /* null_t  */
  YYSYMBOL_type = 118,                     /* type  */
  YYSYMBOL_insert_stmt = 119,              /* insert_stmt  */
  YYSYMBOL_value_list = 120,               /* value_list  */
  YYSYMBOL_value = 121,                    /* value  */
  YYSYMBOL_v_list = 122,                   /* v_list  */
  YYSYMBOL_v_l = 123,                      /* v_l  */
  YYSYMBOL_storage_format = 124,           /* storage_format  */
  YYSYMBOL_delete_stmt = 125,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 126,              /* update_stmt  */
  YYSYMBOL_order_opt = 127,                /* order_opt  */
  YYSYMBOL_order_b = 128,                  /* order_b  */
  YYSYMBOL_order_by = 129,                 /* order_by  */
  YYSYMBOL_order_by_list = 130,            /* order_by_list  */
  YYSYMBOL_select_stmt = 131,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 132,                /* calc_stmt  */
  YYSYMBOL_assign_list = 133,              /* assign_list  */
  YYSYMBOL_expression_list = 134,          /* expression_list  */
  YYSYMBOL_as_opt = 135,                   /* as_opt  */
  YYSYMBOL_expression = 136,               /* expression  */
  YYSYMBOL_inner_joins = 137,              /* inner_joins  */
  YYSYMBOL_inner_join = 138,               /* inner_join  */
  YYSYMBOL_rel_attr = 139,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 140,            /* rel_attr_list  */
  YYSYMBOL_relation = 141,                 /* relation  */
  YYSYMBOL_rel_table_list = 142,           /* rel_table_list  */
  YYSYMBOL_rel_list = 143,                 /* rel_list  */
  YYSYMBOL_having = 144,                   /* having  */
  YYSYMBOL_where = 145,                    /* where  */
  YYSYMBOL_condition_list = 146,           /* condition_list  */
  YYSYMBOL_eq_expr = 147,                  /* eq_expr  */
  YYSYMBOL_condition = 148,                /* condition  */
  YYSYMBOL_comp_op = 149,                  /* comp_op  */
  YYSYMBOL_group_by = 150,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 151,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 152,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 153,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 154             /* opt_semicolon  */
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
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   444

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  346

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


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
       2,     2,    91,    89,     2,    90,     2,    92,     2,     2,
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
      85,    86,    87,    88,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   299,   299,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   330,   336,   341,   347,   353,   359,   365,
     372,   378,   385,   389,   395,   398,   401,   408,   414,   419,
     424,   432,   436,   449,   465,   480,   490,   493,   497,   503,
     531,   553,   556,   569,   588,   604,   608,   611,   615,   619,
     623,   630,   631,   632,   633,   634,   635,   638,   655,   658,
     669,   673,   677,   681,   685,   690,   696,   704,   709,   713,
     717,   721,   730,   733,   740,   751,   765,   768,   772,   779,
     784,   791,   796,   809,   812,   819,   858,   866,   875,   883,
     892,   900,   903,   907,   914,   930,   935,   940,   943,   946,
     949,   952,   955,   959,   963,   967,   970,   976,   980,   984,
     988,   991,   994,   997,  1000,  1003,  1006,  1010,  1014,  1018,
    1022,  1032,  1035,  1046,  1060,  1077,  1082,  1093,  1096,  1101,
    1113,  1119,  1134,  1157,  1166,  1182,  1185,  1193,  1196,  1202,
    1205,  1208,  1214,  1223,  1230,  1234,  1238,  1242,  1249,  1250,
    1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,  1259,  1264,
    1267,  1272,  1285,  1293,  1303,  1304
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
  "EXISTS", "DESC", "ASC", "TYPE", "DISTANCE", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "VECTOR_T", "TEXT_T", "STRING_T",
  "DATE_T", "FLOAT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "WITH",
  "IVFFLAT", "LISTS", "PROBS", "FROM", "SUM", "AVG", "MAX", "MIN", "COUNT",
  "WHERE", "NOT", "IS", "LIKE", "AND", "OR", "SET", "ON", "IN", "LOAD",
  "DATA", "INFILE", "EXPLAIN", "STORAGE", "AS", "FORMAT", "INNER_PRODUCT",
  "INNER", "JOIN", "L2_DIST", "COS_DIST", "NULL_L", "NULL_T", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "unique_op", "distance_type", "vec_index_param",
  "vec_index_list", "create_index_stmt", "drop_index_stmt",
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

#define YYPACT_NINF (-292)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     338,    28,    52,   235,   235,   -65,    13,  -292,    -6,    30,
     -29,  -292,  -292,  -292,  -292,  -292,   -20,    16,   338,    85,
     100,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,    18,   103,   107,    29,    39,   -42,   181,    99,
     104,   134,   135,   136,   149,   154,   155,  -292,  -292,  -292,
     110,  -292,   263,  -292,  -292,  -292,  -292,   124,   -41,   139,
    -292,  -292,   105,   111,   142,   128,   119,  -292,  -292,  -292,
    -292,     7,   125,   131,  -292,   157,   188,   191,   216,   201,
     207,    17,   235,   235,   235,   235,   235,   235,   235,   235,
      24,  -292,  -292,  -292,   235,   151,  -292,   235,   235,   235,
     235,   153,  -292,  -292,   162,   206,   196,   235,    -2,   166,
     168,   240,   192,  -292,   199,   200,   178,   -42,   -42,  -292,
    -292,  -292,  -292,   244,   -16,   246,   248,   254,   261,   271,
     276,   278,   279,   289,   190,   213,   242,  -292,  -292,  -292,
    -292,     5,     5,  -292,  -292,  -292,  -292,   -41,   251,   298,
     115,  -292,   196,   138,   299,    60,  -292,   292,   259,   306,
    -292,   269,  -292,   255,   258,  -292,  -292,  -292,  -292,   260,
    -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,   235,
     235,   235,   315,   283,   196,   251,    -2,   235,   333,   334,
    -292,  -292,    87,  -292,   235,   235,  -292,  -292,   345,  -292,
    -292,  -292,  -292,  -292,  -292,    -5,   168,   330,   282,   339,
     340,   331,   342,  -292,    40,    48,    84,   162,   288,   367,
    -292,   346,   156,   235,   -27,   321,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,   235,   115,   115,   156,  -292,   294,   300,
      73,  -292,  -292,  -292,   306,     9,   295,   162,   162,   296,
    -292,  -292,  -292,  -292,   -41,   386,   382,    -2,   365,   156,
    -292,  -292,  -292,   156,  -292,  -292,  -292,  -292,   366,  -292,
    -292,  -292,   192,  -292,   368,   371,   372,   344,   235,   115,
     387,   346,  -292,   -44,  -292,   162,   359,  -292,   115,  -292,
    -292,   404,  -292,  -292,  -292,  -292,   380,  -292,    49,     8,
    -292,  -292,  -292,   381,   388,  -292,   141,   332,   341,   343,
     348,   397,   399,   235,    49,  -292,  -292,  -292,   383,    23,
     300,   300,     8,  -292,   297,  -292,  -292,  -292,  -292,  -292,
    -292,   235,    90,   401,   300,  -292
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     174,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    74,    70,    72,
     135,    75,     0,   120,   116,    76,    96,   100,   101,     0,
      31,    30,     0,     0,     0,     0,     0,   172,     1,   175,
       2,    48,     0,     0,    29,     0,    80,    79,     0,     0,
       0,     0,   137,   137,   137,   137,   137,     0,     0,     0,
       0,    70,    72,   115,     0,     0,   105,     0,     0,     0,
       0,     0,   103,   104,     0,     0,   147,     0,     0,     0,
       0,     0,    82,    46,     0,     0,     0,     0,     0,    77,
     117,   118,   114,     0,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   136,   119,    99,
     106,   107,   108,   109,   110,   102,   140,   101,   131,     0,
     149,    84,   147,     0,    98,     0,   173,     0,     0,    51,
      47,     0,    50,     0,     0,    45,    81,    78,   127,   137,
     122,   128,   123,   129,   124,   130,   125,   126,   121,     0,
       0,     0,   141,     0,   147,   131,     0,     0,     0,     0,
     148,   157,   150,    85,     0,     0,    71,    73,     0,    61,
      65,    66,    62,    63,    64,    56,     0,     0,     0,     0,
       0,   135,   138,   139,     0,     0,     0,     0,     0,   169,
     132,    68,   155,     0,     0,   164,   166,   167,   158,   159,
     160,   161,   162,     0,   149,   149,   153,    97,     0,     0,
       0,    57,    58,    54,    51,    48,     0,     0,     0,     0,
     113,   111,   112,   142,   101,     0,   145,     0,     0,   156,
     165,   168,   163,   154,   151,   152,   171,    55,     0,    60,
      59,    52,    82,    83,   143,     0,     0,   134,     0,   149,
      93,    68,    67,    56,    49,     0,     0,    44,   149,   170,
     146,     0,    95,    69,    53,   144,     0,   133,     0,     0,
      35,    34,    36,     0,    91,    94,    88,     0,     0,     0,
       0,    41,     0,     0,     0,    87,    86,    89,     0,     0,
       0,     0,     0,    43,     0,    92,    40,    37,    38,    39,
      42,     0,     0,     0,     0,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -292,  -292,   413,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,   106,  -292,   101,  -292,  -292,   177,  -292,
     180,   220,  -291,   144,  -292,  -292,   147,  -115,  -292,    31,
     158,  -292,  -292,  -292,  -292,   117,  -292,   -46,  -292,   234,
      -3,  -151,   -48,   247,  -292,   -85,   -77,  -110,   217,  -232,
    -292,  -139,  -224,  -105,  -292,  -292,  -292,  -292,  -292,  -292,
    -292
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    44,   313,   321,   322,    30,    31,   122,    32,
     217,   169,   278,   253,   215,    33,   268,    64,    65,    88,
     172,    34,    35,   327,   314,   315,   302,    36,    37,   162,
      66,   113,    67,   194,   195,    68,   135,   284,   158,   285,
     290,   161,   200,   201,   202,   243,   266,    38,    39,    40,
      80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,    69,    89,   166,   157,    47,   192,   134,   134,   134,
     134,   134,   164,   250,   103,   179,   137,   139,   141,   143,
     274,   275,    70,   203,   249,     4,   286,     4,    71,   111,
     317,   318,   270,   251,   252,   123,   120,   271,    72,   338,
     339,    41,    42,    86,    87,    90,   112,   132,   104,   144,
     145,   146,   250,   345,   111,   229,   319,   320,    74,   151,
     152,   153,   154,   305,    43,   300,    45,    75,    46,   163,
     260,   112,   251,   252,   307,   170,    57,   121,   261,   121,
      73,   231,    76,    58,    59,    78,    61,   105,   165,   133,
     136,   138,   140,   142,   222,   310,   109,   110,   311,   312,
     164,   149,   223,    79,   106,    81,   107,   108,   109,   110,
     105,   147,   199,   287,   262,   148,    84,   157,   105,    82,
     343,   310,    47,    83,   311,   312,    85,   106,    92,   107,
     108,   109,   110,    93,   197,   106,   221,   107,   108,   109,
     110,   224,   225,   226,    48,   206,   207,   244,   245,   232,
     279,   280,   291,   100,   105,   104,   246,   163,   176,   177,
     105,   325,   326,    94,    95,    96,    49,    50,    51,    52,
      53,   106,   198,   107,   108,   109,   110,   106,    97,   107,
     108,   109,   110,    98,    99,   269,   119,    54,    47,   114,
      55,    56,   115,    57,   105,   273,   199,   199,   116,     4,
      58,    59,    60,    61,   117,    62,    63,   118,   105,   123,
      48,   106,   124,   107,   108,   109,   110,   204,   125,   127,
     126,   189,   128,   316,   129,   106,   105,   107,   108,   109,
     110,   130,    49,    50,    51,    52,    53,   131,   150,   316,
     155,   199,    47,   106,   190,   107,   108,   109,   110,   156,
     199,   159,   160,    54,   167,   168,    55,    56,     4,    57,
     105,   171,   173,   174,    48,   175,    58,    59,    60,    61,
      47,    62,    63,   191,   178,   334,   180,   106,   181,   107,
     108,   109,   110,   105,   182,   299,    49,    50,    51,    52,
      53,   183,    48,   342,   209,   210,   211,   212,   213,   214,
     106,   184,   107,   108,   109,   110,   185,    54,   186,   187,
      55,    56,   105,    57,    49,    50,    51,    52,    53,   188,
      58,    59,    60,    61,   193,    62,    63,   196,   341,   106,
     205,   107,   108,   109,   110,    54,   208,   216,    55,    56,
     218,    57,   219,     1,     2,   220,   227,   221,   101,   102,
      60,    61,   233,    62,    63,     3,     4,   228,     5,   248,
     255,   256,     6,     7,     8,     9,    10,   105,   257,   258,
      11,    12,    13,   179,   259,   264,   265,   267,   272,    14,
      15,   276,   283,   147,   106,   277,   107,   108,   109,   110,
     288,   234,   235,   236,   289,   292,   293,   301,   237,   295,
      16,   296,   297,    17,   105,   306,    18,   298,   308,   309,
     323,   328,   344,   204,   238,   239,   240,   241,   242,   324,
     329,   106,   330,   107,   108,   109,   110,   331,   332,   333,
     336,    77,   282,   340,   281,   337,   254,   304,   303,   247,
     294,   335,   230,     0,   263
};

static const yytype_int16 yycheck[] =
{
      48,     4,    48,   118,   114,     7,   157,    92,    93,    94,
      95,    96,   117,    57,    62,    31,    93,    94,    95,    96,
     244,   245,    87,   162,    29,    18,   258,    18,    15,    70,
      22,    23,    59,    77,    78,    81,    29,    64,    44,   330,
     331,    13,    14,    85,    86,    48,    87,    30,    31,    97,
      98,    99,    57,   344,    70,   194,    48,    49,    87,   107,
     108,   109,   110,   295,    36,   289,    14,    87,    16,   117,
      30,    87,    77,    78,   298,   121,    78,    70,    30,    70,
      50,   196,    66,    85,    86,     0,    88,    70,    90,    92,
      93,    94,    95,    96,   179,    72,    91,    92,    75,    76,
     205,   104,   179,     3,    87,    87,    89,    90,    91,    92,
      70,    87,   160,   264,    30,    91,    87,   227,    70,    16,
      30,    72,     7,    16,    75,    76,    87,    87,    29,    89,
      90,    91,    92,    29,    19,    87,    87,    89,    90,    91,
      92,   189,   190,   191,    29,    85,    86,    60,    61,   197,
      77,    78,   267,    43,    70,    31,   204,   205,   127,   128,
      70,    20,    21,    29,    29,    29,    51,    52,    53,    54,
      55,    87,    57,    89,    90,    91,    92,    87,    29,    89,
      90,    91,    92,    29,    29,   233,    67,    72,     7,    50,
      75,    76,    87,    78,    70,   243,   244,   245,    87,    18,
      85,    86,    87,    88,    62,    90,    91,    79,    70,   255,
      29,    87,    87,    89,    90,    91,    92,    79,    87,    31,
      63,    31,    31,   308,     8,    87,    70,    89,    90,    91,
      92,    30,    51,    52,    53,    54,    55,    30,    87,   324,
      87,   289,     7,    87,    31,    89,    90,    91,    92,    87,
     298,    45,    56,    72,    88,    87,    75,    76,    18,    78,
      70,    69,    63,    63,    29,    87,    85,    86,    87,    88,
       7,    90,    91,    31,    30,   323,    30,    87,    30,    89,
      90,    91,    92,    70,    30,   288,    51,    52,    53,    54,
      55,    30,    29,   341,    35,    36,    37,    38,    39,    40,
      87,    30,    89,    90,    91,    92,    30,    72,    30,    30,
      75,    76,    70,    78,    51,    52,    53,    54,    55,    30,
      85,    86,    87,    88,    73,    90,    91,    29,    31,    87,
      31,    89,    90,    91,    92,    72,    44,    31,    75,    76,
      71,    78,    87,     5,     6,    87,    31,    87,    85,    86,
      87,    88,    19,    90,    91,    17,    18,    74,    20,    14,
      30,    79,    24,    25,    26,    27,    28,    70,    29,    29,
      32,    33,    34,    31,    43,    87,     9,    31,    57,    41,
      42,    87,    87,    87,    87,    85,    89,    90,    91,    92,
       4,    57,    58,    59,    12,    30,    30,    10,    64,    31,
      62,    30,    30,    65,    70,    46,    68,    63,     4,    29,
      29,    79,    11,    79,    80,    81,    82,    83,    84,    31,
      79,    87,    79,    89,    90,    91,    92,    79,    31,    30,
      47,    18,   255,   332,   254,   329,   216,   293,   291,   205,
     282,   324,   195,    -1,   227
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    17,    18,    20,    24,    25,    26,    27,
      28,    32,    33,    34,    41,    42,    62,    65,    68,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     110,   111,   113,   119,   125,   126,   131,   132,   151,   152,
     153,    13,    14,    36,   106,    14,    16,     7,    29,    51,
      52,    53,    54,    55,    72,    75,    76,    78,    85,    86,
      87,    88,    90,    91,   121,   122,   134,   136,   139,   134,
      87,    15,    44,    50,    87,    87,    66,    96,     0,     3,
     154,    87,    16,    16,    87,    87,    85,    86,   123,   131,
     134,   136,    29,    29,    29,    29,    29,    29,    29,    29,
      43,    85,    86,   136,    31,    70,    87,    89,    90,    91,
      92,    70,    87,   135,    50,    87,    87,    62,    79,    67,
      29,    70,   112,   131,    87,    87,    63,    31,    31,     8,
      30,    30,    30,   134,   139,   140,   134,   140,   134,   140,
     134,   140,   134,   140,   136,   136,   136,    87,    91,   134,
      87,   136,   136,   136,   136,    87,    87,   141,   142,    45,
      56,   145,   133,   136,   147,    90,   121,    88,    87,   115,
     131,    69,   124,    63,    63,    87,   123,   123,    30,    31,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    31,
      31,    31,   135,    73,   137,   138,    29,    19,    57,   136,
     146,   147,   148,   145,    79,    31,    85,    86,    44,    35,
      36,    37,    38,    39,    40,   118,    31,   114,    71,    87,
      87,    87,   139,   140,   136,   136,   136,    31,    74,   145,
     137,   121,   136,    19,    57,    58,    59,    64,    80,    81,
      82,    83,    84,   149,    60,    61,   136,   133,    14,    29,
      57,    77,    78,   117,   115,    30,    79,    29,    29,    43,
      30,    30,    30,   142,    87,     9,   150,    31,   120,   136,
      59,    64,    57,   136,   146,   146,    87,    85,   116,    77,
      78,   114,   112,    87,   141,   143,   143,   135,     4,    12,
     144,   121,    30,    30,   124,    31,    30,    30,    63,   134,
     146,    10,   130,   120,   117,   143,    46,   146,     4,    29,
      72,    75,    76,   107,   128,   129,   139,    22,    23,    48,
      49,   108,   109,    29,    31,    20,    21,   127,    79,    79,
      79,    79,    31,    30,   136,   129,    47,   107,   116,   116,
     109,    31,   136,    30,    11,   116
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   106,   107,   107,   107,   108,   108,   108,
     108,   109,   109,   110,   110,   111,   112,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   119,   120,   120,
     121,   121,   121,   121,   121,   121,   121,   122,   123,   123,
     123,   123,   124,   124,   125,   126,   127,   127,   127,   128,
     128,   129,   129,   130,   130,   131,   132,   133,   133,   134,
     134,   135,   135,   135,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   137,   137,   138,   138,   139,   139,   140,   140,   140,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   146,   146,   147,   148,   148,   148,   148,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     150,   151,   152,   153,   154,   154
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
       3,     7,     2,     4,     0,     1
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
#line 300 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1995 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 330 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 336 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 341 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 347 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 353 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 359 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 365 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 372 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2062 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 378 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 32: /* unique_op: UNIQUE  */
#line 385 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2080 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: %empty  */
#line 389 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 34: /* distance_type: L2_DIST  */
#line 395 "yacc_sql.y"
            {
      (yyval.number) = 1;
    }
#line 2096 "yacc_sql.cpp"
    break;

  case 35: /* distance_type: INNER_PRODUCT  */
#line 398 "yacc_sql.y"
                        {
          (yyval.number) = 2;
        }
#line 2104 "yacc_sql.cpp"
    break;

  case 36: /* distance_type: COS_DIST  */
#line 401 "yacc_sql.y"
               {
      (yyval.number) = 3;
    }
#line 2112 "yacc_sql.cpp"
    break;

  case 37: /* vec_index_param: DISTANCE EQ distance_type  */
#line 408 "yacc_sql.y"
                              {
    Value val((int)((yyvsp[0].number)));
                Value valf((int)3);

      (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2123 "yacc_sql.cpp"
    break;

  case 38: /* vec_index_param: LISTS EQ number  */
#line 414 "yacc_sql.y"
                      {
        Value val((int)((yyvsp[0].number)));
            Value valf((int)1);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 39: /* vec_index_param: PROBS EQ number  */
#line 419 "yacc_sql.y"
                      {
       Value val((int)((yyvsp[0].number)));
        Value valf((int)2);
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 40: /* vec_index_param: TYPE EQ IVFFLAT  */
#line 424 "yacc_sql.y"
                      {
        Value valf((int)4);
        Value val((int)(1));
        (yyval.expression) = create_comparison_expression(EQUAL_TO, new ValueExpr(valf), new ValueExpr(val), sql_string, &(yyloc));
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 41: /* vec_index_list: vec_index_param  */
#line 432 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2162 "yacc_sql.cpp"
    break;

  case 42: /* vec_index_list: vec_index_param COMMA vec_index_list  */
#line 436 "yacc_sql.y"
                                           {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2175 "yacc_sql.cpp"
    break;

  case 43: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE vec_index_list RBRACE  */
#line 450 "yacc_sql.y"
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
#line 2194 "yacc_sql.cpp"
    break;

  case 44: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 466 "yacc_sql.y"
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
#line 2210 "yacc_sql.cpp"
    break;

  case 45: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 481 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 46: /* as_select_opt: select_stmt  */
#line 490 "yacc_sql.y"
                {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 47: /* as_select_opt: AS select_stmt  */
#line 493 "yacc_sql.y"
                     {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2238 "yacc_sql.cpp"
    break;

  case 48: /* as_select_opt: %empty  */
#line 497 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 2246 "yacc_sql.cpp"
    break;

  case 49: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format  */
#line 504 "yacc_sql.y"
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
#line 2278 "yacc_sql.cpp"
    break;

  case 50: /* create_table_stmt: CREATE TABLE ID as_select_opt storage_format  */
#line 532 "yacc_sql.y"
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
#line 2301 "yacc_sql.cpp"
    break;

  case 51: /* attr_def_list: %empty  */
#line 553 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2309 "yacc_sql.cpp"
    break;

  case 52: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 557 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 53: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 570 "yacc_sql.y"
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
#line 2346 "yacc_sql.cpp"
    break;

  case 54: /* attr_def: ID type null_t  */
#line 589 "yacc_sql.y"
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
#line 2364 "yacc_sql.cpp"
    break;

  case 55: /* number: NUMBER  */
#line 604 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2370 "yacc_sql.cpp"
    break;

  case 56: /* null_t: %empty  */
#line 608 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2378 "yacc_sql.cpp"
    break;

  case 57: /* null_t: NULL_L  */
#line 612 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 58: /* null_t: NULL_T  */
#line 616 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2394 "yacc_sql.cpp"
    break;

  case 59: /* null_t: NOT NULL_T  */
#line 620 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2402 "yacc_sql.cpp"
    break;

  case 60: /* null_t: NOT NULL_L  */
#line 624 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 61: /* type: INT_T  */
#line 630 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2416 "yacc_sql.cpp"
    break;

  case 62: /* type: STRING_T  */
#line 631 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2422 "yacc_sql.cpp"
    break;

  case 63: /* type: DATE_T  */
#line 632 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2428 "yacc_sql.cpp"
    break;

  case 64: /* type: FLOAT_T  */
#line 633 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2434 "yacc_sql.cpp"
    break;

  case 65: /* type: VECTOR_T  */
#line 634 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2440 "yacc_sql.cpp"
    break;

  case 66: /* type: TEXT_T  */
#line 635 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2446 "yacc_sql.cpp"
    break;

  case 67: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 639 "yacc_sql.y"
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
#line 2463 "yacc_sql.cpp"
    break;

  case 68: /* value_list: %empty  */
#line 655 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 69: /* value_list: COMMA value value_list  */
#line 658 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 70: /* value: NUMBER  */
#line 669 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 71: /* value: '-' NUMBER  */
#line 673 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 72: /* value: FLOAT  */
#line 677 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 73: /* value: '-' FLOAT  */
#line 681 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 74: /* value: NULL_T  */
#line 685 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 75: /* value: SSS  */
#line 690 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2542 "yacc_sql.cpp"
    break;

  case 76: /* value: v_list  */
#line 696 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 77: /* v_list: LBRACKET v_l RBRACKET  */
#line 704 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 78: /* v_l: FLOAT COMMA v_l  */
#line 709 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2570 "yacc_sql.cpp"
    break;

  case 79: /* v_l: FLOAT  */
#line 713 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 80: /* v_l: NUMBER  */
#line 717 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2588 "yacc_sql.cpp"
    break;

  case 81: /* v_l: NUMBER COMMA v_l  */
#line 721 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 82: /* storage_format: %empty  */
#line 730 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2605 "yacc_sql.cpp"
    break;

  case 83: /* storage_format: STORAGE FORMAT EQ ID  */
#line 734 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 84: /* delete_stmt: DELETE FROM ID where  */
#line 741 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2626 "yacc_sql.cpp"
    break;

  case 85: /* update_stmt: UPDATE ID SET assign_list where  */
#line 752 "yacc_sql.y"
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
#line 2641 "yacc_sql.cpp"
    break;

  case 86: /* order_opt: ASC  */
#line 765 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 87: /* order_opt: DESC  */
#line 768 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2657 "yacc_sql.cpp"
    break;

  case 88: /* order_opt: %empty  */
#line 772 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2665 "yacc_sql.cpp"
    break;

  case 89: /* order_b: rel_attr order_opt  */
#line 780 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2674 "yacc_sql.cpp"
    break;

  case 90: /* order_b: distance_type LBRACE expression COMMA expression RBRACE LIMIT number  */
#line 785 "yacc_sql.y"
    {
      (yyval.expression) = new VecOrderByExpr((yyvsp[-5].expression),(yyvsp[-3].expression),(yyvsp[-7].number), (yyvsp[0].number));
    }
#line 2682 "yacc_sql.cpp"
    break;

  case 91: /* order_by: order_b  */
#line 792 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 92: /* order_by: order_b COMMA order_by  */
#line 797 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 93: /* order_by_list: %empty  */
#line 809 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 94: /* order_by_list: ORDER BY order_by  */
#line 813 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 95: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 820 "yacc_sql.y"
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
#line 2761 "yacc_sql.cpp"
    break;

  case 96: /* calc_stmt: CALC expression_list  */
#line 859 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 97: /* assign_list: eq_expr COMMA assign_list  */
#line 867 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 98: /* assign_list: eq_expr  */
#line 876 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 99: /* expression_list: expression COMMA expression_list  */
#line 884 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 100: /* expression_list: expression  */
#line 893 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2815 "yacc_sql.cpp"
    break;

  case 101: /* as_opt: %empty  */
#line 900 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2823 "yacc_sql.cpp"
    break;

  case 102: /* as_opt: AS ID  */
#line 904 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 103: /* as_opt: ID  */
#line 908 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 104: /* expression: rel_attr as_opt  */
#line 914 "yacc_sql.y"
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
#line 2860 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression ID  */
#line 930 "yacc_sql.y"
                    {
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression AS ID  */
#line 935 "yacc_sql.y"
                      {
            (yyval.expression) = (yyvsp[-2].expression);
            (yyval.expression)->set_name((yyvsp[0].string));
            free((yyvsp[0].string));
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 107: /* expression: expression '+' expression  */
#line 940 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2888 "yacc_sql.cpp"
    break;

  case 108: /* expression: expression '-' expression  */
#line 943 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2896 "yacc_sql.cpp"
    break;

  case 109: /* expression: expression '*' expression  */
#line 946 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 110: /* expression: expression '/' expression  */
#line 949 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 111: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 952 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 112: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 955 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 113: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 959 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 114: /* expression: LBRACE expression RBRACE  */
#line 963 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2945 "yacc_sql.cpp"
    break;

  case 115: /* expression: '-' expression  */
#line 967 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 116: /* expression: value  */
#line 970 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 117: /* expression: LBRACE select_stmt RBRACE  */
#line 976 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 2972 "yacc_sql.cpp"
    break;

  case 118: /* expression: LBRACE expression_list RBRACE  */
#line 980 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 119: /* expression: ID DOT '*'  */
#line 984 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2990 "yacc_sql.cpp"
    break;

  case 120: /* expression: '*'  */
#line 988 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 121: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 991 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 122: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 994 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 123: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 997 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3022 "yacc_sql.cpp"
    break;

  case 124: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 1000 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3030 "yacc_sql.cpp"
    break;

  case 125: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 1003 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 3038 "yacc_sql.cpp"
    break;

  case 126: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 1006 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3047 "yacc_sql.cpp"
    break;

  case 127: /* expression: SUM LBRACE expression_list RBRACE  */
#line 1010 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3056 "yacc_sql.cpp"
    break;

  case 128: /* expression: AVG LBRACE expression_list RBRACE  */
#line 1014 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3065 "yacc_sql.cpp"
    break;

  case 129: /* expression: MAX LBRACE expression_list RBRACE  */
#line 1018 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3074 "yacc_sql.cpp"
    break;

  case 130: /* expression: MIN LBRACE expression_list RBRACE  */
#line 1022 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 3083 "yacc_sql.cpp"
    break;

  case 131: /* inner_joins: %empty  */
#line 1032 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 132: /* inner_joins: inner_join inner_joins  */
#line 1035 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 3105 "yacc_sql.cpp"
    break;

  case 133: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 1046 "yacc_sql.y"
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
#line 3124 "yacc_sql.cpp"
    break;

  case 134: /* inner_join: INNER JOIN ID as_opt  */
#line 1060 "yacc_sql.y"
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
#line 3143 "yacc_sql.cpp"
    break;

  case 135: /* rel_attr: ID  */
#line 1077 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3153 "yacc_sql.cpp"
    break;

  case 136: /* rel_attr: ID DOT ID  */
#line 1082 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3165 "yacc_sql.cpp"
    break;

  case 137: /* rel_attr_list: %empty  */
#line 1093 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 3173 "yacc_sql.cpp"
    break;

  case 138: /* rel_attr_list: rel_attr  */
#line 1096 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 3183 "yacc_sql.cpp"
    break;

  case 139: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 1101 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 140: /* relation: ID  */
#line 1113 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 141: /* rel_table_list: relation as_opt  */
#line 1119 "yacc_sql.y"
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
#line 3225 "yacc_sql.cpp"
    break;

  case 142: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 1134 "yacc_sql.y"
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
#line 3249 "yacc_sql.cpp"
    break;

  case 143: /* rel_list: relation  */
#line 1157 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3263 "yacc_sql.cpp"
    break;

  case 144: /* rel_list: relation COMMA rel_list  */
#line 1166 "yacc_sql.y"
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
#line 3281 "yacc_sql.cpp"
    break;

  case 145: /* having: %empty  */
#line 1182 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3289 "yacc_sql.cpp"
    break;

  case 146: /* having: HAVING condition_list  */
#line 1185 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 147: /* where: %empty  */
#line 1193 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3305 "yacc_sql.cpp"
    break;

  case 148: /* where: WHERE condition_list  */
#line 1196 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3313 "yacc_sql.cpp"
    break;

  case 149: /* condition_list: %empty  */
#line 1202 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3321 "yacc_sql.cpp"
    break;

  case 150: /* condition_list: condition  */
#line 1205 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3329 "yacc_sql.cpp"
    break;

  case 151: /* condition_list: condition AND condition_list  */
#line 1208 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3340 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: condition OR condition_list  */
#line 1214 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3351 "yacc_sql.cpp"
    break;

  case 153: /* eq_expr: expression EQ expression  */
#line 1224 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3359 "yacc_sql.cpp"
    break;

  case 154: /* condition: expression comp_op expression  */
#line 1231 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3367 "yacc_sql.cpp"
    break;

  case 155: /* condition: EXISTS expression  */
#line 1235 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3375 "yacc_sql.cpp"
    break;

  case 156: /* condition: NOT EXISTS expression  */
#line 1239 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3383 "yacc_sql.cpp"
    break;

  case 157: /* condition: eq_expr  */
#line 1243 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: LT  */
#line 1249 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3397 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: GT  */
#line 1250 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3403 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: LE  */
#line 1251 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3409 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: GE  */
#line 1252 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3415 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NE  */
#line 1253 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3421 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: IS NOT  */
#line 1254 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3427 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: IS  */
#line 1255 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3433 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: NOT LIKE  */
#line 1256 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3439 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: LIKE  */
#line 1257 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3445 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: IN  */
#line 1258 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3451 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NOT IN  */
#line 1259 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3457 "yacc_sql.cpp"
    break;

  case 169: /* group_by: %empty  */
#line 1264 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3465 "yacc_sql.cpp"
    break;

  case 170: /* group_by: GROUP BY expression_list  */
#line 1267 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3473 "yacc_sql.cpp"
    break;

  case 171: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1273 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3487 "yacc_sql.cpp"
    break;

  case 172: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1286 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3496 "yacc_sql.cpp"
    break;

  case 173: /* set_variable_stmt: SET ID EQ value  */
#line 1294 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3508 "yacc_sql.cpp"
    break;


#line 3512 "yacc_sql.cpp"

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

#line 1306 "yacc_sql.y"

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
