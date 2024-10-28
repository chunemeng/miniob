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
  YYSYMBOL_STRING_T = 34,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 35,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 36,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 37,                      /* HELP  */
  YYSYMBOL_EXIT = 38,                      /* EXIT  */
  YYSYMBOL_DOT = 39,                       /* DOT  */
  YYSYMBOL_INTO = 40,                      /* INTO  */
  YYSYMBOL_VALUES = 41,                    /* VALUES  */
  YYSYMBOL_FROM = 42,                      /* FROM  */
  YYSYMBOL_SUM = 43,                       /* SUM  */
  YYSYMBOL_AVG = 44,                       /* AVG  */
  YYSYMBOL_MAX = 45,                       /* MAX  */
  YYSYMBOL_MIN = 46,                       /* MIN  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_WHERE = 48,                     /* WHERE  */
  YYSYMBOL_NOT = 49,                       /* NOT  */
  YYSYMBOL_IS = 50,                        /* IS  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_AND = 52,                       /* AND  */
  YYSYMBOL_OR = 53,                        /* OR  */
  YYSYMBOL_SET = 54,                       /* SET  */
  YYSYMBOL_ON = 55,                        /* ON  */
  YYSYMBOL_IN = 56,                        /* IN  */
  YYSYMBOL_LOAD = 57,                      /* LOAD  */
  YYSYMBOL_DATA = 58,                      /* DATA  */
  YYSYMBOL_INFILE = 59,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 60,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 61,                   /* STORAGE  */
  YYSYMBOL_AS = 62,                        /* AS  */
  YYSYMBOL_FORMAT = 63,                    /* FORMAT  */
  YYSYMBOL_INNER_PRODUCT = 64,             /* INNER_PRODUCT  */
  YYSYMBOL_INNER = 65,                     /* INNER  */
  YYSYMBOL_JOIN = 66,                      /* JOIN  */
  YYSYMBOL_L2_DIST = 67,                   /* L2_DIST  */
  YYSYMBOL_COS_DIST = 68,                  /* COS_DIST  */
  YYSYMBOL_NULL_L = 69,                    /* NULL_L  */
  YYSYMBOL_NULL_T = 70,                    /* NULL_T  */
  YYSYMBOL_EQ = 71,                        /* EQ  */
  YYSYMBOL_LT = 72,                        /* LT  */
  YYSYMBOL_GT = 73,                        /* GT  */
  YYSYMBOL_LE = 74,                        /* LE  */
  YYSYMBOL_GE = 75,                        /* GE  */
  YYSYMBOL_NE = 76,                        /* NE  */
  YYSYMBOL_NUMBER = 77,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 78,                     /* FLOAT  */
  YYSYMBOL_ID = 79,                        /* ID  */
  YYSYMBOL_SSS = 80,                       /* SSS  */
  YYSYMBOL_81_ = 81,                       /* '+'  */
  YYSYMBOL_82_ = 82,                       /* '-'  */
  YYSYMBOL_83_ = 83,                       /* '*'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_UMINUS = 85,                    /* UMINUS  */
  YYSYMBOL_ASSIGN = 86,                    /* ASSIGN  */
  YYSYMBOL_YYACCEPT = 87,                  /* $accept  */
  YYSYMBOL_commands = 88,                  /* commands  */
  YYSYMBOL_command_wrapper = 89,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 90,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 91,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 92,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 93,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 94,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 95,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 96,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 97,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 98,           /* desc_table_stmt  */
  YYSYMBOL_unique_op = 99,                 /* unique_op  */
  YYSYMBOL_create_index_stmt = 100,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 101,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 102,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 103,            /* attr_def_list  */
  YYSYMBOL_attr_def = 104,                 /* attr_def  */
  YYSYMBOL_number = 105,                   /* number  */
  YYSYMBOL_null_t = 106,                   /* null_t  */
  YYSYMBOL_type = 107,                     /* type  */
  YYSYMBOL_insert_stmt = 108,              /* insert_stmt  */
  YYSYMBOL_value_list = 109,               /* value_list  */
  YYSYMBOL_value = 110,                    /* value  */
  YYSYMBOL_v_list = 111,                   /* v_list  */
  YYSYMBOL_v_l = 112,                      /* v_l  */
  YYSYMBOL_storage_format = 113,           /* storage_format  */
  YYSYMBOL_delete_stmt = 114,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 115,              /* update_stmt  */
  YYSYMBOL_order_opt = 116,                /* order_opt  */
  YYSYMBOL_order_b = 117,                  /* order_b  */
  YYSYMBOL_order_by = 118,                 /* order_by  */
  YYSYMBOL_order_by_list = 119,            /* order_by_list  */
  YYSYMBOL_select_stmt = 120,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 121,                /* calc_stmt  */
  YYSYMBOL_assign_list = 122,              /* assign_list  */
  YYSYMBOL_expression_list = 123,          /* expression_list  */
  YYSYMBOL_as_opt = 124,                   /* as_opt  */
  YYSYMBOL_expression = 125,               /* expression  */
  YYSYMBOL_inner_joins = 126,              /* inner_joins  */
  YYSYMBOL_inner_join = 127,               /* inner_join  */
  YYSYMBOL_rel_attr = 128,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 129,            /* rel_attr_list  */
  YYSYMBOL_relation = 130,                 /* relation  */
  YYSYMBOL_rel_table_list = 131,           /* rel_table_list  */
  YYSYMBOL_rel_list = 132,                 /* rel_list  */
  YYSYMBOL_having = 133,                   /* having  */
  YYSYMBOL_where = 134,                    /* where  */
  YYSYMBOL_condition_list = 135,           /* condition_list  */
  YYSYMBOL_eq_expr = 136,                  /* eq_expr  */
  YYSYMBOL_condition = 137,                /* condition  */
  YYSYMBOL_comp_op = 138,                  /* comp_op  */
  YYSYMBOL_group_by = 139,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 140,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 141,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 142,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 143             /* opt_semicolon  */
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
#define YYLAST   386

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   337


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
       2,     2,    83,    81,     2,    82,     2,    84,     2,     2,
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
      75,    76,    77,    78,    79,    80,    85,    86
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   288,   288,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   319,   325,   330,   336,   342,   348,   354,
     361,   367,   374,   378,   386,   401,   411,   435,   438,   451,
     460,   471,   475,   478,   482,   486,   490,   497,   498,   499,
     500,   501,   504,   521,   524,   535,   539,   543,   547,   551,
     556,   562,   570,   575,   579,   583,   587,   596,   599,   606,
     617,   631,   634,   638,   645,   653,   658,   671,   674,   681,
     720,   728,   737,   745,   754,   762,   765,   769,   775,   778,
     781,   784,   787,   790,   794,   798,   802,   805,   810,   824,
     829,   835,   839,   843,   847,   850,   853,   856,   859,   862,
     865,   869,   873,   877,   881,   890,   893,   904,   918,   935,
     940,   951,   954,   959,   971,   977,   992,  1015,  1024,  1040,
    1043,  1051,  1054,  1060,  1063,  1066,  1072,  1081,  1088,  1092,
    1096,  1100,  1107,  1108,  1109,  1110,  1111,  1112,  1113,  1114,
    1115,  1116,  1117,  1122,  1125,  1130,  1143,  1151,  1161,  1162
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
  "STRING_T", "DATE_T", "FLOAT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "SUM", "AVG", "MAX", "MIN", "COUNT", "WHERE", "NOT", "IS",
  "LIKE", "AND", "OR", "SET", "ON", "IN", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "STORAGE", "AS", "FORMAT", "INNER_PRODUCT", "INNER", "JOIN",
  "L2_DIST", "COS_DIST", "NULL_L", "NULL_T", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "ASSIGN", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "unique_op", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "number", "null_t",
  "type", "insert_stmt", "value_list", "value", "v_list", "v_l",
  "storage_format", "delete_stmt", "update_stmt", "order_opt", "order_b",
  "order_by", "order_by_list", "select_stmt", "calc_stmt", "assign_list",
  "expression_list", "as_opt", "expression", "inner_joins", "inner_join",
  "rel_attr", "rel_attr_list", "relation", "rel_table_list", "rel_list",
  "having", "where", "condition_list", "eq_expr", "condition", "comp_op",
  "group_by", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-217)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,     0,    21,   194,   194,   -53,    30,  -217,    24,    29,
      -1,  -217,  -217,  -217,  -217,  -217,     4,    34,    16,    99,
     101,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,    28,   112,    53,    65,    25,   151,   126,   127,
     130,   133,   143,   163,   165,   167,  -217,  -217,  -217,   160,
    -217,   237,  -217,  -217,  -217,  -217,   164,   -37,   171,  -217,
    -217,   123,   135,   152,   145,   158,  -217,  -217,  -217,  -217,
     196,   144,  -217,   169,   197,   214,   242,   228,   229,    39,
     194,   194,   194,   194,   194,   194,   194,   194,   -59,  -217,
    -217,     6,   194,   178,  -217,   194,   194,   194,   194,   180,
    -217,  -217,   181,   224,   218,   194,     2,   187,   190,   223,
     200,    25,    25,  -217,  -217,  -217,  -217,   258,   -14,   259,
     266,   267,   268,   269,   270,   271,   272,   273,   208,   247,
     260,  -217,  -217,  -217,  -217,   121,   121,     6,     6,  -217,
    -217,   -37,   238,   276,    93,  -217,   218,    83,   278,    69,
    -217,   281,   146,   280,   231,  -217,  -217,  -217,  -217,   232,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,   194,
     194,   194,   285,   246,   218,   238,     2,   194,   300,   284,
    -217,  -217,    64,  -217,   194,   194,  -217,  -217,   310,  -217,
    -217,  -217,  -217,  -217,    26,   190,   297,   299,   288,   304,
    -217,    31,    47,   128,   181,   257,   328,  -217,   317,   170,
     194,   -28,   289,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
     194,    93,    93,   170,  -217,   274,   275,    55,  -217,  -217,
    -217,   280,   286,   181,   282,  -217,  -217,  -217,  -217,   -37,
     344,   338,     2,   323,   170,  -217,  -217,  -217,   170,  -217,
    -217,  -217,  -217,   324,  -217,  -217,  -217,   291,  -217,   334,
     337,   314,   194,    93,   360,   317,  -217,   -39,   301,   181,
    -217,    93,  -217,  -217,   367,  -217,  -217,  -217,   294,  -217,
    -217,   232,  -217,   346,  -217,   131,   232,  -217,  -217,  -217,
    -217
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     158,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    55,    57,   119,
      60,     0,   104,    97,    61,    80,    84,    85,     0,    31,
      30,     0,     0,     0,     0,     0,   156,     1,   159,     2,
       0,     0,    29,     0,    65,    64,     0,     0,     0,     0,
     121,   121,   121,   121,   121,     0,     0,     0,     0,    55,
      57,    96,     0,     0,    99,     0,     0,     0,     0,     0,
      87,    98,     0,     0,   131,     0,     0,     0,     0,     0,
       0,     0,     0,    62,   101,   102,    95,     0,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   103,    83,   100,    88,    89,    90,    91,    86,
     124,    85,   115,     0,   133,    69,   131,     0,    82,     0,
     157,     0,     0,    37,     0,    35,    66,    63,   111,   121,
     106,   112,   107,   113,   108,   114,   109,   110,   105,     0,
       0,     0,   125,     0,   131,   115,     0,     0,     0,     0,
     132,   141,   134,    70,     0,     0,    56,    58,     0,    47,
      51,    48,    49,    50,    42,     0,     0,     0,   119,   122,
     123,     0,     0,     0,     0,     0,   153,   116,    53,   139,
       0,     0,   148,   150,   151,   142,   143,   144,   145,   146,
       0,   133,   133,   137,    81,     0,     0,     0,    43,    44,
      40,    37,    67,     0,     0,    94,    92,    93,   126,    85,
       0,   129,     0,     0,   140,   149,   152,   147,   138,   135,
     136,   155,    41,     0,    46,    45,    38,     0,    36,   127,
       0,   118,     0,   133,    77,    53,    52,    42,     0,     0,
      34,   133,   154,   130,     0,    79,    54,    39,     0,   128,
     117,     0,    68,    75,    78,    73,     0,    72,    71,    74,
      76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -217,  -217,   357,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,   136,   173,  -217,   102,
    -217,  -217,   105,  -109,  -217,    66,  -217,  -217,  -217,  -217,
    -217,    80,  -217,   335,  -217,   186,    -4,  -143,   -46,   198,
    -217,   -88,   -75,  -216,   172,   106,  -217,  -127,  -176,  -104,
    -217,  -217,  -217,  -217,  -217,  -217,  -217
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    43,    30,    31,    32,   206,   163,   263,   240,
     204,    33,   253,    63,    64,    86,   268,    34,    35,   299,
     293,   294,   285,    36,    37,   156,    65,   111,    66,   184,
     185,    67,   129,   151,   152,   270,   274,   155,   190,   191,
     192,   230,   251,    38,    39,    40,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    89,   128,   128,   128,   128,   128,   160,   182,    46,
     237,   158,    41,    42,   169,   101,   131,   133,   135,   137,
     141,     1,     2,   255,   142,   109,    69,   269,   256,   193,
     238,   239,     3,     4,    44,     5,    45,     6,     7,     8,
       9,    10,   110,    88,    70,    11,    12,    13,   109,   138,
     139,   140,   236,    14,    15,   259,   260,   216,   245,   145,
     146,   147,   148,   269,    71,   110,   126,   102,   103,   157,
      16,    72,    56,    17,   246,   237,    18,   218,    73,    57,
      58,   209,    60,    74,   159,   104,   127,   130,   132,   134,
     136,   158,    75,   103,   210,   238,   239,   283,   143,    77,
      46,   103,    84,    85,    78,   290,   271,    80,   189,   103,
     104,   187,   105,   106,   107,   108,   231,   232,   104,    47,
     105,   106,   107,   108,   264,   265,   104,    81,   105,   106,
     107,   108,    82,   211,   212,   213,    48,    49,    50,    51,
      52,   219,   188,   275,    83,   103,   196,   197,   233,   157,
     297,   298,    90,    91,   194,   247,    92,    53,    46,    93,
      54,    55,   104,    56,   105,   106,   107,   108,     4,    94,
      57,    58,    59,    60,   254,    61,    62,    47,   199,   200,
     201,   202,   203,   103,   258,   189,   189,   166,   167,    95,
     103,    96,   102,    97,    48,    49,    50,    51,    52,    98,
     104,    46,   113,   295,   107,   108,   115,   104,   295,   105,
     106,   107,   108,   112,   114,    53,   116,   117,    54,    55,
      47,    56,   118,   119,   120,   121,   103,   189,    57,    58,
      59,    60,   103,    61,    62,   189,   179,    48,    49,    50,
      51,    52,   122,   104,    46,   105,   106,   107,   108,   104,
     123,   105,   106,   107,   108,   124,   125,   144,    53,   149,
     150,    54,    55,    47,    56,   153,   154,   161,   282,   162,
     103,    57,    58,    59,    60,   180,    61,    62,   164,   165,
      48,    49,    50,    51,    52,   168,   170,   104,   181,   105,
     106,   107,   108,   171,   172,   173,   174,   175,   176,   177,
     178,    53,   186,   183,    54,    55,   195,    56,   205,   103,
     207,   208,   215,   214,    99,   100,    59,    60,   220,    61,
      62,   198,   103,   235,   242,   243,   104,   244,   105,   106,
     107,   108,   169,   221,   222,   223,   249,   250,   257,   104,
     224,   105,   106,   107,   108,   252,   103,   267,   272,   273,
     276,   277,   262,   261,   278,   194,   225,   226,   227,   228,
     229,   141,   279,   104,   280,   105,   106,   107,   108,   281,
     284,   291,   288,   292,   296,    76,   300,   266,   241,   287,
     286,   234,    87,   217,     0,   289,   248
};

