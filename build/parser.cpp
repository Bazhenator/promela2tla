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

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <memory>
    #include <string>
    #include <vector>
    #include "ast.h"

#line 75 "build/parser.cpp"



/* First part of user prologue.  */
#line 12 "src/parser.y"

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
   - PARSE_PROGRAM:    full file, top-level declarations.
   - PARSE_EXPR:       one expression followed by ';' (test mode).
   - PARSE_STMT_BLOCK: a block { stmt; stmt; ... } (test mode). */
int g_parse_mode = 0;
#define PARSE_PROGRAM     0
#define PARSE_EXPR        1
#define PARSE_STMT_BLOCK  2

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

/* Wrap a (possibly composite) expression into an ExprStmt. */
static p2p::Stmt* wrap_expr_stmt(p2p::Expr* e) {
    auto* s = new p2p::ExprStmt();
    s->expr.reset(e);
    return s;
}

#line 161 "build/parser.cpp"

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
  YYSYMBOL_START_STMT_BLOCK = 61,          /* START_STMT_BLOCK  */
  YYSYMBOL_62_ = 62,                       /* ':'  */
  YYSYMBOL_LOW_PREC = 63,                  /* LOW_PREC  */
  YYSYMBOL_64_ = 64,                       /* '='  */
  YYSYMBOL_65_ = 65,                       /* '!'  */
  YYSYMBOL_66_ = 66,                       /* '?'  */
  YYSYMBOL_67_ = 67,                       /* '<'  */
  YYSYMBOL_68_ = 68,                       /* '>'  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_73_ = 73,                       /* '%'  */
  YYSYMBOL_UMINUS = 74,                    /* UMINUS  */
  YYSYMBOL_UNOT = 75,                      /* UNOT  */
  YYSYMBOL_PREFIX_INCDEC = 76,             /* PREFIX_INCDEC  */
  YYSYMBOL_77_ = 77,                       /* '['  */
  YYSYMBOL_78_ = 78,                       /* '.'  */
  YYSYMBOL_79_ = 79,                       /* ';'  */
  YYSYMBOL_80_ = 80,                       /* ']'  */
  YYSYMBOL_81_ = 81,                       /* '{'  */
  YYSYMBOL_82_ = 82,                       /* '}'  */
  YYSYMBOL_83_ = 83,                       /* ','  */
  YYSYMBOL_84_ = 84,                       /* '('  */
  YYSYMBOL_85_ = 85,                       /* ')'  */
  YYSYMBOL_STMT_AFTER_DECL = 86,           /* STMT_AFTER_DECL  */
  YYSYMBOL_YYACCEPT = 87,                  /* $accept  */
  YYSYMBOL_start = 88,                     /* start  */
  YYSYMBOL_program_body = 89,              /* program_body  */
  YYSYMBOL_top_decl = 90,                  /* top_decl  */
  YYSYMBOL_var_decl_stmt = 91,             /* var_decl_stmt  */
  YYSYMBOL_chan_decl_stmt = 92,            /* chan_decl_stmt  */
  YYSYMBOL_chan_type = 93,                 /* chan_type  */
  YYSYMBOL_basic_type = 94,                /* basic_type  */
  YYSYMBOL_local_basic_type = 95,          /* local_basic_type  */
  YYSYMBOL_declarator_list = 96,           /* declarator_list  */
  YYSYMBOL_declarator = 97,                /* declarator  */
  YYSYMBOL_type_list = 98,                 /* type_list  */
  YYSYMBOL_typedef_decl = 99,              /* typedef_decl  */
  YYSYMBOL_field_decl_list = 100,          /* field_decl_list  */
  YYSYMBOL_field_decl_stmt = 101,          /* field_decl_stmt  */
  YYSYMBOL_field_decl_one_or_more = 102,   /* field_decl_one_or_more  */
  YYSYMBOL_field_one = 103,                /* field_one  */
  YYSYMBOL_mtype_decl = 104,               /* mtype_decl  */
  YYSYMBOL_ident_list = 105,               /* ident_list  */
  YYSYMBOL_ltl_decl = 106,                 /* ltl_decl  */
  YYSYMBOL_ltl_formula = 107,              /* ltl_formula  */
  YYSYMBOL_ltl_unary = 108,                /* ltl_unary  */
  YYSYMBOL_ltl_atom = 109,                 /* ltl_atom  */
  YYSYMBOL_expr_body = 110,                /* expr_body  */
  YYSYMBOL_stmt_body = 111,                /* stmt_body  */
  YYSYMBOL_stmt_block = 112,               /* stmt_block  */
  YYSYMBOL_stmt_seq = 113,                 /* stmt_seq  */
  YYSYMBOL_local_var_decl_stmt = 114,      /* local_var_decl_stmt  */
  YYSYMBOL_local_chan_decl_stmt = 115,     /* local_chan_decl_stmt  */
  YYSYMBOL_stmt = 116,                     /* stmt  */
  YYSYMBOL_assign_or_expr_stmt = 117,      /* assign_or_expr_stmt  */
  YYSYMBOL_simple_stmt = 118,              /* simple_stmt  */
  YYSYMBOL_if_stmt = 119,                  /* if_stmt  */
  YYSYMBOL_do_stmt = 120,                  /* do_stmt  */
  YYSYMBOL_branches = 121,                 /* branches  */
  YYSYMBOL_branch = 122,                   /* branch  */
  YYSYMBOL_atomic_stmt = 123,              /* atomic_stmt  */
  YYSYMBOL_dstep_stmt = 124,               /* dstep_stmt  */
  YYSYMBOL_for_stmt = 125,                 /* for_stmt  */
  YYSYMBOL_select_stmt = 126,              /* select_stmt  */
  YYSYMBOL_send_stmt = 127,                /* send_stmt  */
  YYSYMBOL_recv_stmt = 128,                /* recv_stmt  */
  YYSYMBOL_run_stmt = 129,                 /* run_stmt  */
  YYSYMBOL_break_stmt = 130,               /* break_stmt  */
  YYSYMBOL_skip_stmt = 131,                /* skip_stmt  */
  YYSYMBOL_goto_stmt = 132,                /* goto_stmt  */
  YYSYMBOL_expr_args = 133,                /* expr_args  */
  YYSYMBOL_expr_args_nonempty = 134,       /* expr_args_nonempty  */
  YYSYMBOL_expr = 135,                     /* expr  */
  YYSYMBOL_primary = 136                   /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 95 "src/parser.y"

    /* Helpers and globals that reference types defined in %code requires.
       Must live in %code (not %{...%}) so they appear after the type
       definitions in parser.cpp. */

    /* Outputs captured in test modes. */
    p2p::Expr*  g_expr_result = nullptr;
    StmtList*   g_stmt_result = nullptr;

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

    /* Wrap a list of VarDecls (the result of a "type d1, d2;" declaration)
       into a sequence of LocalVarDeclStmt nodes, appended to `out`. */
    static void wrap_local_decls(VarDeclList& list, StmtList& out) {
        for (auto& d : list.items) {
            auto* s = new p2p::LocalVarDeclStmt();
            s->decl = std::move(d);
            out.items.emplace_back(s);
        }
    }

