/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     NUMBER = 258,
     INUM = 259,
     RNUM = 260,
     ID = 261,
     NOT = 262,
     ASSIGNOP = 263,
     RELOP = 264,
     LT = 265,
     LE = 266,
     GT = 267,
     GE = 268,
     EQ = 269,
     NEQ = 270,
     ADDOP = 271,
     OR = 272,
     PLUS = 273,
     MINUS = 274,
     MULOP = 275,
     AND = 276,
     STAR = 277,
     SLASH = 278,
     DIV = 279,
     MOD = 280,
     PROGRAM = 281,
     VAR = 282,
     ARRAY = 283,
     OF = 284,
     DOTDOT = 285,
     INTEGER = 286,
     REAL = 287,
     FUNCTION = 288,
     PROCEDURE = 289,
     BBEGIN = 290,
     END = 291,
     IF = 292,
     THEN = 293,
     ELSE = 294,
     WHILE = 295,
     DO = 296,
     LIST = 297,
     ARRAY_ACCESS = 298,
     FUNCTION_CALL = 299
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define INUM 259
#define RNUM 260
#define ID 261
#define NOT 262
#define ASSIGNOP 263
#define RELOP 264
#define LT 265
#define LE 266
#define GT 267
#define GE 268
#define EQ 269
#define NEQ 270
#define ADDOP 271
#define OR 272
#define PLUS 273
#define MINUS 274
#define MULOP 275
#define AND 276
#define STAR 277
#define SLASH 278
#define DIV 279
#define MOD 280
#define PROGRAM 281
#define VAR 282
#define ARRAY 283
#define OF 284
#define DOTDOT 285
#define INTEGER 286
#define REAL 287
#define FUNCTION 288
#define PROCEDURE 289
#define BBEGIN 290
#define END 291
#define IF 292
#define THEN 293
#define ELSE 294
#define WHILE 295
#define DO 296
#define LIST 297
#define ARRAY_ACCESS 298
#define FUNCTION_CALL 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "dragon.y"
{
	/* scanner */
	int ival;
	float rval;
	char *sval;
	int opval;

	/* semantic + code gen */
	tree_t *tval;
}
/* Line 1529 of yacc.c.  */
#line 148 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