static const yytype_int16 yycheck[] =
{
       4,    47,    90,    91,    92,    93,    94,   116,   151,     7,
      49,   115,    12,    13,    28,    61,    91,    92,    93,    94,
      79,     5,     6,    51,    83,    62,    79,   243,    56,   156,
      69,    70,    16,    17,    13,    19,    15,    21,    22,    23,
      24,    25,    79,    47,    14,    29,    30,    31,    62,    95,
      96,    97,    26,    37,    38,   231,   232,   184,    27,   105,
     106,   107,   108,   279,    40,    79,    27,    28,    62,   115,
      54,    42,    70,    57,    27,    49,    60,   186,    79,    77,
      78,   169,    80,    79,    82,    79,    90,    91,    92,    93,
      94,   195,    58,    62,   169,    69,    70,   273,   102,     0,
       7,    62,    77,    78,     3,   281,   249,    79,   154,    62,
      79,    18,    81,    82,    83,    84,    52,    53,    79,    26,
      81,    82,    83,    84,    69,    70,    79,    15,    81,    82,
      83,    84,    79,   179,   180,   181,    43,    44,    45,    46,
      47,   187,    49,   252,    79,    62,    77,    78,   194,   195,
      19,    20,    26,    26,    71,    27,    26,    64,     7,    26,
      67,    68,    79,    70,    81,    82,    83,    84,    17,    26,
      77,    78,    79,    80,   220,    82,    83,    26,    32,    33,
      34,    35,    36,    62,   230,   231,   232,   121,   122,    26,
      62,    26,    28,    26,    43,    44,    45,    46,    47,    39,
      79,     7,    79,   291,    83,    84,    54,    79,   296,    81,
      82,    83,    84,    42,    79,    64,    71,    59,    67,    68,
      26,    70,    26,    79,    55,    28,    62,   273,    77,    78,
      79,    80,    62,    82,    83,   281,    28,    43,    44,    45,
      46,    47,    28,    79,     7,    81,    82,    83,    84,    79,
       8,    81,    82,    83,    84,    27,    27,    79,    64,    79,
      79,    67,    68,    26,    70,    41,    48,    80,   272,    79,
      62,    77,    78,    79,    80,    28,    82,    83,    55,    79,
      43,    44,    45,    46,    47,    27,    27,    79,    28,    81,
      82,    83,    84,    27,    27,    27,    27,    27,    27,    27,
      27,    64,    26,    65,    67,    68,    28,    70,    28,    62,
      79,    79,    66,    28,    77,    78,    79,    80,    18,    82,
      83,    40,    62,    13,    27,    26,    79,    39,    81,    82,
      83,    84,    28,    49,    50,    51,    79,     9,    49,    79,
      56,    81,    82,    83,    84,    28,    62,    61,     4,    11,
      27,    27,    77,    79,    63,    71,    72,    73,    74,    75,
      76,    79,    28,    79,    27,    81,    82,    83,    84,    55,
      10,     4,    71,    79,    28,    18,   296,   241,   205,   277,
     275,   195,    47,   185,    -1,   279,   214
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    16,    17,    19,    21,    22,    23,    24,
      25,    29,    30,    31,    37,    38,    54,    57,    60,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     100,   101,   102,   108,   114,   115,   120,   121,   140,   141,
     142,    12,    13,    99,    13,    15,     7,    26,    43,    44,
      45,    46,    47,    64,    67,    68,    70,    77,    78,    79,
      80,    82,    83,   110,   111,   123,   125,   128,   123,    79,
      14,    40,    42,    79,    79,    58,    89,     0,     3,   143,
      79,    15,    79,    79,    77,    78,   112,   120,   123,   125,
      26,    26,    26,    26,    26,    26,    26,    26,    39,    77,
      78,   125,    28,    62,    79,    81,    82,    83,    84,    62,
      79,   124,    42,    79,    79,    54,    71,    59,    26,    79,
      55,    28,    28,     8,    27,    27,    27,   123,   128,   129,
     123,   129,   123,   129,   123,   129,   123,   129,   125,   125,
     125,    79,    83,   123,    79,   125,   125,   125,   125,    79,
      79,   130,   131,    41,    48,   134,   122,   125,   136,    82,
     110,    80,    79,   104,    55,    79,   112,   112,    27,    28,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    28,
      28,    28,   124,    65,   126,   127,    26,    18,    49,   125,
     135,   136,   137,   134,    71,    28,    77,    78,    40,    32,
      33,    34,    35,    36,   107,    28,   103,    79,    79,   128,
     129,   125,   125,   125,    28,    66,   134,   126,   110,   125,
      18,    49,    50,    51,    56,    72,    73,    74,    75,    76,
     138,    52,    53,   125,   122,    13,    26,    49,    69,    70,
     106,   104,    27,    26,    39,    27,    27,    27,   131,    79,
       9,   139,    28,   109,   125,    51,    56,    49,   125,   135,
     135,    79,    77,   105,    69,    70,   103,    61,   113,   130,
     132,   124,     4,    11,   133,   110,    27,    27,    63,    28,
      27,    55,   123,   135,    10,   119,   109,   106,    71,   132,
     135,     4,    79,   117,   118,   128,    28,    19,    20,   116,
     118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    99,   100,   101,   102,   103,   103,   104,
     104,   105,   106,   106,   106,   106,   106,   107,   107,   107,
     107,   107,   108,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   111,   112,   112,   112,   112,   113,   113,   114,
     115,   116,   116,   116,   117,   118,   118,   119,   119,   120,
     121,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   129,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   135,   135,   136,   137,   137,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   140,   141,   142,   143,   143
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     0,     9,     5,     8,     0,     3,     6,
       3,     1,     0,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     2,     1,     2,     1,
       1,     1,     3,     3,     1,     1,     3,     0,     4,     4,
       5,     1,     1,     0,     2,     1,     3,     0,     3,     9,
       2,     3,     1,     3,     1,     0,     2,     1,     3,     3,
       3,     3,     6,     6,     6,     3,     2,     1,     2,     2,
       3,     3,     3,     3,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     0,     2,     6,     4,     1,
       3,     0,     1,     3,     1,     2,     4,     1,     3,     0,
       2,     0,     2,     0,     1,     3,     3,     3,     3,     2,
       3,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     2,     0,     3,     7,     2,     4,     0,     1
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
#line 289 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1949 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 319 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1958 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 325 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1966 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 330 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1974 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 336 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1982 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 342 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1990 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 348 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1998 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 354 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2008 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 361 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 367 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2026 "yacc_sql.cpp"
    break;

  case 32: /* unique_op: UNIQUE  */
#line 374 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2034 "yacc_sql.cpp"
    break;

  case 33: /* unique_op: %empty  */
#line 378 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2042 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE unique_op INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 387 "yacc_sql.y"
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
#line 2058 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 402 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 412 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 435 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 439 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE null_t  */
#line 452 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = ((yyvsp[-2].number)) * sizeof(float);
      (yyval.attr_info)->nullable = (yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 2130 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type null_t  */
#line 461 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 41: /* number: NUMBER  */
#line 471 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2149 "yacc_sql.cpp"
    break;

  case 42: /* null_t: %empty  */
#line 475 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 43: /* null_t: NULL_L  */
#line 479 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2165 "yacc_sql.cpp"
    break;

  case 44: /* null_t: NULL_T  */
#line 483 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 45: /* null_t: NOT NULL_T  */
#line 487 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 46: /* null_t: NOT NULL_L  */
#line 491 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 47: /* type: INT_T  */
#line 497 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2195 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 498 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2201 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 499 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2207 "yacc_sql.cpp"
    break;

  case 50: /* type: FLOAT_T  */
#line 500 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2213 "yacc_sql.cpp"
    break;

  case 51: /* type: VECTOR_T  */
#line 501 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2219 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 505 "yacc_sql.y"
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
#line 2236 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 521 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2244 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 524 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2258 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 535 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2267 "yacc_sql.cpp"
    break;

  case 56: /* value: '-' NUMBER  */
#line 539 "yacc_sql.y"
                 {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2276 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 543 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 58: /* value: '-' FLOAT  */
#line 547 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2294 "yacc_sql.cpp"
    break;

  case 59: /* value: NULL_T  */
#line 551 "yacc_sql.y"
             {
        (yyval.value) = new Value();
        (yyval.value)->set_null();
        (yyloc) = (yylsp[0]);
    }
#line 2304 "yacc_sql.cpp"
    break;

  case 60: /* value: SSS  */
#line 556 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2315 "yacc_sql.cpp"
    break;

  case 61: /* value: v_list  */
#line 562 "yacc_sql.y"
             {
      std::reverse((yyvsp[0].vec_list)->begin(), (yyvsp[0].vec_list)->end());
      (yyval.value) = new Value(*(yyvsp[0].vec_list));

      delete (yyvsp[0].vec_list);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 62: /* v_list: LBRACKET v_l RBRACKET  */
#line 570 "yacc_sql.y"
                          {
      (yyval.vec_list) = (yyvsp[-1].vec_list);
    }
#line 2334 "yacc_sql.cpp"
    break;

  case 63: /* v_l: FLOAT COMMA v_l  */
#line 575 "yacc_sql.y"
                    {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].floats));
    }
#line 2343 "yacc_sql.cpp"
    break;

  case 64: /* v_l: FLOAT  */
#line 579 "yacc_sql.y"
            {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].floats));
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 65: /* v_l: NUMBER  */
#line 583 "yacc_sql.y"
             {
      (yyval.vec_list) = new std::vector<float>;
      (yyval.vec_list)->push_back((yyvsp[0].number));
    }