#line 365 "build/parser.cpp"

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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1406

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  345

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
       2,     2,     2,    65,     2,     2,     2,    73,     2,     2,
      84,    85,    71,    69,    83,    70,    78,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    79,
      67,    64,    68,    66,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,     2,    82,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    63,    74,    75,
      76,    86
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   226,   226,   227,   228,   231,   233,   241,   242,   243,
     244,   245,   250,   261,   268,   286,   290,   291,   292,   293,
     294,   295,   296,   297,   304,   314,   315,   316,   317,   318,
     319,   320,   321,   331,   337,   345,   351,   358,   365,   376,
     382,   391,   402,   403,   412,   421,   427,   435,   441,   452,
     459,   470,   477,   487,   497,   498,   505,   512,   522,   529,
     536,   543,   544,   554,   555,   556,   557,   562,   567,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   589,   595,   596,   603,   607,   611,   621,   627,   632,
     637,   641,   645,   651,   657,   663,   669,   675,   682,   694,
     706,   717,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   769,   783,   791,   798,
     803,   814,   824,   831,   843,   851,   859,   867,   879,   889,
     900,   915,   927,   939,   953,   963,   964,   965,   975,   976,
     980,   986,   996,   997,   998,   999,  1000,  1001,  1002,  1003,
    1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,
    1014,  1025,  1026,  1027,  1028,  1034,  1040,  1047,  1055,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1063
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
  "LTL_UNTIL", "START_PROGRAM", "START_EXPR", "START_STMT_BLOCK", "':'",
  "LOW_PREC", "'='", "'!'", "'?'", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "UMINUS", "UNOT", "PREFIX_INCDEC", "'['", "'.'", "';'",
  "']'", "'{'", "'}'", "','", "'('", "')'", "STMT_AFTER_DECL", "$accept",
  "start", "program_body", "top_decl", "var_decl_stmt", "chan_decl_stmt",
  "chan_type", "basic_type", "local_basic_type", "declarator_list",
  "declarator", "type_list", "typedef_decl", "field_decl_list",
  "field_decl_stmt", "field_decl_one_or_more", "field_one", "mtype_decl",
  "ident_list", "ltl_decl", "ltl_formula", "ltl_unary", "ltl_atom",
  "expr_body", "stmt_body", "stmt_block", "stmt_seq",
  "local_var_decl_stmt", "local_chan_decl_stmt", "stmt",
  "assign_or_expr_stmt", "simple_stmt", "if_stmt", "do_stmt", "branches",
  "branch", "atomic_stmt", "dstep_stmt", "for_stmt", "select_stmt",
  "send_stmt", "recv_stmt", "run_stmt", "break_stmt", "skip_stmt",
  "goto_stmt", "expr_args", "expr_args_nonempty", "expr", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-223)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     126,  -223,     6,   274,     5,   394,  -223,  -223,   -71,   -63,
     -54,   -27,    27,  -223,  -223,    31,    31,     6,     6,     6,
    -223,  1105,   -14,   -47,  -223,  -223,  -223,  -223,  -223,  -223,
      57,  -223,    45,    45,  -223,   139,  -223,    97,    97,   100,
     148,   178,   342,   199,   201,  -223,  -223,   244,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  1299,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,    18,   230,   265,  -223,  -223,  -223,
     266,   201,  -223,  -223,  -223,     6,     6,     6,     6,     6,
     -14,   -14,  -223,  -223,   158,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,  -223,  -223,  -223,     6,   268,   669,     6,   270,   410,
      -8,  -223,    17,  -223,  -223,  -223,   271,   272,   164,  -223,
     116,   -41,   -53,   -21,  -223,   614,   546,   669,   669,     6,
       6,     6,   284,   176,   210,   222,    -9,     0,   674,   712,
     750,   788,   826,  -223,  1137,   719,  1333,   757,   757,   121,
     121,   167,   167,   121,   121,   173,   173,  -223,  -223,  -223,
     940,  -223,  -223,   228,   224,  1230,  -223,   275,   253,  -223,
    -223,  -223,   255,   257,     6,   478,  -223,   237,  -223,     6,
       6,  -223,   201,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    1307,   224,   224,   258,   320,   461,    88,   248,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,     6,  -223,  -223,     6,   546,
     546,     6,     6,   242,  -223,     6,  1230,   973,  -223,   247,
    -223,    72,   269,   326,    98,  -223,  -223,  -223,  -223,  -223,
      88,    88,    88,     4,    88,    11,  -223,  1268,     6,  1230,
    1230,   385,  1168,  1199,  -223,  1006,   273,   320,   254,   330,
     332,   261,   259,  -223,   461,   262,  -223,  -223,  -223,   119,
     -29,    88,    88,    88,  -223,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   336,  1039,   546,
       6,     6,   310,     6,   117,  -223,  -223,  -223,     6,   326,
    -223,  -223,  -223,   125,  -223,   308,    79,    79,    64,    64,
      64,    64,    93,    93,   119,   119,   119,  1237,  -223,   324,
     864,   902,   278,  1230,   281,  1072,  -223,  -223,   283,    97,
    -223,   461,  -223,  -223,   461,  -223,  -223,   133,   136,   286,
     461,   292,  -223,  -223,  -223
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     2,   161,   164,     0,     0,
       0,     0,     0,   162,   163,     0,     0,     0,     0,     0,
       3,     0,   142,   164,    25,    26,    27,    28,    29,    30,
      31,    15,     0,     0,   135,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     4,    82,    83,    90,    91,
      87,   119,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   118,     1,    24,    16,    17,
      18,    19,    20,    21,    22,     0,     0,     6,     7,     8,
       0,     0,     9,    10,    11,     0,     0,     0,     0,     0,
     170,   171,   159,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,   168,   169,     0,     0,     0,   138,     0,     0,
       0,   122,     0,   137,   128,   129,     0,     0,     0,    84,
       0,     0,    35,     0,    33,     0,     0,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,     0,   156,   157,   154,   155,   152,
     153,   148,   149,   150,   151,   143,   144,   145,   146,   147,
       0,   167,   115,     0,   139,   140,    32,     0,   124,   121,
     123,   120,     0,     0,   138,     0,    85,     0,   100,     0,
       0,    99,     0,    94,    89,    92,    93,    88,    97,    98,
     116,   132,   133,    23,     0,     0,     0,     0,    13,    12,
     174,   172,   173,   176,   175,     0,   166,   117,     0,     0,
     127,     0,     0,     0,    86,     0,    36,     0,    34,     0,
      51,     0,    22,     0,     0,    42,    63,    66,    64,    65,
       0,     0,     0,     0,     0,     0,    54,    62,     0,   160,
     141,   125,     0,     0,   134,     0,    37,     0,     0,     0,
       0,    47,    44,    45,     0,     0,    58,    59,    60,    80,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
       0,     0,     0,     0,     0,    49,    52,    23,     0,     0,
      43,    41,    61,    57,    55,    56,    78,    79,    76,    77,
      74,    75,    69,    70,    71,    72,    73,     0,    68,     0,
       0,     0,     0,    38,     0,     0,    46,    67,     0,     0,
     131,     0,    50,    48,     0,   130,    39,     0,     0,     0,
       0,     0,   101,    40,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,  -223,  -223,  -223,   357,    -5,  -223,   294,
     189,    48,  -223,  -223,   122,  -223,    86,  -223,   130,  -223,
    -222,    26,   252,  -223,  -223,   -35,   -38,   -18,   -16,  -110,
    -223,  -223,  -223,  -223,   375,    41,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,   225,    82,    -1,   226
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     4,     5,    77,    78,    79,    43,   233,    44,   133,
     134,   337,    82,   234,   235,   262,   263,    83,   231,    84,
     245,   246,   247,    20,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   120,   121,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,   173,   174,    65,    22
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    21,   124,   125,   130,    66,   172,   236,   237,     6,
       7,   189,   179,    85,   271,   116,    92,    93,    94,   272,
     273,    86,   270,   187,   190,   194,   197,   198,   199,   137,
      87,   138,   112,   113,     6,     7,   119,   117,   188,   181,
       8,     9,    10,    11,    12,   238,   239,    13,    14,   303,
     304,   305,    15,    16,   271,   207,   302,    88,   191,   272,
     273,   119,   192,   114,   115,     8,     9,    10,    11,    12,
     208,    17,    13,    14,   243,   197,    18,    15,    16,   209,
     142,   178,   143,   192,   148,   149,   150,   151,   152,   119,
      19,   236,   237,   274,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     197,    89,   137,   170,   138,    19,   175,   193,   195,   118,
     196,    24,    25,    26,    27,    28,    29,    30,    31,   238,
     239,   277,   278,   281,   282,   283,   284,   285,   200,   175,
     175,   286,   287,   123,   240,   241,   279,   280,   281,   282,
     283,   284,   285,   242,   258,   259,   286,   287,   243,   135,
     137,   180,   138,   180,   283,   284,   285,   195,   271,   196,
     286,   287,   244,   272,   273,   102,   103,   264,    42,   197,
     265,   251,   128,   175,   126,     1,     2,     3,   226,   227,
     106,   107,   108,   109,   110,   185,   286,   287,   186,   324,
     259,    95,   195,   131,   196,   132,    96,    97,    98,    99,
     100,   101,   102,   103,   249,   339,   340,   250,   341,   340,
     252,   253,   201,   202,   255,   104,   105,   106,   107,   108,
     109,   110,   127,   137,   144,   138,   106,   107,   108,   109,
     110,    90,    91,   153,   108,   109,   110,   288,   184,    24,
      25,    26,    27,    28,    29,    30,    31,   204,    24,    25,
      26,    27,    28,    29,    30,    31,   266,   267,   268,   145,
     146,   195,   171,   196,   176,   182,   183,     6,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   135,   203,   320,
     321,   205,   323,    32,   335,    33,   135,   325,    34,    35,
      36,    37,    38,   206,    39,    40,    41,   218,     8,     9,
      10,    11,    12,   217,   225,    13,    14,   221,   219,   222,
      15,    16,   229,   136,   230,   248,   336,   254,   257,   336,
     261,   260,   220,   295,   296,   343,   297,   293,   298,    17,
     318,   301,   299,   322,    18,     6,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    42,   272,   328,    19,   331,
     332,    32,    80,    33,   334,   342,    34,    35,    36,    37,
      38,   344,    39,    40,    41,   147,     8,     9,    10,    11,
      12,   228,   338,    13,    14,   326,   300,   294,    15,    16,
      24,    25,    26,    27,    28,    29,    30,    31,    67,    68,
      69,    70,    71,    72,    73,    74,    31,    17,   122,   223,
      75,    76,    18,     6,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,   129,     0,    19,     0,   135,    32,
       0,    33,     0,   177,    34,    35,    36,    37,    38,     0,
      39,    40,    41,     0,     8,     9,    10,    11,    12,     0,
       0,    13,    14,     0,     0,     0,    15,    16,     0,     0,
       0,     0,     0,     0,   289,    67,    68,    69,    70,    71,
      72,    73,   232,     0,     0,    17,     0,     0,     0,     0,
      18,     6,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,     0,     0,    19,   269,     0,    32,     0,    33,
       0,     0,    34,    35,    36,    37,    38,     0,    39,    40,
      41,     0,     8,     9,    10,    11,    12,     0,     0,    13,
      14,     0,     0,     0,    15,    16,     0,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,     0,
       0,     0,     0,    17,     0,     0,     0,     0,    18,     6,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
     224,     0,    19,     0,     0,    32,     0,    33,     0,     0,
      34,    35,    36,    37,    38,     0,    39,    40,    41,     0,
       8,     9,    10,    11,    12,     0,     0,    13,    14,     0,
       0,     0,    15,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,    18,     6,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,     0,
      19,     0,     0,    32,     0,    33,     0,     0,    34,    35,
      36,    37,    38,     0,    39,    40,    41,     0,     8,     9,
      10,    11,    12,     0,     0,    13,    14,     0,     0,     0,
      15,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,    23,     0,     0,     0,     0,     0,    17,
       0,     0,     0,     0,    18,     0,     0,     0,    32,     0,
      33,     0,     0,    34,    35,    36,    37,    38,    19,    39,
      40,    41,     0,     8,     9,    10,    11,    12,     0,     0,
      13,    14,     0,     0,     0,    15,    16,    95,     0,     0,
       0,     0,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,    17,     0,     0,     0,     0,    18,
       0,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,     0,    19,     0,    95,     0,     0,     0,   210,
      96,    97,    98,    99,   100,   101,   102,   103,     0,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,   104,
     105,   106,   107,   108,   109,   110,   104,   105,   106,   107,
     108,   109,   110,    95,     0,     0,     0,   211,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   100,
     101,   102,   103,     0,     0,     0,     0,   104,   105,   106,
     107,   108,   109,   110,   104,   105,   106,   107,   108,   109,
     110,    95,     0,     0,     0,   212,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,   213,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,   214,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,   329,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,   330,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,   105,   106,
     107,   108,   109,   110,     0,     0,    95,     0,     0,     0,
     216,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   105,   106,   107,   108,   109,   110,     0,     0,    95,
       0,     0,     0,   256,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,   105,   106,   107,   108,   109,   110,
       0,     0,    95,     0,     0,     0,   292,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,     0,     0,    95,     0,     0,     0,   319,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,   106,   107,   108,   109,   110,     0,     0,    95,     0,
       0,     0,   333,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,   105,   106,   107,   108,   109,   110,     0,
      95,     0,     0,     0,   111,    96,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,     0,   215,
       0,     0,     0,     0,   104,   105,   106,   107,   108,   109,
     110,    95,     0,   290,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,   106,   107,   108,
     109,   110,    95,     0,   291,     0,     0,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,     0,   275,   276,   277,
     278,     0,     0,     0,     0,     0,     0,   104,   105,   106,
     107,   108,   109,   110,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,   286,   287,     0,   327,   275,   276,
     277,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,     0,     0,     0,   286,   287,    96,    97,    98,
      99,   100,   101,   102,   103,    96,    97,    98,    99,   100,
     101,   102,   103,   139,   140,   141,   104,   105,   106,   107,
     108,   109,   110,     0,   104,   105,   106,   107,   108,   109,
     110,    96,     0,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   105,   106,   107,   108,   109,   110
};

