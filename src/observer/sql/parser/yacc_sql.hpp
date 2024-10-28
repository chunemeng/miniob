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
    STRING_T = 289,                /* STRING_T  */
    DATE_T = 290,                  /* DATE_T  */
    FLOAT_T = 291,                 /* FLOAT_T  */
    HELP = 292,                    /* HELP  */
    EXIT = 293,                    /* EXIT  */
    DOT = 294,                     /* DOT  */
    INTO = 295,                    /* INTO  */
    VALUES = 296,                  /* VALUES  */
    FROM = 297,                    /* FROM  */
    SUM = 298,                     /* SUM  */
    AVG = 299,                     /* AVG  */
    MAX = 300,                     /* MAX  */
    MIN = 301,                     /* MIN  */
    COUNT = 302,                   /* COUNT  */
    WHERE = 303,                   /* WHERE  */
    NOT = 304,                     /* NOT  */
    IS = 305,                      /* IS  */
    LIKE = 306,                    /* LIKE  */
    AND = 307,                     /* AND  */
    OR = 308,                      /* OR  */
    SET = 309,                     /* SET  */
    ON = 310,                      /* ON  */
    IN = 311,                      /* IN  */
    LOAD = 312,                    /* LOAD  */
    DATA = 313,                    /* DATA  */
    INFILE = 314,                  /* INFILE  */
    EXPLAIN = 315,                 /* EXPLAIN  */
    STORAGE = 316,                 /* STORAGE  */
    AS = 317,                      /* AS  */
    FORMAT = 318,                  /* FORMAT  */
    INNER_PRODUCT = 319,           /* INNER_PRODUCT  */
    INNER = 320,                   /* INNER  */
    JOIN = 321,                    /* JOIN  */
    L2_DIST = 322,                 /* L2_DIST  */
    COS_DIST = 323,                /* COS_DIST  */
    NULL_L = 324,                  /* NULL_L  */
    NULL_T = 325,                  /* NULL_T  */
    EQ = 326,                      /* EQ  */
    LT = 327,                      /* LT  */
    GT = 328,                      /* GT  */
    LE = 329,                      /* LE  */
    GE = 330,                      /* GE  */
    NE = 331,                      /* NE  */
    NUMBER = 332,                  /* NUMBER  */
    FLOAT = 333,                   /* FLOAT  */
    ID = 334,                      /* ID  */
    SSS = 335,                     /* SSS  */
    UMINUS = 336,                  /* UMINUS  */
    ASSIGN = 337                   /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 196 "yacc_sql.y"

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
