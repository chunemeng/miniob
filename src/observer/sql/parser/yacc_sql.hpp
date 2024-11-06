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
    NAMES = 275,                   /* NAMES  */
    DESC = 276,                    /* DESC  */
    COLLATE = 277,                 /* COLLATE  */
    ASC = 278,                     /* ASC  */
    TYPE = 279,                    /* TYPE  */
    DISTANCE = 280,                /* DISTANCE  */
    SHOW = 281,                    /* SHOW  */
    SYNC = 282,                    /* SYNC  */
    INSERT = 283,                  /* INSERT  */
    DELETE = 284,                  /* DELETE  */
    UPDATE = 285,                  /* UPDATE  */
    LBRACE = 286,                  /* LBRACE  */
    VIEW = 287,                    /* VIEW  */
    RBRACE = 288,                  /* RBRACE  */
    COMMA = 289,                   /* COMMA  */
    TRX_BEGIN = 290,               /* TRX_BEGIN  */
    TRX_COMMIT = 291,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 292,            /* TRX_ROLLBACK  */
    INT_T = 293,                   /* INT_T  */
    VECTOR_T = 294,                /* VECTOR_T  */
    TEXT_T = 295,                  /* TEXT_T  */
    STRING_T = 296,                /* STRING_T  */
    UTF8MB4_BIN = 297,             /* UTF8MB4_BIN  */
    DATE_T = 298,                  /* DATE_T  */
    FLOAT_T = 299,                 /* FLOAT_T  */
    HELP = 300,                    /* HELP  */
    EXIT = 301,                    /* EXIT  */
    DOT = 302,                     /* DOT  */
    INTO = 303,                    /* INTO  */
    VALUES = 304,                  /* VALUES  */
    WITH = 305,                    /* WITH  */
    IVFFLAT = 306,                 /* IVFFLAT  */
    LISTS = 307,                   /* LISTS  */
    PROBS = 308,                   /* PROBS  */
    FROM = 309,                    /* FROM  */
    SUM = 310,                     /* SUM  */
    AVG = 311,                     /* AVG  */
    MAX = 312,                     /* MAX  */
    MIN = 313,                     /* MIN  */
    COUNT = 314,                   /* COUNT  */
    WHERE = 315,                   /* WHERE  */
    NOT = 316,                     /* NOT  */
    IS = 317,                      /* IS  */
    LIKE = 318,                    /* LIKE  */
    AND = 319,                     /* AND  */
    OR = 320,                      /* OR  */
    SET = 321,                     /* SET  */
    ON = 322,                      /* ON  */
    IN = 323,                      /* IN  */
    LOAD = 324,                    /* LOAD  */
    DATA = 325,                    /* DATA  */
    INFILE = 326,                  /* INFILE  */
    EXPLAIN = 327,                 /* EXPLAIN  */
    STORAGE = 328,                 /* STORAGE  */
    AS = 329,                      /* AS  */
    FORMAT = 330,                  /* FORMAT  */
    INNER_PRODUCT = 331,           /* INNER_PRODUCT  */
    INNER = 332,                   /* INNER  */
    JOIN = 333,                    /* JOIN  */
    L2_DIST = 334,                 /* L2_DIST  */
    COS_DIST = 335,                /* COS_DIST  */
    NULL_L = 336,                  /* NULL_L  */
    NULL_T = 337,                  /* NULL_T  */
    EQ = 338,                      /* EQ  */
    LT = 339,                      /* LT  */
    GT = 340,                      /* GT  */
    LE = 341,                      /* LE  */
    GE = 342,                      /* GE  */
    NE = 343,                      /* NE  */
    NUMBER = 344,                  /* NUMBER  */
    FLOAT = 345,                   /* FLOAT  */
    ID = 346,                      /* ID  */
    SSS = 347,                     /* SSS  */
    UMINUS = 348                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 208 "yacc_sql.y"

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

#line 179 "yacc_sql.hpp"

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
