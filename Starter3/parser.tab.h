/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FLOAT_T = 258,
     INT_T = 259,
     BOOL_T = 260,
     CONST = 261,
     FUNC = 262,
     IF = 263,
     ELSE = 264,
     AND = 265,
     OR = 266,
     NEQ = 267,
     EQ = 268,
     LEQ = 269,
     GEQ = 270,
     VEC_T = 271,
     BVEC_T = 272,
     IVEC_T = 273,
     FLOAT_C = 274,
     INT_C = 275,
     FALSE_C = 276,
     TRUE_C = 277,
     ID = 278,
     UMINUS = 279,
     WITHOUT_ELSE = 280,
     WITH_ELSE = 281
   };
#endif
/* Tokens.  */
#define FLOAT_T 258
#define INT_T 259
#define BOOL_T 260
#define CONST 261
#define FUNC 262
#define IF 263
#define ELSE 264
#define AND 265
#define OR 266
#define NEQ 267
#define EQ 268
#define LEQ 269
#define GEQ 270
#define VEC_T 271
#define BVEC_T 272
#define IVEC_T 273
#define FLOAT_C 274
#define INT_C 275
#define FALSE_C 276
#define TRUE_C 277
#define ID 278
#define UMINUS 279
#define WITHOUT_ELSE 280
#define WITH_ELSE 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 62 "parser.y"

  int as_int;
  int as_vec;
  float as_float;
  char *as_str;
  int as_func;
  node *as_ast;



/* Line 2068 of yacc.c  */
#line 113 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


