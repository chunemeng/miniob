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
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    CALC = 268,                    /* CALC  */
    SELECT = 269,                  /* SELECT  */
    EXISTS = 270,                  /* EXISTS  */
    DESC = 271,                    /* DESC  */
    SHOW = 272,                    /* SHOW  */
    SYNC = 273,                    /* SYNC  */
    INSERT = 274,                  /* INSERT  */
    DELETE = 275,                  /* DELETE  */
    UPDATE = 276,                  /* UPDATE  */
    LBRACE = 277,                  /* LBRACE  */
    RBRACE = 278,                  /* RBRACE  */
    COMMA = 279,                   /* COMMA  */
    TRX_BEGIN = 280,               /* TRX_BEGIN  */
    TRX_COMMIT = 281,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 282,            /* TRX_ROLLBACK  */
    INT_T = 283,                   /* INT_T  */
    VECTOR_T = 284,                /* VECTOR_T  */
    STRING_T = 285,                /* STRING_T  */
    DATE_T = 286,                  /* DATE_T  */
    FLOAT_T = 287,                 /* FLOAT_T  */
    HELP = 288,                    /* HELP  */
    EXIT = 289,                    /* EXIT  */
    DOT = 290,                     /* DOT  */
    INTO = 291,                    /* INTO  */
    VALUES = 292,                  /* VALUES  */
    FROM = 293,                    /* FROM  */
    SUM = 294,                     /* SUM  */
    AVG = 295,                     /* AVG  */
    MAX = 296,                     /* MAX  */
    MIN = 297,                     /* MIN  */
    COUNT = 298,                   /* COUNT  */
    WHERE = 299,                   /* WHERE  */
    NOT = 300,                     /* NOT  */
    IS = 301,                      /* IS  */
    LIKE = 302,                    /* LIKE  */
    AND = 303,                     /* AND  */
    SET = 304,                     /* SET  */
    ON = 305,                      /* ON  */
    IN = 306,                      /* IN  */
    LOAD = 307,                    /* LOAD  */
    DATA = 308,                    /* DATA  */
    INFILE = 309,                  /* INFILE  */
    EXPLAIN = 310,                 /* EXPLAIN  */
    STORAGE = 311,                 /* STORAGE  */
    FORMAT = 312,                  /* FORMAT  */
    INNER = 313,                   /* INNER  */
    JOIN = 314,                    /* JOIN  */
    L2_DIST = 315,                 /* L2_DIST  */
    COS_DIST = 316,                /* COS_DIST  */
    INNER_PRODUCT = 317,           /* INNER_PRODUCT  */
    NULL_L = 318,                  /* NULL_L  */
    NULL_T = 319,                  /* NULL_T  */
    EQ = 320,                      /* EQ  */
    LT = 321,                      /* LT  */
    GT = 322,                      /* GT  */
    LE = 323,                      /* LE  */
    GE = 324,                      /* GE  */
    NE = 325,                      /* NE  */
    NUMBER = 326,                  /* NUMBER  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    UMINUS = 330                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 190 "yacc_sql.y"

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

#line 161 "yacc_sql.hpp"

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