#line 2361 "yacc_sql.cpp"
    break;

  case 66: /* v_l: NUMBER COMMA v_l  */
#line 587 "yacc_sql.y"
                       {
      (yyval.vec_list) = (yyvsp[0].vec_list);
      (yyval.vec_list)->push_back((yyvsp[-2].number));
    }
#line 2370 "yacc_sql.cpp"
    break;

  case 67: /* storage_format: %empty  */
#line 596 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2378 "yacc_sql.cpp"
    break;

  case 68: /* storage_format: STORAGE FORMAT EQ ID  */
#line 600 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 69: /* delete_stmt: DELETE FROM ID where  */
#line 607 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 70: /* update_stmt: UPDATE ID SET assign_list where  */
#line 618 "yacc_sql.y"
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
#line 2414 "yacc_sql.cpp"
    break;

  case 71: /* order_opt: ASC  */
#line 631 "yacc_sql.y"
        {
      (yyval.number) = 0;
    }
#line 2422 "yacc_sql.cpp"
    break;

  case 72: /* order_opt: DESC  */
#line 634 "yacc_sql.y"
           {
      (yyval.number) = 1;
    }
#line 2430 "yacc_sql.cpp"
    break;

  case 73: /* order_opt: %empty  */
#line 638 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2438 "yacc_sql.cpp"
    break;

  case 74: /* order_b: rel_attr order_opt  */
