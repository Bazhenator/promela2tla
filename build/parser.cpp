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

extern int yylex_raw();
int yylex();  /* defined below for ASI */
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

#line 162 "build/parser.cpp"

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
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_start = 87,                     /* start  */
  YYSYMBOL_program_body = 88,              /* program_body  */
  YYSYMBOL_top_decl = 89,                  /* top_decl  */
  YYSYMBOL_var_decl_stmt = 90,             /* var_decl_stmt  */
  YYSYMBOL_chan_decl_stmt = 91,            /* chan_decl_stmt  */
  YYSYMBOL_chan_type = 92,                 /* chan_type  */
  YYSYMBOL_basic_type = 93,                /* basic_type  */
  YYSYMBOL_local_basic_type = 94,          /* local_basic_type  */
  YYSYMBOL_declarator_list = 95,           /* declarator_list  */
  YYSYMBOL_declarator = 96,                /* declarator  */
  YYSYMBOL_type_list = 97,                 /* type_list  */
  YYSYMBOL_typedef_decl = 98,              /* typedef_decl  */
  YYSYMBOL_field_decl_list = 99,           /* field_decl_list  */
  YYSYMBOL_field_decl_stmt = 100,          /* field_decl_stmt  */
  YYSYMBOL_field_decl_one_or_more = 101,   /* field_decl_one_or_more  */
  YYSYMBOL_field_one = 102,                /* field_one  */
  YYSYMBOL_mtype_decl = 103,               /* mtype_decl  */
  YYSYMBOL_ident_list = 104,               /* ident_list  */
  YYSYMBOL_ltl_decl = 105,                 /* ltl_decl  */
  YYSYMBOL_ltl_formula = 106,              /* ltl_formula  */
  YYSYMBOL_ltl_unary = 107,                /* ltl_unary  */
  YYSYMBOL_ltl_atom = 108,                 /* ltl_atom  */
  YYSYMBOL_proctype_decl = 109,            /* proctype_decl  */
  YYSYMBOL_inline_decl = 110,              /* inline_decl  */
  YYSYMBOL_init_decl = 111,                /* init_decl  */
  YYSYMBOL_params_opt = 112,               /* params_opt  */
  YYSYMBOL_param_list = 113,               /* param_list  */
  YYSYMBOL_param_group = 114,              /* param_group  */
  YYSYMBOL_ident_list_opt = 115,           /* ident_list_opt  */
  YYSYMBOL_expr_body = 116,                /* expr_body  */
  YYSYMBOL_stmt_body = 117,                /* stmt_body  */
  YYSYMBOL_stmt_block = 118,               /* stmt_block  */
  YYSYMBOL_stmt_seq = 119,                 /* stmt_seq  */
  YYSYMBOL_local_var_decl_stmt = 120,      /* local_var_decl_stmt  */
  YYSYMBOL_local_chan_decl_stmt = 121,     /* local_chan_decl_stmt  */
  YYSYMBOL_stmt = 122,                     /* stmt  */
  YYSYMBOL_assign_or_expr_stmt = 123,      /* assign_or_expr_stmt  */
  YYSYMBOL_simple_stmt = 124,              /* simple_stmt  */
  YYSYMBOL_if_stmt = 125,                  /* if_stmt  */
  YYSYMBOL_do_stmt = 126,                  /* do_stmt  */
  YYSYMBOL_branches = 127,                 /* branches  */
  YYSYMBOL_branch = 128,                   /* branch  */
  YYSYMBOL_atomic_stmt = 129,              /* atomic_stmt  */
  YYSYMBOL_dstep_stmt = 130,               /* dstep_stmt  */
  YYSYMBOL_for_stmt = 131,                 /* for_stmt  */
  YYSYMBOL_select_stmt = 132,              /* select_stmt  */
  YYSYMBOL_send_stmt = 133,                /* send_stmt  */
  YYSYMBOL_recv_stmt = 134,                /* recv_stmt  */
  YYSYMBOL_run_stmt = 135,                 /* run_stmt  */
  YYSYMBOL_break_stmt = 136,               /* break_stmt  */
  YYSYMBOL_skip_stmt = 137,                /* skip_stmt  */
  YYSYMBOL_goto_stmt = 138,                /* goto_stmt  */
  YYSYMBOL_expr_args = 139,                /* expr_args  */
  YYSYMBOL_expr_args_nonempty = 140,       /* expr_args_nonempty  */
  YYSYMBOL_expr = 141,                     /* expr  */
  YYSYMBOL_expr_no_ternary = 142,          /* expr_no_ternary  */
  YYSYMBOL_primary = 143                   /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 96 "src/parser.y"

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