static const yytype_int16 yycheck[] =
{
       5,     2,    37,    38,    42,     0,   116,     3,     4,     3,
       4,    64,    20,    84,    43,    62,    17,    18,    19,    48,
      49,    84,   244,    64,    77,   135,   136,   137,   138,    47,
      84,    47,    46,    47,     3,     4,    44,    84,    79,    22,
      34,    35,    36,    37,    38,    41,    42,    41,    42,   271,
     272,   273,    46,    47,    43,    64,    85,    84,    79,    48,
      49,    44,    83,    77,    78,    34,    35,    36,    37,    38,
      79,    65,    41,    42,    70,   185,    70,    46,    47,    79,
      62,   119,    64,    83,    85,    86,    87,    88,    89,    44,
      84,     3,     4,    82,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     220,    84,   130,   114,   130,    84,   117,   135,   136,    62,
     136,     5,     6,     7,     8,     9,    10,    11,    12,    41,
      42,    52,    53,    69,    70,    71,    72,    73,   139,   140,
     141,    77,    78,     4,    56,    57,    67,    68,    69,    70,
      71,    72,    73,    65,    82,    83,    77,    78,    70,    43,
     178,   120,   178,   122,    71,    72,    73,   185,    43,   185,
      77,    78,    84,    48,    49,    54,    55,    79,    81,   289,
      82,   219,     4,   184,    84,    59,    60,    61,   189,   190,
      69,    70,    71,    72,    73,    79,    77,    78,    82,    82,
      83,    43,   220,     4,   220,     4,    48,    49,    50,    51,
      52,    53,    54,    55,   215,    82,    83,   218,    82,    83,
     221,   222,   140,   141,   225,    67,    68,    69,    70,    71,
      72,    73,    84,   251,     4,   251,    69,    70,    71,    72,
      73,    15,    16,    85,    71,    72,    73,   248,    84,     5,
       6,     7,     8,     9,    10,    11,    12,    81,     5,     6,
       7,     8,     9,    10,    11,    12,   240,   241,   242,     4,
       4,   289,     4,   289,     4,     4,     4,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    43,     4,   290,
     291,    81,   293,    19,   329,    21,    43,   298,    24,    25,
      26,    27,    28,    81,    30,    31,    32,    83,    34,    35,
      36,    37,    38,    85,    77,    41,    42,    62,    43,    62,
      46,    47,    64,    79,     4,    77,   331,    85,    81,   334,
       4,    62,    79,    79,     4,   340,     4,    64,    77,    65,
       4,    79,    83,    33,    70,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    81,    48,    33,    84,    81,
      79,    19,     5,    21,    81,    79,    24,    25,    26,    27,
      28,    79,    30,    31,    32,    81,    34,    35,    36,    37,
      38,   192,   334,    41,    42,   299,   264,   257,    46,    47,
       5,     6,     7,     8,     9,    10,    11,    12,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    65,    33,   184,
      16,    17,    70,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    82,    -1,    84,    -1,    43,    19,
      -1,    21,    -1,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    41,    42,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    79,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      70,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    84,   243,    -1,    19,    -1,    21,
      -1,    -1,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    -1,    -1,    41,
      42,    -1,    -1,    -1,    46,    47,    -1,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    70,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      82,    -1,    84,    -1,    -1,    19,    -1,    21,    -1,    -1,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    41,    42,    -1,
      -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    70,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    19,    -1,    21,    -1,    -1,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    41,    42,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    19,    -1,
      21,    -1,    -1,    24,    25,    26,    27,    28,    84,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    42,    -1,    -1,    -1,    46,    47,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    70,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    43,    -1,    -1,    -1,    85,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    67,    68,    69,    70,
      71,    72,    73,    43,    -1,    -1,    -1,    85,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    67,    68,    69,    70,    71,    72,
      73,    43,    -1,    -1,    -1,    85,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    85,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    85,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    85,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    85,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    43,    -1,    -1,    -1,
      80,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    43,
      -1,    -1,    -1,    80,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    43,    -1,    -1,    -1,    80,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    43,    -1,    -1,    -1,    80,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    43,    -1,
      -1,    -1,    80,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      43,    -1,    -1,    -1,    79,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    43,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    43,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    43,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    50,    51,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    77,    78,    -1,    80,    50,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    77,    78,    48,    49,    50,
      51,    52,    53,    54,    55,    48,    49,    50,    51,    52,
      53,    54,    55,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    -1,    67,    68,    69,    70,    71,    72,
      73,    48,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    59,    60,    61,    88,    89,     3,     4,    34,    35,
      36,    37,    38,    41,    42,    46,    47,    65,    70,    84,
     110,   135,   136,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    19,    21,    24,    25,    26,    27,    28,    30,
      31,    32,    81,    93,    95,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   135,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    16,    17,    90,    91,    92,
      93,    94,    99,   104,   106,    84,    84,    84,    84,    84,
     136,   136,   135,   135,   135,    43,    48,    49,    50,    51,
      52,    53,    54,    55,    67,    68,    69,    70,    71,    72,
      73,    79,    46,    47,    77,    78,    62,    84,    62,    44,
     121,   122,   121,     4,   112,   112,    84,    84,     4,    82,
     113,     4,     4,    96,    97,    43,    79,   114,   115,    64,
      65,    66,    62,    64,     4,     4,     4,    96,   135,   135,
     135,   135,   135,    85,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,     4,   116,   133,   134,   135,     4,    23,   113,    20,
     122,    22,     4,     4,    84,    79,    82,    64,    79,    64,
      77,    79,    83,   114,   116,   114,   115,   116,   116,   116,
     135,   134,   134,     4,    81,    81,    81,    64,    79,    79,
      85,    85,    85,    85,    85,    62,    80,    85,    83,    43,
      79,    62,    62,   133,    82,    77,   135,   135,    97,    64,
       4,   105,    11,    94,   100,   101,     3,     4,    41,    42,
      56,    57,    65,    70,    84,   107,   108,   109,    77,   135,
     135,   113,   135,   135,    85,   135,    80,    81,    82,    83,
      62,     4,   102,   103,    79,    82,   108,   108,   108,   109,
     107,    43,    48,    49,    82,    50,    51,    52,    53,    67,
      68,    69,    70,    71,    72,    73,    77,    78,   135,    79,
      45,    45,    80,    64,   105,    79,     4,     4,    77,    83,
     101,    79,    85,   107,   107,   107,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,     4,    80,
     135,   135,    33,   135,    82,   135,   103,    80,    33,    85,
      85,    81,    79,    80,    81,   112,    94,    98,    98,    82,
      83,    82,    79,    94,    79
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    88,    88,    89,    89,    90,    90,    90,
      90,    90,    91,    92,    92,    93,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    97,    97,    98,
      98,    99,   100,   100,   101,   102,   102,   103,   103,   104,
     104,   105,   105,   106,   107,   107,   107,   107,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   111,   111,   112,   112,   112,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   117,   117,   118,
     119,   120,   121,   121,   122,   122,   122,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   133,
     134,   134,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     2,     1,     1,     1,
       1,     1,     3,     3,    11,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     4,     6,     1,
       3,     6,     1,     3,     2,     1,     3,     1,     4,     6,
       8,     1,     3,     5,     1,     3,     3,     3,     2,     2,
       2,     3,     1,     1,     1,     1,     1,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     2,     3,     4,     1,     3,     3,
       1,     1,     3,     3,     3,     2,     2,     3,     3,     3,
       3,    11,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     4,     1,     1,
       3,     3,     1,     2,     2,     4,     5,     3,     2,     2,
       9,     8,     3,     3,     5,     1,     1,     2,     0,     1,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       5,     1,     1,     1,     1,     3,     4,     3,     2,     2,
       2,     2,     4,     4,     4,     4,     4
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
#line 226 "src/parser.y"
                                       { if (!g_root) g_root = new p2p::Module(); }
#line 2045 "build/parser.cpp"
    break;

  case 6: /* program_body: program_body top_decl  */
#line 234 "src/parser.y"
        {
            if (!g_root) g_root = new p2p::Module();
            if ((yyvsp[0].node)) g_root->declarations.emplace_back((yyvsp[0].node));
        }
#line 2054 "build/parser.cpp"
    break;

  case 7: /* top_decl: var_decl_stmt  */
#line 241 "src/parser.y"
                           { push_decls(*(yyvsp[0].vardecl_list)); delete (yyvsp[0].vardecl_list); (yyval.node) = nullptr; }
#line 2060 "build/parser.cpp"
    break;

  case 8: /* top_decl: chan_decl_stmt  */
#line 242 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2066 "build/parser.cpp"
    break;

  case 9: /* top_decl: typedef_decl  */
#line 243 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2072 "build/parser.cpp"
    break;

  case 10: /* top_decl: mtype_decl  */
#line 244 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2078 "build/parser.cpp"
    break;

  case 11: /* top_decl: ltl_decl  */
#line 245 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2084 "build/parser.cpp"
    break;

  case 12: /* var_decl_stmt: basic_type declarator_list ';'  */
#line 251 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            (yyval.vardecl_list) = (yyvsp[-1].vardecl_list);
        }
