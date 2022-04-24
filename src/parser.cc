/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 2 "src/parser.yy"

#include <cstdio>
#include "vm.hh"
#include "symbols.hh"

extern int yylineno;
extern int yylex(void);
void yyerror(const char *);

#define DECLARE_ERROR(msg) do { yyerror(msg); YYERROR; } while(0)


#line 80 "src/parser.cc"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 131 "src/parser.cc"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    42,    42,    46,    47,    50,    51,    54,    66,    69,
      70,    71,    74,    75,    78,    79,    82,    83,    86,    87,
      88,    91,    92,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   107,   126,   127,   130,   132,   130,
     145,   148,   153,   148,   161,   161,   170,   180,   183,   183,
     191,   199,   202,   210,   213,   221,   224,   232,   241,   249,
     258,   266,   275,   278,   285,   292,   295,   302,   310,   318,
     321,   329,   332,   338,   343,   344,   345,   346,   358,   361,
     362,   365,   366
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_INT", "TOKEN_STR", "TOKEN_BLK",
  "TOKEN_FUN", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_FOR", "TOKEN_FROM",
  "TOKEN_TO", "TOKEN_WHILE", "TOKEN_VAR", "TOKEN_BRK", "TOKEN_CNT",
  "TOKEN_RET", "TOKEN_NIL", "TOKEN_DIR_GRID", "TOKEN_DIR_TITLE",
  "TOKEN_DIR_ICON", "TOKEN_SQ_BRACK_L", "TOKEN_SQ_BRACK_R",
  "TOKEN_PAREN_L", "TOKEN_PAREN_R", "TOKEN_BRACE_L", "TOKEN_BRACE_R",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_SLASH", "TOKEN_STAR", "TOKEN_MODULO",
  "TOKEN_DOUBLE_EQ", "TOKEN_NOT_EQ", "TOKEN_GREATER_EQ", "TOKEN_LESS_EQ",
  "TOKEN_EQUAL", "TOKEN_LESS", "TOKEN_GREATER", "TOKEN_LOGICAL_AND",
  "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_NOT", "TOKEN_SEMICOLON",
  "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_INT_VAL", "TOKEN_STR_VAL",
  "TOKEN_IDENTIFIER", "TOKEN_LOG", "TOKEN_ERR", "$accept", "program",
  "definitions", "definition", "variable", "function", "params", "params_",
  "param", "type", "stmts", "stmt", "retstmt", "whilestmt", "@1", "@2",
  "forstmt", "ifstmt", "@3", "@4", "@5", "asgnstmt", "blckstmt", "$@6",
  "expr", "andexpr", "notexpr", "relexpr", "sumexpr", "mulexpr", "unexpr",
  "smolexpr", "callexpr", "args", "args_", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,   -11,    -8,    64,   -57,    14,   -57,   -57,    54,    37,
     -57,   -57,    85,    11,    42,    75,   -57,    70,   -57,   -57,
     -57,    40,    11,   -12,    85,    22,    22,   113,   -57,    11,
     -57,   -57,    22,     9,    12,   -57,   -57,     5,    95,    97,
     -57,    72,   -10,    67,   -57,   -57,   -57,   115,    94,    79,
     117,   -57,    90,   -17,   -57,    72,    22,    22,    22,    22,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,   104,    22,   -57,   -57,    -4,   119,   -57,   -57,    38,
     118,    97,   -57,   -10,   -10,   -10,   -10,   -10,   -10,    67,
      67,   -57,   -57,   -57,   122,    95,    22,    98,   -57,   102,
     105,     6,   -57,   -57,    50,    22,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,    80,   121,   -57,   -57,    22,    95,
     138,    22,   -57,   -57,   -57,    84,    22,    22,    87,   -57,
     -57,   127,   121,   121,    22,    95,   -57,    44,    88,   -57,
     108,   -57,   -57,    -7,   121,   116,   -57,   -57,   143,    22,
     -57,    22,   121,    47,    91,   -57,   -57,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     0,     2,     4,     5,     6,     0,     0,
       1,     3,    13,     0,     0,     0,    12,    14,    18,    19,
      20,     0,     0,     0,     0,    80,     0,    16,    48,     0,
       9,    15,     0,     0,     0,    72,    73,    77,    82,    51,
      53,    55,    62,    65,    69,    71,    76,     0,    79,     0,
       0,    22,     0,     0,    70,    54,     0,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    17,     0,     0,    10,    74,     0,
       0,    50,    52,    60,    61,    57,    56,    58,    59,    63,
      64,    67,    66,    68,     0,    81,     0,     0,    37,     0,
       0,     0,    49,    33,    77,     0,    23,    21,    28,    27,
      25,    26,    29,    30,     0,     0,    75,    78,    80,    41,
       0,     0,    31,    32,    35,     0,     0,     0,     0,    24,
      11,     0,     0,     0,     0,    38,    36,     0,     0,    34,
       0,    42,    45,     0,     0,    75,    46,     8,     0,     0,
      39,     0,     0,     0,     0,    43,    40,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -57,   -57,   148,   -57,    81,   -57,   -57,   130,   -57,    52,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -50,   -57,   -26,    99,    96,   124,    28,    46,
      48,   126,   -57,   -56,   -57
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    16,    17,    21,
      75,   107,   108,   109,   121,   144,   110,   111,   132,   148,
     133,   112,    30,    51,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    80,    77,    96,   149,    97,    53,    78,    98,     2,
      99,   100,   101,    28,    18,    19,    20,    66,    67,    32,
       1,    28,   102,    58,    33,   113,    56,     2,    57,    32,
      79,    29,    32,    58,    33,    32,     8,    34,   103,     9,
      33,    35,    36,   104,   105,    32,    95,    34,   124,   114,
      33,    35,    36,    37,    35,    36,    37,    35,    36,    37,
     116,    25,   131,    34,    10,   130,   145,    35,    36,    37,
     119,   126,    28,    57,    27,   125,    26,    12,    58,   128,
      13,    52,   141,   142,    58,    22,   127,    58,    83,    84,
      85,    86,    87,    88,   150,   135,    68,    69,    70,    23,
     137,   138,   155,   156,    60,    61,    62,    63,   143,    64,
      65,    76,    89,    90,    24,    28,    91,    92,    93,    58,
      58,    73,   129,   153,    58,   154,   136,    58,    58,   139,
     146,    58,    14,   157,    50,    58,    59,    71,    72,    74,
      94,   115,   117,   118,   122,   120,    28,   123,   134,   140,
     147,   152,   151,    11,    31,    82,   106,    81,    55,    54
};

