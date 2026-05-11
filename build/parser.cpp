/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 15 "src/parser.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

p2p::Module* g_root = nullptr;

/* Set by main() before calling yyparse():
   - PARSE_PROGRAM: full file, top-level declarations.
   - PARSE_EXPR:    one expression followed by a semicolon (test mode). */
int g_parse_mode = 0;
#define PARSE_PROGRAM 0
#define PARSE_EXPR    1

/* When PARSE_EXPR mode is used, the resulting expression is captured here
   so that main() can print it. */
p2p::Expr* g_expr_result = nullptr;

/* Expression-building helpers. */
static p2p::Expr* make_bin(p2p::BinaryOp op, p2p::Expr* lhs, p2p::Expr* rhs) {
    auto* e = new p2p::BinaryExpr();
    e->op = op;
    e->lhs.reset(lhs);
    e->rhs.reset(rhs);
    return e;
}

static p2p::Expr* make_un(p2p::UnaryOp op, p2p::Expr* operand) {
    auto* e = new p2p::UnaryExpr();
    e->op = op;
    e->operand.reset(operand);
    return e;
}

static p2p::Expr* make_builtin(p2p::BuiltinKind k, p2p::Expr* arg) {
    auto* c = new p2p::BuiltinCallExpr();
    c->kind = k;
    c->arg.reset(arg);
    return c;
}

/* Type-building helpers. */
static p2p::Type* make_basic(p2p::BasicTypeKind k) {
    auto* t = new p2p::Type();
    t->kind = k;
    return t;
}

static p2p::Type* make_named(const char* name) {
    auto* t = new p2p::Type();
    t->kind = p2p::BasicTypeKind::Named;
    t->named = name;
    return t;
}

/* Deep-copy a Type. Each declarator in a comma list owns an independent
   Type so later mutations don't bleed between them. */
static p2p::Type* clone_type(const p2p::Type& src) {
    auto* t = new p2p::Type();
    t->kind = src.kind;
    t->named = src.named;
    t->mtype_set = src.mtype_set;
    t->chan_capacity = src.chan_capacity;
    for (auto& el : src.chan_msg_types) {
        t->chan_msg_types.push_back(p2p::TypePtr(clone_type(*el)));
    }
    return t;
}