#line 2094 "build/parser.cpp"
    break;

  case 13: /* chan_decl_stmt: chan_type IDENT ';'  */
#line 262 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-1].str_val); free((yyvsp[-1].str_val));
            d->type.reset((yyvsp[-2].type));
            (yyval.node) = d;
        }
#line 2105 "build/parser.cpp"
    break;

  case 14: /* chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 269 "src/parser.y"
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
#line 2124 "build/parser.cpp"
    break;

  case 15: /* chan_type: T_CHAN  */
#line 286 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Chan); }
#line 2130 "build/parser.cpp"
    break;

  case 16: /* basic_type: T_BYTE  */
#line 290 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2136 "build/parser.cpp"
    break;

  case 17: /* basic_type: T_INT  */
#line 291 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2142 "build/parser.cpp"
    break;

  case 18: /* basic_type: T_BOOL  */
#line 292 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2148 "build/parser.cpp"
    break;

  case 19: /* basic_type: T_BIT  */
#line 293 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2154 "build/parser.cpp"
    break;

  case 20: /* basic_type: T_SHORT  */
#line 294 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2160 "build/parser.cpp"
    break;

  case 21: /* basic_type: T_UNSIGNED  */
#line 295 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2166 "build/parser.cpp"
    break;

  case 22: /* basic_type: T_MTYPE  */