#line 373 "build/parser.cpp"

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
#define YYLAST   1517

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  211
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  423

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
      76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   230,   230,   231,   232,   235,   237,   245,   246,   247,
     248,   249,   250,   251,   252,   257,   268,   275,   293,   297,
     298,   299,   300,   301,   302,   303,   304,   311,   321,   322,
     323,   324,   325,   326,   327,   328,   338,   344,   352,   358,
     365,   372,   383,   389,   398,   409,   410,   419,   428,   434,
     442,   448,   459,   466,   477,   484,   494,   504,   505,   512,
     519,   529,   536,   543,   550,   551,   561,   562,   563,   564,
     569,   574,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   601,   611,   622,   638,   657,   670,
     671,   675,   676,   686,   699,   716,   717,   722,   728,   729,
     736,   738,   740,   749,   755,   759,   763,   768,   773,   779,
     785,   791,   798,   804,   811,   818,   830,   842,   853,   876,
     877,   878,   879,   880,   881,   882,   883,   884,   885,   886,
     887,   888,   889,   905,   919,   927,   934,   939,   950,   960,
     967,   979,   987,   995,  1003,  1015,  1025,  1036,  1051,  1063,
    1075,  1089,  1099,  1100,  1101,  1111,  1112,  1116,  1122,  1132,
    1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1165,  1166,
    1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,
    1177,  1178,  1179,  1180,  1181,  1182,  1186,  1187,  1188,  1189,
    1195,  1201,  1208,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,  1224
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
  "']'", "'{'", "'}'", "','", "'('", "')'", "$accept", "start",
  "program_body", "top_decl", "var_decl_stmt", "chan_decl_stmt",
  "chan_type", "basic_type", "local_basic_type", "declarator_list",
  "declarator", "type_list", "typedef_decl", "field_decl_list",
  "field_decl_stmt", "field_decl_one_or_more", "field_one", "mtype_decl",
  "ident_list", "ltl_decl", "ltl_formula", "ltl_unary", "ltl_atom",
  "proctype_decl", "inline_decl", "init_decl", "params_opt", "param_list",
  "param_group", "ident_list_opt", "expr_body", "stmt_body", "stmt_block",
  "stmt_seq", "local_var_decl_stmt", "local_chan_decl_stmt", "stmt",
  "assign_or_expr_stmt", "simple_stmt", "if_stmt", "do_stmt", "branches",
  "branch", "atomic_stmt", "dstep_stmt", "for_stmt", "select_stmt",
  "send_stmt", "recv_stmt", "run_stmt", "break_stmt", "skip_stmt",
  "goto_stmt", "expr_args", "expr_args_nonempty", "expr",
  "expr_no_ternary", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-276)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,  -276,   654,   163,    39,  1499,  -276,  -276,   -74,   -21,
      19,    40,    65,  -276,  -276,    37,    37,   654,   654,   654,
    -276,  1167,   -10,   -40,  -276,  -276,  -276,  -276,  -276,  -276,
      38,  -276,    26,    26,  -276,   130,  -276,    73,    73,    74,
      95,   182,   410,   192,   204,  -276,  -276,   380,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  1361,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,    69,   212,    -1,   217,   227,   237,
      73,  -276,  -276,  -276,   239,   204,  -276,  -276,  -276,  -276,
    -276,  -276,   654,   654,   654,   654,   654,   -10,   -10,  -276,
    -276,    92,   654,   654,   654,   654,   654,   654,   654,   654,
     654,   654,   654,   654,   654,   654,   654,   654,  -276,  -276,
    -276,   654,   244,   288,   669,   255,   478,   -11,  -276,    25,
    -276,  -276,  -276,   268,   286,   210,  -276,    50,   -41,   -46,
     -37,  -276,   614,   614,   288,   288,   654,   669,   669,   304,
     236,   257,   324,   335,   259,   258,   273,  -276,   -36,    -2,
     736,   774,   812,   850,   888,  -276,  1199,   743,  1403,   819,
     819,   180,   180,    16,    16,   180,   180,    80,    80,  -276,
    -276,  -276,  1002,  -276,  -276,   669,   669,   270,   276,  1369,
     -10,  -276,   319,   455,  -276,  -276,  -276,   302,   303,   669,
     546,  -276,   289,  -276,   654,   654,  -276,   204,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  1395,   276,   276,   306,
     363,   294,   284,   291,   363,   531,   341,   297,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,   654,  -276,  -276,  -276,  -276,
     669,   669,   669,   669,   669,   669,   669,   669,   669,   669,
     669,   669,   669,   669,   669,   669,   614,   614,   654,   654,
     290,  -276,   654,  1292,  1035,  -276,   295,  -276,     8,   315,
     363,   363,   293,   301,  -276,   294,   368,   310,   299,   390,
      20,  -276,  -276,  -276,  -276,  -276,   341,   341,   341,    10,
     341,   -32,  -276,  1330,   654,  1292,  1369,   781,  1429,   857,
     857,   399,   399,   142,   142,   399,   399,   194,   194,  -276,
    -276,  -276,   521,  1230,  1261,  -276,  1068,   332,   363,   320,
     396,   398,   310,   310,    73,   294,   318,   400,    73,   330,
     325,  -276,   531,   331,  -276,  -276,  -276,   125,   107,   341,
     341,   341,  -276,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,   405,  1101,   614,   654,   654,
     391,   654,   144,  -276,  -276,  -276,  -276,  -276,    73,   342,
    -276,   654,   390,  -276,  -276,  -276,   -14,  -276,   379,   279,
     279,   185,   185,   185,   185,   152,   152,   125,   125,   125,
    1299,  -276,   395,   926,   964,   349,  1292,   353,  -276,   294,
    1134,  -276,  -276,   352,    73,  -276,   531,  -276,   354,  -276,
     531,  -276,  -276,   228,    73,   254,   364,   531,  -276,   370,
    -276,  -276,  -276
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     2,   196,   199,     0,     0,
       0,     0,     0,   197,   198,     0,     0,     0,     0,     0,
       3,     0,   159,   199,    28,    29,    30,    31,    32,    33,
      34,    18,     0,     0,   152,     0,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     4,    98,    99,   104,   105,
     103,   136,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   135,     1,    27,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     6,     7,     8,     0,     0,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,   205,   206,   176,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,   203,
     204,     0,     0,     0,   155,     0,     0,     0,   139,     0,
     154,   145,   146,     0,     0,     0,   100,     0,     0,    38,
       0,    36,     0,     0,   112,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,     0,   200,     0,   173,   174,   171,
     172,   169,   170,   165,   166,   167,   168,   160,   161,   162,
     163,   164,     0,   202,   132,     0,     0,     0,   156,   157,
     178,    35,     0,   141,   138,   140,   137,     0,     0,   155,
       0,   101,     0,   117,     0,     0,   116,     0,   110,   111,
     107,   108,   109,   106,   114,   115,   133,   149,   150,    26,
       0,    89,     0,     0,    95,     0,     0,     0,    16,    15,
     209,   207,   208,   211,   210,     0,   201,   195,   194,   134,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   144,     0,     0,
       0,   102,     0,    39,     0,    37,     0,    54,     0,    25,
       0,     0,     0,    90,    91,    89,     0,    96,     0,     0,
       0,    45,    66,    69,    67,    68,     0,     0,     0,     0,
       0,     0,    57,    65,     0,   177,   158,   192,   193,   190,
     191,   188,   189,   184,   185,   186,   187,   179,   180,   181,
     182,   183,   142,     0,     0,   151,     0,    40,     0,     0,
       0,     0,    94,    93,     0,     0,     0,     0,     0,    50,
      47,    48,     0,     0,    61,    62,    63,    83,     0,     0,
       0,     0,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   143,     0,     0,
       0,     0,     0,    52,    55,    26,    84,    92,     0,     0,
      87,     0,     0,    46,    44,    64,    60,    58,    59,    81,
      82,    79,    80,    77,    78,    72,    73,    74,    75,    76,
       0,    71,     0,     0,     0,     0,    41,     0,    85,    89,
       0,    49,    70,     0,     0,   148,     0,    53,     0,    51,
       0,   147,    42,     0,     0,     0,     0,     0,    86,     0,
     118,    43,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -276,  -276,  -276,  -276,  -276,  -276,    -4,    -5,  -276,   365,
     248,    48,  -276,  -276,   141,  -276,   102,  -276,  -217,  -276,
    -275,   -18,   397,  -276,  -276,  -276,  -269,  -276,   151,  -276,
    -276,  -276,   -35,   -34,   -17,   -15,  -118,  -276,  -276,  -276,
    -276,   444,   109,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,   280,    98,     2,   523,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     4,     5,    81,    82,    83,    43,   271,    44,   140,
     141,   413,    86,   280,   281,   330,   331,    87,   268,    88,
     291,   292,   293,    89,    90,    91,   272,   273,   274,   278,
      20,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   127,   128,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,   187,   188,    65,   189,    22
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,    84,   131,   132,    21,   184,   326,   277,   137,   194,
      92,   339,   152,   282,   283,   338,   340,   341,   204,    99,
     100,   101,   123,   202,   210,   213,   214,   215,   227,   339,
     144,   205,   145,   126,   340,   341,   119,   120,   203,    66,
       6,     7,   206,   228,   124,   157,   207,   196,    97,    98,
     342,   284,   285,   322,   323,    24,    25,    26,    27,    28,
      29,    30,    31,    93,   376,   377,   378,   121,   122,   126,
     126,     8,     9,    10,    11,    12,   153,   229,    13,    14,
     289,   207,   213,    15,    16,   113,   114,   115,   116,   117,
     319,   320,   193,   142,   160,   161,   162,   163,   164,   332,
     125,   362,   333,    94,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     144,    19,   145,   182,    95,   208,   211,   209,   212,   200,
     408,   149,   201,   150,   130,   102,     1,     2,     3,   213,
     103,   104,   105,   106,   107,   108,   109,   110,   216,    96,
     339,   115,   116,   117,    42,   340,   341,   190,   133,   111,
     112,   113,   114,   115,   116,   117,     6,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   144,   165,   145,   134,
     190,   190,    32,   211,    33,   212,   135,    34,    35,    36,
      37,    38,   375,    39,    40,    41,   138,     8,     9,    10,
      11,    12,   354,   355,    13,    14,   263,   264,   139,    15,
      16,   251,   252,   253,   254,   255,   151,   270,   190,   190,
     279,   154,   312,   351,   352,   353,   397,   320,    17,   354,
     355,   155,   190,    18,   109,   110,   195,   295,   195,   213,
     211,   156,   212,   158,    42,   217,   218,    19,   183,   113,
     114,   115,   116,   117,   349,   350,   351,   352,   353,   191,
     313,   314,   354,   355,   316,   253,   254,   255,   334,   335,
     336,   270,   197,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   366,
     198,     6,    23,   370,   199,   144,   356,   145,    67,    68,
      69,    70,    71,    72,    73,   269,    31,    32,   219,    33,
     416,   417,    34,    35,    36,    37,    38,   220,    39,    40,
      41,   270,     8,     9,    10,    11,    12,   279,   222,    13,
      14,   345,   346,   398,    15,    16,   419,   417,   223,   225,
     211,   221,   212,   224,   282,   283,   347,   348,   349,   350,
     351,   352,   353,    17,   226,   239,   354,   355,    18,   240,
     393,   394,   256,   396,   258,   259,   262,   267,   275,   411,
     266,   276,    19,   400,   294,   315,   318,   321,   324,   418,
     325,   327,   284,   285,   328,    24,    25,    26,    27,    28,
      29,    30,    31,   320,   329,   270,   361,   286,   287,   363,
     364,   412,   365,   368,   369,   412,   288,   371,   372,   391,
     374,   289,   421,     6,    23,    24,    25,    26,    27,    28,
      29,    30,    31,   142,   395,   290,   399,   340,   403,    32,
     406,    33,   407,   410,    34,    35,    36,    37,    38,   414,
      39,    40,    41,   420,     8,     9,    10,    11,    12,   422,
     159,    13,    14,   247,   248,   265,    15,    16,   415,   143,
      24,    25,    26,    27,    28,    29,    30,    31,   251,   252,
     253,   254,   255,   373,   401,    17,   367,   129,     0,   260,
      18,     6,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,   136,     0,    19,     0,     0,    32,   142,    33,
       0,   192,    34,    35,    36,    37,    38,     0,    39,    40,
      41,     0,     8,     9,    10,    11,    12,     0,     0,    13,
      14,     0,     0,     0,    15,    16,    24,    25,    26,    27,
      28,    29,    30,    31,   257,    67,    68,    69,    70,    71,
      72,    73,   269,    17,     0,     0,     0,     0,    18,     6,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
       0,     0,    19,     0,   142,    32,     0,    33,     0,     0,
      34,    35,    36,    37,    38,     0,    39,    40,    41,     0,
       8,     9,    10,    11,    12,     0,     0,    13,    14,     0,
       0,     0,    15,    16,     0,     0,     0,     0,     0,     0,
     357,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,    18,     6,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,   261,     0,
      19,     0,     0,    32,     0,    33,     0,     0,    34,    35,
      36,    37,    38,     0,    39,    40,    41,     0,     8,     9,
      10,    11,    12,     0,     0,    13,    14,     6,     7,     0,
      15,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     7,     0,     0,     0,     0,     0,    17,
       0,     0,     0,     0,    18,     0,   337,     0,     8,     9,
      10,    11,    12,     0,     0,    13,    14,     0,    19,     0,
      15,    16,     0,     8,     9,    10,    11,    12,   237,   238,
      13,    14,     0,     0,     0,    15,    16,     0,     0,    17,
       0,     0,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   185,     0,     0,     0,    19,   186,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   102,
       0,     0,     0,     0,   103,   104,   105,   106,   107,   108,
     109,   110,     0,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,   111,   112,   113,   114,   115,   116,   117,
     111,   112,   113,   114,   115,   116,   117,   102,     0,     0,
       0,   230,   103,   104,   105,   106,   107,   108,   109,   110,
       0,   243,   244,   245,   246,   247,   248,     0,     0,     0,
       0,   111,   112,   113,   114,   115,   116,   117,   249,   250,
     251,   252,   253,   254,   255,   102,     0,     0,     0,   231,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,   107,   108,   109,   110,     0,     0,     0,     0,   111,
     112,   113,   114,   115,   116,   117,   111,   112,   113,   114,
     115,   116,   117,   102,     0,     0,     0,   232,   103,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,   245,
     246,   247,   248,     0,     0,     0,     0,   111,   112,   113,
     114,   115,   116,   117,   249,   250,   251,   252,   253,   254,
     255,   102,     0,     0,     0,   233,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,   234,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,   404,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,     0,     0,     0,     0,   102,     0,     0,     0,   405,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   102,     0,
       0,     0,   236,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,   112,   113,   114,   115,   116,   117,     0,
       0,   102,     0,     0,     0,   317,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   112,   113,   114,   115,
     116,   117,     0,     0,   102,     0,     0,     0,   360,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,   115,   116,   117,     0,     0,   102,     0,     0,
       0,   392,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     102,     0,     0,     0,   409,   103,   104,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,   112,   113,   114,   115,   116,
     117,     0,   102,     0,     0,     0,   118,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,   235,     0,     0,     0,     0,   111,   112,   113,   114,
     115,   116,   117,   102,     0,   358,     0,     0,   103,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   111,   112,   113,
     114,   115,   116,   117,   102,     0,   359,     0,     0,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,   115,   116,   117,   102,     0,     0,     0,     0,
     103,   104,   105,   106,   107,   108,   109,   110,     0,   343,
     344,   345,   346,     0,     0,     0,     0,     0,     0,   111,
     112,   113,   114,   115,   116,   117,   347,   348,   349,   350,
     351,   352,   353,     0,     0,     0,   354,   355,     0,   402,
     343,   344,   345,   346,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   347,   348,   349,
     350,   351,   352,   353,     0,     0,     0,   354,   355,   103,
     104,   105,   106,   107,   108,   109,   110,   241,   242,   243,
     244,   245,   246,   247,   248,   146,   147,   148,   111,   112,
     113,   114,   115,   116,   117,     0,   249,   250,   251,   252,
     253,   254,   255,   103,   104,   105,   106,   107,   108,   109,
     110,   103,     0,   105,   106,   107,   108,   109,   110,     0,
       0,     0,   111,   112,   113,   114,   115,   116,   117,     0,
     111,   112,   113,   114,   115,   116,   117,   241,     0,   243,
     244,   245,   246,   247,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,   250,   251,   252,
     253,   254,   255,    67,    68,    69,    70,    71,    72,    73,
      74,    31,    75,    76,    77,    78,    79,    80
};

