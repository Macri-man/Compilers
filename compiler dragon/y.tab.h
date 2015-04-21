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
     CHAR = 288,
     STRING = 289,
     BOOLEAN = 290,
     FUNCTION = 291,
     PROCEDURE = 292,
     BBEGIN = 293,
     END = 294,
     IF = 295,
     THEN = 296,
     ELSE = 297,
     WHILE = 298,
     DO = 299,
     FOR = 300,
     TO = 301,
     EMTPY = 302,
     CONDITIONAL = 303,
     TYPE = 304,
     LIST = 305,
     ARRAY_ACCESS = 306,
     STATEMENT = 307,
     FUNCTION_CALL = 308,
     PROCEDURE_CALL = 309,
     WHILE_DO = 310,
     DECL = 311,
     SUBDECL = 312,
     SUBPROGDECL = 313,
     LOCAL = 314,
     PARAMETER = 315,
     IDLIST = 316,
     EXPR = 317,
     EXPRLIST = 318,
     PARALIST = 319,
     ARGLIST = 320,
     DECLIST = 321,
     STATLIST = 322,
     PROCSTAT = 323,
     COMPSTAT = 324
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
#define CHAR 288
#define STRING 289
#define BOOLEAN 290
#define FUNCTION 291
#define PROCEDURE 292
#define BBEGIN 293
#define END 294
#define IF 295
#define THEN 296
#define ELSE 297
#define WHILE 298
#define DO 299
#define FOR 300
#define TO 301
#define EMTPY 302
#define CONDITIONAL 303
#define TYPE 304
#define LIST 305
#define ARRAY_ACCESS 306
#define STATEMENT 307
#define FUNCTION_CALL 308
#define PROCEDURE_CALL 309
#define WHILE_DO 310
#define DECL 311
#define SUBDECL 312
#define SUBPROGDECL 313
#define LOCAL 314
#define PARAMETER 315
#define IDLIST 316
#define EXPR 317
#define EXPRLIST 318
#define PARALIST 319
#define ARGLIST 320
#define DECLIST 321
#define STATLIST 322
#define PROCSTAT 323
#define COMPSTAT 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "dragon.y"
{
	/* scanner */
	int ival;
	float rval;
	char *sval;
	int opval;
	char cval;

	/* semantic + code gen */
	tree_t *tval;
	list_t *lval;

	int type;
}
/* Line 1529 of yacc.c.  */
#line 202 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

