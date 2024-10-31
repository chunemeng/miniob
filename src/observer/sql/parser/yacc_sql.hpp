/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    LBRACKET = 262,                /* LBRACKET  */
    RBRACKET = 263,                /* RBRACKET  */
    GROUP = 264,                   /* GROUP  */
    ORDER = 265,                   /* ORDER  */
    HAVING = 266,                  /* HAVING  */
    UNIQUE = 267,                  /* UNIQUE  */
    TABLE = 268,                   /* TABLE  */
    TABLES = 269,                  /* TABLES  */
    INDEX = 270,                   /* INDEX  */
    CALC = 271,                    /* CALC  */
    SELECT = 272,                  /* SELECT  */
    EXISTS = 273,                  /* EXISTS  */
    DESC = 274,                    /* DESC  */
    ASC = 275,                     /* ASC  */
    SHOW = 276,                    /* SHOW  */
    SYNC = 277,                    /* SYNC  */
    INSERT = 278,                  /* INSERT  */
    DELETE = 279,                  /* DELETE  */
    UPDATE = 280,                  /* UPDATE  */
    LBRACE = 281,                  /* LBRACE  */
    RBRACE = 282,                  /* RBRACE  */
    COMMA = 283,                   /* COMMA  */
    TRX_BEGIN = 284,               /* TRX_BEGIN  */
    TRX_COMMIT = 285,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 286,            /* TRX_ROLLBACK  */
    INT_T = 287,                   /* INT_T  */
    VECTOR_T = 288,                /* VECTOR_T  */
    TEXT_T = 289,                  /* TEXT_T  */
    STRING_T = 290,                /* STRING_T  */
    DATE_T = 291,                  /* DATE_T  */
    FLOAT_T = 292,                 /* FLOAT_T  */
    HELP = 293,                    /* HELP  */
    EXIT = 294,                    /* EXIT  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    FROM = 298,                    /* FROM  */
    SUM = 299,                     /* SUM  */
    AVG = 300,                     /* AVG  */
    MAX = 301,                     /* MAX  */
    MIN = 302,                     /* MIN  */
    COUNT = 303,                   /* COUNT  */
    WHERE = 304,                   /* WHERE  */
    NOT = 305,                     /* NOT  */
    IS = 306,                      /* IS  */
    LIKE = 307,                    /* LIKE  */
    AND = 308,                     /* AND  */
    OR = 309,                      /* OR  */
    SET = 310,                     /* SET  */
    ON = 311,                      /* ON  */
    IN = 312,                      /* IN  */
    LOAD = 313,                    /* LOAD  */
    DATA = 314,                    /* DATA  */
    INFILE = 315,                  /* INFILE  */
    EXPLAIN = 316,                 /* EXPLAIN  */
    STORAGE = 317,                 /* STORAGE  */
    AS = 318,                      /* AS  */
    FORMAT = 319,                  /* FORMAT  */
    INNER_PRODUCT = 320,           /* INNER_PRODUCT  */
    INNER = 321,                   /* INNER  */
    JOIN = 322,                    /* JOIN  */
    L2_DIST = 323,                 /* L2_DIST  */
    COS_DIST = 324,                /* COS_DIST  */
    NULL_L = 325,                  /* NULL_L  */
    NULL_T = 326,                  /* NULL_T  */
    EQ = 327,                      /* EQ  */
    LT = 328,                      /* LT  */
    GT = 329,                      /* GT  */
    LE = 330,                      /* LE  */
    GE = 331,                      /* GE  */
    NE = 332,                      /* NE  */
    NUMBER = 333,                  /* NUMBER  */
    FLOAT = 334,                   /* FLOAT  */
    ID = 335,                      /* ID  */
    SSS = 336,                     /* SSS  */
    UMINUS = 337                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 197 "yacc_sql.y"

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

#line 168 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