static const yytype_int16 yycheck[] =
{
       5,     5,    37,    38,     2,   123,   275,   224,    42,    20,
      84,    43,    13,     3,     4,   290,    48,    49,    64,    17,
      18,    19,    62,    64,   142,   143,   144,   145,    64,    43,
      47,    77,    47,    44,    48,    49,    46,    47,    79,     0,
       3,     4,    79,    79,    84,    80,    83,    22,    15,    16,
      82,    41,    42,   270,   271,     5,     6,     7,     8,     9,
      10,    11,    12,    84,   339,   340,   341,    77,    78,    44,
      44,    34,    35,    36,    37,    38,    77,    79,    41,    42,
      70,    83,   200,    46,    47,    69,    70,    71,    72,    73,
      82,    83,   126,    43,    92,    93,    94,    95,    96,    79,
      62,   318,    82,    84,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     137,    84,   137,   121,    84,   142,   143,   142,   143,    79,
     399,    62,    82,    64,     4,    43,    59,    60,    61,   257,
      48,    49,    50,    51,    52,    53,    54,    55,   146,    84,
      43,    71,    72,    73,    81,    48,    49,   124,    84,    67,
      68,    69,    70,    71,    72,    73,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,   193,    85,   193,    84,
     147,   148,    19,   200,    21,   200,     4,    24,    25,    26,
      27,    28,    85,    30,    31,    32,     4,    34,    35,    36,
      37,    38,    77,    78,    41,    42,   204,   205,     4,    46,
      47,    69,    70,    71,    72,    73,     4,   221,   185,   186,
     225,     4,   256,    71,    72,    73,    82,    83,    65,    77,
      78,     4,   199,    70,    54,    55,   127,   235,   129,   357,
     257,     4,   257,     4,    81,   147,   148,    84,     4,    69,
      70,    71,    72,    73,    69,    70,    71,    72,    73,     4,
     258,   259,    77,    78,   262,    71,    72,    73,   286,   287,
     288,   275,     4,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   324,
       4,     3,     4,   328,    84,   312,   294,   312,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    19,     4,    21,
      82,    83,    24,    25,    26,    27,    28,    81,    30,    31,
      32,   325,    34,    35,    36,    37,    38,   332,     4,    41,
      42,    52,    53,   368,    46,    47,    82,    83,     3,    81,
     357,    84,   357,    84,     3,     4,    67,    68,    69,    70,
      71,    72,    73,    65,    81,    85,    77,    78,    70,    83,
     358,   359,    43,   361,    62,    62,    77,     4,    84,   404,
      64,    80,    84,   371,    77,    85,    81,    62,    85,   414,
      79,    13,    41,    42,    85,     5,     6,     7,     8,     9,
      10,    11,    12,    83,     4,   399,    64,    56,    57,    79,
       4,   406,     4,    85,     4,   410,    65,    77,    83,     4,
      79,    70,   417,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    43,    33,    84,    84,    48,    33,    19,
      81,    21,    79,    81,    24,    25,    26,    27,    28,    85,
      30,    31,    32,    79,    34,    35,    36,    37,    38,    79,
      85,    41,    42,    54,    55,   207,    46,    47,   410,    79,
       5,     6,     7,     8,     9,    10,    11,    12,    69,    70,
      71,    72,    73,   332,   372,    65,   325,    33,    -1,   199,
      70,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    82,    -1,    84,    -1,    -1,    19,    43,    21,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    -1,    -1,    41,
      42,    -1,    -1,    -1,    46,    47,     5,     6,     7,     8,
       9,    10,    11,    12,    79,     4,     5,     6,     7,     8,
       9,    10,    11,    65,    -1,    -1,    -1,    -1,    70,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    84,    -1,    43,    19,    -1,    21,    -1,    -1,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    41,    42,    -1,
      -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    70,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    82,    -1,
      84,    -1,    -1,    19,    -1,    21,    -1,    -1,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    41,    42,     3,     4,    -1,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    70,    -1,   289,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    41,    42,    -1,    84,    -1,
      46,    47,    -1,    34,    35,    36,    37,    38,   185,   186,
      41,    42,    -1,    -1,    -1,    46,    47,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    84,    70,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      67,    68,    69,    70,    71,    72,    73,    43,    -1,    -1,
      -1,    85,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    67,    68,
      69,    70,    71,    72,    73,    43,    -1,    -1,    -1,    85,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    67,
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
      68,    69,    70,    71,    72,    73,    -1,    -1,    43,    -1,
      -1,    -1,    80,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    43,    -1,    -1,    -1,    80,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    43,    -1,    -1,    -1,    80,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    43,    -1,    -1,
      -1,    80,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      43,    -1,    -1,    -1,    80,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    43,    -1,    -1,    -1,    79,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    43,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    43,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    77,    78,    -1,    80,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    77,    78,    48,
      49,    50,    51,    52,    53,    54,    55,    48,    49,    50,
      51,    52,    53,    54,    55,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    67,    68,    69,    70,
      71,    72,    73,    48,    49,    50,    51,    52,    53,    54,
      55,    48,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      67,    68,    69,    70,    71,    72,    73,    48,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    59,    60,    61,    87,    88,     3,     4,    34,    35,
      36,    37,    38,    41,    42,    46,    47,    65,    70,    84,
     116,   141,   143,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    19,    21,    24,    25,    26,    27,    28,    30,
      31,    32,    81,    92,    94,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   141,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    13,    14,    15,    16,    17,
      18,    89,    90,    91,    92,    93,    98,   103,   105,   109,
     110,   111,    84,    84,    84,    84,    84,   143,   143,   141,
     141,   141,    43,    48,    49,    50,    51,    52,    53,    54,
      55,    67,    68,    69,    70,    71,    72,    73,    79,    46,
      47,    77,    78,    62,    84,    62,    44,   127,   128,   127,
       4,   118,   118,    84,    84,     4,    82,   119,     4,     4,
      95,    96,    43,    79,   120,   121,    64,    65,    66,    62,
      64,     4,    13,    77,     4,     4,     4,   118,     4,    95,
     141,   141,   141,   141,   141,    85,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,     4,   122,    65,    70,   139,   140,   142,
     143,     4,    23,   119,    20,   128,    22,     4,     4,    84,
      79,    82,    64,    79,    64,    77,    79,    83,   120,   121,
     122,   120,   121,   122,   122,   122,   141,   140,   140,     4,
      81,    84,     4,     3,    84,    81,    81,    64,    79,    79,
      85,    85,    85,    85,    85,    62,    80,   142,   142,    85,
      83,    48,    49,    50,    51,    52,    53,    54,    55,    67,
      68,    69,    70,    71,    72,    73,    43,    79,    62,    62,
     139,    82,    77,   141,   141,    96,    64,     4,   104,    11,
      92,    93,   112,   113,   114,    84,    80,   104,   115,    93,
      99,   100,     3,     4,    41,    42,    56,    57,    65,    70,
      84,   106,   107,   108,    77,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   119,   141,   141,    85,   141,    80,    81,    82,
      83,    62,   104,   104,    85,    79,   112,    13,    85,     4,
     101,   102,    79,    82,   107,   107,   107,   108,   106,    43,
      48,    49,    82,    50,    51,    52,    53,    67,    68,    69,
      70,    71,    72,    73,    77,    78,   141,    79,    45,    45,
      80,    64,   104,    79,     4,     4,   118,   114,    85,     4,
     118,    77,    83,   100,    79,    85,   106,   106,   106,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,     4,    80,   141,   141,    33,   141,    82,   118,    84,
     141,   102,    80,    33,    85,    85,    81,    79,   112,    80,
      81,   118,    93,    97,    85,    97,    82,    83,   118,    82,
      79,    93,    79
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    90,    91,    91,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    95,    96,    96,
      96,    96,    97,    97,    98,    99,    99,   100,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   110,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   117,   117,
     118,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   124,   125,   126,   127,
     127,   128,   128,   128,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   139,   140,   140,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,    11,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       4,     6,     1,     3,     6,     1,     3,     2,     1,     3,
       1,     4,     6,     8,     1,     3,     5,     1,     3,     3,
       3,     2,     2,     2,     3,     1,     1,     1,     1,     1,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     6,     7,    10,     6,     2,     0,
       1,     1,     3,     2,     2,     0,     1,     2,     1,     1,
       2,     3,     4,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,    11,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     1,     1,     3,     3,     1,
       2,     2,     4,     5,     3,     2,     2,     9,     8,     3,
       3,     5,     1,     1,     2,     0,     1,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     5,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     1,     1,
       3,     4,     3,     2,     2,     2,     2,     4,     4,     4,
       4,     4
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
#line 230 "src/parser.y"
                                       { if (!g_root) g_root = new p2p::Module(); }
#line 2115 "build/parser.cpp"
    break;

  case 6: /* program_body: program_body top_decl  */
#line 238 "src/parser.y"
        {
            if (!g_root) g_root = new p2p::Module();
            if ((yyvsp[0].node)) g_root->declarations.emplace_back((yyvsp[0].node));
        }
#line 2124 "build/parser.cpp"
    break;

  case 7: /* top_decl: var_decl_stmt  */
#line 245 "src/parser.y"
                           { push_decls(*(yyvsp[0].vardecl_list)); delete (yyvsp[0].vardecl_list); (yyval.node) = nullptr; }
#line 2130 "build/parser.cpp"
    break;

  case 8: /* top_decl: chan_decl_stmt  */
#line 246 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2136 "build/parser.cpp"
    break;

  case 9: /* top_decl: typedef_decl  */
#line 247 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2142 "build/parser.cpp"
    break;

  case 10: /* top_decl: mtype_decl  */
#line 248 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2148 "build/parser.cpp"
    break;

  case 11: /* top_decl: ltl_decl  */
#line 249 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2154 "build/parser.cpp"
    break;

  case 12: /* top_decl: proctype_decl  */
#line 250 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2160 "build/parser.cpp"
    break;

  case 13: /* top_decl: inline_decl  */
#line 251 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2166 "build/parser.cpp"
    break;

  case 14: /* top_decl: init_decl  */
#line 252 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2172 "build/parser.cpp"
    break;

  case 15: /* var_decl_stmt: basic_type declarator_list ';'  */
#line 258 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            (yyval.vardecl_list) = (yyvsp[-1].vardecl_list);
        }