#line 150 "build/parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_T_BYTE = 5,                     /* T_BYTE  */
  YYSYMBOL_T_INT = 6,                      /* T_INT  */
  YYSYMBOL_T_BOOL = 7,                     /* T_BOOL  */
  YYSYMBOL_T_BIT = 8,                      /* T_BIT  */
  YYSYMBOL_T_SHORT = 9,                    /* T_SHORT  */
  YYSYMBOL_T_UNSIGNED = 10,                /* T_UNSIGNED  */
  YYSYMBOL_T_MTYPE = 11,                   /* T_MTYPE  */
  YYSYMBOL_T_CHAN = 12,                    /* T_CHAN  */
  YYSYMBOL_K_PROCTYPE = 13,                /* K_PROCTYPE  */
  YYSYMBOL_K_ACTIVE = 14,                  /* K_ACTIVE  */
  YYSYMBOL_K_INLINE = 15,                  /* K_INLINE  */
  YYSYMBOL_K_TYPEDEF = 16,                 /* K_TYPEDEF  */
  YYSYMBOL_K_LTL = 17,                     /* K_LTL  */
  YYSYMBOL_K_INIT = 18,                    /* K_INIT  */
  YYSYMBOL_K_DO = 19,                      /* K_DO  */
  YYSYMBOL_K_OD = 20,                      /* K_OD  */
  YYSYMBOL_K_IF = 21,                      /* K_IF  */
  YYSYMBOL_K_FI = 22,                      /* K_FI  */
  YYSYMBOL_K_ELSE = 23,                    /* K_ELSE  */
  YYSYMBOL_K_BREAK = 24,                   /* K_BREAK  */
  YYSYMBOL_K_GOTO = 25,                    /* K_GOTO  */
  YYSYMBOL_K_SKIP = 26,                    /* K_SKIP  */
  YYSYMBOL_K_ATOMIC = 27,                  /* K_ATOMIC  */
  YYSYMBOL_K_D_STEP = 28,                  /* K_D_STEP  */
  YYSYMBOL_K_UNLESS = 29,                  /* K_UNLESS  */
  YYSYMBOL_K_FOR = 30,                     /* K_FOR  */
  YYSYMBOL_K_SELECT = 31,                  /* K_SELECT  */
  YYSYMBOL_K_RUN = 32,                     /* K_RUN  */
  YYSYMBOL_K_OF = 33,                      /* K_OF  */
  YYSYMBOL_K_LEN = 34,                     /* K_LEN  */
  YYSYMBOL_K_NEMPTY = 35,                  /* K_NEMPTY  */
  YYSYMBOL_K_EMPTY = 36,                   /* K_EMPTY  */
  YYSYMBOL_K_NFULL = 37,                   /* K_NFULL  */
  YYSYMBOL_K_FULL = 38,                    /* K_FULL  */
  YYSYMBOL_K_PRINTF = 39,                  /* K_PRINTF  */
  YYSYMBOL_K_ASSERT = 40,                  /* K_ASSERT  */
  YYSYMBOL_K_TRUE = 41,                    /* K_TRUE  */
  YYSYMBOL_K_FALSE = 42,                   /* K_FALSE  */
  YYSYMBOL_OP_ARROW = 43,                  /* OP_ARROW  */
  YYSYMBOL_OP_DCOLON = 44,                 /* OP_DCOLON  */
  YYSYMBOL_OP_DOTDOT = 45,                 /* OP_DOTDOT  */
  YYSYMBOL_OP_INC = 46,                    /* OP_INC  */
  YYSYMBOL_OP_DEC = 47,                    /* OP_DEC  */
  YYSYMBOL_OP_AND = 48,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 49,                     /* OP_OR  */
  YYSYMBOL_OP_EQ = 50,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 51,                    /* OP_NEQ  */
  YYSYMBOL_OP_LE = 52,                     /* OP_LE  */
  YYSYMBOL_OP_GE = 53,                     /* OP_GE  */
  YYSYMBOL_OP_SHL = 54,                    /* OP_SHL  */
  YYSYMBOL_OP_SHR = 55,                    /* OP_SHR  */
  YYSYMBOL_LTL_ALWAYS = 56,                /* LTL_ALWAYS  */
  YYSYMBOL_LTL_EVENTUALLY = 57,            /* LTL_EVENTUALLY  */
  YYSYMBOL_LTL_UNTIL = 58,                 /* LTL_UNTIL  */
  YYSYMBOL_START_PROGRAM = 59,             /* START_PROGRAM  */
  YYSYMBOL_START_EXPR = 60,                /* START_EXPR  */
  YYSYMBOL_61_ = 61,                       /* ':'  */
  YYSYMBOL_62_ = 62,                       /* '<'  */
  YYSYMBOL_63_ = 63,                       /* '>'  */
  YYSYMBOL_64_ = 64,                       /* '+'  */
  YYSYMBOL_65_ = 65,                       /* '-'  */
  YYSYMBOL_66_ = 66,                       /* '*'  */
  YYSYMBOL_67_ = 67,                       /* '/'  */
  YYSYMBOL_68_ = 68,                       /* '%'  */
  YYSYMBOL_UMINUS = 69,                    /* UMINUS  */
  YYSYMBOL_UNOT = 70,                      /* UNOT  */
  YYSYMBOL_PREFIX_INCDEC = 71,             /* PREFIX_INCDEC  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* '.'  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* '='  */
  YYSYMBOL_76_ = 76,                       /* ']'  */
  YYSYMBOL_77_ = 77,                       /* '{'  */
  YYSYMBOL_78_ = 78,                       /* '}'  */
  YYSYMBOL_79_ = 79,                       /* ','  */
  YYSYMBOL_80_ = 80,                       /* '!'  */
  YYSYMBOL_81_ = 81,                       /* '('  */
  YYSYMBOL_82_ = 82,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_start = 84,                     /* start  */
  YYSYMBOL_program_body = 85,              /* program_body  */
  YYSYMBOL_top_decl = 86,                  /* top_decl  */
  YYSYMBOL_var_decl_stmt = 87,             /* var_decl_stmt  */
  YYSYMBOL_chan_decl_stmt = 88,            /* chan_decl_stmt  */
  YYSYMBOL_chan_type = 89,                 /* chan_type  */
  YYSYMBOL_basic_type = 90,                /* basic_type  */
  YYSYMBOL_declarator_list = 91,           /* declarator_list  */
  YYSYMBOL_declarator = 92,                /* declarator  */
  YYSYMBOL_type_list = 93,                 /* type_list  */
  YYSYMBOL_typedef_decl = 94,              /* typedef_decl  */
  YYSYMBOL_field_decl_list = 95,           /* field_decl_list  */
  YYSYMBOL_field_decl_stmt = 96,           /* field_decl_stmt  */
  YYSYMBOL_field_decl_one_or_more = 97,    /* field_decl_one_or_more  */
  YYSYMBOL_field_one = 98,                 /* field_one  */
  YYSYMBOL_mtype_decl = 99,                /* mtype_decl  */
  YYSYMBOL_ident_list = 100,               /* ident_list  */
  YYSYMBOL_ltl_decl = 101,                 /* ltl_decl  */
  YYSYMBOL_ltl_formula = 102,              /* ltl_formula  */
  YYSYMBOL_ltl_unary = 103,                /* ltl_unary  */
  YYSYMBOL_ltl_atom = 104,                 /* ltl_atom  */
  YYSYMBOL_expr_body = 105,                /* expr_body  */
  YYSYMBOL_expr = 106,                     /* expr  */
  YYSYMBOL_primary = 107                   /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 94 "src/parser.y"

    /* These helpers reference VarDeclList declared in %code requires,
       so they must live after that block has been emitted. */
    static void attach_type(VarDeclList& list, const p2p::Type& t) {
        for (auto& d : list.items) {
            d->type.reset(clone_type(t));
        }
    }

    static void push_decls(VarDeclList& list) {
        if (!g_root) g_root = new p2p::Module();
        for (auto& d : list.items) {
            g_root->declarations.emplace_back(std::move(d));
        }
    }

