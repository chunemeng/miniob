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
  YYSYMBOL_HAVING = 11,                    /* HAVING  */
  YYSYMBOL_UNIQUE = 12,                    /* UNIQUE  */
  YYSYMBOL_TABLE = 13,                     /* TABLE  */
  YYSYMBOL_TABLES = 14,                    /* TABLES  */
  YYSYMBOL_INDEX = 15,                     /* INDEX  */
  YYSYMBOL_CALC = 16,                      /* CALC  */
  YYSYMBOL_SELECT = 17,                    /* SELECT  */
  YYSYMBOL_EXISTS = 18,                    /* EXISTS  */
  YYSYMBOL_DESC = 19,                      /* DESC  */
  YYSYMBOL_ASC = 20,                       /* ASC  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_VECTOR_T = 33,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 34,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 35,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 36,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 37,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_SUM = 44,                       /* SUM  */
  YYSYMBOL_AVG = 45,                       /* AVG  */
  YYSYMBOL_MAX = 46,                       /* MAX  */
  YYSYMBOL_MIN = 47,                       /* MIN  */
  YYSYMBOL_COUNT = 48,                     /* COUNT  */
  YYSYMBOL_WHERE = 49,                     /* WHERE  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_IS = 51,                        /* IS  */
  YYSYMBOL_LIKE = 52,                      /* LIKE  */
  YYSYMBOL_AND = 53,                       /* AND  */
  YYSYMBOL_OR = 54,                        /* OR  */
  YYSYMBOL_SET = 55,                       /* SET  */
  YYSYMBOL_ON = 56,                        /* ON  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_LOAD = 58,                      /* LOAD  */
  YYSYMBOL_DATA = 59,                      /* DATA  */
  YYSYMBOL_INFILE = 60,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 61,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 62,                   /* STORAGE  */
  YYSYMBOL_AS = 63,                        /* AS  */
  YYSYMBOL_FORMAT = 64,                    /* FORMAT  */
  YYSYMBOL_INNER_PRODUCT = 65,             /* INNER_PRODUCT  */
  YYSYMBOL_INNER = 66,                     /* INNER  */
  YYSYMBOL_JOIN = 67,                      /* JOIN  */
  YYSYMBOL_L2_DIST = 68,                   /* L2_DIST  */
  YYSYMBOL_COS_DIST = 69,                  /* COS_DIST  */
  YYSYMBOL_NULL_L = 70,                    /* NULL_L  */
  YYSYMBOL_NULL_T = 71,                    /* NULL_T  */
  YYSYMBOL_EQ = 72,                        /* EQ  */
  YYSYMBOL_LT = 73,                        /* LT  */
  YYSYMBOL_GT = 74,                        /* GT  */
  YYSYMBOL_LE = 75,                        /* LE  */
  YYSYMBOL_GE = 76,                        /* GE  */
  YYSYMBOL_NE = 77,                        /* NE  */
  YYSYMBOL_NUMBER = 78,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 79,                     /* FLOAT  */
  YYSYMBOL_ID = 80,                        /* ID  */
  YYSYMBOL_SSS = 81,                       /* SSS  */
  YYSYMBOL_82_ = 82,                       /* '+'  */
  YYSYMBOL_83_ = 83,                       /* '-'  */
  YYSYMBOL_84_ = 84,                       /* '*'  */
  YYSYMBOL_85_ = 85,                       /* '/'  */
  YYSYMBOL_UMINUS = 86,                    /* UMINUS  */
  YYSYMBOL_ASSIGN = 87,                    /* ASSIGN  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_commands = 89,                  /* commands  */
  YYSYMBOL_command_wrapper = 90,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 91,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 92,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 93,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 94,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 95,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 96,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 97,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 98,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 99,           /* desc_table_stmt  */
  YYSYMBOL_unique_op = 100,                /* unique_op  */
  YYSYMBOL_create_index_stmt = 101,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 102,          /* drop_index_stmt  */
  YYSYMBOL_as_select_opt = 103,            /* as_select_opt  */
  YYSYMBOL_create_table_stmt = 104,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 105,            /* attr_def_list  */
  YYSYMBOL_attr_def = 106,                 /* attr_def  */
  YYSYMBOL_number = 107,                   /* number  */
  YYSYMBOL_null_t = 108,                   /* null_t  */
  YYSYMBOL_type = 109,                     /* type  */
  YYSYMBOL_insert_stmt = 110,              /* insert_stmt  */
  YYSYMBOL_value_list = 111,               /* value_list  */
  YYSYMBOL_value = 112,                    /* value  */
  YYSYMBOL_v_list = 113,                   /* v_list  */
  YYSYMBOL_v_l = 114,                      /* v_l  */
  YYSYMBOL_storage_format = 115,           /* storage_format  */
  YYSYMBOL_delete_stmt = 116,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 117,              /* update_stmt  */
  YYSYMBOL_order_opt = 118,                /* order_opt  */
  YYSYMBOL_order_b = 119,                  /* order_b  */
  YYSYMBOL_order_by = 120,                 /* order_by  */
  YYSYMBOL_order_by_list = 121,            /* order_by_list  */
  YYSYMBOL_select_stmt = 122,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 123,                /* calc_stmt  */
  YYSYMBOL_assign_list = 124,              /* assign_list  */
  YYSYMBOL_expression_list = 125,          /* expression_list  */
  YYSYMBOL_as_opt = 126,                   /* as_opt  */
  YYSYMBOL_expression = 127,               /* expression  */
  YYSYMBOL_inner_joins = 128,              /* inner_joins  */
  YYSYMBOL_inner_join = 129,               /* inner_join  */
  YYSYMBOL_rel_attr = 130,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 131,            /* rel_attr_list  */
  YYSYMBOL_relation = 132,                 /* relation  */
  YYSYMBOL_rel_table_list = 133,           /* rel_table_list  */
  YYSYMBOL_rel_list = 134,                 /* rel_list  */
  YYSYMBOL_having = 135,                   /* having  */
  YYSYMBOL_where = 136,                    /* where  */
  YYSYMBOL_condition_list = 137,           /* condition_list  */
  YYSYMBOL_eq_expr = 138,                  /* eq_expr  */
  YYSYMBOL_condition = 139,                /* condition  */
  YYSYMBOL_comp_op = 140,                  /* comp_op  */
  YYSYMBOL_group_by = 141,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 142,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 143,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 144,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 145             /* opt_semicolon  */
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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   396

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   338


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
       2,     2,    84,    82,     2,    83,     2,    85,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    86,    87
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   290,   290,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   321,   327,   332,   338,   344,   350,   356,
     363,   369,   376,   380,   388,   403,   413,   416,   420,   426,
     454,   476,   479,   492,   511,   527,   531,   534,   538,   542,
     546,   553,   554,   555,   556,   557,   558,   561,   578,   581,
     592,   596,   600,   604,   608,   613,   619,   627,   632,   636,
     640,   644,   653,   656,   663,   674,   688,   691,   695,   702,
     710,   715,   728,   731,   738,   777,   785,   794,   802,   811,
     819,   822,   826,   832,   835,   838,   841,   844,   847,   851,
     855,   859,   862,   867,   881,   886,   892,   896,   900,   904,
     907,   910,   913,   916,   919,   922,   926,   930,   934,   938,
     947,   950,   961,   975,   992,   997,  1008,  1011,  1016,  1028,
    1034,  1049,  1072,  1081,  1097,  1100,  1108,  1111,  1117,  1120,
    1123,  1129,  1138,  1145,  1149,  1153,  1157,  1164,  1165,  1166,
    1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1179,  1182,
    1187,  1200,  1208,  1218,  1219
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
  "CREATE", "DROP", "LBRACKET", "RBRACKET", "GROUP", "ORDER", "HAVING",
  "UNIQUE", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "EXISTS", "DESC",
  "ASC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "VECTOR_T",
  "TEXT_T", "STRING_T", "DATE_T", "FLOAT_T", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "SUM", "AVG", "MAX", "MIN", "COUNT", "WHERE", "NOT",
  "IS", "LIKE", "AND", "OR", "SET", "ON", "IN", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "STORAGE", "AS", "FORMAT", "INNER_PRODUCT", "INNER", "JOIN",
  "L2_DIST", "COS_DIST", "NULL_L", "NULL_T", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "ASSIGN", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "unique_op", "create_index_stmt", "drop_index_stmt",
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

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     322,    24,    19,   207,   207,   -66,     9,  -225,    -8,     2,
     -41,  -225,  -225,  -225,  -225,  -225,   -10,    35,   322,    52,
      78,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,    29,   104,    45,    57,   -12,   178,   125,   132,
     135,   144,   148,   152,   158,   171,  -225,  -225,  -225,   102,
    -225,   253,  -225,  -225,  -225,  -225,   116,   -25,   130,  -225,
    -225,   122,   123,   151,   136,   149,  -225,  -225,  -225,  -225,
       5,   127,  -225,   156,   183,   188,   209,   193,   194,    -7,
     207,   207,   207,   207,   207,   207,   207,   207,   -54,  -225,
    -225,    36,   207,   161,  -225,   207,   207,   207,   207,   162,
    -225,  -225,   165,   186,   201,   207,    34,   153,   184,   246,
     204,  -225,   215,   200,   -12,   -12,  -225,  -225,  -225,  -225,
     247,   -23,   254,   265,   266,   267,   269,   275,   276,   283,
     284,   147,   155,   185,  -225,  -225,  -225,  -225,   -38,   -38,
      36,    36,  -225,  -225,   -25,   257,   287,    88,  -225,   201,
      80,   245,    67,  -225,   278,   154,   292,  -225,   261,  -225,
     249,  -225,  -225,  -225,  -225,   250,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,   207,   207,   207,   298,   268,
     201,   257,    34,   207,   324,   232,  -225,  -225,    49,  -225,
     207,   207,  -225,  -225,   327,  -225,  -225,  -225,  -225,  -225,
    -225,    22,   184,   323,   277,   328,   315,   329,  -225,     0,
      38,    44,   165,   279,   347,  -225,   330,   285,   207,   -28,
     312,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   207,    88,
      88,   285,  -225,   286,   293,    79,  -225,  -225,  -225,   292,
      -5,   294,   165,   295,  -225,  -225,  -225,  -225,   -25,   359,
     353,    34,   345,   285,  -225,  -225,  -225,   285,  -225,  -225,
    -225,  -225,   346,  -225,  -225,  -225,   204,  -225,   348,   351,
     325,   207,    88,   369,   330,  -225,    60,  -225,   165,  -225,
      88,  -225,  -225,   378,  -225,  -225,  -225,  -225,  -225,   250,
     356,  -225,   157,   250,  -225,  -225,  -225,  -225
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     163,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    60,    62,   124,
      65,     0,   109,   102,    66,    85,    89,    90,     0,    31,
      30,     0,     0,     0,     0,     0,   161,     1,   164,     2,
      38,     0,    29,     0,    70,    69,     0,     0,     0,     0,
     126,   126,   126,   126,   126,     0,     0,     0,     0,    60,
      62,   101,     0,     0,   104,     0,     0,     0,     0,     0,
      92,   103,     0,     0,   136,     0,     0,     0,     0,     0,
      72,    36,     0,     0,     0,     0,    67,   106,   107,   100,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   108,    88,   105,    93,    94,
      95,    96,    91,   129,    90,   120,     0,   138,    74,   136,
       0,    87,     0,   162,     0,     0,    41,    37,     0,    40,
       0,    35,    71,    68,   116,   126,   111,   117,   112,   118,
     113,   119,   114,   115,   110,     0,     0,     0,   130,     0,
     136,   120,     0,     0,     0,     0,   137,   146,   139,    75,
       0,     0,    61,    63,     0,    51,    55,    56,    52,    53,
      54,    46,     0,     0,     0,     0,   124,   127,   128,     0,
       0,     0,     0,     0,   158,   121,    58,   144,     0,     0,
     153,   155,   156,   147,   148,   149,   150,   151,     0,   138,
     138,   142,    86,     0,     0,     0,    47,    48,    44,    41,
      38,     0,     0,     0,    99,    97,    98,   131,    90,     0,
     134,     0,     0,   145,   154,   157,   152,   143,   140,   141,
     160,    45,     0,    50,    49,    42,    72,    73,   132,     0,
     123,     0,   138,    82,    58,    57,    46,    39,     0,    34,
     138,   159,   135,     0,    84,    59,    43,   133,   122,     0,
      80,    83,    78,     0,    77,    76,    79,    81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,   367,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,   137,  -225,   139,   174,  -225,
     103,  -225,  -225,   106,  -113,  -225,    56,   115,  -225,  -225,
    -225,  -225,    89,  -225,   -45,  -225,   192,    -4,  -150,   -46,
     203,  -225,   -84,   -75,  -224,   173,   108,  -225,  -146,  -186,
    -104,  -225,  -225,  -225,  -225,  -225,  -225,  -225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    43,    30,    31,   120,    32,   213,   166,   272,
     248,   211,    33,   262,    63,    64,    86,   169,    34,    35,
     306,   300,   301,   294,    36,    37,   159,    65,   111,    66,
     190,   191,    67,   132,   154,   155,   279,   283,   158,   196,
     197,   198,   238,   260,    38,    39,    40,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    89,    87,   163,   188,   175,   131,   131,   131,   131,
     131,   161,     4,   199,    69,   101,   134,   136,   138,   140,
     129,   102,     4,    70,   264,   103,   144,   254,   278,   265,
     145,   118,    44,    71,    45,   121,    41,    42,   109,    73,
     109,    46,   104,    88,   224,    72,   107,   108,   244,   141,
     142,   143,    77,   268,   269,   110,   103,   110,   119,   148,
     149,   150,   151,   103,   278,   255,    84,    85,   119,   160,
      74,   256,   245,   104,   167,   105,   106,   107,   108,   226,
     104,    78,   105,   106,   107,   108,   130,   133,   135,   137,
     139,   217,   246,   247,    75,    46,   292,   161,   146,   103,
     218,   103,   239,   240,   298,    56,   193,   103,   280,    80,
     245,   195,    57,    58,    47,    60,   104,   162,   104,    81,
     105,   106,   107,   108,   104,    82,   105,   106,   107,   108,
     246,   247,    48,    49,    50,    51,    52,    83,   194,   219,
     220,   221,    98,   103,   102,   202,   203,   227,   284,   273,
     274,    90,   200,    53,   241,   160,    54,    55,    91,    56,
     104,    92,   105,   106,   107,   108,    57,    58,    59,    60,
      93,    61,    62,   112,    94,   185,   304,   305,    95,   103,
     172,   173,   263,   186,    96,    46,   205,   206,   207,   208,
     209,   210,   267,   195,   195,     4,   104,    97,   105,   106,
     107,   108,   113,   114,    47,   121,   115,   122,   116,   117,
     103,   124,   123,   187,    46,   302,   125,   126,   103,   302,
     127,   128,    48,    49,    50,    51,    52,   104,   156,   105,
     106,   107,   108,    47,   164,   104,   195,   105,   106,   107,
     108,   147,   152,    53,   195,   153,    54,    55,   103,    56,
     157,    48,    49,    50,    51,    52,    57,    58,    59,    60,
      46,    61,    62,     4,   165,   104,   168,   105,   106,   107,
     108,   170,    53,   201,   174,    54,    55,   291,    56,    47,
     171,   176,   229,   230,   231,    57,    58,    59,    60,   232,
      61,    62,   177,   178,   179,   103,   180,    48,    49,    50,
      51,    52,   181,   182,   200,   233,   234,   235,   236,   237,
     183,   184,   104,   192,   105,   106,   107,   108,    53,   204,
     212,    54,    55,   189,    56,   214,   222,     1,     2,   215,
     216,    99,   100,    59,    60,   223,    61,    62,     3,     4,
     243,     5,   228,     6,     7,     8,     9,    10,   103,   251,
     250,    11,    12,    13,   252,   253,   259,   175,   261,   258,
      14,    15,   266,   281,   282,   104,   270,   105,   106,   107,
     108,   271,   285,   286,   277,   144,   288,    16,   289,   293,
      17,   290,   299,    18,   303,    76,   249,   276,   275,   296,
     295,   287,   307,   242,   225,   257,   297
};