#line 296 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2172 "build/parser.cpp"
    break;

  case 23: /* basic_type: T_MTYPE ':' IDENT  */
#line 298 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2183 "build/parser.cpp"
    break;

  case 24: /* basic_type: IDENT  */
#line 304 "src/parser.y"
                           { (yyval.type) = make_named((yyvsp[0].str_val)); free((yyvsp[0].str_val)); }
#line 2189 "build/parser.cpp"
    break;

  case 25: /* local_basic_type: T_BYTE  */
#line 314 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2195 "build/parser.cpp"
    break;

  case 26: /* local_basic_type: T_INT  */
#line 315 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2201 "build/parser.cpp"
    break;

  case 27: /* local_basic_type: T_BOOL  */
#line 316 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2207 "build/parser.cpp"
    break;

  case 28: /* local_basic_type: T_BIT  */
#line 317 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2213 "build/parser.cpp"
    break;

  case 29: /* local_basic_type: T_SHORT  */
#line 318 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2219 "build/parser.cpp"
    break;

  case 30: /* local_basic_type: T_UNSIGNED  */
#line 319 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2225 "build/parser.cpp"
    break;

  case 31: /* local_basic_type: T_MTYPE  */
#line 320 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2231 "build/parser.cpp"
    break;

  case 32: /* local_basic_type: T_MTYPE ':' IDENT  */
#line 322 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2242 "build/parser.cpp"
    break;

  case 33: /* declarator_list: declarator  */
#line 332 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2252 "build/parser.cpp"
    break;

  case 34: /* declarator_list: declarator_list ',' declarator  */
#line 338 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2261 "build/parser.cpp"
    break;

  case 35: /* declarator: IDENT  */
#line 346 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2271 "build/parser.cpp"
    break;

  case 36: /* declarator: IDENT '=' expr  */
#line 352 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2282 "build/parser.cpp"
    break;

  case 37: /* declarator: IDENT '[' expr ']'  */
#line 359 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2293 "build/parser.cpp"
    break;

  case 38: /* declarator: IDENT '[' expr ']' '=' expr  */
#line 366 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            d->array_size.reset((yyvsp[-3].expr));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2305 "build/parser.cpp"
    break;

  case 39: /* type_list: basic_type  */
#line 377 "src/parser.y"
        {
            auto* tl = new TypeList();
            tl->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = tl;
        }
#line 2315 "build/parser.cpp"
    break;

  case 40: /* type_list: type_list ',' basic_type  */
#line 383 "src/parser.y"
        {
            (yyvsp[-2].type_list)->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = (yyvsp[-2].type_list);
        }
#line 2324 "build/parser.cpp"
    break;

  case 41: /* typedef_decl: K_TYPEDEF IDENT '{' field_decl_list '}' ';'  */
#line 392 "src/parser.y"
        {
            auto* td = new p2p::TypedefDecl();
            td->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            td->fields = std::move((yyvsp[-2].vardecl_list)->items);
            delete (yyvsp[-2].vardecl_list);
            (yyval.node) = td;
        }
#line 2336 "build/parser.cpp"
    break;

  case 42: /* field_decl_list: field_decl_stmt  */
#line 402 "src/parser.y"
                                               { (yyval.vardecl_list) = (yyvsp[0].vardecl_list); }
#line 2342 "build/parser.cpp"
    break;

  case 43: /* field_decl_list: field_decl_list ';' field_decl_stmt  */
