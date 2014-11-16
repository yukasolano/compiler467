/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"

/***********************************************************************
 * --YOUR GROUP INFO SHOULD GO HERE--
 * 
 *   Interface to the parser module for CSC467 course project.
 * 
 *   Phase 2: Implement context free grammar for source language, and
 *            parse tracing functionality.
 *   Phase 3: Construct the AST for the source language program.
 ***********************************************************************/

/***********************************************************************
 *  C Definitions and external declarations for this module.
 *
 *  Phase 3: Include ast.h if needed, and declarations for other global or
 *           external vars, functions etc. as needed.
 ***********************************************************************/

#include <string.h>

#include "common.h"
#include "ast.h"
#include "symbol.h"
#include "semantic.h"

#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n", x); }

void yyerror(char* s);    /* what to do in case of error            */
int yylex();              /* procedure for calling lexical analyzer */
extern int yyline;        /* variable holding current line number   */

enum {
  DP3 = 0, 
  LIT = 1, 
  RSQ = 2
};


/* Line 268 of yacc.c  */
#line 57 "parser.y"

#define YYDEBUG 1


/* Line 268 of yacc.c  */
#line 117 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

/* Line 293 of yacc.c  */
#line 62 "parser.y"

  int as_int;
  int as_vec;
  float as_float;
  char *as_str;
  int as_func;
  node *as_ast;



/* Line 293 of yacc.c  */
#line 216 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 228 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   208

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNRULES -- Number of states.  */
#define YYNSTATES  96

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
      33,    41,    28,    26,    43,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      24,    40,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    42,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    32,
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    10,    13,    14,    17,    18,    22,
      28,    35,    40,    48,    54,    56,    58,    60,    62,    64,
      66,    68,    70,    75,    80,    83,    86,    90,    94,    98,
     102,   106,   110,   114,   118,   122,   126,   130,   134,   138,
     140,   142,   144,   146,   150,   151,   154,   156,   161,   165,
     167,   169
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    37,    47,    48,    38,    -1,
      47,    49,    -1,    -1,    48,    50,    -1,    -1,    51,    23,
      39,    -1,    51,    23,    40,    52,    39,    -1,     6,    51,
      23,    40,    52,    39,    -1,    54,    40,    52,    39,    -1,
       8,    33,    52,    41,    50,     9,    50,    -1,     8,    33,
      52,    41,    50,    -1,    46,    -1,    39,    -1,     4,    -1,
      18,    -1,     5,    -1,    17,    -1,     3,    -1,    16,    -1,
      51,    33,    56,    41,    -1,     7,    33,    56,    41,    -1,
      27,    52,    -1,    31,    52,    -1,    52,    10,    52,    -1,
      52,    11,    52,    -1,    52,    13,    52,    -1,    52,    12,
      52,    -1,    52,    24,    52,    -1,    52,    14,    52,    -1,
      52,    25,    52,    -1,    52,    15,    52,    -1,    52,    26,
      52,    -1,    52,    27,    52,    -1,    52,    28,    52,    -1,
      52,    29,    52,    -1,    52,    30,    52,    -1,    22,    -1,
      21,    -1,    20,    -1,    19,    -1,    33,    52,    41,    -1,
      -1,    54,    53,    -1,    23,    -1,    23,    34,    20,    42,
      -1,    55,    43,    52,    -1,    52,    -1,    55,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   140,   145,   148,   152,   155,   159,   161,
     163,   168,   170,   172,   174,   176,   181,   183,   185,   187,
     189,   191,   198,   200,   204,   206,   210,   212,   214,   216,
     218,   220,   222,   224,   226,   228,   230,   232,   234,   238,
     240,   242,   244,   248,   250,   250,   255,   257,   262,   264,
     269,   272
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FLOAT_T", "INT_T", "BOOL_T", "CONST",
  "FUNC", "IF", "ELSE", "AND", "OR", "NEQ", "EQ", "LEQ", "GEQ", "VEC_T",
  "BVEC_T", "IVEC_T", "FLOAT_C", "INT_C", "FALSE_C", "TRUE_C", "ID", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'^'", "'!'", "UMINUS", "'('", "'['",
  "WITHOUT_ELSE", "WITH_ELSE", "'{'", "'}'", "';'", "'='", "')'", "']'",
  "','", "$accept", "program", "scope", "declarations", "statements",
  "declaration", "statement", "type", "expression", "$@1", "variable",
  "arguments", "arguments_opt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    60,    62,    43,    45,    42,    47,
      94,    33,   279,    40,    91,   280,   281,   123,   125,    59,
      61,    41,    93,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    48,    49,    49,
      49,    50,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    52,    54,    54,    55,    55,
      56,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     2,     0,     2,     0,     3,     5,
       6,     4,     7,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     3,     0,     2,     1,     4,     3,     1,
       1,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     2,     7,     1,    20,    16,    18,     0,
      21,    19,    17,     0,     4,     0,     0,     0,    46,     3,
      15,    14,     6,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     0,    42,    41,    40,    39,     0,     0,     0,
       0,     0,    44,     0,     0,     0,     0,    51,    24,    25,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,    47,    11,     9,
      10,    49,    50,     0,    43,     0,    26,    27,    29,    28,
      31,    33,    30,    32,    34,    35,    36,    37,    38,    13,
       0,    23,    22,     0,    48,    12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    21,     4,    13,    14,    22,    40,    71,    66,
      42,    72,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -48
