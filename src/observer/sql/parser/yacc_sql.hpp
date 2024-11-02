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
    LIMIT = 266,                   /* LIMIT  */
    HAVING = 267,                  /* HAVING  */
    UNIQUE = 268,                  /* UNIQUE  */
    TABLE = 269,                   /* TABLE  */
    TABLES = 270,                  /* TABLES  */
    INDEX = 271,                   /* INDEX  */
    CALC = 272,                    /* CALC  */
    SELECT = 273,                  /* SELECT  */
    EXISTS = 274,                  /* EXISTS  */
    DESC = 275,                    /* DESC  */
    ASC = 276,                     /* ASC  */
    TYPE = 277,                    /* TYPE  */
    DISTANCE = 278,                /* DISTANCE  */
    SHOW = 279,                    /* SHOW  */
    SYNC = 280,                    /* SYNC  */
    INSERT = 281,                  /* INSERT  */
    DELETE = 282,                  /* DELETE  */
    UPDATE = 283,                  /* UPDATE  */
    LBRACE = 284,                  /* LBRACE  */
    RBRACE = 285,                  /* RBRACE  */
    COMMA = 286,                   /* COMMA  */
    TRX_BEGIN = 287,               /* TRX_BEGIN  */
    TRX_COMMIT = 288,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 289,            /* TRX_ROLLBACK  */
    INT_T = 290,                   /* INT_T  */
    VECTOR_T = 291,                /* VECTOR_T  */
    TEXT_T = 292,                  /* TEXT_T  */
    STRING_T = 293,                /* STRING_T  */
    DATE_T = 294,                  /* DATE_T  */
    FLOAT_T = 295,                 /* FLOAT_T  */
    HELP = 296,                    /* HELP  */
    EXIT = 297,                    /* EXIT  */
    DOT = 298,                     /* DOT  */
    INTO = 299,                    /* INTO  */
    VALUES = 300,                  /* VALUES  */
    WITH = 301,                    /* WITH  */
    IVFFLAT = 302,                 /* IVFFLAT  */
    LISTS = 303,                   /* LISTS  */
    PROBS = 304,                   /* PROBS  */
    FROM = 305,                    /* FROM  */
    SUM = 306,                     /* SUM  */
    AVG = 307,                     /* AVG  */
    MAX = 308,                     /* MAX  */
    MIN = 309,                     /* MIN  */
    COUNT = 310,                   /* COUNT  */
    WHERE = 311,                   /* WHERE  */
    NOT = 312,                     /* NOT  */
    IS = 313,                      /* IS  */
    LIKE = 314,                    /* LIKE  */
    AND = 315,                     /* AND  */
    OR = 316,                      /* OR  */
    SET = 317,                     /* SET  */
    ON = 318,                      /* ON  */
    IN = 319,                      /* IN  */
    LOAD = 320,                    /* LOAD  */
    DATA = 321,                    /* DATA  */
    INFILE = 322,                  /* INFILE  */
    EXPLAIN = 323,                 /* EXPLAIN  */
    STORAGE = 324,                 /* STORAGE  */
    AS = 325,                      /* AS  */
    FORMAT = 326,                  /* FORMAT  */
    INNER_PRODUCT = 327,           /* INNER_PRODUCT  */
    INNER = 328,                   /* INNER  */
    JOIN = 329,                    /* JOIN  */
    L2_DIST = 330,                 /* L2_DIST  */
    COS_DIST = 331,                /* COS_DIST  */
    NULL_L = 332,                  /* NULL_L  */
    NULL_T = 333,                  /* NULL_T  */
    EQ = 334,                      /* EQ  */
    LT = 335,                      /* LT  */
    GT = 336,                      /* GT  */
    LE = 337,                      /* LE  */
    GE = 338,                      /* GE  */
    NE = 339,                      /* NE  */
    NUMBER = 340,                  /* NUMBER  */
    FLOAT = 341,                   /* FLOAT  */
    ID = 342,                      /* ID  */
    SSS = 343,                     /* SSS  */
    UMINUS = 344                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 204 "yacc_sql.y"

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

#line 175 "yacc_sql.hpp"

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