#line 404 "src/parser.y"
        {
            for (auto& f : (yyvsp[0].vardecl_list)->items) (yyvsp[-2].vardecl_list)->items.emplace_back(std::move(f));
            delete (yyvsp[0].vardecl_list);
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2352 "build/parser.cpp"
    break;

  case 44: /* field_decl_stmt: basic_type field_decl_one_or_more  */
#line 413 "src/parser.y"
        {
            attach_type(*(yyvsp[0].vardecl_list), *(yyvsp[-1].type));
            delete (yyvsp[-1].type);
            (yyval.vardecl_list) = (yyvsp[0].vardecl_list);
        }
#line 2362 "build/parser.cpp"
    break;

  case 45: /* field_decl_one_or_more: field_one  */
#line 422 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2372 "build/parser.cpp"
    break;

  case 46: /* field_decl_one_or_more: field_decl_one_or_more ',' field_one  */
#line 428 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2381 "build/parser.cpp"
    break;

  case 47: /* field_one: IDENT  */
#line 436 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2391 "build/parser.cpp"
    break;

  case 48: /* field_one: IDENT '[' expr ']'  */
#line 442 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2402 "build/parser.cpp"
    break;

  case 49: /* mtype_decl: T_MTYPE '=' '{' ident_list '}' ';'  */
#line 453 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2413 "build/parser.cpp"
    break;

  case 50: /* mtype_decl: T_MTYPE ':' IDENT '=' '{' ident_list '}' ';'  */
#line 460 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->set_name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2425 "build/parser.cpp"
    break;

  case 51: /* ident_list: IDENT  */
#line 471 "src/parser.y"
        {
            auto* il = new IdentList();
            il->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = il;
        }
#line 2436 "build/parser.cpp"
    break;

  case 52: /* ident_list: ident_list ',' IDENT  */
#line 478 "src/parser.y"
        {
            (yyvsp[-2].ident_list)->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = (yyvsp[-2].ident_list);
        }
#line 2446 "build/parser.cpp"
    break;

  case 53: /* ltl_decl: K_LTL IDENT '{' ltl_formula '}'  */
#line 488 "src/parser.y"
        {
            auto* l = new p2p::LtlDecl();
            l->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            l->formula.reset((yyvsp[-1].ltl));
            (yyval.node) = l;
        }
#line 2457 "build/parser.cpp"
    break;

  case 54: /* ltl_formula: ltl_unary  */
#line 497 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[0].ltl); }
#line 2463 "build/parser.cpp"
    break;

  case 55: /* ltl_formula: ltl_formula OP_AND ltl_formula  */
#line 499 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::And;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2474 "build/parser.cpp"
    break;

  case 56: /* ltl_formula: ltl_formula OP_OR ltl_formula  */
#line 506 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Or;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2485 "build/parser.cpp"
    break;

  case 57: /* ltl_formula: ltl_formula OP_ARROW ltl_formula  */
#line 513 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Implies;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2496 "build/parser.cpp"
    break;

  case 58: /* ltl_unary: LTL_ALWAYS ltl_unary  */
#line 523 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Always;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2507 "build/parser.cpp"
    break;

  case 59: /* ltl_unary: LTL_EVENTUALLY ltl_unary  */
#line 530 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Eventually;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2518 "build/parser.cpp"
    break;

  case 60: /* ltl_unary: '!' ltl_unary  */
#line 537 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Not;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2529 "build/parser.cpp"
    break;

  case 61: /* ltl_unary: '(' ltl_formula ')'  */
#line 543 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[-1].ltl); }
#line 2535 "build/parser.cpp"
    break;

  case 62: /* ltl_unary: ltl_atom  */
#line 545 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Atom;
            f->atom.reset((yyvsp[0].expr));
            (yyval.ltl) = f;
        }
#line 2546 "build/parser.cpp"
    break;

  case 63: /* ltl_atom: INT_LITERAL  */