static const yytype_int16 yypact[] =
{
     -35,   -48,     4,   -48,   101,   -48,   -48,   -48,   -48,   190,
     -48,   -48,   -48,    45,   -48,    -8,    -6,    -7,    35,   -48,
     -48,   -48,   -48,    38,    27,    41,    93,    50,    93,   -48,
      93,    93,    52,   -48,   -48,   -48,   -48,    93,    93,    93,
      61,    30,   -48,    57,   117,   124,   147,    93,   -48,   -48,
      62,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    56,   -48,   -48,   -48,   -48,
     -48,   154,    58,    67,   -48,    80,    -5,   175,    21,    21,
      21,    21,    21,    21,    33,    33,    72,    72,    72,   113,
      93,   -48,   -48,    56,   154,   -48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,   123,   -48,   -48,   -48,   -47,     7,   -25,   -48,
     -13,   -48,    74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      23,    41,     1,    44,     5,    45,    46,    54,    55,    56,
      57,    15,    48,    49,    50,    24,    16,    25,    89,    58,
      59,    60,    61,    62,    63,    64,    26,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      52,    53,    54,    55,    56,    57,    95,    60,    61,    62,
      63,    64,    23,    17,    58,    59,    60,    61,    62,    63,
      64,    62,    63,    64,    17,    94,    29,    30,    18,    27,
      43,    65,    52,    53,    54,    55,    56,    57,    28,    18,
      23,    31,     1,    19,    20,    47,    58,    59,    60,    61,
      62,    63,    64,     1,    51,    20,     6,     7,     8,    67,
      32,    90,    64,    74,     6,     7,     8,     9,    91,    10,
      11,    12,    33,    34,    35,    36,    18,    10,    11,    12,
      37,    92,    93,     3,    38,    75,    39,    52,    53,    54,
      55,    56,    57,     0,    52,    53,    54,    55,    56,    57,
       0,    58,    59,    60,    61,    62,    63,    64,    58,    59,
      60,    61,    62,    63,    64,     0,    68,    52,    53,    54,
      55,    56,    57,    69,    52,    53,    54,    55,    56,    57,
       0,    58,    59,    60,    61,    62,    63,    64,    58,    59,
      60,    61,    62,    63,    64,    52,    70,    54,    55,    56,
      57,     0,     0,     6,     7,     8,     0,     0,     0,    58,
      59,    60,    61,    62,    63,    64,    10,    11,    12
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-48))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      13,    26,    37,    28,     0,    30,    31,    12,    13,    14,
      15,     4,    37,    38,    39,    23,     9,    23,    65,    24,
      25,    26,    27,    28,    29,    30,    33,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      10,    11,    12,    13,    14,    15,    93,    26,    27,    28,
      29,    30,    65,     8,    24,    25,    26,    27,    28,    29,
      30,    28,    29,    30,     8,    90,    39,    40,    23,    34,
      20,    41,    10,    11,    12,    13,    14,    15,    40,    23,
      93,    40,    37,    38,    39,    33,    24,    25,    26,    27,
      28,    29,    30,    37,    33,    39,     3,     4,     5,    42,
       7,    43,    30,    41,     3,     4,     5,     6,    41,    16,
      17,    18,    19,    20,    21,    22,    23,    16,    17,    18,
      27,    41,     9,     0,    31,    51,    33,    10,    11,    12,
      13,    14,    15,    -1,    10,    11,    12,    13,    14,    15,
      -1,    24,    25,    26,    27,    28,    29,    30,    24,    25,
      26,    27,    28,    29,    30,    -1,    39,    10,    11,    12,
      13,    14,    15,    39,    10,    11,    12,    13,    14,    15,
      -1,    24,    25,    26,    27,    28,    29,    30,    24,    25,
      26,    27,    28,    29,    30,    10,    39,    12,    13,    14,
      15,    -1,    -1,     3,     4,     5,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    16,    17,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    45,    46,    47,     0,     3,     4,     5,     6,
      16,    17,    18,    48,    49,    51,    51,     8,    23,    38,
      39,    46,    50,    54,    23,    23,    33,    34,    40,    39,
      40,    40,     7,    19,    20,    21,    22,    27,    31,    33,
      51,    52,    54,    20,    52,    52,    52,    33,    52,    52,
      52,    33,    10,    11,    12,    13,    14,    15,    24,    25,
      26,    27,    28,    29,    30,    41,    53,    42,    39,    39,
      39,    52,    55,    56,    41,    56,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    50,
      43,    41,    41,     9,    52,    50
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 136 "parser.y"
    { yTRACE("program -> scope\n"); ast = ast_allocate(NESTED_SCOPE_NODE,(yyvsp[(1) - (1)].as_ast));}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 141 "parser.y"
    { yTRACE("scope -> { declarations statements }\n"); (yyval.as_ast) = ast_allocate(SCOPE_NODE, (yyvsp[(2) - (4)].as_ast), (yyvsp[(3) - (4)].as_ast)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 146 "parser.y"
    { yTRACE("declarations -> declarations declaration\n"); (yyval.as_ast) = ast_allocate(DECLARATIONS_NODE, (yyvsp[(1) - (2)].as_ast), (yyvsp[(2) - (2)].as_ast)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 148 "parser.y"
    { yTRACE("declarations -> \n"); (yyval.as_ast) = NULL;}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 153 "parser.y"
    { yTRACE("statements -> statements statement\n"); (yyval.as_ast) = ast_allocate(STATEMENT_NODE, (yyvsp[(1) - (2)].as_ast), (yyvsp[(2) - (2)].as_ast)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 155 "parser.y"
    { yTRACE("statements -> \n"); (yyval.as_ast) = NULL;}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 160 "parser.y"
    { yTRACE("declaration -> type ID ;\n") ; (yyval.as_ast) = ast_allocate(DECLARATION_NODE, (yyvsp[(1) - (3)].as_ast), (yyvsp[(2) - (3)].as_str), NULL, 0);}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 162 "parser.y"
    { yTRACE("declaration -> type ID = expression ;\n"); (yyval.as_ast) = ast_allocate(DECLARATION_NODE, (yyvsp[(1) - (5)].as_ast), (yyvsp[(2) - (5)].as_str), (yyvsp[(4) - (5)].as_ast), 0); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 164 "parser.y"
    { yTRACE("declaration -> CONST type ID = expression ;\n"); (yyval.as_ast) = ast_allocate(DECLARATION_NODE, (yyvsp[(2) - (6)].as_ast), (yyvsp[(3) - (6)].as_str), (yyvsp[(5) - (6)].as_ast), 1); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 169 "parser.y"
    { yTRACE("statement -> variable = expression ;\n"); (yyval.as_ast) = ast_allocate(ASSIGNMENT_NODE, (yyvsp[(1) - (4)].as_ast), (yyvsp[(3) - (4)].as_ast)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 171 "parser.y"
    { yTRACE("statement -> IF ( expression ) statement ELSE statement \n"); (yyval.as_ast) = ast_allocate(IF_STATEMENT_NODE, (yyvsp[(3) - (7)].as_ast), (yyvsp[(5) - (7)].as_ast), (yyvsp[(7) - (7)].as_ast));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 173 "parser.y"
    { yTRACE("statement -> IF ( expression ) statement \n"); (yyval.as_ast) = ast_allocate(IF_STATEMENT_NODE, (yyvsp[(3) - (5)].as_ast), (yyvsp[(5) - (5)].as_ast), NULL); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 175 "parser.y"
    { yTRACE("statement -> scope \n"); (yyval.as_ast) = ast_allocate(INTERMEDIATE_NODE, (yyvsp[(1) - (1)].as_ast)); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 177 "parser.y"
    { yTRACE("statement -> ; \n"); (yyval.as_ast) = NULL; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 182 "parser.y"
    { yTRACE("type -> INT_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "int", NULL); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 184 "parser.y"
    { yTRACE("type -> IVEC_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "ivec", (yyvsp[(1) - (1)].as_vec)); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 186 "parser.y"
    { yTRACE("type -> BOOL_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "bool", NULL); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 188 "parser.y"
    { yTRACE("type -> BVEC_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "bvec", (yyvsp[(1) - (1)].as_vec)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 190 "parser.y"
    { yTRACE("type -> FLOAT_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "float", NULL); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 192 "parser.y"
    { yTRACE("type -> VEC_T \n"); (yyval.as_ast) = ast_allocate(TYPE_NODE, "vec", (yyvsp[(1) - (1)].as_vec)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 199 "parser.y"
    { yTRACE("expression -> type ( arguments_opt ) \n"); (yyval.as_ast) = ast_allocate(CONSTRUCTOR_NODE, (yyvsp[(1) - (4)].as_ast), (yyvsp[(3) - (4)].as_ast)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 201 "parser.y"
    { yTRACE("expression -> FUNC ( arguments_opt ) \n"); (yyval.as_ast) = ast_allocate(FUNCTION_NODE, (yyvsp[(1) - (4)].as_func), (yyvsp[(3) - (4)].as_ast));}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 205 "parser.y"
    { yTRACE("expression -> - expression \n"); (yyval.as_ast) = ast_allocate(UNARY_EXPRESSION_NODE, "-", (yyvsp[(2) - (2)].as_ast)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 207 "parser.y"
    { yTRACE("expression -> ! expression \n"); (yyval.as_ast) = ast_allocate(UNARY_EXPRESSION_NODE, "!", (yyvsp[(2) - (2)].as_ast)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 211 "parser.y"
    { yTRACE("expression -> expression AND expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "&&", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 213 "parser.y"
    { yTRACE("expression -> expression OR expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "||", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 215 "parser.y"
    { yTRACE("expression -> expression EQ expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "==", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 217 "parser.y"
    { yTRACE("expression -> expression NEQ expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "!=", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 219 "parser.y"
    { yTRACE("expression -> expression < expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "<", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 221 "parser.y"
    { yTRACE("expression -> expression LEQ expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "<=", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 223 "parser.y"
    { yTRACE("expression -> expression > expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, ">", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 225 "parser.y"
    { yTRACE("expression -> expression GEQ expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, ">=", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 227 "parser.y"
    { yTRACE("expression -> expression + expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "+", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    { yTRACE("expression -> expression - expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "-", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    { yTRACE("expression -> expression * expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "*", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 233 "parser.y"
    { yTRACE("expression -> expression / expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "/", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 235 "parser.y"
    { yTRACE("expression -> expression ^ expression \n"); (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, "^", (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 239 "parser.y"
    { yTRACE("expression -> TRUE_C \n"); (yyval.as_ast) = ast_allocate(BOOL_NODE, (yyvsp[(1) - (1)].as_int)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 241 "parser.y"
    { yTRACE("expression -> FALSE_C \n"); (yyval.as_ast) = ast_allocate(BOOL_NODE, (yyvsp[(1) - (1)].as_int)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 243 "parser.y"
    { yTRACE("expression -> INT_C \n"); (yyval.as_ast) = ast_allocate(INT_NODE, (yyvsp[(1) - (1)].as_int)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 245 "parser.y"
    { yTRACE("expression -> FLOAT_C \n"); (yyval.as_ast) = ast_allocate(FLOAT_NODE, (yyvsp[(1) - (1)].as_float));  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 249 "parser.y"
    { yTRACE("expression -> ( expression ) \n"); (yyval.as_ast) = ast_allocate(EXPRESSION_NODE, (yyvsp[(2) - (3)].as_ast));  }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 250 "parser.y"
    { }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 251 "parser.y"
    { yTRACE("expression -> variable \n"); (yyval.as_ast) = ast_allocate(VAR_NODE, (yyvsp[(1) - (2)].as_ast));  }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 256 "parser.y"
    { yTRACE("variable -> ID \n"); (yyval.as_ast) = ast_allocate(IDENT_NODE, (yyvsp[(1) - (1)].as_str), NULL);  }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 258 "parser.y"
    { yTRACE("variable -> ID [ INT_C ] \n"); (yyval.as_ast) = ast_allocate(IDENT_NODE, (yyvsp[(1) - (4)].as_str), (yyvsp[(3) - (4)].as_int));  }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    { yTRACE("arguments -> arguments , expression \n"); (yyval.as_ast) = ast_allocate(ARGUMENTS_NODE, (yyvsp[(1) - (3)].as_ast), (yyvsp[(3) - (3)].as_ast));  }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 265 "parser.y"
    { yTRACE("arguments -> expression \n"); (yyval.as_ast) = ast_allocate(EXPRESSION_NODE, (yyvsp[(1) - (1)].as_ast)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 270 "parser.y"
    { yTRACE("arguments_opt -> arguments \n"); (yyval.as_ast) = ast_allocate(ARGUMENTS_NODE, (yyvsp[(1) - (1)].as_ast), NULL); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 272 "parser.y"
    { yTRACE("arguments_opt -> \n"); (yyval.as_ast) = NULL; }
    break;



/* Line 1806 of yacc.c  */
#line 1905 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 275 "parser.y"


/***********************************************************************ol
 * Extra C code.
 *
 * The given yyerror function should not be touched. You may add helper
 * functions as necessary in subsequent phases.
 ***********************************************************************/
void yyerror(char* s) {
  if(errorOccurred) {
    return;    /* Error has already been reported by scanner */
  } else {
    errorOccurred = 1;
  }

  fprintf(errorFile, "\nPARSER ERROR, LINE %d", yyline);
  
  if(strcmp(s, "parse error")) {
    if(strncmp(s, "parse error, ", 13)) {
      fprintf(errorFile, ": %s\n", s);
    } else {
      fprintf(errorFile, ": %s\n", s+13);
    }
  } else {
    fprintf(errorFile, ": Reading token %s\n", yytname[YYTRANSLATE(yychar)]);
  }
}


