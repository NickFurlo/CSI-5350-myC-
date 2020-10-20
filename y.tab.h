/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    ID = 259,
    bool_val = 260,
    float_val = 261,
    int_val = 262,
    string_val = 263,
    char_val = 264,
    SEMICOLON = 265,
    EQUALS = 266,
    PRINT = 267,
    PLUS = 268,
    MINUS = 269,
    TIMES = 270,
    DIVIDE = 271,
    LPAREN = 272,
    RPAREN = 273,
    LBRACE = 274,
    RBRACE = 275,
    LBRACKET = 276,
    RBRACKET = 277,
    EQUAL = 278,
    NOTEQUAL = 279,
    NOT = 280,
    LESS = 281,
    GREATER = 282,
    LESSEQUAL = 283,
    GREATEREQUAL = 284,
    EXPO = 285,
    COMMA = 286,
    ADD = 287,
    AND = 288,
    OR = 289,
    IF = 290,
    THEN = 291,
    ELSE = 292,
    WHILE = 293,
    stringexpr = 294
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define ID 259
#define bool_val 260
#define float_val 261
#define int_val 262
#define string_val 263
#define char_val 264
#define SEMICOLON 265
#define EQUALS 266
#define PRINT 267
#define PLUS 268
#define MINUS 269
#define TIMES 270
#define DIVIDE 271
#define LPAREN 272
#define RPAREN 273
#define LBRACE 274
#define RBRACE 275
#define LBRACKET 276
#define RBRACKET 277
#define EQUAL 278
#define NOTEQUAL 279
#define NOT 280
#define LESS 281
#define GREATER 282
#define LESSEQUAL 283
#define GREATEREQUAL 284
#define EXPO 285
#define COMMA 286
#define ADD 287
#define AND 288
#define OR 289
#define IF 290
#define THEN 291
#define ELSE 292
#define WHILE 293
#define stringexpr 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 32 "myC.yacc" /* yacc.c:1909  */

  float number;
  char * var_name;
  exp_node *exp_node_ptr;
  stmt_node *stmt_node_ptr;

#line 139 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