#line 309 "build/parser.cpp"

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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   625

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  221

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    68,     2,     2,
      81,    82,    66,    64,    79,    65,    73,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    74,
      62,    75,    63,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    76,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    77,     2,    78,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   185,   185,   186,   189,   191,   199,   200,   201,   202,
     203,   208,   219,   226,   244,   248,   249,   250,   251,   252,
     253,   254,   255,   262,   266,   272,   280,   286,   293,   300,
     311,   317,   326,   337,   338,   347,   356,   362,   370,   376,
     387,   394,   405,   412,   422,   436,   437,   444,   451,   461,
     468,   475,   482,   483,   497,   498,   499,   500,   505,   510,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   532,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   566,   567,   568,   569,   574,   579,   585,   592,
     593,   594,   595,   596,   597,   598,   599,   600
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL", "IDENT",
  "T_BYTE", "T_INT", "T_BOOL", "T_BIT", "T_SHORT", "T_UNSIGNED", "T_MTYPE",
  "T_CHAN", "K_PROCTYPE", "K_ACTIVE", "K_INLINE", "K_TYPEDEF", "K_LTL",
  "K_INIT", "K_DO", "K_OD", "K_IF", "K_FI", "K_ELSE", "K_BREAK", "K_GOTO",
  "K_SKIP", "K_ATOMIC", "K_D_STEP", "K_UNLESS", "K_FOR", "K_SELECT",
  "K_RUN", "K_OF", "K_LEN", "K_NEMPTY", "K_EMPTY", "K_NFULL", "K_FULL",
  "K_PRINTF", "K_ASSERT", "K_TRUE", "K_FALSE", "OP_ARROW", "OP_DCOLON",
  "OP_DOTDOT", "OP_INC", "OP_DEC", "OP_AND", "OP_OR", "OP_EQ", "OP_NEQ",
  "OP_LE", "OP_GE", "OP_SHL", "OP_SHR", "LTL_ALWAYS", "LTL_EVENTUALLY",
  "LTL_UNTIL", "START_PROGRAM", "START_EXPR", "':'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UMINUS", "UNOT", "PREFIX_INCDEC", "'['",
  "'.'", "';'", "'='", "']'", "'{'", "'}'", "','", "'!'", "'('", "')'",
  "$accept", "start", "program_body", "top_decl", "var_decl_stmt",
  "chan_decl_stmt", "chan_type", "basic_type", "declarator_list",
  "declarator", "type_list", "typedef_decl", "field_decl_list",
  "field_decl_stmt", "field_decl_one_or_more", "field_one", "mtype_decl",
  "ident_list", "ltl_decl", "ltl_formula", "ltl_unary", "ltl_atom",
  "expr_body", "expr", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,  -111,    29,    25,   600,  -111,  -111,   -68,   -19,    14,
      17,    33,  -111,  -111,    65,    65,    29,    29,    29,  -111,
     373,   -38,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
     -57,  -111,    50,   113,  -111,  -111,  -111,   141,   147,  -111,
    -111,  -111,    29,    29,    29,    29,    29,   -38,   -38,  -111,
    -111,    70,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,  -111,  -111,
    -111,    29,   165,   187,   118,   122,   123,    66,   -58,   -64,
    -111,   110,   153,   179,   205,   231,  -111,   423,   518,   499,
     535,   535,   116,   116,   172,   172,   116,   116,    61,    61,
    -111,  -111,  -111,   257,  -111,   134,   207,   614,    74,  -111,
     140,    29,    29,  -111,   147,  -111,  -111,  -111,  -111,  -111,
      29,  -111,   136,  -111,    64,   162,   220,    30,  -111,  -111,
    -111,  -111,  -111,    74,    74,    16,    74,    74,   101,  -111,
     456,    29,   286,   449,  -111,   449,   207,   151,   222,   245,
     178,   173,  -111,   614,   177,  -111,  -111,    75,  -111,   -27,
      74,    74,    74,  -111,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,   258,   315,   188,    78,
    -111,  -111,  -111,    29,   220,  -111,  -111,  -111,    31,  -111,
     216,   473,   473,   121,   121,   121,   121,   -61,   -61,    75,
      75,    75,   392,  -111,   232,    29,   192,   344,  -111,  -111,
     198,   449,  -111,  -111,   614,  -111,    88,   202,   614,  -111,
    -111
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     2,    92,    95,     0,     0,     0,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     3,
       0,    73,     1,    23,    15,    16,    17,    18,    19,    20,
      21,    14,     0,     0,     5,     6,     7,     0,     0,     8,
       9,    10,     0,     0,     0,     0,     0,   101,   102,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    72,    99,
     100,     0,     0,     0,     0,     0,     0,     0,    26,     0,
      24,     0,     0,     0,     0,     0,    96,     0,    87,    88,
      85,    86,    83,    84,    79,    80,    81,    82,    74,    75,
      76,    77,    78,     0,    98,    22,     0,     0,     0,    12,
       0,     0,     0,    11,     0,   105,   103,   104,   107,   106,
       0,    97,     0,    42,     0,    21,     0,     0,    33,    54,
      57,    55,    56,     0,     0,     0,     0,     0,     0,    45,
      53,     0,     0,    27,    25,    91,     0,     0,     0,     0,
      38,    35,    36,     0,     0,    49,    50,    71,    51,     0,
       0,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
      40,    43,    22,     0,     0,    34,    32,    52,    48,    46,
      47,    69,    70,    67,    68,    65,    66,    60,    61,    62,
      63,    64,     0,    59,     0,     0,     0,     0,    37,    58,
       0,    29,    41,    39,     0,    30,     0,     0,     0,    13,
      31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,  -111,  -111,  -111,  -111,    -4,  -111,   163,
    -111,  -111,  -111,   125,  -111,   104,  -111,   143,  -111,  -101,
    -110,   -82,  -111,   -15,   183
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    34,    35,    36,    37,   126,    79,    80,
     216,    39,   127,   128,   151,   152,    40,   124,    41,   138,
     139,   140,    19,    20,    21
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      38,    49,    50,    51,    73,   172,   173,   174,    69,    70,
     113,   175,   176,    42,   111,   114,   160,   112,    74,   129,
     130,   161,   162,   155,   156,    22,   158,    81,    82,    83,
      84,    85,     5,     6,    71,    72,   159,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   157,    75,   187,   103,   131,   132,   188,
     189,   190,    43,     7,     8,     9,    10,    11,     5,     6,
      12,    13,     1,     2,   160,    14,    15,   129,   130,   161,
     162,   135,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,    16,    44,   142,   143,    45,     7,
       8,     9,    10,    11,   153,   145,    12,    13,   154,    17,
      18,    14,    15,    52,    46,   131,   132,    76,    53,    54,
      55,    56,    57,    58,    59,    60,   177,    65,    66,    67,
     133,   134,    61,    62,    63,    64,    65,    66,    67,   135,
     109,   110,   147,   148,   160,    77,    18,   175,   176,   161,
     162,    78,    86,    52,   136,   137,   206,   148,    53,    54,
      55,    56,    57,    58,    59,    60,   217,   218,   207,   104,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   163,
      63,    64,    65,    66,    67,   170,   171,   172,   173,   174,
     211,   105,   115,   175,   176,   106,    52,    47,    48,   107,
     108,    53,    54,    55,    56,    57,    58,    59,    60,   122,
     215,   123,   141,   146,   220,    61,    62,    63,    64,    65,
      66,    67,    52,   149,   150,   180,   181,    53,    54,    55,
      56,    57,    58,    59,    60,   116,    63,    64,    65,    66,
      67,    61,    62,    63,    64,    65,    66,    67,    52,   182,
     183,   186,   184,    53,    54,    55,    56,    57,    58,    59,
      60,   117,   203,   205,   161,   210,   212,    61,    62,    63,
      64,    65,    66,    67,    52,   214,   219,   144,   185,    53,
      54,    55,    56,    57,    58,    59,    60,   118,   208,   179,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      52,     0,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,    60,   119,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,    52,
       0,     0,     0,   121,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,     0,     0,    52,     0,
       0,     0,   178,    53,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,    52,     0,     0,
       0,   204,    53,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     0,     0,    52,     0,     0,     0,
     213,    53,    54,    55,    56,    57,    58,    59,    60,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    67,   164,   165,   166,   167,     0,    68,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,   175,   176,    52,     0,   209,     0,
       0,    53,    54,    55,    56,    57,    58,    59,    60,     0,
       0,     0,     0,     0,   120,    61,    62,    63,    64,    65,
      66,    67,    52,     0,     0,     0,     0,    53,    54,    55,
      56,    57,    58,    59,    60,     0,   164,   165,   166,   167,
       0,    61,    62,    63,    64,    65,    66,    67,   168,   169,
     170,   171,   172,   173,   174,   166,   167,     0,   175,   176,
       0,     0,     0,     0,     0,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,   175,   176,    53,     0,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,     0,     0,    32,    33,    23,    24,
      25,    26,    27,    28,    29,   125
};