#line 554 "src/parser.y"
                                        { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 2552 "build/parser.cpp"
    break;

  case 64: /* ltl_atom: K_TRUE  */
#line 555 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 2558 "build/parser.cpp"
    break;

  case 65: /* ltl_atom: K_FALSE  */
#line 556 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 2564 "build/parser.cpp"
    break;

  case 66: /* ltl_atom: IDENT  */
#line 557 "src/parser.y"
                                        {
                                          auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
                                          free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2574 "build/parser.cpp"
    break;

  case 67: /* ltl_atom: ltl_atom '[' ltl_atom ']'  */
#line 562 "src/parser.y"
                                        {
                                          auto* e = new p2p::IndexExpr();
                                          e->base.reset((yyvsp[-3].expr)); e->index.reset((yyvsp[-1].expr));
                                          (yyval.expr) = e;
                                        }
#line 2584 "build/parser.cpp"
    break;

  case 68: /* ltl_atom: ltl_atom '.' IDENT  */
#line 567 "src/parser.y"
                                        {
                                          auto* e = new p2p::FieldExpr();
                                          e->base.reset((yyvsp[-2].expr));
                                          e->field = (yyvsp[0].str_val); free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2595 "build/parser.cpp"
    break;

  case 69: /* ltl_atom: ltl_atom '+' ltl_atom  */
#line 573 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2601 "build/parser.cpp"
    break;

  case 70: /* ltl_atom: ltl_atom '-' ltl_atom  */
#line 574 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2607 "build/parser.cpp"
    break;

  case 71: /* ltl_atom: ltl_atom '*' ltl_atom  */
#line 575 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2613 "build/parser.cpp"
    break;

  case 72: /* ltl_atom: ltl_atom '/' ltl_atom  */
#line 576 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2619 "build/parser.cpp"
    break;

  case 73: /* ltl_atom: ltl_atom '%' ltl_atom  */
#line 577 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2625 "build/parser.cpp"
    break;

  case 74: /* ltl_atom: ltl_atom '<' ltl_atom  */
#line 578 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2631 "build/parser.cpp"
    break;

  case 75: /* ltl_atom: ltl_atom '>' ltl_atom  */
#line 579 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2637 "build/parser.cpp"
    break;

  case 76: /* ltl_atom: ltl_atom OP_LE ltl_atom  */
#line 580 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2643 "build/parser.cpp"
    break;

  case 77: /* ltl_atom: ltl_atom OP_GE ltl_atom  */
#line 581 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2649 "build/parser.cpp"
    break;

  case 78: /* ltl_atom: ltl_atom OP_EQ ltl_atom  */
#line 582 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2655 "build/parser.cpp"
    break;

  case 79: /* ltl_atom: ltl_atom OP_NEQ ltl_atom  */
#line 583 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2661 "build/parser.cpp"
    break;

  case 80: /* ltl_atom: '-' ltl_atom  */
#line 584 "src/parser.y"
                                        { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 2667 "build/parser.cpp"
    break;

  case 81: /* expr_body: expr ';'  */
#line 589 "src/parser.y"
                { g_expr_result = (yyvsp[-1].expr); }
#line 2673 "build/parser.cpp"
    break;

  case 82: /* stmt_body: stmt_block  */
#line 595 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2679 "build/parser.cpp"
    break;

  case 83: /* stmt_body: stmt_seq  */
#line 596 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2685 "build/parser.cpp"
    break;

  case 84: /* stmt_block: '{' '}'  */
#line 604 "src/parser.y"
        {
            (yyval.stmt_list) = new StmtList();
        }
#line 2693 "build/parser.cpp"
    break;

  case 85: /* stmt_block: '{' stmt_seq '}'  */
#line 608 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 2701 "build/parser.cpp"
    break;

  case 86: /* stmt_block: '{' stmt_seq ';' '}'  */
#line 612 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2709 "build/parser.cpp"
    break;

  case 87: /* stmt_seq: stmt  */
#line 622 "src/parser.y"
        {
            auto* l = new StmtList();
            l->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = l;
        }
#line 2719 "build/parser.cpp"
    break;

  case 88: /* stmt_seq: stmt_seq ';' stmt  */
#line 628 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2728 "build/parser.cpp"
    break;

  case 89: /* stmt_seq: stmt_seq OP_ARROW stmt  */
#line 633 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2737 "build/parser.cpp"
    break;

  case 90: /* stmt_seq: local_var_decl_stmt  */
#line 638 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2745 "build/parser.cpp"
    break;

  case 91: /* stmt_seq: local_chan_decl_stmt  */
#line 642 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2753 "build/parser.cpp"
    break;

  case 92: /* stmt_seq: stmt_seq ';' local_var_decl_stmt  */
#line 646 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2763 "build/parser.cpp"
    break;

  case 93: /* stmt_seq: stmt_seq ';' local_chan_decl_stmt  */
#line 652 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2773 "build/parser.cpp"
    break;

  case 94: /* stmt_seq: stmt_seq OP_ARROW local_var_decl_stmt  */
#line 658 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2783 "build/parser.cpp"
    break;

  case 95: /* stmt_seq: stmt_seq local_var_decl_stmt  */
#line 664 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 2793 "build/parser.cpp"
    break;

  case 96: /* stmt_seq: stmt_seq local_chan_decl_stmt  */
#line 670 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 2803 "build/parser.cpp"
    break;

  case 97: /* stmt_seq: stmt_seq local_var_decl_stmt stmt  */
#line 676 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2814 "build/parser.cpp"
    break;

  case 98: /* stmt_seq: stmt_seq local_chan_decl_stmt stmt  */
#line 683 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2825 "build/parser.cpp"
    break;

  case 99: /* local_var_decl_stmt: local_basic_type declarator_list ';'  */
#line 695 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            auto* out = new StmtList();
            wrap_local_decls(*(yyvsp[-1].vardecl_list), *out);
            delete (yyvsp[-1].vardecl_list);
            (yyval.stmt_list) = out;
        }
#line 2838 "build/parser.cpp"
    break;

  case 100: /* local_chan_decl_stmt: chan_type IDENT ';'  */
#line 707 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-1].str_val); free((yyvsp[-1].str_val));
            d->type.reset((yyvsp[-2].type));
            auto* s = new p2p::LocalVarDeclStmt();
            s->decl.reset(d);
            auto* out = new StmtList();
            out->items.emplace_back(s);
            (yyval.stmt_list) = out;
        }
#line 2853 "build/parser.cpp"
    break;

  case 101: /* local_chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 718 "src/parser.y"
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
            auto* s = new p2p::LocalVarDeclStmt();
            s->decl.reset(d);
            auto* out = new StmtList();
            out->items.emplace_back(s);
            (yyval.stmt_list) = out;
        }
#line 2876 "build/parser.cpp"
    break;

  case 102: /* stmt: simple_stmt  */
#line 740 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2882 "build/parser.cpp"
    break;

  case 103: /* stmt: if_stmt  */
#line 741 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2888 "build/parser.cpp"
    break;

  case 104: /* stmt: do_stmt  */
#line 742 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2894 "build/parser.cpp"
    break;

  case 105: /* stmt: atomic_stmt  */
#line 743 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2900 "build/parser.cpp"
    break;

  case 106: /* stmt: dstep_stmt  */
#line 744 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2906 "build/parser.cpp"
    break;

  case 107: /* stmt: for_stmt  */
#line 745 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2912 "build/parser.cpp"
    break;

  case 108: /* stmt: select_stmt  */
#line 746 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2918 "build/parser.cpp"
    break;

  case 109: /* stmt: send_stmt  */
#line 747 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2924 "build/parser.cpp"
    break;

  case 110: /* stmt: recv_stmt  */
#line 748 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2930 "build/parser.cpp"
    break;

  case 111: /* stmt: run_stmt  */
#line 749 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2936 "build/parser.cpp"
    break;

  case 112: /* stmt: break_stmt  */
#line 750 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2942 "build/parser.cpp"
    break;

  case 113: /* stmt: skip_stmt  */
#line 751 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2948 "build/parser.cpp"
    break;

  case 114: /* stmt: goto_stmt  */
#line 752 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2954 "build/parser.cpp"
    break;

  case 115: /* stmt: IDENT ':' stmt  */
#line 754 "src/parser.y"
        {
            auto* l = new p2p::LabeledStmt();
            l->label = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            l->stmt.reset((yyvsp[0].stmt));
            (yyval.stmt) = l;
        }
#line 2965 "build/parser.cpp"
    break;

  case 116: /* assign_or_expr_stmt: expr '=' expr  */
#line 770 "src/parser.y"
        {
            if (!dynamic_cast<p2p::IdentExpr*>((yyvsp[-2].expr))
             && !dynamic_cast<p2p::IndexExpr*>((yyvsp[-2].expr))
             && !dynamic_cast<p2p::FieldExpr*>((yyvsp[-2].expr))) {
                yyerror("left side of '=' is not assignable");
                delete (yyvsp[-2].expr); delete (yyvsp[0].expr);
                YYERROR;
            }
            auto* a = new p2p::AssignStmt();
            a->lhs.reset((yyvsp[-2].expr));
            a->rhs.reset((yyvsp[0].expr));
            (yyval.stmt) = a;
        }
#line 2983 "build/parser.cpp"
    break;

  case 117: /* assign_or_expr_stmt: IDENT '(' expr_args ')'  */
#line 784 "src/parser.y"
        {
            auto* c = new p2p::InlineCallStmt();
            c->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            c->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = c;
        }
#line 2995 "build/parser.cpp"
    break;

  case 118: /* assign_or_expr_stmt: expr  */
#line 792 "src/parser.y"
        {
            (yyval.stmt) = wrap_expr_stmt((yyvsp[0].expr));
        }
#line 3003 "build/parser.cpp"
    break;

  case 119: /* simple_stmt: assign_or_expr_stmt  */
#line 798 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3009 "build/parser.cpp"
    break;

  case 120: /* if_stmt: K_IF branches K_FI  */
#line 804 "src/parser.y"
        {
            auto* s = new p2p::IfStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3020 "build/parser.cpp"
    break;

  case 121: /* do_stmt: K_DO branches K_OD  */
#line 815 "src/parser.y"
        {
            auto* s = new p2p::DoStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3031 "build/parser.cpp"
    break;

  case 122: /* branches: branch  */
#line 825 "src/parser.y"
        {
            auto* l = new BranchList();
            l->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = l;
        }
#line 3042 "build/parser.cpp"
    break;

  case 123: /* branches: branches branch  */
#line 832 "src/parser.y"
        {
            (yyvsp[-1].branch_list)->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = (yyvsp[-1].branch_list);
        }
#line 3052 "build/parser.cpp"
    break;

  case 124: /* branch: OP_DCOLON stmt_seq  */
#line 844 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3064 "build/parser.cpp"
    break;

  case 125: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq  */
#line 852 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3076 "build/parser.cpp"
    break;

  case 126: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq ';'  */
#line 860 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3088 "build/parser.cpp"
    break;

  case 127: /* branch: OP_DCOLON stmt_seq ';'  */
#line 868 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3100 "build/parser.cpp"
    break;

  case 128: /* atomic_stmt: K_ATOMIC stmt_block  */
#line 880 "src/parser.y"
        {
            auto* s = new p2p::AtomicStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3111 "build/parser.cpp"
    break;

  case 129: /* dstep_stmt: K_D_STEP stmt_block  */
#line 890 "src/parser.y"
        {
            auto* s = new p2p::DStepStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3122 "build/parser.cpp"
    break;

  case 130: /* for_stmt: K_FOR '(' IDENT ':' expr OP_DOTDOT expr ')' stmt_block  */
#line 901 "src/parser.y"
        {
            auto* s = new p2p::ForStmt();
            s->var = (yyvsp[-6].str_val); free((yyvsp[-6].str_val));
            s->low.reset((yyvsp[-4].expr));
            s->high.reset((yyvsp[-2].expr));
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3136 "build/parser.cpp"
    break;

  case 131: /* select_stmt: K_SELECT '(' IDENT ':' expr OP_DOTDOT expr ')'  */
#line 916 "src/parser.y"
        {
            auto* s = new p2p::SelectStmt();
            s->var = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            s->low.reset((yyvsp[-3].expr));
            s->high.reset((yyvsp[-1].expr));
            (yyval.stmt) = s;
        }
#line 3148 "build/parser.cpp"
    break;

  case 132: /* send_stmt: expr '!' expr_args_nonempty  */
#line 928 "src/parser.y"
        {
            auto* s = new p2p::SendStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3160 "build/parser.cpp"
    break;

  case 133: /* recv_stmt: expr '?' expr_args_nonempty  */
#line 940 "src/parser.y"
        {
            auto* s = new p2p::RecvStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3172 "build/parser.cpp"
    break;

  case 134: /* run_stmt: K_RUN IDENT '(' expr_args ')'  */
#line 954 "src/parser.y"
        {
            auto* s = new p2p::RunStmt();
            s->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            s->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = s;
        }
#line 3184 "build/parser.cpp"
    break;

  case 135: /* break_stmt: K_BREAK  */
#line 963 "src/parser.y"
                            { (yyval.stmt) = new p2p::BreakStmt(); }
#line 3190 "build/parser.cpp"
    break;

  case 136: /* skip_stmt: K_SKIP  */
#line 964 "src/parser.y"
                            { (yyval.stmt) = new p2p::SkipStmt(); }
#line 3196 "build/parser.cpp"
    break;

  case 137: /* goto_stmt: K_GOTO IDENT  */
#line 966 "src/parser.y"
        {
            auto* g = new p2p::GotoStmt();
            g->label = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.stmt) = g;
        }
#line 3206 "build/parser.cpp"
    break;

  case 138: /* expr_args: %empty  */
#line 975 "src/parser.y"
                                        { (yyval.expr_list) = new ExprList(); }
#line 3212 "build/parser.cpp"
    break;

  case 139: /* expr_args: expr_args_nonempty  */
#line 976 "src/parser.y"
                                        { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 3218 "build/parser.cpp"
    break;

  case 140: /* expr_args_nonempty: expr  */
#line 981 "src/parser.y"
        {
            auto* l = new ExprList();
            l->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = l;
        }
#line 3228 "build/parser.cpp"
    break;

  case 141: /* expr_args_nonempty: expr_args_nonempty ',' expr  */
#line 987 "src/parser.y"
        {
            (yyvsp[-2].expr_list)->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = (yyvsp[-2].expr_list);
        }
#line 3237 "build/parser.cpp"
    break;

  case 142: /* expr: primary  */
#line 996 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 3243 "build/parser.cpp"
    break;

  case 143: /* expr: expr '+' expr  */
#line 997 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3249 "build/parser.cpp"
    break;

  case 144: /* expr: expr '-' expr  */
#line 998 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3255 "build/parser.cpp"
    break;

  case 145: /* expr: expr '*' expr  */
#line 999 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3261 "build/parser.cpp"
    break;

  case 146: /* expr: expr '/' expr  */
#line 1000 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3267 "build/parser.cpp"
    break;

  case 147: /* expr: expr '%' expr  */
#line 1001 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3273 "build/parser.cpp"
    break;

  case 148: /* expr: expr OP_SHL expr  */
#line 1002 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3279 "build/parser.cpp"
    break;

  case 149: /* expr: expr OP_SHR expr  */
#line 1003 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3285 "build/parser.cpp"
    break;

  case 150: /* expr: expr '<' expr  */
#line 1004 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3291 "build/parser.cpp"
    break;

  case 151: /* expr: expr '>' expr  */
#line 1005 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3297 "build/parser.cpp"
    break;

  case 152: /* expr: expr OP_LE expr  */
#line 1006 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3303 "build/parser.cpp"
    break;

  case 153: /* expr: expr OP_GE expr  */
#line 1007 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3309 "build/parser.cpp"
    break;

  case 154: /* expr: expr OP_EQ expr  */
#line 1008 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3315 "build/parser.cpp"
    break;

  case 155: /* expr: expr OP_NEQ expr  */
#line 1009 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3321 "build/parser.cpp"
    break;

  case 156: /* expr: expr OP_AND expr  */
#line 1010 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3327 "build/parser.cpp"
    break;

  case 157: /* expr: expr OP_OR expr  */
#line 1011 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Or,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3333 "build/parser.cpp"
    break;

  case 158: /* expr: '-' expr  */
#line 1012 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 3339 "build/parser.cpp"
    break;

  case 159: /* expr: '!' expr  */
#line 1013 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 3345 "build/parser.cpp"
    break;

  case 160: /* expr: expr OP_ARROW expr ':' expr  */
#line 1015 "src/parser.y"
        {
            auto* t = new p2p::TernaryExpr();
            t->cond.reset((yyvsp[-4].expr));
            t->then_expr.reset((yyvsp[-2].expr));
            t->else_expr.reset((yyvsp[0].expr));
            (yyval.expr) = t;
        }
#line 3357 "build/parser.cpp"
    break;

  case 161: /* primary: INT_LITERAL  */
#line 1025 "src/parser.y"
                           { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 3363 "build/parser.cpp"
    break;

  case 162: /* primary: K_TRUE  */
#line 1026 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 3369 "build/parser.cpp"
    break;

  case 163: /* primary: K_FALSE  */
#line 1027 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 3375 "build/parser.cpp"
    break;

  case 164: /* primary: IDENT  */
#line 1029 "src/parser.y"
        {
            auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3385 "build/parser.cpp"
    break;

  case 165: /* primary: '(' expr ')'  */
#line 1035 "src/parser.y"
        {
            auto* p = new p2p::ParenExpr();
            p->inner.reset((yyvsp[-1].expr));
            (yyval.expr) = p;
        }
#line 3395 "build/parser.cpp"
    break;

  case 166: /* primary: primary '[' expr ']'  */
#line 1041 "src/parser.y"
        {
            auto* e = new p2p::IndexExpr();
            e->base.reset((yyvsp[-3].expr));
            e->index.reset((yyvsp[-1].expr));
            (yyval.expr) = e;
        }
#line 3406 "build/parser.cpp"
    break;

  case 167: /* primary: primary '.' IDENT  */
#line 1048 "src/parser.y"
        {
            auto* e = new p2p::FieldExpr();
            e->base.reset((yyvsp[-2].expr));
            e->field = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3418 "build/parser.cpp"
    break;

  case 168: /* primary: primary OP_INC  */
#line 1055 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostInc, (yyvsp[-1].expr)); }
#line 3424 "build/parser.cpp"
    break;

  case 169: /* primary: primary OP_DEC  */
#line 1056 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostDec, (yyvsp[-1].expr)); }
#line 3430 "build/parser.cpp"
    break;

  case 170: /* primary: OP_INC primary  */
#line 1057 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreInc,  (yyvsp[0].expr)); }
#line 3436 "build/parser.cpp"
    break;

  case 171: /* primary: OP_DEC primary  */
#line 1058 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreDec,  (yyvsp[0].expr)); }
#line 3442 "build/parser.cpp"
    break;

  case 172: /* primary: K_NEMPTY '(' expr ')'  */
#line 1059 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nempty, (yyvsp[-1].expr)); }
#line 3448 "build/parser.cpp"
    break;

  case 173: /* primary: K_EMPTY '(' expr ')'  */
#line 1060 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Empty,  (yyvsp[-1].expr)); }
#line 3454 "build/parser.cpp"
    break;

  case 174: /* primary: K_LEN '(' expr ')'  */
#line 1061 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Len,    (yyvsp[-1].expr)); }
#line 3460 "build/parser.cpp"
    break;

  case 175: /* primary: K_FULL '(' expr ')'  */
#line 1062 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Full,   (yyvsp[-1].expr)); }
#line 3466 "build/parser.cpp"
    break;

  case 176: /* primary: K_NFULL '(' expr ')'  */
#line 1063 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nfull,  (yyvsp[-1].expr)); }
#line 3472 "build/parser.cpp"
    break;


#line 3476 "build/parser.cpp"

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

#line 1066 "src/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