static const yytype_int16 yycheck[] =
{
       4,    47,    47,   116,   154,    28,    90,    91,    92,    93,
      94,   115,    17,   159,    80,    61,    91,    92,    93,    94,
      27,    28,    17,    14,    52,    63,    80,    27,   252,    57,
      84,    26,    13,    41,    15,    80,    12,    13,    63,    80,
      63,     7,    80,    47,   190,    43,    84,    85,    26,    95,
      96,    97,     0,   239,   240,    80,    63,    80,    63,   105,
     106,   107,   108,    63,   288,    27,    78,    79,    63,   115,
      80,    27,    50,    80,   119,    82,    83,    84,    85,   192,
      80,     3,    82,    83,    84,    85,    90,    91,    92,    93,
      94,   175,    70,    71,    59,     7,   282,   201,   102,    63,
     175,    63,    53,    54,   290,    71,    18,    63,   258,    80,
      50,   157,    78,    79,    26,    81,    80,    83,    80,    15,
      82,    83,    84,    85,    80,    80,    82,    83,    84,    85,
      70,    71,    44,    45,    46,    47,    48,    80,    50,   185,
     186,   187,    40,    63,    28,    78,    79,   193,   261,    70,
      71,    26,    72,    65,   200,   201,    68,    69,    26,    71,
      80,    26,    82,    83,    84,    85,    78,    79,    80,    81,
      26,    83,    84,    43,    26,    28,    19,    20,    26,    63,
     124,   125,   228,    28,    26,     7,    32,    33,    34,    35,
      36,    37,   238,   239,   240,    17,    80,    26,    82,    83,
      84,    85,    80,    80,    26,   250,    55,    80,    72,    60,
      63,    28,    56,    28,     7,   299,    28,     8,    63,   303,
      27,    27,    44,    45,    46,    47,    48,    80,    42,    82,
      83,    84,    85,    26,    81,    80,   282,    82,    83,    84,
      85,    80,    80,    65,   290,    80,    68,    69,    63,    71,
      49,    44,    45,    46,    47,    48,    78,    79,    80,    81,
       7,    83,    84,    17,    80,    80,    62,    82,    83,    84,
      85,    56,    65,    28,    27,    68,    69,   281,    71,    26,
      80,    27,    50,    51,    52,    78,    79,    80,    81,    57,
      83,    84,    27,    27,    27,    63,    27,    44,    45,    46,
      47,    48,    27,    27,    72,    73,    74,    75,    76,    77,
      27,    27,    80,    26,    82,    83,    84,    85,    65,    41,
      28,    68,    69,    66,    71,    64,    28,     5,     6,    80,
      80,    78,    79,    80,    81,    67,    83,    84,    16,    17,
      13,    19,    18,    21,    22,    23,    24,    25,    63,    72,
      27,    29,    30,    31,    26,    40,     9,    28,    28,    80,
      38,    39,    50,     4,    11,    80,    80,    82,    83,    84,
      85,    78,    27,    27,    80,    80,    28,    55,    27,    10,
      58,    56,     4,    61,    28,    18,   212,   250,   249,   286,
     284,   276,   303,   201,   191,   222,   288
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    16,    17,    19,    21,    22,    23,    24,
      25,    29,    30,    31,    38,    39,    55,    58,    61,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     101,   102,   104,   110,   116,   117,   122,   123,   142,   143,
     144,    12,    13,   100,    13,    15,     7,    26,    44,    45,
      46,    47,    48,    65,    68,    69,    71,    78,    79,    80,
      81,    83,    84,   112,   113,   125,   127,   130,   125,    80,
      14,    41,    43,    80,    80,    59,    90,     0,     3,   145,
      80,    15,    80,    80,    78,    79,   114,   122,   125,   127,
      26,    26,    26,    26,    26,    26,    26,    26,    40,    78,
      79,   127,    28,    63,    80,    82,    83,    84,    85,    63,
      80,   126,    43,    80,    80,    55,    72,    60,    26,    63,
     103,   122,    80,    56,    28,    28,     8,    27,    27,    27,
     125,   130,   131,   125,   131,   125,   131,   125,   131,   125,
     131,   127,   127,   127,    80,    84,   125,    80,   127,   127,
     127,   127,    80,    80,   132,   133,    42,    49,   136,   124,
     127,   138,    83,   112,    81,    80,   106,   122,    62,   115,
      56,    80,   114,   114,    27,    28,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    28,    28,    28,   126,    66,
     128,   129,    26,    18,    50,   127,   137,   138,   139,   136,
      72,    28,    78,    79,    41,    32,    33,    34,    35,    36,
      37,   109,    28,   105,    64,    80,    80,   130,   131,   127,
     127,   127,    28,    67,   136,   128,   112,   127,    18,    50,
      51,    52,    57,    73,    74,    75,    76,    77,   140,    53,
      54,   127,   124,    13,    26,    50,    70,    71,   108,   106,
      27,    72,    26,    40,    27,    27,    27,   133,    80,     9,
     141,    28,   111,   127,    52,    57,    50,   127,   137,   137,
      80,    78,   107,    70,    71,   105,   103,    80,   132,   134,
     126,     4,    11,   135,   112,    27,    27,   115,    28,    27,
      56,   125,   137,    10,   121,   111,   108,   134,   137,     4,
     119,   120,   130,    28,    19,    20,   118,   120
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   100,   101,   102,   103,   103,   103,   104,
     104,   105,   105,   106,   106,   107,   108,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   109,   110,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   113,   114,   114,
     114,   114,   115,   115,   116,   117,   118,   118,   118,   119,
     120,   120,   121,   121,   122,   123,   124,   124,   125,   125,
     126,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     137,   137,   138,   139,   139,   139,   139,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   141,   141,
     142,   143,   144,   145,   145
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     0,     9,     5,     1,     2,     0,     9,
       5,     0,     3,     6,     3,     1,     0,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       1,     2,     1,     2,     1,     1,     1,     3,     3,     1,
       1,     3,     0,     4,     4,     5,     1,     1,     0,     2,
       1,     3,     0,     3,     9,     2,     3,     1,     3,     1,
       0,     2,     1,     3,     3,     3,     3,     6,     6,     6,
       3,     2,     1,     2,     2,     3,     3,     3,     3,     1,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       0,     2,     6,     4,     1,     3,     0,     1,     3,     1,
       2,     4,     1,     3,     0,     2,     0,     2,     0,     1,
       3,     3,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     2,     0,     3,
       7,     2,     4,     0,     1
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
#line 291 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1956 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 321 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1965 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 327 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1973 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 332 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1981 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 338 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 344 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1997 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 350 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2005 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 356 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 363 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2023 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 369 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2033 "yacc_sql.cpp"
    break;

  case 32: /* unique_op: UNIQUE  */
#line 376 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: %empty  */
#line 380 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2049 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 389 "yacc_sql.y"
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
#line 2065 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 404 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2077 "yacc_sql.cpp"
    break;

  case 36: /* as_select_opt: select_stmt  */
#line 413 "yacc_sql.y"
                {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2085 "yacc_sql.cpp"
    break;

  case 37: /* as_select_opt: AS select_stmt  */
#line 416 "yacc_sql.y"
                     {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2093 "yacc_sql.cpp"
    break;

  case 38: /* as_select_opt: %empty  */
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 2101 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_select_opt storage_format  */
#line 427 "yacc_sql.y"
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
#line 2133 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID as_select_opt storage_format  */
#line 455 "yacc_sql.y"
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
#line 2156 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 476 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 480 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 493 "yacc_sql.y"
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
#line 2201 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type null_t  */
#line 512 "yacc_sql.y"
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
#line 2219 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 527 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2225 "yacc_sql.cpp"
    break;

  case 46: /* null_t: %empty  */
#line 531 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 47: /* null_t: NULL_L  */
#line 535 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 48: /* null_t: NULL_T  */
#line 539 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2249 "yacc_sql.cpp"
    break;

  case 49: /* null_t: NOT NULL_T  */
#line 543 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 50: /* null_t: NOT NULL_L  */
#line 547 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 51: /* type: INT_T  */
#line 553 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2271 "yacc_sql.cpp"
    break;

  case 52: /* type: STRING_T  */
#line 554 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2277 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 555 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2283 "yacc_sql.cpp"
    break;

  case 54: /* type: FLOAT_T  */
#line 556 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2289 "yacc_sql.cpp"
    break;

  case 55: /* type: VECTOR_T  */
#line 557 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2295 "yacc_sql.cpp"
    break;

  case 56: /* type: TEXT_T  */
#line 558 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2301 "yacc_sql.cpp"
    break;

  case 57: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 562 "yacc_sql.y"
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
#line 2318 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 578 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 581 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 592 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 61: /* value: '-' NUMBER  */
#line 596 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2358 "yacc_sql.cpp"
    break;

  case 62: /* value: FLOAT  */
#line 600 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 63: /* value: '-' FLOAT  */
#line 604 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 64: /* value: NULL_T  */
#line 608 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 613 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 66: /* value: v_list  */
#line 619 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 67: /* v_list: LBRACKET v_l RBRACKET  */
#line 627 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2416 "yacc_sql.cpp"
    break;

  case 68: /* v_l: FLOAT COMMA v_l  */
#line 632 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2425 "yacc_sql.cpp"
    break;

  case 69: /* v_l: FLOAT  */
#line 636 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2434 "yacc_sql.cpp"
    break;

  case 70: /* v_l: NUMBER  */
#line 640 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 71: /* v_l: NUMBER COMMA v_l  */
#line 644 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2452 "yacc_sql.cpp"
    break;

  case 72: /* storage_format: %empty  */
#line 653 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2460 "yacc_sql.cpp"
    break;

  case 73: /* storage_format: STORAGE FORMAT EQ ID  */
#line 657 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2468 "yacc_sql.cpp"
    break;

  case 74: /* delete_stmt: DELETE FROM ID where  */
#line 664 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2481 "yacc_sql.cpp"
    break;

  case 75: /* update_stmt: UPDATE ID SET assign_list where  */
#line 675 "yacc_sql.y"
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
#line 2496 "yacc_sql.cpp"
    break;

  case 76: /* order_opt: ASC  */
#line 688 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 77: /* order_opt: DESC  */
#line 691 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 78: /* order_opt: %empty  */
#line 695 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 79: /* order_b: rel_attr order_opt  */
#line 703 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 80: /* order_by: order_b  */
#line 711 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 81: /* order_by: order_b COMMA order_by  */
#line 716 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 82: /* order_by_list: %empty  */
#line 728 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 83: /* order_by_list: ORDER BY order_by  */
#line 732 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 84: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 739 "yacc_sql.y"
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
#line 2608 "yacc_sql.cpp"
    break;

  case 85: /* calc_stmt: CALC expression_list  */
#line 778 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 86: /* assign_list: eq_expr COMMA assign_list  */
#line 786 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 87: /* assign_list: eq_expr  */
#line 795 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression COMMA expression_list  */
#line 803 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression  */
#line 812 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 90: /* as_opt: %empty  */
#line 819 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 91: /* as_opt: AS ID  */
#line 823 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 92: /* as_opt: ID  */
#line 827 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '+' expression  */
#line 832 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '-' expression  */
#line 835 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '*' expression  */
#line 838 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2710 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression '/' expression  */
#line 841 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 97: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 844 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 98: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 847 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 99: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 851 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 100: /* expression: LBRACE expression RBRACE  */
#line 855 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 101: /* expression: '-' expression  */
#line 859 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2759 "yacc_sql.cpp"
    break;

  case 102: /* expression: value  */
#line 862 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 103: /* expression: rel_attr as_opt  */
#line 867 "yacc_sql.y"
                      {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      UnboundFieldExpr * ex = new UnboundFieldExpr(node->relation_name, node->attribute_name);

      if ((yyvsp[0].string) != nullptr) {
        ex->set_alias(true);
        ex->set_name((yyvsp[0].string));
        free((yyvsp[0].string));
      } else {
        ex->set_name(token_name(sql_string, &(yyloc)));
      }
      (yyval.expression) = ex;
      delete (yyvsp[-1].rel_attr);
    }
#line 2788 "yacc_sql.cpp"
    break;

  case 104: /* expression: expression ID  */
#line 881 "yacc_sql.y"
                    {
        (yyval.expression) = (yyvsp[-1].expression);
        (yyval.expression)->set_name((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression AS ID  */
#line 886 "yacc_sql.y"
                       {
        (yyval.expression) = (yyvsp[-2].expression);
        (yyval.expression)->set_name((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 106: /* expression: LBRACE select_stmt RBRACE  */
#line 892 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 107: /* expression: LBRACE expression_list RBRACE  */
#line 896 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 108: /* expression: ID DOT '*'  */
#line 900 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2835 "yacc_sql.cpp"
    break;

  case 109: /* expression: '*'  */
#line 904 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 110: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 907 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 111: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 910 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 112: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 913 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 113: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 916 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2875 "yacc_sql.cpp"
    break;

  case 114: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 919 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2883 "yacc_sql.cpp"
    break;

  case 115: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 922 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 116: /* expression: SUM LBRACE expression_list RBRACE  */
#line 926 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 117: /* expression: AVG LBRACE expression_list RBRACE  */
#line 930 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 118: /* expression: MAX LBRACE expression_list RBRACE  */
#line 934 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2919 "yacc_sql.cpp"
    break;

  case 119: /* expression: MIN LBRACE expression_list RBRACE  */
#line 938 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 120: /* inner_joins: %empty  */
#line 947 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 121: /* inner_joins: inner_join inner_joins  */
#line 950 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 122: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 961 "yacc_sql.y"
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
#line 2969 "yacc_sql.cpp"
    break;

  case 123: /* inner_join: INNER JOIN ID as_opt  */
#line 975 "yacc_sql.y"
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
#line 2988 "yacc_sql.cpp"
    break;

  case 124: /* rel_attr: ID  */
#line 992 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 125: /* rel_attr: ID DOT ID  */
#line 997 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 126: /* rel_attr_list: %empty  */
#line 1008 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 3018 "yacc_sql.cpp"
    break;

  case 127: /* rel_attr_list: rel_attr  */
#line 1011 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 3028 "yacc_sql.cpp"
    break;

  case 128: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 1016 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 129: /* relation: ID  */
#line 1028 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3050 "yacc_sql.cpp"
    break;

  case 130: /* rel_table_list: relation as_opt  */
#line 1034 "yacc_sql.y"
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
#line 3070 "yacc_sql.cpp"
    break;

  case 131: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 1049 "yacc_sql.y"
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
#line 3094 "yacc_sql.cpp"
    break;

  case 132: /* rel_list: relation  */
#line 1072 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 133: /* rel_list: relation COMMA rel_list  */
#line 1081 "yacc_sql.y"
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
#line 3126 "yacc_sql.cpp"
    break;

  case 134: /* having: %empty  */
#line 1097 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3134 "yacc_sql.cpp"
    break;

  case 135: /* having: HAVING condition_list  */
#line 1100 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 136: /* where: %empty  */
#line 1108 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 137: /* where: WHERE condition_list  */
#line 1111 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 138: /* condition_list: %empty  */
#line 1117 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3166 "yacc_sql.cpp"
    break;

  case 139: /* condition_list: condition  */
#line 1120 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 140: /* condition_list: condition AND condition_list  */
#line 1123 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 141: /* condition_list: condition OR condition_list  */
#line 1129 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3196 "yacc_sql.cpp"
    break;

  case 142: /* eq_expr: expression EQ expression  */
#line 1139 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3204 "yacc_sql.cpp"
    break;

  case 143: /* condition: expression comp_op expression  */
#line 1146 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3212 "yacc_sql.cpp"
    break;

  case 144: /* condition: EXISTS expression  */
#line 1150 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3220 "yacc_sql.cpp"
    break;

  case 145: /* condition: NOT EXISTS expression  */
#line 1154 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3228 "yacc_sql.cpp"
    break;

  case 146: /* condition: eq_expr  */
#line 1158 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3236 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: LT  */
#line 1164 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3242 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: GT  */
#line 1165 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3248 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: LE  */
#line 1166 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3254 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: GE  */
#line 1167 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3260 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: NE  */
#line 1168 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3266 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: IS NOT  */
#line 1169 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3272 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: IS  */
#line 1170 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3278 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: NOT LIKE  */
#line 1171 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3284 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: LIKE  */
#line 1172 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3290 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: IN  */
#line 1173 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3296 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: NOT IN  */
#line 1174 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3302 "yacc_sql.cpp"
    break;

  case 158: /* group_by: %empty  */
#line 1179 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3310 "yacc_sql.cpp"
    break;

  case 159: /* group_by: GROUP BY expression_list  */
#line 1182 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3318 "yacc_sql.cpp"
    break;

  case 160: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1188 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 161: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1201 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3341 "yacc_sql.cpp"
    break;

  case 162: /* set_variable_stmt: SET ID EQ value  */
#line 1209 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3353 "yacc_sql.cpp"
    break;


#line 3357 "yacc_sql.cpp"

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

#line 1221 "yacc_sql.y"

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
