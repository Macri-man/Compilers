/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "dragon.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
	#include "node.h"
	#include "scope.h"
	#include "list.h"
	#include "tree.h"
	#include "semantic.h"
	#include "y.tab.h"

	extern void yyerror(char* message);
	extern int yylex(void);
	extern int yyparse(void);

	extern scope_t *top_scope;
	extern node_t *temp;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 268 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 281 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,    71,     2,    78,    74,    79,    73,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    75,    72,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    16,    18,    22,    29,    30,    32,
      41,    43,    45,    47,    49,    51,    55,    56,    61,    62,
      70,    71,    77,    81,    82,    86,    92,    96,    98,    99,
     101,   105,   107,   109,   113,   115,   117,   124,   129,   138,
     143,   150,   152,   157,   159,   164,   166,   170,   172,   176,
     178,   181,   185,   187,   191,   193,   198,   203,   205,   207,
     211,   214,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      81,     0,    -1,    -1,    82,    26,     6,    70,    83,    71,
      72,    84,    87,    94,    73,    -1,     6,    -1,    83,    74,
       6,    -1,    84,    27,    83,    75,    85,    72,    -1,    -1,
      86,    -1,    28,    76,     4,    30,     4,    77,    29,    86,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,
      -1,    87,    88,    72,    -1,    -1,    89,    84,    87,    94,
      -1,    -1,    36,     6,    90,    92,    75,    86,    72,    -1,
      -1,    37,     6,    91,    92,    72,    -1,    70,    93,    71,
      -1,    -1,    83,    75,    85,    -1,    93,    72,    83,    75,
      85,    -1,    38,    95,    39,    -1,    96,    -1,    -1,    97,
      -1,    96,    72,    97,    -1,    98,    -1,    99,    -1,   100,
       8,   103,    -1,   101,    -1,    94,    -1,    40,   103,    41,
      97,    42,    97,    -1,    43,   103,    44,    97,    -1,    45,
       6,     8,   103,    46,   103,    44,    98,    -1,    40,   103,
      41,    97,    -1,    40,   103,    41,    98,    42,    99,    -1,
       6,    -1,     6,    76,   103,    77,    -1,     6,    -1,     6,
      70,   102,    71,    -1,   103,    -1,   102,    74,   103,    -1,
     104,    -1,   104,     9,   104,    -1,   105,    -1,   107,   105,
      -1,   104,    16,   105,    -1,   106,    -1,   105,    20,   106,
      -1,     6,    -1,     6,    70,   102,    71,    -1,     6,    76,
     102,    77,    -1,     4,    -1,     5,    -1,    70,   103,    71,
      -1,     7,   106,    -1,    78,    -1,    79,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    96,   111,   118,   128,   139,   143,   145,
     153,   154,   155,   156,   157,   161,   164,   168,   177,   176,
     191,   190,   207,   210,   214,   223,   235,   240,   243,   247,
     250,   256,   258,   263,   269,   271,   273,   279,   285,   296,
     302,   312,   314,   322,   328,   337,   339,   344,   346,   351,
     353,   355,   360,   362,   367,   374,   384,   394,   396,   398,
     400,   404,   405
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "INUM", "RNUM", "ID", "NOT",
  "ASSIGNOP", "RELOP", "LT", "LE", "GT", "GE", "EQ", "NEQ", "ADDOP", "OR",
  "PLUS", "MINUS", "MULOP", "AND", "STAR", "SLASH", "DIV", "MOD",
  "PROGRAM", "VAR", "ARRAY", "OF", "DOTDOT", "INTEGER", "REAL", "CHAR",
  "STRING", "BOOLEAN", "FUNCTION", "PROCEDURE", "BBEGIN", "END", "IF",
  "THEN", "ELSE", "WHILE", "DO", "FOR", "TO", "EMTPY", "CONDITIONAL",
  "TYPE", "LIST", "ARRAY_ACCESS", "STATEMENT", "FUNCTION_CALL",
  "PROCEDURE_CALL", "WHILE_DO", "DECL", "SUBDECL", "SUBPROGDECL", "LOCAL",
  "PARAMETER", "IDLIST", "EXPR", "EXPRLIST", "PARALIST", "ARGLIST",
  "DECLIST", "STATLIST", "PROCSTAT", "COMPSTAT", "'('", "')'", "';'",
  "'.'", "','", "':'", "'['", "']'", "'+'", "'-'", "$accept", "program",
  "@1", "identifier_list", "declarations", "type", "standard_type",
  "subprogram_declarations", "subprogram_declaration", "subprogram_head",
  "@2", "@3", "arguments", "parameter_list", "compound_statement",
  "optional_statements", "statement_list", "statement", "conditions",
  "ifelse", "variable", "procedure_statement", "expression_list",
  "expression", "simple_expression", "term", "factor", "sign", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      40,    41,    59,    46,    44,    58,    91,    93,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    82,    81,    83,    83,    84,    84,    85,    85,
      86,    86,    86,    86,    86,    87,    87,    88,    90,    89,
      91,    89,    92,    92,    93,    93,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    11,     1,     3,     6,     0,     1,     8,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     7,
       0,     5,     3,     0,     3,     5,     3,     1,     0,     1,
       3,     1,     1,     3,     1,     1,     6,     4,     8,     4,
       6,     1,     4,     1,     4,     1,     3,     1,     3,     1,
       2,     3,     1,     3,     1,     4,     4,     1,     1,     3,
       2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     0,     0,
       0,     7,     5,    16,     0,     0,     0,     0,     0,    28,
       0,     7,     0,     0,    18,    20,    43,     0,     0,     0,
      35,     0,    27,    29,    31,    32,     0,    34,    15,    16,
       3,     0,    10,    11,    12,    13,    14,     0,     8,    23,
      23,     0,     0,    57,    58,    54,     0,     0,    61,    62,
       0,    47,    49,    52,     0,     0,     0,    26,     0,     0,
       0,     0,     6,     0,     0,     0,     0,    45,     0,     0,
       0,    60,     0,     0,     0,     0,     0,    50,     0,     0,
      30,    33,    17,     0,     0,     0,     0,    21,    44,     0,
      42,     0,     0,    59,    39,    31,    48,    51,    53,    37,
       0,     0,     0,    22,     0,     0,    46,    55,    56,     0,
       0,     0,     0,    24,     0,    19,    36,     0,    40,     0,
       0,     0,     0,     0,     0,    25,     0,     0,    38,     9,
      39,     0,     0,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    13,    47,    48,    15,    20,    21,
      49,    50,    74,    95,    30,    31,    32,    33,    34,    35,
      36,    37,    76,    77,    61,    62,    63,    64
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int8 yypact[] =
{
     -94,    24,    15,   -94,    25,   -23,    46,   -94,   -34,     8,
      65,   -94,   -94,    60,    46,    52,    -8,    87,    93,     5,
      29,   -94,    30,     1,   -94,   -94,     0,    -1,    -1,    98,
     -94,    66,    34,   -94,   -94,   -94,    99,   -94,   -94,    60,
     -94,    32,   -94,   -94,   -94,   -94,   -94,    37,   -94,    41,
      41,    -1,    -1,   -94,   -94,   -50,     9,    -1,   -94,   -94,
      71,    12,    94,   -94,     9,    69,   107,   -94,     5,    -1,
      52,   112,   -94,    46,    42,    47,   -17,   -94,    43,    -1,
      -1,   -94,    50,     5,    -1,     9,     9,    94,     5,    -1,
     -94,   -94,   -94,    88,    17,     2,    51,   -94,   -94,    -1,
     -94,   -15,    -9,   -94,    80,    81,   108,    94,   -94,   -94,
      79,   122,     1,   -94,    46,    55,   -94,   -94,   -94,     5,
      89,    -1,    53,   -94,    21,   -94,   -94,    -1,   -94,    84,
     102,     1,    91,     6,    51,   -94,     5,    -1,   -94,   -94,
     -94,    92,     5,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   -94,   -12,   113,   -93,   -79,    96,   -94,   -94,
     -94,   -94,    86,   -94,    -6,   -94,   -94,   -61,   -73,    19,
     -94,   -94,    18,   -27,    54,   -46,   -33,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const yytype_int16 yytable[] =
{
      60,    65,    16,    53,    54,    55,    56,    90,   -41,    22,
     105,    26,    26,    53,    54,    55,    56,   115,    87,   123,
      79,    84,   104,    81,     3,    78,    80,   109,    85,    41,
      82,     5,    42,    43,    44,    45,    46,     9,   135,   107,
      10,     4,    91,    19,    19,    27,   137,     6,    28,    28,
      29,    29,     7,   108,    98,   139,   117,    99,   126,    99,
     138,    94,   110,   105,    92,    99,    10,    23,   118,    57,
      51,    12,   116,   113,   114,   140,    52,    58,    59,    57,
      11,   143,    42,    43,    44,    45,    46,    14,    17,    18,
      19,    10,   112,    24,   129,    10,   131,   101,   102,    25,
     132,    38,   124,    40,    66,    67,    68,    69,    71,    72,
     141,    73,    83,    88,    86,    89,    93,    96,   111,    97,
     100,   103,   119,   120,    85,   121,   122,   125,   133,   127,
     130,   134,   136,   142,    39,    70,    75,     0,   106,   128
};

static const yytype_int16 yycheck[] =
{
      27,    28,    14,     4,     5,     6,     7,    68,     8,    15,
      83,     6,     6,     4,     5,     6,     7,    96,    64,   112,
      70,     9,    83,    56,     0,    52,    76,    88,    16,    28,
      57,     6,    31,    32,    33,    34,    35,    71,   131,    85,
      74,    26,    69,    38,    38,    40,    40,    70,    43,    43,
      45,    45,     6,    86,    71,   134,    71,    74,   119,    74,
     133,    73,    89,   136,    70,    74,    74,    75,    77,    70,
      70,     6,    99,    71,    72,   136,    76,    78,    79,    70,
      72,   142,    31,    32,    33,    34,    35,    27,    36,    37,
      38,    74,    75,     6,   121,    74,    75,    79,    80,     6,
     127,    72,   114,    73,     6,    39,    72,     8,    76,    72,
     137,    70,    41,    44,    20,     8,     4,    75,    30,    72,
      77,    71,    42,    42,    16,    46,     4,    72,    44,    40,
      77,    29,    41,    41,    21,    39,    50,    -1,    84,   120
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,    82,     0,    26,     6,    70,     6,    83,    71,
      74,    72,     6,    84,    27,    87,    83,    36,    37,    38,
      88,    89,    94,    75,     6,     6,     6,    40,    43,    45,
      94,    95,    96,    97,    98,    99,   100,   101,    72,    84,
      73,    28,    31,    32,    33,    34,    35,    85,    86,    90,
      91,    70,    76,     4,     5,     6,     7,    70,    78,    79,
     103,   104,   105,   106,   107,   103,     6,    39,    72,     8,
      87,    76,    72,    70,    92,    92,   102,   103,   103,    70,
      76,   106,   103,    41,     9,    16,    20,   105,    44,     8,
      97,   103,    94,     4,    83,    93,    75,    72,    71,    74,
      77,   102,   102,    71,    97,    98,   104,   105,   106,    97,
     103,    30,    75,    71,    72,    86,   103,    71,    77,    42,
      42,    46,     4,    85,    83,    72,    97,    40,    99,   103,
      77,    75,   103,    44,    29,    85,    41,    40,    98,    86,
      97,   103,    41,    97
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 96 "dragon.y"
    { top_scope = scope_push(top_scope,"PROGRAM"); }
    break;

  case 3:
#line 102 "dragon.y"
    {
		(yyval.tval) = make_tree(PROGRAM,make_id(temp=scope_insert(top_scope,(yyvsp[(3) - (11)].sval))),make_tree(LIST,make_treeFromList(IDLIST,(yyvsp[(5) - (11)].lval)),make_tree(LIST,make_treeFromList(DECLIST,(yyvsp[(8) - (11)].lval)),make_tree(SUBPROGDECL,(yyvsp[(9) - (11)].tval),(yyvsp[(10) - (11)].tval)))));
		//print_tree(make_treeFromList(DECLIST,$8),0);
		top_scope = scope_pop(top_scope);
		print_tree((yyval.tval),0);
	}
    break;

  case 4:
#line 112 "dragon.y"
    {
			//insert ID into scope
			(yyval.lval) = make_list_node(temp=scope_insert(top_scope,(yyvsp[(1) - (1)].sval)),(yyvsp[(1) - (1)].sval),IDLIST);
			//$$ = make_id(scope_insert(top_scope,$1));
			//temp->type=ID;
		}
    break;

  case 5:
#line 119 "dragon.y"
    {
			//insert ID into scope
			(yyval.lval) = list_append_node((yyvsp[(1) - (3)].lval),temp=scope_insert(top_scope,(yyvsp[(3) - (3)].sval)));
			//$$ = make_tree(IDLIST,$1,scope_insert(top_scope,$1));
			//temp->type=ID;
		}
    break;

  case 6:
#line 129 "dragon.y"
    {
			//set the types of the id list and set the mark to local
			//set_names($3,$5,LOCAL);
			//$$ = make_decl(DECLIST,make_idlist(IDLIST,$3),$5,LOCAL);
			assign_type((yyvsp[(3) - (6)].lval),(yyvsp[(5) - (6)].tval));
			assign_mark((yyvsp[(3) - (6)].lval),LOCAL);
			//make list of identifier list and append id list to the declarations list
			(yyval.lval) = list_append(DECLIST,(yyvsp[(1) - (6)].lval),(yyvsp[(3) - (6)].lval));
		}
    break;

  case 7:
#line 139 "dragon.y"
    { (yyval.lval) = NULL; }
    break;

  case 8:
#line 144 "dragon.y"
    { (yyval.tval) = make_tree((yyvsp[(1) - (1)].type),NULL,NULL); }
    break;

  case 9:
#line 146 "dragon.y"
    { 
			//make sure the ID knows the range of the array
			(yyval.tval) = make_tree(ARRAY,make_tree((yyvsp[(8) - (8)].type),NULL,NULL),make_tree((yyvsp[(8) - (8)].type),make_inum(INUM),make_inum(INUM))); 
		}
    break;

  case 10:
#line 153 "dragon.y"
    { (yyval.type) = INTEGER; }
    break;

  case 11:
#line 154 "dragon.y"
    { (yyval.type) = REAL; }
    break;

  case 12:
#line 155 "dragon.y"
    { (yyval.type) = CHAR; }
    break;

  case 13:
#line 156 "dragon.y"
    { (yyval.type) = STRING; }
    break;

  case 14:
#line 157 "dragon.y"
    { (yyval.type) = BOOLEAN; }
    break;

  case 15:
#line 162 "dragon.y"
    { (yyval.tval) = make_tree(SUBDECL,(yyvsp[(1) - (3)].tval),(yyvsp[(2) - (3)].tval)); }
    break;

  case 16:
#line 164 "dragon.y"
    { (yyval.tval) = NULL; }
    break;

  case 17:
#line 169 "dragon.y"
    {	
			top_scope = scope_pop(top_scope); 
			(yyval.tval) = make_tree(SUBPROGDECL,(yyvsp[(1) - (4)].tval),make_tree(SUBPROGDECL,(yyvsp[(2) - (4)].lval),(yyvsp[(3) - (4)].tval)));
		}
    break;

  case 18:
#line 177 "dragon.y"
    {	
			//insert ID into scope
			assert((top_scope = scope_push(top_scope,"FUNCTION"))!=NULL);
			temp=scope_insert(top_scope,(yyvsp[(2) - (2)].sval)); 
			temp->mark=FUNCTION;

		}
    break;

  case 19:
#line 185 "dragon.y"
    {
			temp->type=(yyvsp[(6) - (7)].type);
			temp->list=(yyvsp[(4) - (7)].lval);
			(yyval.tval) = make_tree(FUNCTION,make_id(temp),make_treeFromList(ARGLIST,(yyvsp[(4) - (7)].lval)));
		}
    break;

  case 20:
#line 191 "dragon.y"
    {	
			//insert ID into scope
			assert((top_scope = scope_push(top_scope,"PROCEDURE"))!=NULL);
			temp=scope_insert(top_scope,(yyvsp[(2) - (2)].sval)); 
			temp->type=PROCEDURE;
			temp->mark=PROCEDURE;

		}
    break;

  case 21:
#line 200 "dragon.y"
    { 
			temp->list=(yyvsp[(4) - (5)].lval);
			(yyval.tval) = make_tree(PROCEDURE,make_id(temp),make_treeFromList(ARGLIST,(yyvsp[(4) - (5)].lval))); 
		}
    break;

  case 22:
#line 208 "dragon.y"
    { (yyval.lval) = (yyvsp[(2) - (3)].lval); }
    break;

  case 23:
#line 210 "dragon.y"
    { (yyval.lval) = NULL; }
    break;

  case 24:
#line 215 "dragon.y"
    { 
			//set the types of the id list and mark then as paramters
			//set_names($1,$3,PARAMETER);
			assign_type((yyvsp[(1) - (3)].lval),(yyvsp[(3) - (3)].tval));
			assign_mark((yyvsp[(1) - (3)].lval),PARAMETER);
			//make list of parameters
			(yyval.lval) = make_list(PARALIST,(yyvsp[(1) - (3)].lval)); 
		}
    break;

  case 25:
#line 224 "dragon.y"
    { 	
			//set the types of the id list and mark then as paramters
			//set_names($3,$5,PARAMETER);
			assign_type((yyvsp[(3) - (5)].lval),(yyvsp[(5) - (5)].tval));
			assign_mark((yyvsp[(3) - (5)].lval),PARAMETER);
			//make list of identifier list and append id list to the parameter list
			(yyval.lval) = list_append(PARALIST,(yyvsp[(1) - (5)].lval),(yyvsp[(3) - (5)].lval)); 
		}
    break;

  case 26:
#line 236 "dragon.y"
    { (yyval.tval) = (yyvsp[(2) - (3)].tval); }
    break;

  case 27:
#line 241 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 28:
#line 243 "dragon.y"
    { (yyval.tval) = NULL; }
    break;

  case 29:
#line 249 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 30:
#line 252 "dragon.y"
    { (yyval.tval) = make_tree(STATLIST,(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); }
    break;

  case 31:
#line 257 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 32:
#line 259 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 33:
#line 264 "dragon.y"
    { 
			//check type of varibale == type of expression
			if(type((yyvsp[(1) - (3)].tval))!=type((yyvsp[(3) - (3)].tval))){ fprintf(stderr,"Type Mismatch: \n"); }
			(yyval.tval) = make_tree(ASSIGNOP,(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); 
		}
    break;

  case 34:
#line 270 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 35:
#line 272 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 36:
#line 274 "dragon.y"
    { 
			//check type of expression for boolean
			if(type((yyvsp[(2) - (6)].tval))!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); } 
			(yyval.tval) = make_tree(IF,(yyvsp[(2) - (6)].tval),make_tree(THEN,(yyvsp[(4) - (6)].tval),(yyvsp[(6) - (6)].tval))); 
		}
    break;

  case 37:
#line 280 "dragon.y"
    { 
			//check if expression is type boolean
			if(type((yyvsp[(2) - (4)].tval))!=BOOLEAN) { fprintf(stderr,"Boolean Error: \n");  }
			(yyval.tval) = make_tree(WHILE_DO,(yyvsp[(2) - (4)].tval),(yyvsp[(4) - (4)].tval)); 
		}
    break;

  case 38:
#line 286 "dragon.y"
    {	
			//check if type of temp is type of expression before TO and type temp is type of expression after TO
			temp=scope_search(top_scope,(yyvsp[(2) - (8)].sval));
			if(type(make_id(temp))!=type((yyvsp[(4) - (8)].tval))){ fprintf(stderr,"Boolean Error: \n"); } 
			if(type(make_id(temp))!=type((yyvsp[(6) - (8)].tval))){ fprintf(stderr,"Boolean Error: \n"); }
			(yyval.tval) = make_tree(FOR,make_id(temp),make_tree(DO,make_tree(TO,(yyvsp[(4) - (8)].tval),(yyvsp[(6) - (8)].tval)),(yyvsp[(8) - (8)].tval)));
		}
    break;

  case 39:
#line 297 "dragon.y"
    {
			//check type of expresion is boolean
			if(type((yyvsp[(2) - (4)].tval))!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree((yyvsp[(2) - (4)].tval),0); }
			(yyval.tval) = make_tree(IF,(yyvsp[(2) - (4)].tval),(yyvsp[(4) - (4)].tval));
		}
    break;

  case 40:
#line 303 "dragon.y"
    {
			//check type of expression is boolean
			if(type((yyvsp[(2) - (6)].tval))!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree((yyvsp[(2) - (6)].tval),0); } 
			(yyval.tval) = make_tree(IF, (yyvsp[(2) - (6)].tval), make_tree(THEN,(yyvsp[(2) - (6)].tval),(yyvsp[(6) - (6)].tval)));
		}
    break;

  case 41:
#line 313 "dragon.y"
    { (yyval.tval) = make_id(scope_search(top_scope,(yyvsp[(1) - (1)].sval))); }
    break;

  case 42:
#line 315 "dragon.y"
    { 
			(yyval.tval) = make_tree(ARRAY_ACCESS,make_id(scope_search(top_scope,(yyvsp[(1) - (4)].sval))),(yyvsp[(3) - (4)].tval));
			check_array((yyval.tval),ARRAY_ACCESS); 
		}
    break;

  case 43:
#line 323 "dragon.y"
    { 
	 		//search ID and check if valid procedure call
	 		(yyval.tval) = make_tree(PROCEDURE,make_id(scope_search(top_scope,(yyvsp[(1) - (1)].sval))),NULL); 
	 		check_procedure((yyval.tval),PROCEDURE);
	 	}
    break;

  case 44:
#line 329 "dragon.y"
    {
			//search ID and check if valid procedure call
			(yyval.tval) = make_tree(PROCEDURE,make_id(scope_search(top_scope,(yyvsp[(1) - (4)].sval))),(yyvsp[(3) - (4)].tval)); 
			check_procedure((yyval.tval),PROCEDURE);
		}
    break;

  case 45:
#line 338 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 46:
#line 340 "dragon.y"
    { (yyval.tval) = make_tree(EXPRLIST,(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); }
    break;

  case 47:
#line 345 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 48:
#line 347 "dragon.y"
    { (yyval.tval)=make_op(RELOP,(yyvsp[(2) - (3)].opval),(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); }
    break;

  case 49:
#line 352 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 50:
#line 354 "dragon.y"
    { (yyval.tval) = make_op(ADDOP,(yyvsp[(1) - (2)].cval),(yyvsp[(2) - (2)].tval),NULL); }
    break;

  case 51:
#line 356 "dragon.y"
    { (yyval.tval) = make_op(ADDOP,(yyvsp[(2) - (3)].opval),(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); }
    break;

  case 52:
#line 361 "dragon.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); }
    break;

  case 53:
#line 363 "dragon.y"
    { (yyval.tval) = make_op(MULOP,(yyvsp[(2) - (3)].opval),(yyvsp[(1) - (3)].tval),(yyvsp[(3) - (3)].tval)); }
    break;

  case 54:
#line 367 "dragon.y"
    { 	
			if((temp=scope_search_all(top_scope,(yyvsp[(1) - (1)].sval))) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",(yyvsp[(1) - (1)].sval));
				exit(1);
			}
			(yyval.tval) = make_id(temp); 
		}
    break;

  case 55:
#line 375 "dragon.y"
    {
			//check if valid function call
			if((temp=scope_search_all(top_scope,(yyvsp[(1) - (4)].sval))) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",(yyvsp[(1) - (4)].sval));
				exit(1);
			}
			(yyval.tval) = make_tree(FUNCTION_CALL,make_id(temp),(yyvsp[(3) - (4)].tval));
			check_function((yyval.tval),FUNCTION); 
		}
    break;

  case 56:
#line 385 "dragon.y"
    { 
			//check if valid array access
			if((temp=scope_search_all(top_scope,(yyvsp[(1) - (4)].sval))) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",(yyvsp[(1) - (4)].sval));
				exit(1);
			}
			(yyval.tval) = make_tree(ARRAY_ACCESS,make_id(temp),(yyvsp[(3) - (4)].tval)); 
			check_array((yyval.tval),ARRAY_ACCESS);
		}
    break;

  case 57:
#line 395 "dragon.y"
    { (yyval.tval) = make_inum((yyvsp[(1) - (1)].ival)); }
    break;

  case 58:
#line 397 "dragon.y"
    { (yyval.tval) = make_rnum((yyvsp[(1) - (1)].rval)); }
    break;

  case 59:
#line 399 "dragon.y"
    {(yyval.tval) = (yyvsp[(2) - (3)].tval); }
    break;

  case 60:
#line 401 "dragon.y"
    { (yyval.tval) = make_tree(NOT,(yyvsp[(2) - (2)].tval),NULL); }
    break;

  case 61:
#line 404 "dragon.y"
    { (yyval.cval) = '+'; }
    break;

  case 62:
#line 405 "dragon.y"
    { (yyval.cval) = '-'; }
    break;


/* Line 1267 of yacc.c.  */
#line 2033 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 408 "dragon.y"



scope_t *top_scope;
node_t *temp;
int main(){
	top_scope=NULL;
	temp=NULL;
	yyparse();
}