static const yytype_int16 yycheck[] =
{
       4,    16,    17,    18,    61,    66,    67,    68,    46,    47,
      74,    72,    73,    81,    72,    79,    43,    75,    75,     3,
       4,    48,    49,   133,   134,     0,   136,    42,    43,    44,
      45,    46,     3,     4,    72,    73,   137,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   135,     4,    82,    71,    41,    42,   160,
     161,   162,    81,    34,    35,    36,    37,    38,     3,     4,
      41,    42,    59,    60,    43,    46,    47,     3,     4,    48,
      49,    65,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,    65,    81,   111,   112,    81,    34,
      35,    36,    37,    38,    74,   120,    41,    42,    78,    80,
      81,    46,    47,    43,    81,    41,    42,     4,    48,    49,
      50,    51,    52,    53,    54,    55,   141,    66,    67,    68,
      56,    57,    62,    63,    64,    65,    66,    67,    68,    65,
      74,    75,    78,    79,    43,     4,    81,    72,    73,    48,
      49,     4,    82,    43,    80,    81,    78,    79,    48,    49,
      50,    51,    52,    53,    54,    55,    78,    79,   183,     4,
      54,    55,    62,    63,    64,    65,    66,    67,    68,    78,
      64,    65,    66,    67,    68,    64,    65,    66,    67,    68,
     205,     4,    82,    72,    73,    77,    43,    14,    15,    77,
      77,    48,    49,    50,    51,    52,    53,    54,    55,    75,
     214,     4,    72,    77,   218,    62,    63,    64,    65,    66,
      67,    68,    43,    61,     4,    74,     4,    48,    49,    50,
      51,    52,    53,    54,    55,    82,    64,    65,    66,    67,
      68,    62,    63,    64,    65,    66,    67,    68,    43,     4,
      72,    74,    79,    48,    49,    50,    51,    52,    53,    54,
      55,    82,     4,    75,    48,    33,    74,    62,    63,    64,
      65,    66,    67,    68,    43,    77,    74,   114,   153,    48,
      49,    50,    51,    52,    53,    54,    55,    82,   184,   146,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    82,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    76,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    76,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    76,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      76,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    50,    51,    52,    53,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    73,    43,    -1,    76,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    50,    51,    52,    53,
      -1,    62,    63,    64,    65,    66,    67,    68,    62,    63,
      64,    65,    66,    67,    68,    52,    53,    -1,    72,    73,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    72,    73,    48,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    16,    17,     4,     5,
       6,     7,     8,     9,    10,    11
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    59,    60,    84,    85,     3,     4,    34,    35,    36,
      37,    38,    41,    42,    46,    47,    65,    80,    81,   105,
     106,   107,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    16,    17,    86,    87,    88,    89,    90,    94,
      99,   101,    81,    81,    81,    81,    81,   107,   107,   106,
     106,   106,    43,    48,    49,    50,    51,    52,    53,    54,
      55,    62,    63,    64,    65,    66,    67,    68,    74,    46,
      47,    72,    73,    61,    75,     4,     4,     4,     4,    91,
      92,   106,   106,   106,   106,   106,    82,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,     4,     4,    77,    77,    77,    74,
      75,    72,    75,    74,    79,    82,    82,    82,    82,    82,
      61,    76,    75,     4,   100,    11,    90,    95,    96,     3,
       4,    41,    42,    56,    57,    65,    80,    81,   102,   103,
     104,    72,   106,   106,    92,   106,    77,    78,    79,    61,
       4,    97,    98,    74,    78,   103,   103,   104,   103,   102,
      43,    48,    49,    78,    50,    51,    52,    53,    62,    63,
      64,    65,    66,    67,    68,    72,    73,   106,    76,   100,
      74,     4,     4,    72,    79,    96,    74,    82,   102,   102,
     102,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,     4,    76,    75,    78,   106,    98,    76,
      33,   106,    74,    76,    77,    90,    93,    78,    79,    74,
      90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    83,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    87,    88,    88,    89,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    91,    92,    92,    92,    92,
      93,    93,    94,    95,    95,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     3,     3,    11,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     3,     1,     3,     4,     6,
       1,     3,     6,     1,     3,     2,     1,     3,     1,     4,
       6,     8,     1,     3,     5,     1,     3,     3,     3,     2,
       2,     2,     3,     1,     1,     1,     1,     1,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     5,     1,     1,     1,     1,     3,     4,     3,     2,
       2,     2,     2,     4,     4,     4,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* start: START_PROGRAM program_body  */
#line 185 "src/parser.y"
                                   { if (!g_root) g_root = new p2p::Module(); }
#line 1765 "build/parser.cpp"
    break;

  case 5: /* program_body: program_body top_decl  */
#line 192 "src/parser.y"
        {
            if (!g_root) g_root = new p2p::Module();
            if ((yyvsp[0].node)) g_root->declarations.emplace_back((yyvsp[0].node));
        }
#line 1774 "build/parser.cpp"
    break;

  case 6: /* top_decl: var_decl_stmt  */
#line 199 "src/parser.y"
                           { push_decls(*(yyvsp[0].vardecl_list)); delete (yyvsp[0].vardecl_list); (yyval.node) = nullptr; }
#line 1780 "build/parser.cpp"
    break;

  case 7: /* top_decl: chan_decl_stmt  */
#line 200 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1786 "build/parser.cpp"
    break;

  case 8: /* top_decl: typedef_decl  */
#line 201 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1792 "build/parser.cpp"
    break;

  case 9: /* top_decl: mtype_decl  */
#line 202 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1798 "build/parser.cpp"
    break;

  case 10: /* top_decl: ltl_decl  */
#line 203 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1804 "build/parser.cpp"
    break;

  case 11: /* var_decl_stmt: basic_type declarator_list ';'  */
#line 209 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            (yyval.vardecl_list) = (yyvsp[-1].vardecl_list);
        }