static const yytype_uint8 yycheck[] =
{
      26,    57,    52,     7,    11,     9,    32,    24,    12,    13,
      14,    15,    16,    25,     3,     4,     5,    27,    28,    23,
       6,    25,    26,    40,    28,    75,    21,    13,    23,    23,
      56,    43,    23,    40,    28,    23,    47,    41,    42,    47,
      28,    45,    46,    47,    48,    23,    72,    41,    42,    75,
      28,    45,    46,    47,    45,    46,    47,    45,    46,    47,
      22,    21,   118,    41,     0,   115,    22,    45,    46,    47,
      96,    21,    25,    23,    22,   101,    36,    23,    40,   105,
      43,    29,   132,   133,    40,    43,    36,    40,    60,    61,
      62,    63,    64,    65,   144,   121,    29,    30,    31,    24,
     126,   127,   152,   153,    32,    33,    34,    35,   134,    37,
      38,    21,    66,    67,    44,    25,    68,    69,    70,    40,
      40,    42,    42,   149,    40,   151,    42,    40,    40,    42,
      42,    40,    47,    42,    21,    40,    39,    22,    44,    22,
      36,    22,    24,    21,    42,    47,    25,    42,    10,    22,
      42,     8,    36,     5,    24,    59,    75,    58,    34,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    13,    51,    52,    53,    54,    55,    47,    47,
       0,    52,    23,    43,    47,    56,    57,    58,     3,     4,
       5,    59,    43,    24,    44,    21,    36,    59,    25,    43,
      72,    57,    23,    28,    41,    45,    46,    47,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    74,
      21,    73,    59,    74,    81,    77,    21,    23,    40,    39,
      32,    33,    34,    35,    37,    38,    27,    28,    29,    30,
      31,    22,    44,    42,    22,    60,    21,    72,    24,    74,
      83,    75,    76,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80,    36,    74,     7,     9,    12,    14,
      15,    16,    26,    42,    47,    48,    54,    61,    62,    63,
      66,    67,    71,    72,    74,    22,    22,    24,    21,    74,
      47,    64,    42,    42,    42,    74,    21,    36,    74,    42,
      72,    83,    68,    70,    10,    74,    42,    74,    74,    42,
      22,    72,    72,    74,    65,    22,    42,    42,    69,    11,
      72,    36,     8,    74,    74,    72,    72,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    64,    65,    63,
      66,    68,    69,    67,    70,    67,    71,    71,    73,    72,
      74,    74,    75,    75,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    78,    78,    78,    79,    79,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     7,    12,     6,
       8,    10,     1,     0,     1,     3,     3,     5,     1,     1,
       1,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     3,     2,     3,     0,     0,     5,
       7,     0,     0,     7,     0,     4,     4,     7,     0,     4,
       3,     1,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     1,     1,     1,     3,     4,     1,     1,     4,     1,
       0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 7:
#line 55 "src/parser.yy"
{
        if(yyvsp[-3].type != yyvsp[-1].type) DECLARE_ERROR("Type mismatch");

        usize id = vm.write_decl_var();
        string ident = yyvsp[-5].as.str_val;
        Entry entry = { yyvsp[-3].type, id };

        if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");

}
#line 1487 "src/parser.cc"
    break;

  case 18:
#line 86 "src/parser.yy"
                 { yyval.type = DataType::INT; }
#line 1493 "src/parser.cc"
    break;

  case 19:
#line 87 "src/parser.yy"
                    { yyval.type = DataType::STR; }
#line 1499 "src/parser.cc"
    break;

  case 20:
#line 88 "src/parser.yy"
                    { yyval.type = DataType::BLK; }
#line 1505 "src/parser.cc"
    break;

  case 34:
#line 108 "src/parser.yy"
        {
                switch(yyvsp[-1].type)
                {
                        case DataType::STR:
                        vm.write_op(OP::LOGSTR);
                        break;

                        case DataType::INT:
                        vm.write_op(OP::LOGINT);
                        break;

                        default:
                        DECLARE_ERROR("Invalid operand for log\n");
                        break;
                }
        }
#line 1526 "src/parser.cc"
    break;

  case 37:
#line 130 "src/parser.yy"
                        {
        yyval.as.int_val = vm.bytecode_len();
}
#line 1534 "src/parser.cc"
    break;

  case 38:
#line 132 "src/parser.yy"
                    {
        yyval.as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
}
#line 1544 "src/parser.cc"
    break;

  case 39:
#line 136 "src/parser.yy"
                        {
        vm.write_op(OP::LOOP);
        i64 offset = vm.bytecode_len() - 1 - yyvsp[-3].as.int_val;
        if(offset > UINT16_MAX) DECLARE_ERROR("Code jump too big");
        vm.write_word(static_cast<u16>(offset));
        vm.patch_jump(yyvsp[-1].as.int_val);  
}
#line 1556 "src/parser.cc"
    break;

  case 41:
#line 148 "src/parser.yy"
                        {
        yyval.as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
        
}
#line 1567 "src/parser.cc"
    break;

  case 42:
#line 153 "src/parser.yy"
                        {
        yyval.as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP);
        vm.write_word(0);
        vm.patch_jump(yyvsp[-1].as.int_val);
}
#line 1578 "src/parser.cc"
    break;

  case 43:
#line 158 "src/parser.yy"
                                    {
        vm.patch_jump(yyvsp[-2].as.int_val);
}
#line 1586 "src/parser.cc"
    break;

  case 44:
#line 161 "src/parser.yy"
                        {
        yyval.as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
}
#line 1596 "src/parser.cc"
    break;

  case 45:
#line 165 "src/parser.yy"
                   {
        vm.patch_jump(yyvsp[-1].as.int_val);        
}
#line 1604 "src/parser.cc"
    break;

  case 46:
#line 171 "src/parser.yy"
{
string ident = yyvsp[-3].as.str_val;
Entry entry;
if(!check_symbol(ident, entry)) DECLARE_ERROR("Undeclared identifier");
if(entry.type != yyvsp[-1].type) DECLARE_ERROR("Type mismatch");

vm.write_op(OP::VARSET);
vm.write_byte(entry.id);
}
#line 1618 "src/parser.cc"
    break;

  case 48:
#line 183 "src/parser.yy"
                         { open_scope(); }
#line 1624 "src/parser.cc"
    break;

  case 49:
#line 184 "src/parser.yy"
        { 
                usize var_count = get_scope_var_count();
                close_scope();
                vm.undecl_vars(var_count);
        }
#line 1634 "src/parser.cc"
    break;

  case 50:
#line 192 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::OR);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1646 "src/parser.cc"
    break;

  case 51:
#line 199 "src/parser.yy"
                  { yyval.type = yyvsp[0].type; }
#line 1652 "src/parser.cc"
    break;

  case 52:
#line 203 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::AND);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1664 "src/parser.cc"
    break;

  case 53:
#line 210 "src/parser.yy"
                  { yyval.type = yyvsp[0].type; }
#line 1670 "src/parser.cc"
    break;

  case 54:
#line 214 "src/parser.yy"
{
                if(yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1682 "src/parser.cc"
    break;

  case 55:
#line 221 "src/parser.yy"
                  { yyval.type = yyvsp[0].type; }
#line 1688 "src/parser.cc"
    break;

  case 56:
#line 225 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1700 "src/parser.cc"
    break;

  case 57:
#line 233 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::LESS);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1713 "src/parser.cc"
    break;

  case 58:
#line 242 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::LESS);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1725 "src/parser.cc"
    break;

  case 59:
#line 250 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                }     
}
#line 1738 "src/parser.cc"
    break;

  case 60:
#line 259 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1750 "src/parser.cc"
    break;

  case 61:
#line 267 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1763 "src/parser.cc"
    break;

  case 62:
#line 275 "src/parser.yy"
                  { yyval.type = yyvsp[0].type; }
#line 1769 "src/parser.cc"
    break;

  case 63:
#line 278 "src/parser.yy"
                                    {
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::ADD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
}
#line 1781 "src/parser.cc"
    break;

  case 64:
#line 285 "src/parser.yy"
                                      { 
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::SUB);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
#line 1793 "src/parser.cc"
    break;

  case 65:
#line 292 "src/parser.yy"
                  { yyval.type = yyvsp[0].type; }
#line 1799 "src/parser.cc"
    break;

  case 66:
#line 295 "src/parser.yy"
                                   {
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::MUL);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
}
#line 1811 "src/parser.cc"
    break;

  case 67:
#line 303 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::DIV);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
#line 1823 "src/parser.cc"
    break;

  case 68:
#line 311 "src/parser.yy"
{
                if(yyvsp[-2].type == DataType::INT && yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::MOD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
#line 1835 "src/parser.cc"
    break;

  case 69:
#line 318 "src/parser.yy"
                 { yyval.type = yyvsp[0].type; }
#line 1841 "src/parser.cc"
    break;

  case 70:
#line 322 "src/parser.yy"
{
                if(yyvsp[0].type == DataType::INT) {
                        vm.write_op(OP::NEG);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
#line 1853 "src/parser.cc"
    break;

  case 71:
#line 329 "src/parser.yy"
                   { yyval.type = yyvsp[0].type; }
#line 1859 "src/parser.cc"
    break;

  case 72:
#line 333 "src/parser.yy"
{
        vm.write_constant_op(OP::CONST, yyvsp[0].as.int_val);
        yyval.type = DataType::INT;
}
#line 1868 "src/parser.cc"
    break;

  case 73:
#line 339 "src/parser.yy"
        {
                vm.write_constant_op(OP::CONST, (u64) yyvsp[0].as.str_val);
                yyval.type = DataType::STR;
        }
#line 1877 "src/parser.cc"
    break;

  case 77:
#line 347 "src/parser.yy"
        {
                string ident = yyvsp[0].as.str_val;
                Entry entry;
                if(!check_symbol(ident, entry)) DECLARE_ERROR("Undeclared identifier");

                vm.write_op(OP::VARGET);
                vm.write_byte(entry.id);
                yyval.type = entry.type;
        }
#line 1891 "src/parser.cc"
    break;


#line 1895 "src/parser.cc"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 370 "src/parser.yy"


void yyerror(const char *msg)
{
fprintf(stderr, "<Line %d> Syntax error: %s\n", yylineno, msg);
}