#line 2182 "build/parser.cpp"
    break;

  case 16: /* chan_decl_stmt: chan_type IDENT ';'  */
#line 269 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-1].str_val); free((yyvsp[-1].str_val));
            d->type.reset((yyvsp[-2].type));
            (yyval.node) = d;
        }
#line 2193 "build/parser.cpp"
    break;

  case 17: /* chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 276 "src/parser.y"
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
#line 2212 "build/parser.cpp"
    break;

  case 18: /* chan_type: T_CHAN  */
#line 293 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Chan); }
#line 2218 "build/parser.cpp"
    break;

  case 19: /* basic_type: T_BYTE  */
#line 297 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2224 "build/parser.cpp"
    break;

  case 20: /* basic_type: T_INT  */
#line 298 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2230 "build/parser.cpp"
    break;

  case 21: /* basic_type: T_BOOL  */
#line 299 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2236 "build/parser.cpp"
    break;

  case 22: /* basic_type: T_BIT  */
#line 300 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2242 "build/parser.cpp"
    break;

  case 23: /* basic_type: T_SHORT  */
#line 301 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2248 "build/parser.cpp"
    break;

  case 24: /* basic_type: T_UNSIGNED  */
#line 302 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2254 "build/parser.cpp"
    break;

  case 25: /* basic_type: T_MTYPE  */
#line 303 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2260 "build/parser.cpp"
    break;

  case 26: /* basic_type: T_MTYPE ':' IDENT  */
#line 305 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2271 "build/parser.cpp"
    break;

  case 27: /* basic_type: IDENT  */
#line 311 "src/parser.y"
                           { (yyval.type) = make_named((yyvsp[0].str_val)); free((yyvsp[0].str_val)); }
#line 2277 "build/parser.cpp"
    break;

  case 28: /* local_basic_type: T_BYTE  */
#line 321 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2283 "build/parser.cpp"
    break;

  case 29: /* local_basic_type: T_INT  */
#line 322 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2289 "build/parser.cpp"
    break;

  case 30: /* local_basic_type: T_BOOL  */
#line 323 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2295 "build/parser.cpp"
    break;

  case 31: /* local_basic_type: T_BIT  */
#line 324 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2301 "build/parser.cpp"
    break;

  case 32: /* local_basic_type: T_SHORT  */
#line 325 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2307 "build/parser.cpp"
    break;

  case 33: /* local_basic_type: T_UNSIGNED  */
#line 326 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2313 "build/parser.cpp"
    break;

  case 34: /* local_basic_type: T_MTYPE  */