#line 1814 "build/parser.cpp"
    break;

  case 12: /* chan_decl_stmt: chan_type IDENT ';'  */
#line 220 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-1].str_val); free((yyvsp[-1].str_val));
            d->type.reset((yyvsp[-2].type));
            (yyval.node) = d;
        }
#line 1825 "build/parser.cpp"
    break;

  case 13: /* chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 227 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-9].str_val); free((yyvsp[-9].str_val));
            d->type.reset((yyvsp[-10].type));
            if (auto* lit = dynamic_cast<p2p::IntLiteral*>((yyvsp[-6].expr))) {
                d->type->chan_capacity = (int)lit->value;
            } else {
                d->type->chan_capacity = 0;
            }
            delete (yyvsp[-6].expr);
            d->type->chan_msg_types = std::move((yyvsp[-2].type_list)->items);
            delete (yyvsp[-2].type_list);
            (yyval.node) = d;
        }
#line 1844 "build/parser.cpp"
    break;

  case 14: /* chan_type: T_CHAN  */
#line 244 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Chan); }
#line 1850 "build/parser.cpp"
    break;

  case 15: /* basic_type: T_BYTE  */
#line 248 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 1856 "build/parser.cpp"
    break;

  case 16: /* basic_type: T_INT  */
#line 249 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 1862 "build/parser.cpp"
    break;

  case 17: /* basic_type: T_BOOL  */
#line 250 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 1868 "build/parser.cpp"
    break;

  case 18: /* basic_type: T_BIT  */