#line 646 "yacc_sql.y"
    {
      (yyval.expression) = new OrderByExpr((yyvsp[-1].rel_attr)->relation_name, (yyvsp[-1].rel_attr)->attribute_name, (yyvsp[0].number));
      delete (yyvsp[-1].rel_attr);
    }
#line 2447 "yacc_sql.cpp"
    break;

  case 75: /* order_by: order_b  */
#line 654 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2456 "yacc_sql.cpp"
    break;

  case 76: /* order_by: order_b COMMA order_by  */
#line 659 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->insert((yyval.expression_list)->begin(),std::unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 77: /* order_by_list: %empty  */
#line 671 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 78: /* order_by_list: ORDER BY order_by  */
#line 675 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 79: /* select_stmt: SELECT expression_list FROM rel_table_list inner_joins where group_by having order_by_list  */
#line 682 "yacc_sql.y"
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
#line 2526 "yacc_sql.cpp"
    break;

  case 80: /* calc_stmt: CALC expression_list  */
#line 721 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 81: /* assign_list: eq_expr COMMA assign_list  */
#line 729 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 82: /* assign_list: eq_expr  */
#line 738 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2558 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression COMMA expression_list  */
#line 746 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 84: /* expression_list: expression  */
#line 755 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 85: /* as_opt: %empty  */
#line 762 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2588 "yacc_sql.cpp"
    break;

  case 86: /* as_opt: AS ID  */