#line 327 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2319 "build/parser.cpp"
    break;

  case 35: /* local_basic_type: T_MTYPE ':' IDENT  */
#line 329 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2330 "build/parser.cpp"
    break;

  case 36: /* declarator_list: declarator  */
#line 339 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2340 "build/parser.cpp"
    break;

  case 37: /* declarator_list: declarator_list ',' declarator  */
#line 345 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2349 "build/parser.cpp"
    break;

  case 38: /* declarator: IDENT  */
#line 353 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2359 "build/parser.cpp"
    break;

  case 39: /* declarator: IDENT '=' expr  */
#line 359 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2370 "build/parser.cpp"
    break;

  case 40: /* declarator: IDENT '[' expr ']'  */
#line 366 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2381 "build/parser.cpp"
    break;

  case 41: /* declarator: IDENT '[' expr ']' '=' expr  */
#line 373 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            d->array_size.reset((yyvsp[-3].expr));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2393 "build/parser.cpp"
    break;

  case 42: /* type_list: basic_type  */
#line 384 "src/parser.y"
        {
            auto* tl = new TypeList();
            tl->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = tl;
        }
#line 2403 "build/parser.cpp"
    break;

  case 43: /* type_list: type_list ',' basic_type  */
#line 390 "src/parser.y"
        {
            (yyvsp[-2].type_list)->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = (yyvsp[-2].type_list);
        }
#line 2412 "build/parser.cpp"
    break;

  case 44: /* typedef_decl: K_TYPEDEF IDENT '{' field_decl_list '}' ';'  */
#line 399 "src/parser.y"
        {
            auto* td = new p2p::TypedefDecl();
            td->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            td->fields = std::move((yyvsp[-2].vardecl_list)->items);
            delete (yyvsp[-2].vardecl_list);
            (yyval.node) = td;
        }
#line 2424 "build/parser.cpp"
    break;

  case 45: /* field_decl_list: field_decl_stmt  */
#line 409 "src/parser.y"
                                               { (yyval.vardecl_list) = (yyvsp[0].vardecl_list); }
#line 2430 "build/parser.cpp"
    break;

  case 46: /* field_decl_list: field_decl_list ';' field_decl_stmt  */
#line 411 "src/parser.y"
        {
            for (auto& f : (yyvsp[0].vardecl_list)->items) (yyvsp[-2].vardecl_list)->items.emplace_back(std::move(f));
            delete (yyvsp[0].vardecl_list);
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2440 "build/parser.cpp"
    break;

  case 47: /* field_decl_stmt: basic_type field_decl_one_or_more  */
#line 420 "src/parser.y"
        {
            attach_type(*(yyvsp[0].vardecl_list), *(yyvsp[-1].type));
            delete (yyvsp[-1].type);
            (yyval.vardecl_list) = (yyvsp[0].vardecl_list);
        }
#line 2450 "build/parser.cpp"
    break;

  case 48: /* field_decl_one_or_more: field_one  */
#line 429 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2460 "build/parser.cpp"
    break;

  case 49: /* field_decl_one_or_more: field_decl_one_or_more ',' field_one  */
#line 435 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2469 "build/parser.cpp"
    break;

  case 50: /* field_one: IDENT  */
#line 443 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2479 "build/parser.cpp"
    break;

  case 51: /* field_one: IDENT '[' expr ']'  */
#line 449 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2490 "build/parser.cpp"
    break;

  case 52: /* mtype_decl: T_MTYPE '=' '{' ident_list '}' ';'  */
#line 460 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2501 "build/parser.cpp"
    break;

  case 53: /* mtype_decl: T_MTYPE ':' IDENT '=' '{' ident_list '}' ';'  */
#line 467 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->set_name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2513 "build/parser.cpp"
    break;

  case 54: /* ident_list: IDENT  */
#line 478 "src/parser.y"
        {
            auto* il = new IdentList();
            il->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = il;
        }
#line 2524 "build/parser.cpp"
    break;

  case 55: /* ident_list: ident_list ',' IDENT  */
#line 485 "src/parser.y"
        {
            (yyvsp[-2].ident_list)->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = (yyvsp[-2].ident_list);
        }
#line 2534 "build/parser.cpp"
    break;

  case 56: /* ltl_decl: K_LTL IDENT '{' ltl_formula '}'  */
#line 495 "src/parser.y"
        {
            auto* l = new p2p::LtlDecl();
            l->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            l->formula.reset((yyvsp[-1].ltl));
            (yyval.node) = l;
        }
#line 2545 "build/parser.cpp"
    break;

  case 57: /* ltl_formula: ltl_unary  */
#line 504 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[0].ltl); }
#line 2551 "build/parser.cpp"
    break;

  case 58: /* ltl_formula: ltl_formula OP_AND ltl_formula  */
#line 506 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::And;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2562 "build/parser.cpp"
    break;

  case 59: /* ltl_formula: ltl_formula OP_OR ltl_formula  */
#line 513 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Or;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2573 "build/parser.cpp"
    break;

  case 60: /* ltl_formula: ltl_formula OP_ARROW ltl_formula  */
#line 520 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Implies;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2584 "build/parser.cpp"
    break;

  case 61: /* ltl_unary: LTL_ALWAYS ltl_unary  */
#line 530 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Always;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2595 "build/parser.cpp"
    break;

  case 62: /* ltl_unary: LTL_EVENTUALLY ltl_unary  */
#line 537 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Eventually;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2606 "build/parser.cpp"
    break;

  case 63: /* ltl_unary: '!' ltl_unary  */
#line 544 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Not;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2617 "build/parser.cpp"
    break;

  case 64: /* ltl_unary: '(' ltl_formula ')'  */
#line 550 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[-1].ltl); }
#line 2623 "build/parser.cpp"
    break;

  case 65: /* ltl_unary: ltl_atom  */
#line 552 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Atom;
            f->atom.reset((yyvsp[0].expr));
            (yyval.ltl) = f;
        }
#line 2634 "build/parser.cpp"
    break;

  case 66: /* ltl_atom: INT_LITERAL  */