#line 251 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 1874 "build/parser.cpp"
    break;

  case 19: /* basic_type: T_SHORT  */
#line 252 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 1880 "build/parser.cpp"
    break;

  case 20: /* basic_type: T_UNSIGNED  */
#line 253 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 1886 "build/parser.cpp"
    break;

  case 21: /* basic_type: T_MTYPE  */
#line 254 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 1892 "build/parser.cpp"
    break;

  case 22: /* basic_type: T_MTYPE ':' IDENT  */
#line 256 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 1903 "build/parser.cpp"
    break;

  case 23: /* basic_type: IDENT  */
#line 262 "src/parser.y"
                           { (yyval.type) = make_named((yyvsp[0].str_val)); free((yyvsp[0].str_val)); }
#line 1909 "build/parser.cpp"
    break;

  case 24: /* declarator_list: declarator  */
#line 267 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 1919 "build/parser.cpp"
    break;

  case 25: /* declarator_list: declarator_list ',' declarator  */
#line 273 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 1928 "build/parser.cpp"
    break;

  case 26: /* declarator: IDENT  */
#line 281 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 1938 "build/parser.cpp"
    break;

  case 27: /* declarator: IDENT '=' expr  */
#line 287 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 1949 "build/parser.cpp"
    break;

  case 28: /* declarator: IDENT '[' expr ']'  */
#line 294 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 1960 "build/parser.cpp"
    break;

  case 29: /* declarator: IDENT '[' expr ']' '=' expr  */
#line 301 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            d->array_size.reset((yyvsp[-3].expr));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 1972 "build/parser.cpp"
    break;

  case 30: /* type_list: basic_type  */
#line 312 "src/parser.y"
        {
            auto* tl = new TypeList();
            tl->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = tl;
        }
#line 1982 "build/parser.cpp"
    break;

  case 31: /* type_list: type_list ',' basic_type  */
#line 318 "src/parser.y"
        {
            (yyvsp[-2].type_list)->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = (yyvsp[-2].type_list);
        }
#line 1991 "build/parser.cpp"
    break;

  case 32: /* typedef_decl: K_TYPEDEF IDENT '{' field_decl_list '}' ';'  */
#line 327 "src/parser.y"
        {
            auto* td = new p2p::TypedefDecl();
            td->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            td->fields = std::move((yyvsp[-2].vardecl_list)->items);
            delete (yyvsp[-2].vardecl_list);
            (yyval.node) = td;
        }
#line 2003 "build/parser.cpp"
    break;

  case 33: /* field_decl_list: field_decl_stmt  */
#line 337 "src/parser.y"
                                               { (yyval.vardecl_list) = (yyvsp[0].vardecl_list); }
#line 2009 "build/parser.cpp"
    break;

  case 34: /* field_decl_list: field_decl_list ';' field_decl_stmt  */
#line 339 "src/parser.y"
        {
            for (auto& f : (yyvsp[0].vardecl_list)->items) (yyvsp[-2].vardecl_list)->items.emplace_back(std::move(f));
            delete (yyvsp[0].vardecl_list);
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2019 "build/parser.cpp"
    break;

  case 35: /* field_decl_stmt: basic_type field_decl_one_or_more  */
#line 348 "src/parser.y"
        {
            attach_type(*(yyvsp[0].vardecl_list), *(yyvsp[-1].type));
            delete (yyvsp[-1].type);
            (yyval.vardecl_list) = (yyvsp[0].vardecl_list);
        }
#line 2029 "build/parser.cpp"
    break;

  case 36: /* field_decl_one_or_more: field_one  */
#line 357 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2039 "build/parser.cpp"
    break;

  case 37: /* field_decl_one_or_more: field_decl_one_or_more ',' field_one  */
#line 363 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2048 "build/parser.cpp"
    break;

  case 38: /* field_one: IDENT  */
#line 371 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2058 "build/parser.cpp"
    break;

  case 39: /* field_one: IDENT '[' expr ']'  */
#line 377 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2069 "build/parser.cpp"
    break;

  case 40: /* mtype_decl: T_MTYPE '=' '{' ident_list '}' ';'  */
#line 388 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2080 "build/parser.cpp"
    break;

  case 41: /* mtype_decl: T_MTYPE ':' IDENT '=' '{' ident_list '}' ';'  */
#line 395 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->set_name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2092 "build/parser.cpp"
    break;

  case 42: /* ident_list: IDENT  */
#line 406 "src/parser.y"
        {
            auto* il = new IdentList();
            il->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = il;
        }
#line 2103 "build/parser.cpp"
    break;

  case 43: /* ident_list: ident_list ',' IDENT  */
#line 413 "src/parser.y"
        {
            (yyvsp[-2].ident_list)->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = (yyvsp[-2].ident_list);
        }
#line 2113 "build/parser.cpp"
    break;

  case 44: /* ltl_decl: K_LTL IDENT '{' ltl_formula '}'  */
#line 423 "src/parser.y"
        {
            auto* l = new p2p::LtlDecl();
            l->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            l->formula.reset((yyvsp[-1].ltl));
            (yyval.node) = l;
        }
#line 2124 "build/parser.cpp"
    break;

  case 45: /* ltl_formula: ltl_unary  */
#line 436 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[0].ltl); }
#line 2130 "build/parser.cpp"
    break;

  case 46: /* ltl_formula: ltl_formula OP_AND ltl_formula  */
#line 438 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::And;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2141 "build/parser.cpp"
    break;

  case 47: /* ltl_formula: ltl_formula OP_OR ltl_formula  */
#line 445 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Or;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2152 "build/parser.cpp"
    break;

  case 48: /* ltl_formula: ltl_formula OP_ARROW ltl_formula  */
#line 452 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Implies;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2163 "build/parser.cpp"
    break;

  case 49: /* ltl_unary: LTL_ALWAYS ltl_unary  */
#line 462 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Always;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2174 "build/parser.cpp"
    break;

  case 50: /* ltl_unary: LTL_EVENTUALLY ltl_unary  */
#line 469 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Eventually;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2185 "build/parser.cpp"
    break;

  case 51: /* ltl_unary: '!' ltl_unary  */
#line 476 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Not;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2196 "build/parser.cpp"
    break;

  case 52: /* ltl_unary: '(' ltl_formula ')'  */
#line 482 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[-1].ltl); }
#line 2202 "build/parser.cpp"
    break;

  case 53: /* ltl_unary: ltl_atom  */
#line 484 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Atom;
            f->atom.reset((yyvsp[0].expr));
            (yyval.ltl) = f;
        }
