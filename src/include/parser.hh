/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_PARSER_HH_INCLUDED
# define YY_YY_SRC_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 16 "src/parser.yy"

    #include <cstdint>
    #include "types.hh"
    

#line 54 "src/parser.hh"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_INT = 258,
    TOKEN_STR = 259,
    TOKEN_BLK = 260,
    TOKEN_FUN = 261,
    TOKEN_IF = 262,
    TOKEN_ELSE = 263,
    TOKEN_FOR = 264,
    TOKEN_FROM = 265,
    TOKEN_TO = 266,
    TOKEN_WHILE = 267,
    TOKEN_VAR = 268,
    TOKEN_BRK = 269,
    TOKEN_CNT = 270,
    TOKEN_RET = 271,
    TOKEN_NIL = 272,
    TOKEN_DIR_GRID = 273,
    TOKEN_DIR_TITLE = 274,
    TOKEN_DIR_ICON = 275,
    TOKEN_SQ_BRACK_L = 276,
    TOKEN_SQ_BRACK_R = 277,
    TOKEN_PAREN_L = 278,
    TOKEN_PAREN_R = 279,
    TOKEN_BRACE_L = 280,
    TOKEN_BRACE_R = 281,
    TOKEN_PLUS = 282,
    TOKEN_MINUS = 283,
    TOKEN_SLASH = 284,
    TOKEN_STAR = 285,
    TOKEN_MODULO = 286,
    TOKEN_DOUBLE_EQ = 287,
    TOKEN_NOT_EQ = 288,
    TOKEN_GREATER_EQ = 289,
    TOKEN_LESS_EQ = 290,
    TOKEN_EQUAL = 291,
    TOKEN_LESS = 292,
    TOKEN_GREATER = 293,
    TOKEN_LOGICAL_AND = 294,
    TOKEN_LOGICAL_OR = 295,
    TOKEN_LOGICAL_NOT = 296,
    TOKEN_SEMICOLON = 297,
    TOKEN_COLON = 298,
    TOKEN_COMMA = 299,
    TOKEN_INT_VAL = 300,
    TOKEN_STR_VAL = 301,
    TOKEN_IDENTIFIER = 302,
    TOKEN_LOG = 303,
    TOKEN_ERR = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  ExprType  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HH_INCLUDED  */