#line 561 "src/parser.y"
                                        { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 2640 "build/parser.cpp"
    break;

  case 67: /* ltl_atom: K_TRUE  */
#line 562 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 2646 "build/parser.cpp"
    break;

  case 68: /* ltl_atom: K_FALSE  */
#line 563 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 2652 "build/parser.cpp"
    break;

  case 69: /* ltl_atom: IDENT  */
#line 564 "src/parser.y"
                                        {
                                          auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
                                          free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2662 "build/parser.cpp"
    break;

  case 70: /* ltl_atom: ltl_atom '[' ltl_atom ']'  */
#line 569 "src/parser.y"
                                        {
                                          auto* e = new p2p::IndexExpr();
                                          e->base.reset((yyvsp[-3].expr)); e->index.reset((yyvsp[-1].expr));
                                          (yyval.expr) = e;
                                        }
#line 2672 "build/parser.cpp"
    break;

  case 71: /* ltl_atom: ltl_atom '.' IDENT  */
#line 574 "src/parser.y"
                                        {
                                          auto* e = new p2p::FieldExpr();
                                          e->base.reset((yyvsp[-2].expr));
                                          e->field = (yyvsp[0].str_val); free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2683 "build/parser.cpp"
    break;

  case 72: /* ltl_atom: ltl_atom '+' ltl_atom  */
#line 580 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2689 "build/parser.cpp"
    break;

  case 73: /* ltl_atom: ltl_atom '-' ltl_atom  */
#line 581 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2695 "build/parser.cpp"
    break;

  case 74: /* ltl_atom: ltl_atom '*' ltl_atom  */
#line 582 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2701 "build/parser.cpp"
    break;

  case 75: /* ltl_atom: ltl_atom '/' ltl_atom  */
#line 583 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2707 "build/parser.cpp"
    break;

  case 76: /* ltl_atom: ltl_atom '%' ltl_atom  */
#line 584 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2713 "build/parser.cpp"
    break;

  case 77: /* ltl_atom: ltl_atom '<' ltl_atom  */
#line 585 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2719 "build/parser.cpp"
    break;

  case 78: /* ltl_atom: ltl_atom '>' ltl_atom  */
#line 586 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2725 "build/parser.cpp"
    break;

  case 79: /* ltl_atom: ltl_atom OP_LE ltl_atom  */
#line 587 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2731 "build/parser.cpp"
    break;

  case 80: /* ltl_atom: ltl_atom OP_GE ltl_atom  */
#line 588 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2737 "build/parser.cpp"
    break;

  case 81: /* ltl_atom: ltl_atom OP_EQ ltl_atom  */
#line 589 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2743 "build/parser.cpp"
    break;

  case 82: /* ltl_atom: ltl_atom OP_NEQ ltl_atom  */
#line 590 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2749 "build/parser.cpp"
    break;

  case 83: /* ltl_atom: '-' ltl_atom  */
#line 591 "src/parser.y"
                                        { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 2755 "build/parser.cpp"
    break;

  case 84: /* proctype_decl: K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 602 "src/parser.y"
        {
            auto* p = new p2p::ProctypeDecl();
            p->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            p->params = std::move((yyvsp[-2].param_list)->items);
            delete (yyvsp[-2].param_list);
            p->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = p;
        }
#line 2769 "build/parser.cpp"
    break;

  case 85: /* proctype_decl: K_ACTIVE K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 612 "src/parser.y"
        {
            auto* p = new p2p::ProctypeDecl();
            p->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            p->instance_count = 1;
            p->params = std::move((yyvsp[-2].param_list)->items);
            delete (yyvsp[-2].param_list);
            p->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = p;
        }
#line 2784 "build/parser.cpp"
    break;

  case 86: /* proctype_decl: K_ACTIVE '[' INT_LITERAL ']' K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 623 "src/parser.y"
        {
            auto* p = new p2p::ProctypeDecl();
            p->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            p->instance_count = (yyvsp[-7].int_val) > 0 ? (yyvsp[-7].int_val) : 1;
            p->params = std::move((yyvsp[-2].param_list)->items);
            delete (yyvsp[-2].param_list);
            p->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = p;
        }
#line 2799 "build/parser.cpp"
    break;

  case 87: /* inline_decl: K_INLINE IDENT '(' ident_list_opt ')' stmt_block  */
#line 639 "src/parser.y"
        {
            auto* d = new p2p::InlineDecl();
            d->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            /* convert IdentList into ParamList with untyped Params */
            for (auto& n : (yyvsp[-2].ident_list)->items) {
                p2p::Param p;
                p.name = std::move(n);
                d->params.push_back(std::move(p));
            }
            delete (yyvsp[-2].ident_list);
            d->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = d;
        }
#line 2818 "build/parser.cpp"
    break;

  case 88: /* init_decl: K_INIT stmt_block  */
#line 658 "src/parser.y"
        {
            auto* d = new p2p::InitDecl();
            d->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = d;
        }
#line 2829 "build/parser.cpp"
    break;

  case 89: /* params_opt: %empty  */
#line 670 "src/parser.y"
                               { (yyval.param_list) = new ParamList(); }
#line 2835 "build/parser.cpp"
    break;

  case 90: /* params_opt: param_list  */
#line 671 "src/parser.y"
                               { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2841 "build/parser.cpp"
    break;

  case 91: /* param_list: param_group  */
#line 675 "src/parser.y"
                               { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2847 "build/parser.cpp"
    break;

  case 92: /* param_list: param_list ';' param_group  */
#line 677 "src/parser.y"
        {
            for (auto& p : (yyvsp[0].param_list)->items) (yyvsp[-2].param_list)->items.push_back(std::move(p));
            delete (yyvsp[0].param_list);
            (yyval.param_list) = (yyvsp[-2].param_list);
        }
#line 2857 "build/parser.cpp"
    break;

  case 93: /* param_group: basic_type ident_list  */
#line 687 "src/parser.y"
        {
            auto* pl = new ParamList();
            for (auto& n : (yyvsp[0].ident_list)->items) {
                p2p::Param p;
                p.type.reset(clone_type(*(yyvsp[-1].type)));
                p.name = std::move(n);
                pl->items.push_back(std::move(p));
            }
            delete (yyvsp[0].ident_list);
            delete (yyvsp[-1].type);
            (yyval.param_list) = pl;
        }
#line 2874 "build/parser.cpp"
    break;

  case 94: /* param_group: chan_type ident_list  */
#line 700 "src/parser.y"
        {
            auto* pl = new ParamList();
            for (auto& n : (yyvsp[0].ident_list)->items) {
                p2p::Param p;
                p.type.reset(clone_type(*(yyvsp[-1].type)));
                p.name = std::move(n);
                pl->items.push_back(std::move(p));
            }
            delete (yyvsp[0].ident_list);
            delete (yyvsp[-1].type);
            (yyval.param_list) = pl;
        }
#line 2891 "build/parser.cpp"
    break;

  case 95: /* ident_list_opt: %empty  */
#line 716 "src/parser.y"
                               { (yyval.ident_list) = new IdentList(); }
#line 2897 "build/parser.cpp"
    break;

  case 96: /* ident_list_opt: ident_list  */
#line 717 "src/parser.y"
                               { (yyval.ident_list) = (yyvsp[0].ident_list); }
#line 2903 "build/parser.cpp"
    break;

  case 97: /* expr_body: expr ';'  */
#line 722 "src/parser.y"
                { g_expr_result = (yyvsp[-1].expr); }
#line 2909 "build/parser.cpp"
    break;

  case 98: /* stmt_body: stmt_block  */
#line 728 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2915 "build/parser.cpp"
    break;

  case 99: /* stmt_body: stmt_seq  */
#line 729 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2921 "build/parser.cpp"
    break;

  case 100: /* stmt_block: '{' '}'  */
#line 737 "src/parser.y"
        { (yyval.stmt_list) = new StmtList(); }
#line 2927 "build/parser.cpp"
    break;

  case 101: /* stmt_block: '{' stmt_seq '}'  */
#line 739 "src/parser.y"
        { (yyval.stmt_list) = (yyvsp[-1].stmt_list); }
#line 2933 "build/parser.cpp"
    break;

  case 102: /* stmt_block: '{' stmt_seq ';' '}'  */
#line 741 "src/parser.y"
        { (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 2939 "build/parser.cpp"
    break;

  case 103: /* stmt_seq: stmt  */
#line 750 "src/parser.y"
        {
            auto* l = new StmtList();
            l->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = l;
        }
#line 2949 "build/parser.cpp"
    break;

  case 104: /* stmt_seq: local_var_decl_stmt  */
#line 756 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2957 "build/parser.cpp"
    break;

  case 105: /* stmt_seq: local_chan_decl_stmt  */
#line 760 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2965 "build/parser.cpp"
    break;

  case 106: /* stmt_seq: stmt_seq ';' stmt  */
#line 764 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2974 "build/parser.cpp"
    break;

  case 107: /* stmt_seq: stmt_seq OP_ARROW stmt  */
#line 769 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2983 "build/parser.cpp"
    break;

  case 108: /* stmt_seq: stmt_seq ';' local_var_decl_stmt  */
#line 774 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 2993 "build/parser.cpp"
    break;

  case 109: /* stmt_seq: stmt_seq ';' local_chan_decl_stmt  */
#line 780 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3003 "build/parser.cpp"
    break;

  case 110: /* stmt_seq: stmt_seq OP_ARROW local_var_decl_stmt  */
#line 786 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3013 "build/parser.cpp"
    break;

  case 111: /* stmt_seq: stmt_seq OP_ARROW local_chan_decl_stmt  */
#line 792 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3023 "build/parser.cpp"
    break;

  case 112: /* stmt_seq: stmt_seq local_var_decl_stmt  */
#line 799 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 3033 "build/parser.cpp"
    break;

  case 113: /* stmt_seq: stmt_seq local_chan_decl_stmt  */
#line 805 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 3043 "build/parser.cpp"
    break;

  case 114: /* stmt_seq: stmt_seq local_var_decl_stmt stmt  */
#line 812 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3054 "build/parser.cpp"
    break;

  case 115: /* stmt_seq: stmt_seq local_chan_decl_stmt stmt  */
#line 819 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3065 "build/parser.cpp"
    break;

  case 116: /* local_var_decl_stmt: local_basic_type declarator_list ';'  */
#line 831 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            auto* out = new StmtList();
            wrap_local_decls(*(yyvsp[-1].vardecl_list), *out);
            delete (yyvsp[-1].vardecl_list);
            (yyval.stmt_list) = out;
        }
#line 3078 "build/parser.cpp"
    break;

  case 117: /* local_chan_decl_stmt: chan_type IDENT ';'  */
#line 843 "src/parser.y"
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
#line 3093 "build/parser.cpp"
    break;

  case 118: /* local_chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 854 "src/parser.y"
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
#line 3116 "build/parser.cpp"
    break;

  case 119: /* stmt: simple_stmt  */
#line 876 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3122 "build/parser.cpp"
    break;

  case 120: /* stmt: if_stmt  */
#line 877 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3128 "build/parser.cpp"
    break;

  case 121: /* stmt: do_stmt  */
#line 878 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3134 "build/parser.cpp"
    break;

  case 122: /* stmt: atomic_stmt  */
#line 879 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3140 "build/parser.cpp"
    break;

  case 123: /* stmt: dstep_stmt  */
#line 880 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3146 "build/parser.cpp"
    break;

  case 124: /* stmt: for_stmt  */
#line 881 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3152 "build/parser.cpp"
    break;

  case 125: /* stmt: select_stmt  */
#line 882 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3158 "build/parser.cpp"
    break;

  case 126: /* stmt: send_stmt  */
#line 883 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3164 "build/parser.cpp"
    break;

  case 127: /* stmt: recv_stmt  */
#line 884 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3170 "build/parser.cpp"
    break;

  case 128: /* stmt: run_stmt  */
#line 885 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3176 "build/parser.cpp"
    break;

  case 129: /* stmt: break_stmt  */
#line 886 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3182 "build/parser.cpp"
    break;

  case 130: /* stmt: skip_stmt  */
#line 887 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3188 "build/parser.cpp"
    break;

  case 131: /* stmt: goto_stmt  */
#line 888 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3194 "build/parser.cpp"
    break;

  case 132: /* stmt: IDENT ':' stmt  */
#line 890 "src/parser.y"
        {
            auto* l = new p2p::LabeledStmt();
            l->label = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            l->stmt.reset((yyvsp[0].stmt));
            (yyval.stmt) = l;
        }
#line 3205 "build/parser.cpp"
    break;

  case 133: /* assign_or_expr_stmt: expr '=' expr  */
#line 906 "src/parser.y"
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
#line 3223 "build/parser.cpp"
    break;

  case 134: /* assign_or_expr_stmt: IDENT '(' expr_args ')'  */
#line 920 "src/parser.y"
        {
            auto* c = new p2p::InlineCallStmt();
            c->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            c->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = c;
        }
#line 3235 "build/parser.cpp"
    break;

  case 135: /* assign_or_expr_stmt: expr  */
#line 928 "src/parser.y"
        {
            (yyval.stmt) = wrap_expr_stmt((yyvsp[0].expr));
        }
#line 3243 "build/parser.cpp"
    break;

  case 136: /* simple_stmt: assign_or_expr_stmt  */
#line 934 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3249 "build/parser.cpp"
    break;

  case 137: /* if_stmt: K_IF branches K_FI  */
#line 940 "src/parser.y"
        {
            auto* s = new p2p::IfStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3260 "build/parser.cpp"
    break;

  case 138: /* do_stmt: K_DO branches K_OD  */
#line 951 "src/parser.y"
        {
            auto* s = new p2p::DoStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3271 "build/parser.cpp"
    break;

  case 139: /* branches: branch  */
#line 961 "src/parser.y"
        {
            auto* l = new BranchList();
            l->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = l;
        }
#line 3282 "build/parser.cpp"
    break;

  case 140: /* branches: branches branch  */
#line 968 "src/parser.y"
        {
            (yyvsp[-1].branch_list)->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = (yyvsp[-1].branch_list);
        }
#line 3292 "build/parser.cpp"
    break;

  case 141: /* branch: OP_DCOLON stmt_seq  */
#line 980 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3304 "build/parser.cpp"
    break;

  case 142: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq  */
#line 988 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3316 "build/parser.cpp"
    break;

  case 143: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq ';'  */
#line 996 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3328 "build/parser.cpp"
    break;

  case 144: /* branch: OP_DCOLON stmt_seq ';'  */
#line 1004 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3340 "build/parser.cpp"
    break;

  case 145: /* atomic_stmt: K_ATOMIC stmt_block  */
#line 1016 "src/parser.y"
        {
            auto* s = new p2p::AtomicStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3351 "build/parser.cpp"
    break;

  case 146: /* dstep_stmt: K_D_STEP stmt_block  */
#line 1026 "src/parser.y"
        {
            auto* s = new p2p::DStepStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3362 "build/parser.cpp"
    break;

  case 147: /* for_stmt: K_FOR '(' IDENT ':' expr OP_DOTDOT expr ')' stmt_block  */
#line 1037 "src/parser.y"
        {
            auto* s = new p2p::ForStmt();
            s->var = (yyvsp[-6].str_val); free((yyvsp[-6].str_val));
            s->low.reset((yyvsp[-4].expr));
            s->high.reset((yyvsp[-2].expr));
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3376 "build/parser.cpp"
    break;

  case 148: /* select_stmt: K_SELECT '(' IDENT ':' expr OP_DOTDOT expr ')'  */
#line 1052 "src/parser.y"
        {
            auto* s = new p2p::SelectStmt();
            s->var = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            s->low.reset((yyvsp[-3].expr));
            s->high.reset((yyvsp[-1].expr));
            (yyval.stmt) = s;
        }
#line 3388 "build/parser.cpp"
    break;

  case 149: /* send_stmt: expr '!' expr_args_nonempty  */
#line 1064 "src/parser.y"
        {
            auto* s = new p2p::SendStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3400 "build/parser.cpp"
    break;

  case 150: /* recv_stmt: expr '?' expr_args_nonempty  */
#line 1076 "src/parser.y"
        {
            auto* s = new p2p::RecvStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3412 "build/parser.cpp"
    break;

  case 151: /* run_stmt: K_RUN IDENT '(' expr_args ')'  */
#line 1090 "src/parser.y"
        {
            auto* s = new p2p::RunStmt();
            s->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            s->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = s;
        }
#line 3424 "build/parser.cpp"
    break;

  case 152: /* break_stmt: K_BREAK  */
#line 1099 "src/parser.y"
                            { (yyval.stmt) = new p2p::BreakStmt(); }
#line 3430 "build/parser.cpp"
    break;

  case 153: /* skip_stmt: K_SKIP  */
#line 1100 "src/parser.y"
                            { (yyval.stmt) = new p2p::SkipStmt(); }
#line 3436 "build/parser.cpp"
    break;

  case 154: /* goto_stmt: K_GOTO IDENT  */
#line 1102 "src/parser.y"
        {
            auto* g = new p2p::GotoStmt();
            g->label = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.stmt) = g;
        }
#line 3446 "build/parser.cpp"
    break;

  case 155: /* expr_args: %empty  */
#line 1111 "src/parser.y"
                                        { (yyval.expr_list) = new ExprList(); }
#line 3452 "build/parser.cpp"
    break;

  case 156: /* expr_args: expr_args_nonempty  */
#line 1112 "src/parser.y"
                                        { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 3458 "build/parser.cpp"
    break;

  case 157: /* expr_args_nonempty: expr_no_ternary  */
#line 1117 "src/parser.y"
        {
            auto* l = new ExprList();
            l->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = l;
        }
#line 3468 "build/parser.cpp"
    break;

  case 158: /* expr_args_nonempty: expr_args_nonempty ',' expr_no_ternary  */
#line 1123 "src/parser.y"
        {
            (yyvsp[-2].expr_list)->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = (yyvsp[-2].expr_list);
        }
#line 3477 "build/parser.cpp"
    break;

  case 159: /* expr: primary  */
#line 1132 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 3483 "build/parser.cpp"
    break;

  case 160: /* expr: expr '+' expr  */
#line 1133 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3489 "build/parser.cpp"
    break;

  case 161: /* expr: expr '-' expr  */
#line 1134 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3495 "build/parser.cpp"
    break;

  case 162: /* expr: expr '*' expr  */
#line 1135 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3501 "build/parser.cpp"
    break;

  case 163: /* expr: expr '/' expr  */
#line 1136 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3507 "build/parser.cpp"
    break;

  case 164: /* expr: expr '%' expr  */
#line 1137 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3513 "build/parser.cpp"
    break;

  case 165: /* expr: expr OP_SHL expr  */
#line 1138 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3519 "build/parser.cpp"
    break;

  case 166: /* expr: expr OP_SHR expr  */
#line 1139 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3525 "build/parser.cpp"
    break;

  case 167: /* expr: expr '<' expr  */
#line 1140 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3531 "build/parser.cpp"
    break;

  case 168: /* expr: expr '>' expr  */
#line 1141 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3537 "build/parser.cpp"
    break;

  case 169: /* expr: expr OP_LE expr  */
#line 1142 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3543 "build/parser.cpp"
    break;

  case 170: /* expr: expr OP_GE expr  */
#line 1143 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3549 "build/parser.cpp"
    break;

  case 171: /* expr: expr OP_EQ expr  */
#line 1144 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3555 "build/parser.cpp"
    break;

  case 172: /* expr: expr OP_NEQ expr  */
#line 1145 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3561 "build/parser.cpp"
    break;

  case 173: /* expr: expr OP_AND expr  */
#line 1146 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3567 "build/parser.cpp"
    break;

  case 174: /* expr: expr OP_OR expr  */
#line 1147 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Or,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3573 "build/parser.cpp"
    break;

  case 175: /* expr: '-' expr  */
#line 1148 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 3579 "build/parser.cpp"
    break;

  case 176: /* expr: '!' expr  */
#line 1149 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 3585 "build/parser.cpp"
    break;

  case 177: /* expr: expr OP_ARROW expr ':' expr  */
#line 1151 "src/parser.y"
        {
            auto* t = new p2p::TernaryExpr();
            t->cond.reset((yyvsp[-4].expr));
            t->then_expr.reset((yyvsp[-2].expr));
            t->else_expr.reset((yyvsp[0].expr));
            (yyval.expr) = t;
        }
#line 3597 "build/parser.cpp"
    break;

  case 178: /* expr_no_ternary: primary  */
#line 1165 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 3603 "build/parser.cpp"
    break;

  case 179: /* expr_no_ternary: expr_no_ternary '+' expr_no_ternary  */
#line 1166 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3609 "build/parser.cpp"
    break;

  case 180: /* expr_no_ternary: expr_no_ternary '-' expr_no_ternary  */
#line 1167 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3615 "build/parser.cpp"
    break;

  case 181: /* expr_no_ternary: expr_no_ternary '*' expr_no_ternary  */
#line 1168 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3621 "build/parser.cpp"
    break;

  case 182: /* expr_no_ternary: expr_no_ternary '/' expr_no_ternary  */
#line 1169 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3627 "build/parser.cpp"
    break;

  case 183: /* expr_no_ternary: expr_no_ternary '%' expr_no_ternary  */
#line 1170 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3633 "build/parser.cpp"
    break;

  case 184: /* expr_no_ternary: expr_no_ternary OP_SHL expr_no_ternary  */
#line 1171 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3639 "build/parser.cpp"
    break;

  case 185: /* expr_no_ternary: expr_no_ternary OP_SHR expr_no_ternary  */
#line 1172 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3645 "build/parser.cpp"
    break;

  case 186: /* expr_no_ternary: expr_no_ternary '<' expr_no_ternary  */
#line 1173 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3651 "build/parser.cpp"
    break;

  case 187: /* expr_no_ternary: expr_no_ternary '>' expr_no_ternary  */
#line 1174 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3657 "build/parser.cpp"
    break;

  case 188: /* expr_no_ternary: expr_no_ternary OP_LE expr_no_ternary  */
#line 1175 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Le, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3663 "build/parser.cpp"
    break;

  case 189: /* expr_no_ternary: expr_no_ternary OP_GE expr_no_ternary  */
#line 1176 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Ge, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3669 "build/parser.cpp"
    break;

  case 190: /* expr_no_ternary: expr_no_ternary OP_EQ expr_no_ternary  */
#line 1177 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Eq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3675 "build/parser.cpp"
    break;

  case 191: /* expr_no_ternary: expr_no_ternary OP_NEQ expr_no_ternary  */
#line 1178 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3681 "build/parser.cpp"
    break;

  case 192: /* expr_no_ternary: expr_no_ternary OP_AND expr_no_ternary  */
#line 1179 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3687 "build/parser.cpp"
    break;

  case 193: /* expr_no_ternary: expr_no_ternary OP_OR expr_no_ternary  */
#line 1180 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3693 "build/parser.cpp"
    break;

  case 194: /* expr_no_ternary: '-' expr_no_ternary  */
#line 1181 "src/parser.y"
                                           { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 3699 "build/parser.cpp"
    break;

  case 195: /* expr_no_ternary: '!' expr_no_ternary  */
#line 1182 "src/parser.y"
                                           { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 3705 "build/parser.cpp"
    break;

  case 196: /* primary: INT_LITERAL  */
#line 1186 "src/parser.y"
                           { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 3711 "build/parser.cpp"
    break;

  case 197: /* primary: K_TRUE  */
#line 1187 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 3717 "build/parser.cpp"
    break;

  case 198: /* primary: K_FALSE  */
#line 1188 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 3723 "build/parser.cpp"
    break;

  case 199: /* primary: IDENT  */
#line 1190 "src/parser.y"
        {
            auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3733 "build/parser.cpp"
    break;

  case 200: /* primary: '(' expr ')'  */
#line 1196 "src/parser.y"
        {
            auto* p = new p2p::ParenExpr();
            p->inner.reset((yyvsp[-1].expr));
            (yyval.expr) = p;
        }
#line 3743 "build/parser.cpp"
    break;

  case 201: /* primary: primary '[' expr ']'  */
#line 1202 "src/parser.y"
        {
            auto* e = new p2p::IndexExpr();
            e->base.reset((yyvsp[-3].expr));
            e->index.reset((yyvsp[-1].expr));
            (yyval.expr) = e;
        }
#line 3754 "build/parser.cpp"
    break;

  case 202: /* primary: primary '.' IDENT  */
#line 1209 "src/parser.y"
        {
            auto* e = new p2p::FieldExpr();
            e->base.reset((yyvsp[-2].expr));
            e->field = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3766 "build/parser.cpp"
    break;

  case 203: /* primary: primary OP_INC  */
#line 1216 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostInc, (yyvsp[-1].expr)); }
#line 3772 "build/parser.cpp"
    break;

  case 204: /* primary: primary OP_DEC  */
#line 1217 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostDec, (yyvsp[-1].expr)); }
#line 3778 "build/parser.cpp"
    break;

  case 205: /* primary: OP_INC primary  */
#line 1218 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreInc,  (yyvsp[0].expr)); }
#line 3784 "build/parser.cpp"
    break;

  case 206: /* primary: OP_DEC primary  */
#line 1219 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreDec,  (yyvsp[0].expr)); }
#line 3790 "build/parser.cpp"
    break;

  case 207: /* primary: K_NEMPTY '(' expr ')'  */
#line 1220 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nempty, (yyvsp[-1].expr)); }
#line 3796 "build/parser.cpp"
    break;

  case 208: /* primary: K_EMPTY '(' expr ')'  */
#line 1221 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Empty,  (yyvsp[-1].expr)); }
#line 3802 "build/parser.cpp"
    break;

  case 209: /* primary: K_LEN '(' expr ')'  */
#line 1222 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Len,    (yyvsp[-1].expr)); }
#line 3808 "build/parser.cpp"
    break;

  case 210: /* primary: K_FULL '(' expr ')'  */
#line 1223 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Full,   (yyvsp[-1].expr)); }
#line 3814 "build/parser.cpp"
    break;

  case 211: /* primary: K_NFULL '(' expr ')'  */
#line 1224 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nfull,  (yyvsp[-1].expr)); }
#line 3820 "build/parser.cpp"
    break;


#line 3824 "build/parser.cpp"

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

#line 1227 "src/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}

extern int g_brace_depth;
extern int g_saw_newline;

/* Automatic Semicolon Insertion. Inside a procedure body (g_brace_depth > 0),
   when the previous token was a block terminator ('}' / fi / od) and the
   current token starts a new statement on a new line, inject a virtual ';'
   so the grammar can apply  stmt_seq ';' stmt  uniformly. ASI is disabled
   at the top level so that declarations like  } byte x; ... } byte y;
   are not corrupted by spurious ';' insertions. */
int yylex() {
    static int prev_token = 0;
    static int pending = 0;

    if (pending != 0) {
        int t = pending;
        pending = 0;
        prev_token = t;
        g_saw_newline = 0;
        return t;
    }

    int t = yylex_raw();
    int had_newline = g_saw_newline;
    g_saw_newline = 0;

    bool prev_closes_block =
        prev_token == '}'   ||
        prev_token == K_FI  ||
        prev_token == K_OD;

    bool curr_starts_stmt =
        t == IDENT      || t == K_IF       || t == K_DO       || t == K_ATOMIC ||
        t == K_D_STEP   || t == K_FOR      || t == K_SELECT   || t == K_RUN    ||
        t == K_BREAK    || t == K_SKIP     || t == K_GOTO     ||
        t == T_BYTE     || t == T_INT      || t == T_BOOL     || t == T_BIT    ||
        t == T_SHORT    || t == T_UNSIGNED || t == T_MTYPE    || t == T_CHAN;

    if (g_brace_depth > 0 && prev_closes_block && had_newline && curr_starts_stmt) {
        pending = t;
        prev_token = ';';
        return ';';
    }

    prev_token = t;
    return t;
}