#line 766 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 87: /* as_opt: ID  */
#line 770 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '+' expression  */
#line 775 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '-' expression  */
#line 778 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '*' expression  */
#line 781 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '/' expression  */
#line 784 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 92: /* expression: L2_DIST LBRACE expression COMMA expression RBRACE  */
#line 787 "yacc_sql.y"
                                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_NORM, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 93: /* expression: COS_DIST LBRACE expression COMMA expression RBRACE  */
#line 790 "yacc_sql.y"
                                                         {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_SIMILARITY, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 94: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 794 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 95: /* expression: LBRACE expression RBRACE  */
#line 798 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2669 "yacc_sql.cpp"
    break;

  case 96: /* expression: '-' expression  */
#line 802 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 97: /* expression: value  */
#line 805 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 98: /* expression: rel_attr as_opt  */
#line 810 "yacc_sql.y"
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
#line 2706 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression ID  */
#line 824 "yacc_sql.y"
                    {
        (yyval.expression) = (yyvsp[-1].expression);
        (yyval.expression)->set_name((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression AS ID  */
#line 829 "yacc_sql.y"
                       {
        (yyval.expression) = (yyvsp[-2].expression);
        (yyval.expression)->set_name((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 101: /* expression: LBRACE select_stmt RBRACE  */
#line 835 "yacc_sql.y"
                                {
       (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
       delete (yyvsp[-1].sql_node);
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 102: /* expression: LBRACE expression_list RBRACE  */
#line 839 "yacc_sql.y"
                                    {
       (yyval.expression) = new ValueListExpr(std::move(*(yyvsp[-1].expression_list)));
       delete (yyvsp[-1].expression_list);
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 103: /* expression: ID DOT '*'  */
#line 843 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 104: /* expression: '*'  */
#line 847 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 105: /* expression: COUNT LBRACE rel_attr_list RBRACE  */
#line 850 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 106: /* expression: SUM LBRACE rel_attr_list RBRACE  */
#line 853 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2777 "yacc_sql.cpp"
    break;

  case 107: /* expression: AVG LBRACE rel_attr_list RBRACE  */
#line 856 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2785 "yacc_sql.cpp"
    break;

  case 108: /* expression: MAX LBRACE rel_attr_list RBRACE  */
#line 859 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 109: /* expression: MIN LBRACE rel_attr_list RBRACE  */
#line 862 "yacc_sql.y"
                                      {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, (yyvsp[-1].rel_attr_list), sql_string, &(yyloc));
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 110: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 865 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression(AggrType::COUNT, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 111: /* expression: SUM LBRACE expression_list RBRACE  */
#line 869 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::SUM, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 112: /* expression: AVG LBRACE expression_list RBRACE  */
#line 873 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::AVG, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 113: /* expression: MAX LBRACE expression_list RBRACE  */
#line 877 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MAX, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 114: /* expression: MIN LBRACE expression_list RBRACE  */
#line 881 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression(AggrType::MIN, std::move(*(yyvsp[-1].expression_list)), sql_string, &(yyloc));
      delete (yyvsp[-1].expression_list);
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 115: /* inner_joins: %empty  */
#line 890 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 2854 "yacc_sql.cpp"
    break;

  case 116: /* inner_joins: inner_join inner_joins  */
#line 893 "yacc_sql.y"
                             {
      if ((yyvsp[0].inner_join_list) != nullptr) {
         (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
         (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_j));
      delete (yyvsp[-1].inner_j);
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 117: /* inner_join: INNER JOIN ID as_opt ON condition_list  */
#line 904 "yacc_sql.y"
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
#line 2887 "yacc_sql.cpp"
    break;

  case 118: /* inner_join: INNER JOIN ID as_opt  */
#line 918 "yacc_sql.y"
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
#line 2906 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr: ID  */
#line 935 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2916 "yacc_sql.cpp"
    break;

  case 120: /* rel_attr: ID DOT ID  */
#line 940 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 121: /* rel_attr_list: %empty  */
#line 951 "yacc_sql.y"
    {
       (yyval.rel_attr_list) = nullptr;
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 122: /* rel_attr_list: rel_attr  */
#line 954 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 2946 "yacc_sql.cpp"
    break;

  case 123: /* rel_attr_list: rel_attr COMMA rel_attr_list  */
#line 959 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-2].rel_attr));
      delete (yyvsp[-2].rel_attr);
    }
#line 2960 "yacc_sql.cpp"
    break;

  case 124: /* relation: ID  */
#line 971 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 125: /* rel_table_list: relation as_opt  */
#line 977 "yacc_sql.y"
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
#line 2988 "yacc_sql.cpp"
    break;

  case 126: /* rel_table_list: relation as_opt COMMA rel_table_list  */
#line 992 "yacc_sql.y"
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
#line 3012 "yacc_sql.cpp"
    break;

  case 127: /* rel_list: relation  */
#line 1015 "yacc_sql.y"
             {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>();

        RelAttrSqlNode node;
        node.attribute_name = (yyvsp[0].string);
        (yyval.rel_attr_list)->push_back(node);

      free((yyvsp[0].string));
    }
#line 3026 "yacc_sql.cpp"
    break;

  case 128: /* rel_list: relation COMMA rel_list  */
#line 1024 "yacc_sql.y"
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
#line 3044 "yacc_sql.cpp"
    break;

  case 129: /* having: %empty  */
#line 1040 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3052 "yacc_sql.cpp"
    break;

  case 130: /* having: HAVING condition_list  */
#line 1043 "yacc_sql.y"
                            {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 131: /* where: %empty  */
#line 1051 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 132: /* where: WHERE condition_list  */
#line 1054 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3076 "yacc_sql.cpp"
    break;

  case 133: /* condition_list: %empty  */
#line 1060 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 134: /* condition_list: condition  */
#line 1063 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 135: /* condition_list: condition AND condition_list  */
#line 1066 "yacc_sql.y"
                                   {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND,tmp);
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 136: /* condition_list: condition OR condition_list  */
#line 1072 "yacc_sql.y"
                                  {
      std::vector<std::unique_ptr<Expression>> tmp;
      tmp.emplace_back((yyvsp[-2].expression));
      tmp.emplace_back((yyvsp[0].expression));
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, tmp);
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 137: /* eq_expr: expression EQ expression  */
#line 1082 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EQUAL_TO, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 138: /* condition: expression comp_op expression  */
#line 1089 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 139: /* condition: EXISTS expression  */
#line 1093 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(EXISTS_C, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 140: /* condition: NOT EXISTS expression  */
#line 1097 "yacc_sql.y"
    {
      (yyval.expression) = create_comparison_expression(NOT_EXISTS, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3146 "yacc_sql.cpp"
    break;

  case 141: /* condition: eq_expr  */
#line 1101 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: LT  */
#line 1107 "yacc_sql.y"
       { (yyval.comp) = LESS_THAN; }
#line 3160 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: GT  */
#line 1108 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3166 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: LE  */
#line 1109 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3172 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: GE  */
#line 1110 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3178 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: NE  */
#line 1111 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3184 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: IS NOT  */
#line 1112 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_C;}
#line 3190 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: IS  */
#line 1113 "yacc_sql.y"
         { (yyval.comp) = IS_C;}
#line 3196 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: NOT LIKE  */
#line 1114 "yacc_sql.y"
                { (yyval.comp) = NOT_LIKE; }
#line 3202 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: LIKE  */
#line 1115 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3208 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: IN  */
#line 1116 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3214 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: NOT IN  */
#line 1117 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3220 "yacc_sql.cpp"
    break;

  case 153: /* group_by: %empty  */
#line 1122 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3228 "yacc_sql.cpp"
    break;

  case 154: /* group_by: GROUP BY expression_list  */
#line 1125 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3236 "yacc_sql.cpp"
    break;

  case 155: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1131 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3250 "yacc_sql.cpp"
    break;

  case 156: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1144 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 157: /* set_variable_stmt: SET ID EQ value  */
#line 1152 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3271 "yacc_sql.cpp"
    break;


#line 3275 "yacc_sql.cpp"

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

#line 1164 "yacc_sql.y"

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