#line 2213 "build/parser.cpp"
    break;

  case 54: /* ltl_atom: INT_LITERAL  */
#line 497 "src/parser.y"
                                        { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 2219 "build/parser.cpp"
    break;

  case 55: /* ltl_atom: K_TRUE  */
#line 498 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 2225 "build/parser.cpp"
    break;

  case 56: /* ltl_atom: K_FALSE  */
#line 499 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 2231 "build/parser.cpp"
    break;

  case 57: /* ltl_atom: IDENT  */
#line 500 "src/parser.y"
                                        {
                                          auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
                                          free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2241 "build/parser.cpp"
    break;

  case 58: /* ltl_atom: ltl_atom '[' ltl_atom ']'  */
#line 505 "src/parser.y"
                                        {
                                          auto* e = new p2p::IndexExpr();
                                          e->base.reset((yyvsp[-3].expr)); e->index.reset((yyvsp[-1].expr));
                                          (yyval.expr) = e;
                                        }
#line 2251 "build/parser.cpp"
    break;

  case 59: /* ltl_atom: ltl_atom '.' IDENT  */
#line 510 "src/parser.y"
                                        {
                                          auto* e = new p2p::FieldExpr();
                                          e->base.reset((yyvsp[-2].expr));
                                          e->field = (yyvsp[0].str_val); free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2262 "build/parser.cpp"
    break;

  case 60: /* ltl_atom: ltl_atom '+' ltl_atom  */
#line 516 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2268 "build/parser.cpp"
    break;

  case 61: /* ltl_atom: ltl_atom '-' ltl_atom  */
#line 517 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2274 "build/parser.cpp"
    break;

  case 62: /* ltl_atom: ltl_atom '*' ltl_atom  */
#line 518 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2280 "build/parser.cpp"
    break;

  case 63: /* ltl_atom: ltl_atom '/' ltl_atom  */
#line 519 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2286 "build/parser.cpp"
    break;

  case 64: /* ltl_atom: ltl_atom '%' ltl_atom  */
#line 520 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2292 "build/parser.cpp"
    break;

  case 65: /* ltl_atom: ltl_atom '<' ltl_atom  */
#line 521 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2298 "build/parser.cpp"
    break;

  case 66: /* ltl_atom: ltl_atom '>' ltl_atom  */
#line 522 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2304 "build/parser.cpp"
    break;

  case 67: /* ltl_atom: ltl_atom OP_LE ltl_atom  */
#line 523 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2310 "build/parser.cpp"
    break;

  case 68: /* ltl_atom: ltl_atom OP_GE ltl_atom  */
#line 524 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2316 "build/parser.cpp"
    break;

  case 69: /* ltl_atom: ltl_atom OP_EQ ltl_atom  */
#line 525 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2322 "build/parser.cpp"
    break;

  case 70: /* ltl_atom: ltl_atom OP_NEQ ltl_atom  */
#line 526 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2328 "build/parser.cpp"
    break;

  case 71: /* ltl_atom: '-' ltl_atom  */
#line 527 "src/parser.y"
                                        { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 2334 "build/parser.cpp"
    break;

  case 72: /* expr_body: expr ';'  */
#line 532 "src/parser.y"
                { g_expr_result = (yyvsp[-1].expr); }
#line 2340 "build/parser.cpp"
    break;

  case 73: /* expr: primary  */
#line 538 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 2346 "build/parser.cpp"
    break;

  case 74: /* expr: expr '+' expr  */
#line 539 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2352 "build/parser.cpp"
    break;

  case 75: /* expr: expr '-' expr  */
#line 540 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2358 "build/parser.cpp"
    break;

  case 76: /* expr: expr '*' expr  */
#line 541 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2364 "build/parser.cpp"
    break;

  case 77: /* expr: expr '/' expr  */
#line 542 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2370 "build/parser.cpp"
    break;

  case 78: /* expr: expr '%' expr  */
#line 543 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2376 "build/parser.cpp"
    break;

  case 79: /* expr: expr OP_SHL expr  */
#line 544 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2382 "build/parser.cpp"
    break;

  case 80: /* expr: expr OP_SHR expr  */
#line 545 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2388 "build/parser.cpp"
    break;

  case 81: /* expr: expr '<' expr  */
#line 546 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2394 "build/parser.cpp"
    break;

  case 82: /* expr: expr '>' expr  */
#line 547 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2400 "build/parser.cpp"
    break;

  case 83: /* expr: expr OP_LE expr  */
#line 548 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2406 "build/parser.cpp"
    break;

  case 84: /* expr: expr OP_GE expr  */
#line 549 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2412 "build/parser.cpp"
    break;

  case 85: /* expr: expr OP_EQ expr  */
#line 550 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2418 "build/parser.cpp"
    break;

  case 86: /* expr: expr OP_NEQ expr  */
#line 551 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2424 "build/parser.cpp"
    break;

  case 87: /* expr: expr OP_AND expr  */
#line 552 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2430 "build/parser.cpp"
    break;

  case 88: /* expr: expr OP_OR expr  */
#line 553 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Or,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2436 "build/parser.cpp"
    break;

  case 89: /* expr: '-' expr  */
#line 554 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 2442 "build/parser.cpp"
    break;

  case 90: /* expr: '!' expr  */
#line 555 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 2448 "build/parser.cpp"
    break;

  case 91: /* expr: expr OP_ARROW expr ':' expr  */
#line 556 "src/parser.y"
                                         {
                                            auto* t = new p2p::TernaryExpr();
                                            t->cond.reset((yyvsp[-4].expr));
                                            t->then_expr.reset((yyvsp[-2].expr));
                                            t->else_expr.reset((yyvsp[0].expr));
                                            (yyval.expr) = t;
                                          }
#line 2460 "build/parser.cpp"
    break;

  case 92: /* primary: INT_LITERAL  */
#line 566 "src/parser.y"
                           { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 2466 "build/parser.cpp"
    break;

  case 93: /* primary: K_TRUE  */
#line 567 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 2472 "build/parser.cpp"
    break;

  case 94: /* primary: K_FALSE  */
#line 568 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 2478 "build/parser.cpp"
    break;

  case 95: /* primary: IDENT  */
#line 569 "src/parser.y"
                           {
                              auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
                              free((yyvsp[0].str_val));
                              (yyval.expr) = e;
                           }
#line 2488 "build/parser.cpp"
    break;

  case 96: /* primary: '(' expr ')'  */
#line 574 "src/parser.y"
                           {
                              auto* p = new p2p::ParenExpr();
                              p->inner.reset((yyvsp[-1].expr));
                              (yyval.expr) = p;
                           }
#line 2498 "build/parser.cpp"
    break;

  case 97: /* primary: primary '[' expr ']'  */
#line 579 "src/parser.y"
                           {
                              auto* e = new p2p::IndexExpr();
                              e->base.reset((yyvsp[-3].expr));
                              e->index.reset((yyvsp[-1].expr));
                              (yyval.expr) = e;
                           }
#line 2509 "build/parser.cpp"
    break;

  case 98: /* primary: primary '.' IDENT  */
#line 585 "src/parser.y"
                           {
                              auto* e = new p2p::FieldExpr();
                              e->base.reset((yyvsp[-2].expr));
                              e->field = (yyvsp[0].str_val);
                              free((yyvsp[0].str_val));
                              (yyval.expr) = e;
                           }
#line 2521 "build/parser.cpp"
    break;

  case 99: /* primary: primary OP_INC  */
#line 592 "src/parser.y"
                            { (yyval.expr) = make_un(p2p::UnaryOp::PostInc, (yyvsp[-1].expr)); }
#line 2527 "build/parser.cpp"
    break;

  case 100: /* primary: primary OP_DEC  */
#line 593 "src/parser.y"
                            { (yyval.expr) = make_un(p2p::UnaryOp::PostDec, (yyvsp[-1].expr)); }
#line 2533 "build/parser.cpp"
    break;

  case 101: /* primary: OP_INC primary  */
#line 594 "src/parser.y"
                                                 { (yyval.expr) = make_un(p2p::UnaryOp::PreInc,  (yyvsp[0].expr)); }
#line 2539 "build/parser.cpp"
    break;

  case 102: /* primary: OP_DEC primary  */
#line 595 "src/parser.y"
                                                 { (yyval.expr) = make_un(p2p::UnaryOp::PreDec,  (yyvsp[0].expr)); }
#line 2545 "build/parser.cpp"
    break;

  case 103: /* primary: K_NEMPTY '(' expr ')'  */
#line 596 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nempty, (yyvsp[-1].expr)); }
#line 2551 "build/parser.cpp"
    break;

  case 104: /* primary: K_EMPTY '(' expr ')'  */
#line 597 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Empty,  (yyvsp[-1].expr)); }
#line 2557 "build/parser.cpp"
    break;

  case 105: /* primary: K_LEN '(' expr ')'  */
#line 598 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Len,    (yyvsp[-1].expr)); }
#line 2563 "build/parser.cpp"
    break;

  case 106: /* primary: K_FULL '(' expr ')'  */
#line 599 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Full,   (yyvsp[-1].expr)); }
#line 2569 "build/parser.cpp"
    break;

  case 107: /* primary: K_NFULL '(' expr ')'  */
#line 600 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nfull,  (yyvsp[-1].expr)); }
#line 2575 "build/parser.cpp"
    break;


#line 2579 "build/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 603 "src/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
