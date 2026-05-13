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
#line 13 "src/parser.y"

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
  YYSYMBOL_TYPENAME = 5,                   /* TYPENAME  */
  YYSYMBOL_T_BYTE = 6,                     /* T_BYTE  */
  YYSYMBOL_T_INT = 7,                      /* T_INT  */
  YYSYMBOL_T_BOOL = 8,                     /* T_BOOL  */
  YYSYMBOL_T_BIT = 9,                      /* T_BIT  */
  YYSYMBOL_T_SHORT = 10,                   /* T_SHORT  */
  YYSYMBOL_T_UNSIGNED = 11,                /* T_UNSIGNED  */
  YYSYMBOL_T_MTYPE = 12,                   /* T_MTYPE  */
  YYSYMBOL_T_CHAN = 13,                    /* T_CHAN  */
  YYSYMBOL_K_PROCTYPE = 14,                /* K_PROCTYPE  */
  YYSYMBOL_K_ACTIVE = 15,                  /* K_ACTIVE  */
  YYSYMBOL_K_INLINE = 16,                  /* K_INLINE  */
  YYSYMBOL_K_TYPEDEF = 17,                 /* K_TYPEDEF  */
  YYSYMBOL_K_LTL = 18,                     /* K_LTL  */
  YYSYMBOL_K_INIT = 19,                    /* K_INIT  */
  YYSYMBOL_K_DO = 20,                      /* K_DO  */
  YYSYMBOL_K_OD = 21,                      /* K_OD  */
  YYSYMBOL_K_IF = 22,                      /* K_IF  */
  YYSYMBOL_K_FI = 23,                      /* K_FI  */
  YYSYMBOL_K_ELSE = 24,                    /* K_ELSE  */
  YYSYMBOL_K_BREAK = 25,                   /* K_BREAK  */
  YYSYMBOL_K_GOTO = 26,                    /* K_GOTO  */
  YYSYMBOL_K_SKIP = 27,                    /* K_SKIP  */
  YYSYMBOL_K_ATOMIC = 28,                  /* K_ATOMIC  */
  YYSYMBOL_K_D_STEP = 29,                  /* K_D_STEP  */
  YYSYMBOL_K_UNLESS = 30,                  /* K_UNLESS  */
  YYSYMBOL_K_FOR = 31,                     /* K_FOR  */
  YYSYMBOL_K_SELECT = 32,                  /* K_SELECT  */
  YYSYMBOL_K_RUN = 33,                     /* K_RUN  */
  YYSYMBOL_K_OF = 34,                      /* K_OF  */
  YYSYMBOL_K_LEN = 35,                     /* K_LEN  */
  YYSYMBOL_K_NEMPTY = 36,                  /* K_NEMPTY  */
  YYSYMBOL_K_EMPTY = 37,                   /* K_EMPTY  */
  YYSYMBOL_K_NFULL = 38,                   /* K_NFULL  */
  YYSYMBOL_K_FULL = 39,                    /* K_FULL  */
  YYSYMBOL_K_PRINTF = 40,                  /* K_PRINTF  */
  YYSYMBOL_K_ASSERT = 41,                  /* K_ASSERT  */
  YYSYMBOL_K_TRUE = 42,                    /* K_TRUE  */
  YYSYMBOL_K_FALSE = 43,                   /* K_FALSE  */
  YYSYMBOL_OP_ARROW = 44,                  /* OP_ARROW  */
  YYSYMBOL_OP_DCOLON = 45,                 /* OP_DCOLON  */
  YYSYMBOL_OP_DOTDOT = 46,                 /* OP_DOTDOT  */
  YYSYMBOL_OP_INC = 47,                    /* OP_INC  */
  YYSYMBOL_OP_DEC = 48,                    /* OP_DEC  */
  YYSYMBOL_OP_AND = 49,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 50,                     /* OP_OR  */
  YYSYMBOL_OP_EQ = 51,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 52,                    /* OP_NEQ  */
  YYSYMBOL_OP_LE = 53,                     /* OP_LE  */
  YYSYMBOL_OP_GE = 54,                     /* OP_GE  */
  YYSYMBOL_OP_SHL = 55,                    /* OP_SHL  */
  YYSYMBOL_OP_SHR = 56,                    /* OP_SHR  */
  YYSYMBOL_LTL_ALWAYS = 57,                /* LTL_ALWAYS  */
  YYSYMBOL_LTL_EVENTUALLY = 58,            /* LTL_EVENTUALLY  */
  YYSYMBOL_LTL_UNTIL = 59,                 /* LTL_UNTIL  */
  YYSYMBOL_START_PROGRAM = 60,             /* START_PROGRAM  */
  YYSYMBOL_START_EXPR = 61,                /* START_EXPR  */
  YYSYMBOL_START_STMT_BLOCK = 62,          /* START_STMT_BLOCK  */
  YYSYMBOL_63_ = 63,                       /* ':'  */
  YYSYMBOL_LOW_PREC = 64,                  /* LOW_PREC  */
  YYSYMBOL_65_ = 65,                       /* '='  */
  YYSYMBOL_66_ = 66,                       /* '!'  */
  YYSYMBOL_67_ = 67,                       /* '?'  */
  YYSYMBOL_68_ = 68,                       /* '<'  */
  YYSYMBOL_69_ = 69,                       /* '>'  */
  YYSYMBOL_70_ = 70,                       /* '+'  */
  YYSYMBOL_71_ = 71,                       /* '-'  */
  YYSYMBOL_72_ = 72,                       /* '*'  */
  YYSYMBOL_73_ = 73,                       /* '/'  */
  YYSYMBOL_74_ = 74,                       /* '%'  */
  YYSYMBOL_UMINUS = 75,                    /* UMINUS  */
  YYSYMBOL_UNOT = 76,                      /* UNOT  */
  YYSYMBOL_PREFIX_INCDEC = 77,             /* PREFIX_INCDEC  */
  YYSYMBOL_78_ = 78,                       /* '['  */
  YYSYMBOL_79_ = 79,                       /* '.'  */
  YYSYMBOL_80_ = 80,                       /* ';'  */
  YYSYMBOL_81_ = 81,                       /* ']'  */
  YYSYMBOL_82_ = 82,                       /* '{'  */
  YYSYMBOL_83_ = 83,                       /* '}'  */
  YYSYMBOL_84_ = 84,                       /* ','  */
  YYSYMBOL_85_ = 85,                       /* '('  */
  YYSYMBOL_86_ = 86,                       /* ')'  */
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
  YYSYMBOL_proctype_decl = 110,            /* proctype_decl  */
  YYSYMBOL_inline_decl = 111,              /* inline_decl  */
  YYSYMBOL_init_decl = 112,                /* init_decl  */
  YYSYMBOL_params_opt = 113,               /* params_opt  */
  YYSYMBOL_param_list = 114,               /* param_list  */
  YYSYMBOL_param_group = 115,              /* param_group  */
  YYSYMBOL_ident_list_opt = 116,           /* ident_list_opt  */
  YYSYMBOL_expr_body = 117,                /* expr_body  */
  YYSYMBOL_stmt_body = 118,                /* stmt_body  */
  YYSYMBOL_stmt_block = 119,               /* stmt_block  */
  YYSYMBOL_stmt_seq = 120,                 /* stmt_seq  */
  YYSYMBOL_local_var_decl_stmt = 121,      /* local_var_decl_stmt  */
  YYSYMBOL_local_chan_decl_stmt = 122,     /* local_chan_decl_stmt  */
  YYSYMBOL_stmt = 123,                     /* stmt  */
  YYSYMBOL_assign_or_expr_stmt = 124,      /* assign_or_expr_stmt  */
  YYSYMBOL_simple_stmt = 125,              /* simple_stmt  */
  YYSYMBOL_if_stmt = 126,                  /* if_stmt  */
  YYSYMBOL_do_stmt = 127,                  /* do_stmt  */
  YYSYMBOL_branches = 128,                 /* branches  */
  YYSYMBOL_branch = 129,                   /* branch  */
  YYSYMBOL_atomic_stmt = 130,              /* atomic_stmt  */
  YYSYMBOL_dstep_stmt = 131,               /* dstep_stmt  */
  YYSYMBOL_for_stmt = 132,                 /* for_stmt  */
  YYSYMBOL_select_stmt = 133,              /* select_stmt  */
  YYSYMBOL_send_stmt = 134,                /* send_stmt  */
  YYSYMBOL_recv_stmt = 135,                /* recv_stmt  */
  YYSYMBOL_run_stmt = 136,                 /* run_stmt  */
  YYSYMBOL_break_stmt = 137,               /* break_stmt  */
  YYSYMBOL_skip_stmt = 138,                /* skip_stmt  */
  YYSYMBOL_goto_stmt = 139,                /* goto_stmt  */
  YYSYMBOL_expr_args = 140,                /* expr_args  */
  YYSYMBOL_expr_args_nonempty = 141,       /* expr_args_nonempty  */
  YYSYMBOL_expr = 142,                     /* expr  */
  YYSYMBOL_expr_no_ternary = 143,          /* expr_no_ternary  */
  YYSYMBOL_primary = 144                   /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 97 "src/parser.y"

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

#line 374 "build/parser.cpp"

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1572

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  218
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  430

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
       2,     2,     2,    66,     2,     2,     2,    74,     2,     2,
      85,    86,    72,    70,    84,    71,    79,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    80,
      68,    65,    69,    67,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    78,     2,    81,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,     2,    83,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    64,    75,
      76,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   232,   232,   233,   234,   237,   239,   247,   248,   249,
     250,   251,   252,   253,   254,   259,   270,   277,   295,   299,
     300,   301,   302,   303,   304,   305,   306,   313,   323,   324,
     325,   326,   327,   328,   329,   330,   337,   341,   347,   355,
     361,   368,   375,   386,   392,   401,   414,   415,   424,   433,
     439,   447,   453,   464,   471,   482,   489,   499,   509,   510,
     517,   524,   534,   541,   548,   555,   556,   566,   567,   568,
     569,   574,   579,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   606,   616,   627,   643,   662,
     675,   676,   680,   681,   691,   704,   721,   722,   727,   733,
     734,   741,   743,   745,   754,   760,   764,   768,   776,   784,
     789,   794,   800,   806,   813,   820,   826,   832,   839,   847,
     853,   860,   867,   879,   891,   902,   925,   926,   927,   928,
     929,   930,   931,   932,   933,   934,   935,   936,   937,   938,
     954,   968,   976,   983,   988,   999,  1009,  1016,  1028,  1036,
    1044,  1052,  1064,  1074,  1085,  1100,  1112,  1124,  1138,  1148,
    1149,  1150,  1160,  1161,  1165,  1171,  1181,  1182,  1183,  1184,
    1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,  1193,  1194,
    1195,  1196,  1197,  1198,  1199,  1214,  1215,  1216,  1217,  1218,
    1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,
    1229,  1230,  1231,  1235,  1236,  1237,  1238,  1244,  1250,  1257,
    1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273
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
  "TYPENAME", "T_BYTE", "T_INT", "T_BOOL", "T_BIT", "T_SHORT",
  "T_UNSIGNED", "T_MTYPE", "T_CHAN", "K_PROCTYPE", "K_ACTIVE", "K_INLINE",
  "K_TYPEDEF", "K_LTL", "K_INIT", "K_DO", "K_OD", "K_IF", "K_FI", "K_ELSE",
  "K_BREAK", "K_GOTO", "K_SKIP", "K_ATOMIC", "K_D_STEP", "K_UNLESS",
  "K_FOR", "K_SELECT", "K_RUN", "K_OF", "K_LEN", "K_NEMPTY", "K_EMPTY",
  "K_NFULL", "K_FULL", "K_PRINTF", "K_ASSERT", "K_TRUE", "K_FALSE",
  "OP_ARROW", "OP_DCOLON", "OP_DOTDOT", "OP_INC", "OP_DEC", "OP_AND",
  "OP_OR", "OP_EQ", "OP_NEQ", "OP_LE", "OP_GE", "OP_SHL", "OP_SHR",
  "LTL_ALWAYS", "LTL_EVENTUALLY", "LTL_UNTIL", "START_PROGRAM",
  "START_EXPR", "START_STMT_BLOCK", "':'", "LOW_PREC", "'='", "'!'", "'?'",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "UNOT",
  "PREFIX_INCDEC", "'['", "'.'", "';'", "']'", "'{'", "'}'", "','", "'('",
  "')'", "$accept", "start", "program_body", "top_decl", "var_decl_stmt",
  "chan_decl_stmt", "chan_type", "basic_type", "local_basic_type",
  "declarator_list", "declarator", "type_list", "typedef_decl",
  "field_decl_list", "field_decl_stmt", "field_decl_one_or_more",
  "field_one", "mtype_decl", "ident_list", "ltl_decl", "ltl_formula",
  "ltl_unary", "ltl_atom", "proctype_decl", "inline_decl", "init_decl",
  "params_opt", "param_list", "param_group", "ident_list_opt", "expr_body",
  "stmt_body", "stmt_block", "stmt_seq", "local_var_decl_stmt",
  "local_chan_decl_stmt", "stmt", "assign_or_expr_stmt", "simple_stmt",
  "if_stmt", "do_stmt", "branches", "branch", "atomic_stmt", "dstep_stmt",
  "for_stmt", "select_stmt", "send_stmt", "recv_stmt", "run_stmt",
  "break_stmt", "skip_stmt", "goto_stmt", "expr_args",
  "expr_args_nonempty", "expr", "expr_no_ternary", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-275)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,  -275,    19,   417,    59,   613,  -275,  -275,   -12,    65,
      70,    82,    85,  -275,  -275,   211,   211,    19,    19,    19,
    -275,  1236,   -32,   -25,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,    94,  -275,    26,    26,  -275,   157,  -275,    91,    91,
      93,    95,   172,   500,   181,   183,  -275,  -275,   226,   762,
     762,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  1430,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,    29,   204,     0,   220,   224,
     225,    91,  -275,  -275,  -275,   237,   183,  -275,  -275,  -275,
    -275,  -275,  -275,    19,    19,    19,    19,    19,   -32,   -32,
    -275,  -275,   767,    19,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,    19,    19,    19,    19,  -275,
    -275,  -275,    19,   238,   762,   159,   247,   569,    -3,  -275,
      20,  -275,  -275,  -275,   248,   251,   137,  -275,   133,   -52,
      15,   -55,  -275,   707,   707,   762,   762,  -275,  -275,    19,
     159,   159,   256,   179,   177,   261,   263,   184,   194,   195,
    -275,   -48,    72,   805,   843,   881,   919,   957,  -275,  1268,
     812,  1472,   888,   888,   119,   119,    63,    63,   119,   119,
      92,    92,  -275,  -275,  -275,  1071,  -275,  -275,   159,   159,
     212,   213,  1438,   -32,  -275,   272,   274,  -275,  -275,  -275,
     242,   254,   159,   638,  -275,   222,  -275,    19,    19,  -275,
     183,   762,   762,  -275,   762,   762,  -275,  -275,  -275,  1464,
     213,   213,   255,   315,   461,   239,   241,   315,   682,     6,
     245,  -275,  -275,  -275,  -275,  -275,  -275,  -275,    19,  -275,
    -275,  -275,  -275,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   707,
     707,    19,    19,   240,  -275,    19,  1361,  1104,  -275,  -275,
    -275,  -275,  -275,   243,  -275,   -57,   264,   315,   315,   244,
     249,  -275,   461,   319,   252,   257,   331,   -39,  -275,  -275,
    -275,  -275,  -275,     6,     6,     6,     8,     6,   -14,  -275,
    1399,    19,  1361,  1438,   850,  1498,   926,   926,   201,   201,
     218,   218,   201,   201,   110,   110,  -275,  -275,  -275,   302,
    1299,  1330,  -275,  1137,   273,   315,   260,   333,   337,   252,
     252,    91,   461,   258,   338,    91,   270,   266,  -275,   682,
     271,  -275,  -275,  -275,   -26,   -10,     6,     6,     6,  -275,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,   348,  1170,   707,    19,    19,   335,    19,   116,
    -275,  -275,  -275,  -275,  -275,    91,   268,  -275,    19,   331,
    -275,  -275,  -275,    81,  -275,   322,   408,   408,   362,   362,
     362,   362,    75,    75,   -26,   -26,   -26,  1368,  -275,   339,
     995,  1033,   290,  1361,   294,  -275,   461,  1203,  -275,  -275,
     295,    91,  -275,   682,  -275,   292,  -275,   682,  -275,  -275,
     128,    91,   135,   296,   682,  -275,   299,  -275,  -275,  -275
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     2,   203,   206,     0,     0,
       0,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       3,     0,   166,   206,    36,    28,    29,    30,    31,    32,
      33,    34,    18,     0,     0,   159,     0,   160,     0,     0,
       0,     0,     0,     0,     0,     0,     4,    99,   100,   105,
     106,   104,   143,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   142,     1,    27,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     6,     7,     8,     0,     0,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,   212,   213,
     183,   182,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
     210,   211,     0,     0,     0,   162,     0,     0,     0,   146,
       0,   161,   152,   153,     0,     0,     0,   101,     0,     0,
      39,     0,    37,     0,     0,   119,   120,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,     0,     0,     0,     0,   207,     0,
     180,   181,   178,   179,   176,   177,   172,   173,   174,   175,
     167,   168,   169,   170,   171,     0,   209,   139,     0,     0,
       0,   163,   164,   185,    35,     0,   148,   145,   147,   144,
       0,     0,   162,     0,   102,     0,   124,     0,     0,   123,
       0,   115,   116,   110,   111,   112,   109,   121,   122,   140,
     156,   157,    26,     0,    90,     0,     0,    96,     0,     0,
       0,    16,    15,   216,   214,   215,   218,   217,     0,   208,
     202,   201,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,     0,     0,     0,   103,     0,    40,     0,    38,   117,
     118,   113,   114,     0,    55,     0,    25,     0,     0,     0,
      91,    92,    90,     0,    97,     0,     0,     0,    46,    67,
      70,    68,    69,     0,     0,     0,     0,     0,     0,    58,
      66,     0,   184,   165,   199,   200,   197,   198,   195,   196,
     191,   192,   193,   194,   186,   187,   188,   189,   190,   149,
       0,     0,   158,     0,    41,     0,     0,     0,     0,    95,
      94,     0,     0,     0,     0,     0,    51,    48,    49,     0,
       0,    62,    63,    64,    84,     0,     0,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,     0,     0,     0,     0,     0,
      53,    56,    26,    85,    93,     0,     0,    88,     0,     0,
      47,    45,    65,    61,    59,    60,    82,    83,    80,    81,
      78,    79,    73,    74,    75,    76,    77,     0,    72,     0,
       0,     0,     0,    42,     0,    86,    90,     0,    50,    71,
       0,     0,   155,     0,    54,     0,    52,     0,   154,    43,
       0,     0,     0,     0,     0,    87,     0,   125,    44,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,  -275,  -275,  -275,  -275,    -4,    -5,  -275,   297,
     171,   -33,  -275,  -275,    64,  -275,    25,  -275,  -203,  -275,
    -260,   -90,     5,  -275,  -275,  -275,  -274,  -275,    73,  -275,
    -275,  -275,   -36,   -38,   -17,   -15,   -43,  -275,  -275,  -275,
    -275,   372,   -60,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   205,    76,     2,   306,   143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     4,     5,    82,    83,    84,    44,   278,    45,   141,
     142,   420,    87,   287,   288,   337,   338,    88,   275,    89,
     298,   299,   300,    90,    91,    92,   279,   280,   281,   285,
      20,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   128,   129,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   190,   191,    66,   192,    22
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    85,   132,   133,    21,   138,   147,   148,   333,   289,
     290,   289,   290,   205,   155,   120,   121,   230,   197,   100,
     101,   102,     6,     7,   284,   209,   326,   327,   206,   210,
     346,   145,   231,   146,   346,   347,   348,   345,   124,   347,
     348,   339,   127,   199,   340,   160,   122,   123,   291,   292,
     291,   292,   361,   362,     8,     9,    10,    11,    12,    67,
     125,    13,    14,   293,   294,   127,    15,    16,   198,   349,
     198,   127,   295,    93,   329,   330,   382,   296,   156,   296,
     207,   187,     1,     2,     3,    17,   383,   384,   385,   196,
      18,   297,   152,   208,   153,   163,   164,   165,   166,   167,
     213,   216,   217,   218,    19,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   145,   369,   146,   185,   346,   211,   214,   212,   215,
     347,   348,   415,   114,   115,   116,   117,   118,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   358,   359,   360,
      94,   219,   232,   361,   362,    95,   210,   126,    98,    99,
     216,   131,     6,     7,   116,   117,   118,    96,   269,   270,
      97,   271,   272,    43,   110,   111,   136,   143,   134,   145,
     135,   146,   256,   257,   258,   139,   214,   140,   215,   114,
     115,   116,   117,   118,     8,     9,    10,    11,    12,   404,
     327,    13,    14,   341,   342,   343,    15,    16,   154,   266,
     267,   423,   424,   203,     6,     7,   204,   216,   426,   424,
     277,   319,   202,   286,   157,   188,   220,   221,   158,   159,
     189,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     302,   161,   186,   214,    19,   215,     8,     9,    10,    11,
      12,   194,   200,    13,    14,   201,   250,   251,    15,    16,
     222,   223,   224,   320,   321,   225,   226,   323,   193,   227,
     143,   254,   255,   256,   257,   258,   228,   229,   277,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   254,   255,
     256,   257,   258,   193,   193,   373,    19,   243,   242,   377,
     265,   344,   145,   363,   146,   261,   144,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   259,   262,   143,   274,
     273,   216,   283,   301,   282,   325,   322,   328,   277,   332,
     331,   193,   193,   334,   286,   336,   327,   371,   368,   405,
     370,   372,   376,   335,   375,   193,   143,   214,   378,   215,
     379,   381,   398,   406,   260,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   400,   401,   402,
     403,   347,   413,   410,   414,   418,   427,   417,   421,   429,
     407,   268,   364,   162,   422,   425,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   277,   380,   408,   374,   130,   263,   419,     0,
       0,     0,   419,     0,     0,     0,     0,     0,     0,   428,
       6,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,   356,   357,   358,   359,   360,    33,     0,    34,
     361,   362,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     8,     9,    10,    11,    12,     0,     0,    13,
      14,   352,   353,     0,    15,    16,    68,    69,    70,    71,
      72,    73,    74,   276,    32,     0,   354,   355,   356,   357,
     358,   359,   360,    17,     0,     0,   361,   362,    18,     0,
       0,     0,     0,     0,   240,   241,     0,     0,     0,    43,
       0,     0,    19,     6,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,     0,     0,     0,     0,
      33,     0,    34,     0,     0,    35,    36,    37,    38,    39,
       0,    40,    41,    42,     0,     8,     9,    10,    11,    12,
       0,     0,    13,    14,     0,     0,     0,    15,    16,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,     0,    17,     0,     0,     0,
       0,    18,     6,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,   137,     0,    19,     0,     0,     0,    33,
       0,    34,     0,   195,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     8,     9,    10,    11,    12,     0,
       0,    13,    14,     0,     0,     0,    15,    16,    68,    69,
      70,    71,    72,    73,    74,    75,    32,    76,    77,    78,
      79,    80,    81,     0,     0,    17,     0,     0,     0,     0,
      18,     6,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,     0,    19,     0,     0,     0,    33,     0,
      34,     0,     0,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     8,     9,    10,    11,    12,     0,     0,
      13,    14,     0,     0,     0,    15,    16,    68,    69,    70,
      71,    72,    73,    74,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,     0,    18,
       6,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,   264,     0,    19,     0,     0,     0,    33,     0,    34,
       0,     0,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     8,     9,    10,    11,    12,     0,     0,    13,
      14,     0,     0,     0,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    23,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,    18,     0,
       0,     0,    33,     0,    34,     0,     0,    35,    36,    37,
      38,    39,    19,    40,    41,    42,     0,     8,     9,    10,
      11,    12,     0,     0,    13,    14,     0,     0,     0,    15,
      16,   103,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,    17,     0,
       0,     0,     0,    18,     0,   112,   113,   114,   115,   116,
     117,   118,     0,     0,     0,     0,     0,    19,     0,   103,
       0,     0,     0,   168,   104,   105,   106,   107,   108,   109,
     110,   111,     0,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   118,
     112,   113,   114,   115,   116,   117,   118,   103,     0,     0,
       0,   233,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   246,   247,   248,   249,   250,   251,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,   118,   252,   253,
     254,   255,   256,   257,   258,   103,     0,     0,     0,   234,
     104,   105,   106,   107,   108,   109,   110,   111,     0,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   118,   112,   113,   114,   115,
     116,   117,   118,   103,     0,     0,     0,   235,   104,   105,
     106,   107,   108,   109,   110,   111,     0,     0,     0,   248,
     249,   250,   251,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,   118,   252,   253,   254,   255,   256,   257,
     258,   103,     0,     0,     0,   236,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   118,     0,     0,     0,     0,     0,     0,     0,   103,
       0,     0,     0,   237,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   118,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,   411,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,   103,     0,     0,     0,   412,
     104,   105,   106,   107,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   118,     0,     0,   103,     0,
       0,     0,   239,   104,   105,   106,   107,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   118,     0,
       0,   103,     0,     0,     0,   324,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   118,     0,     0,   103,     0,     0,     0,   367,   104,
     105,   106,   107,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   118,     0,     0,   103,     0,     0,
       0,   399,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,   118,     0,     0,
     103,     0,     0,     0,   416,   104,   105,   106,   107,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117,
     118,     0,   103,     0,     0,     0,   119,   104,   105,   106,
     107,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,   112,   113,   114,   115,
     116,   117,   118,   103,     0,   365,     0,     0,   104,   105,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,   118,   103,     0,   366,     0,     0,   104,
     105,   106,   107,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   118,   103,     0,     0,     0,     0,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   350,
     351,   352,   353,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   118,   354,   355,   356,   357,
     358,   359,   360,     0,     0,     0,   361,   362,     0,   409,
     350,   351,   352,   353,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   354,   355,   356,
     357,   358,   359,   360,     0,     0,     0,   361,   362,   104,
     105,   106,   107,   108,   109,   110,   111,   244,   245,   246,
     247,   248,   249,   250,   251,   149,   150,   151,   112,   113,
     114,   115,   116,   117,   118,     0,   252,   253,   254,   255,
     256,   257,   258,   104,   105,   106,   107,   108,   109,   110,
     111,   104,     0,   106,   107,   108,   109,   110,   111,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   118,     0,
     112,   113,   114,   115,   116,   117,   118,   244,     0,   246,
     247,   248,   249,   250,   251,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   252,   253,   254,   255,
     256,   257,   258
};

static const yytype_int16 yycheck[] =
{
       5,     5,    38,    39,     2,    43,    49,    50,   282,     3,
       4,     3,     4,    65,    14,    47,    48,    65,    21,    17,
      18,    19,     3,     4,   227,    80,    83,    84,    80,    84,
      44,    48,    80,    48,    44,    49,    50,   297,    63,    49,
      50,    80,    45,    23,    83,    81,    78,    79,    42,    43,
      42,    43,    78,    79,    35,    36,    37,    38,    39,     0,
      85,    42,    43,    57,    58,    45,    47,    48,   128,    83,
     130,    45,    66,    85,   277,   278,    86,    71,    78,    71,
      65,   124,    60,    61,    62,    66,   346,   347,   348,   127,
      71,    85,    63,    78,    65,    93,    94,    95,    96,    97,
     143,   144,   145,   146,    85,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   138,   325,   138,   122,    44,   143,   144,   143,   144,
      49,    50,   406,    70,    71,    72,    73,    74,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    72,    73,    74,
      85,   149,    80,    78,    79,    85,    84,    63,    15,    16,
     203,     4,     3,     4,    72,    73,    74,    85,   211,   212,
      85,   214,   215,    82,    55,    56,     4,    44,    85,   196,
      85,   196,    72,    73,    74,     4,   203,     4,   203,    70,
      71,    72,    73,    74,    35,    36,    37,    38,    39,    83,
      84,    42,    43,   293,   294,   295,    47,    48,     4,   207,
     208,    83,    84,    80,     3,     4,    83,   260,    83,    84,
     224,   259,    85,   228,     4,    66,   150,   151,     4,     4,
      71,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     238,     4,     4,   260,    85,   260,    35,    36,    37,    38,
      39,     4,     4,    42,    43,     4,    55,    56,    47,    48,
       4,    82,    85,   261,   262,     4,     3,   265,   125,    85,
      44,    70,    71,    72,    73,    74,    82,    82,   282,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    70,    71,
      72,    73,    74,   150,   151,   331,    85,    84,    86,   335,
      78,   296,   319,   301,   319,    63,    80,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    44,    63,    44,     4,
      65,   364,    81,    78,    85,    82,    86,    63,   332,    80,
      86,   188,   189,    14,   339,     4,    84,     4,    65,   375,
      80,     4,     4,    86,    86,   202,    44,   364,    78,   364,
      84,    80,     4,    85,    80,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   365,   366,    34,
     368,    49,    82,    34,    80,   411,    80,    82,    86,    80,
     378,   210,    80,    86,   417,   421,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   406,   339,   379,   332,    34,   202,   413,    -1,
      -1,    -1,   417,    -1,    -1,    -1,    -1,    -1,    -1,   424,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    70,    71,    72,    73,    74,    20,    -1,    22,
      78,    79,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    42,
      43,    53,    54,    -1,    47,    48,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    68,    69,    70,    71,
      72,    73,    74,    66,    -1,    -1,    78,    79,    71,    -1,
      -1,    -1,    -1,    -1,   188,   189,    -1,    -1,    -1,    82,
      -1,    -1,    85,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    -1,    -1,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      -1,    -1,    42,    43,    -1,    -1,    -1,    47,    48,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,    -1,    66,    -1,    -1,    -1,
      -1,    71,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    83,    -1,    85,    -1,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    -1,
      -1,    42,    43,    -1,    -1,    -1,    47,    48,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      71,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    85,    -1,    -1,    -1,    20,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    -1,    -1,
      42,    43,    -1,    -1,    -1,    47,    48,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    83,    -1,    85,    -1,    -1,    -1,    20,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    42,
      43,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    20,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    29,    85,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    -1,    -1,    42,    43,    -1,    -1,    -1,    47,
      48,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    71,    -1,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    85,    -1,    44,
      -1,    -1,    -1,    86,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      68,    69,    70,    71,    72,    73,    74,    44,    -1,    -1,
      -1,    86,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    68,    69,
      70,    71,    72,    73,    74,    44,    -1,    -1,    -1,    86,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    68,    69,    70,    71,
      72,    73,    74,    44,    -1,    -1,    -1,    86,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    68,    69,    70,    71,    72,    73,
      74,    44,    -1,    -1,    -1,    86,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    86,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    86,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    86,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    44,    -1,
      -1,    -1,    81,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    44,    -1,    -1,    -1,    81,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    44,    -1,    -1,    -1,    81,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    44,    -1,    -1,
      -1,    81,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      44,    -1,    -1,    -1,    81,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    -1,    44,    -1,    -1,    -1,    80,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    44,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    44,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    78,    79,    -1,    81,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    78,    79,    49,
      50,    51,    52,    53,    54,    55,    56,    49,    50,    51,
      52,    53,    54,    55,    56,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    68,    69,    70,    71,
      72,    73,    74,    49,    50,    51,    52,    53,    54,    55,
      56,    49,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    -1,
      68,    69,    70,    71,    72,    73,    74,    49,    -1,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,    61,    62,    88,    89,     3,     4,    35,    36,
      37,    38,    39,    42,    43,    47,    48,    66,    71,    85,
     117,   142,   144,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    20,    22,    25,    26,    27,    28,    29,
      31,    32,    33,    82,    93,    95,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   142,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    14,    15,    16,    17,
      18,    19,    90,    91,    92,    93,    94,    99,   104,   106,
     110,   111,   112,    85,    85,    85,    85,    85,   144,   144,
     142,   142,   142,    44,    49,    50,    51,    52,    53,    54,
      55,    56,    68,    69,    70,    71,    72,    73,    74,    80,
      47,    48,    78,    79,    63,    85,    63,    45,   128,   129,
     128,     4,   119,   119,    85,    85,     4,    83,   120,     4,
       4,    96,    97,    44,    80,   121,   122,   123,   123,    65,
      66,    67,    63,    65,     4,    14,    78,     4,     4,     4,
     119,     4,    96,   142,   142,   142,   142,   142,    86,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,     4,   123,    66,    71,
     140,   141,   143,   144,     4,    24,   120,    21,   129,    23,
       4,     4,    85,    80,    83,    65,    80,    65,    78,    80,
      84,   121,   122,   123,   121,   122,   123,   123,   123,   142,
     141,   141,     4,    82,    85,     4,     3,    85,    82,    82,
      65,    80,    80,    86,    86,    86,    86,    86,    63,    81,
     143,   143,    86,    84,    49,    50,    51,    52,    53,    54,
      55,    56,    68,    69,    70,    71,    72,    73,    74,    44,
      80,    63,    63,   140,    83,    78,   142,   142,    97,   123,
     123,   123,   123,    65,     4,   105,    12,    93,    94,   113,
     114,   115,    85,    81,   105,   116,    94,   100,   101,     3,
       4,    42,    43,    57,    58,    66,    71,    85,   107,   108,
     109,    78,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   120,
     142,   142,    86,   142,    81,    82,    83,    84,    63,   105,
     105,    86,    80,   113,    14,    86,     4,   102,   103,    80,
      83,   108,   108,   108,   109,   107,    44,    49,    50,    83,
      51,    52,    53,    54,    68,    69,    70,    71,    72,    73,
      74,    78,    79,   142,    80,    46,    46,    81,    65,   105,
      80,     4,     4,   119,   115,    86,     4,   119,    78,    84,
     101,    80,    86,   107,   107,   107,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,     4,    81,
     142,   142,    34,   142,    83,   119,    85,   142,   103,    81,
      34,    86,    86,    82,    80,   113,    81,    82,   119,    94,
      98,    86,    98,    83,    84,   119,    83,    80,    94,    80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    88,    88,    89,    89,    90,    90,    90,
      90,    90,    90,    90,    90,    91,    92,    92,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    97,
      97,    97,    97,    98,    98,    99,   100,   100,   101,   102,
     102,   103,   103,   104,   104,   105,   105,   106,   107,   107,
     107,   107,   108,   108,   108,   108,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   111,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   118,
     118,   119,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   122,   122,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   124,   125,   126,   127,   128,   128,   129,   129,
     129,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   140,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,    11,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     3,     1,
       3,     4,     6,     1,     3,     6,     1,     3,     2,     1,
       3,     1,     4,     6,     8,     1,     3,     5,     1,     3,
       3,     3,     2,     2,     2,     3,     1,     1,     1,     1,
       1,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     6,     7,    10,     6,     2,
       0,     1,     1,     3,     2,     2,     0,     1,     2,     1,
       1,     2,     3,     4,     1,     1,     1,     2,     2,     3,
       3,     3,     3,     4,     4,     3,     3,     4,     4,     2,
       2,     3,     3,     3,     3,    11,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     4,     1,     1,     3,     3,     1,     2,     2,     4,
       5,     3,     2,     2,     9,     8,     3,     3,     5,     1,
       1,     2,     0,     1,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     5,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     1,     1,     3,     4,     3,
       2,     2,     2,     2,     4,     4,     4,     4,     4
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
#line 232 "src/parser.y"
                                       { if (!g_root) g_root = new p2p::Module(); }
#line 2128 "build/parser.cpp"
    break;

  case 6: /* program_body: program_body top_decl  */
#line 240 "src/parser.y"
        {
            if (!g_root) g_root = new p2p::Module();
            if ((yyvsp[0].node)) g_root->declarations.emplace_back((yyvsp[0].node));
        }
#line 2137 "build/parser.cpp"
    break;

  case 7: /* top_decl: var_decl_stmt  */
#line 247 "src/parser.y"
                           { push_decls(*(yyvsp[0].vardecl_list)); delete (yyvsp[0].vardecl_list); (yyval.node) = nullptr; }
#line 2143 "build/parser.cpp"
    break;

  case 8: /* top_decl: chan_decl_stmt  */
#line 248 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2149 "build/parser.cpp"
    break;

  case 9: /* top_decl: typedef_decl  */
#line 249 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2155 "build/parser.cpp"
    break;

  case 10: /* top_decl: mtype_decl  */
#line 250 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2161 "build/parser.cpp"
    break;

  case 11: /* top_decl: ltl_decl  */
#line 251 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2167 "build/parser.cpp"
    break;

  case 12: /* top_decl: proctype_decl  */
#line 252 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2173 "build/parser.cpp"
    break;

  case 13: /* top_decl: inline_decl  */
#line 253 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2179 "build/parser.cpp"
    break;

  case 14: /* top_decl: init_decl  */
#line 254 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2185 "build/parser.cpp"
    break;

  case 15: /* var_decl_stmt: basic_type declarator_list ';'  */
#line 260 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            (yyval.vardecl_list) = (yyvsp[-1].vardecl_list);
        }
#line 2195 "build/parser.cpp"
    break;

  case 16: /* chan_decl_stmt: chan_type IDENT ';'  */
#line 271 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-1].str_val); free((yyvsp[-1].str_val));
            d->type.reset((yyvsp[-2].type));
            (yyval.node) = d;
        }
#line 2206 "build/parser.cpp"
    break;

  case 17: /* chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 278 "src/parser.y"
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
#line 2225 "build/parser.cpp"
    break;

  case 18: /* chan_type: T_CHAN  */
#line 295 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Chan); }
#line 2231 "build/parser.cpp"
    break;

  case 19: /* basic_type: T_BYTE  */
#line 299 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2237 "build/parser.cpp"
    break;

  case 20: /* basic_type: T_INT  */
#line 300 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2243 "build/parser.cpp"
    break;

  case 21: /* basic_type: T_BOOL  */
#line 301 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2249 "build/parser.cpp"
    break;

  case 22: /* basic_type: T_BIT  */
#line 302 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2255 "build/parser.cpp"
    break;

  case 23: /* basic_type: T_SHORT  */
#line 303 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2261 "build/parser.cpp"
    break;

  case 24: /* basic_type: T_UNSIGNED  */
#line 304 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2267 "build/parser.cpp"
    break;

  case 25: /* basic_type: T_MTYPE  */
#line 305 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2273 "build/parser.cpp"
    break;

  case 26: /* basic_type: T_MTYPE ':' IDENT  */
#line 307 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2284 "build/parser.cpp"
    break;

  case 27: /* basic_type: TYPENAME  */
#line 313 "src/parser.y"
                           { (yyval.type) = make_named((yyvsp[0].str_val)); free((yyvsp[0].str_val)); }
#line 2290 "build/parser.cpp"
    break;

  case 28: /* local_basic_type: T_BYTE  */
#line 323 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Byte); }
#line 2296 "build/parser.cpp"
    break;

  case 29: /* local_basic_type: T_INT  */
#line 324 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Int); }
#line 2302 "build/parser.cpp"
    break;

  case 30: /* local_basic_type: T_BOOL  */
#line 325 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bool); }
#line 2308 "build/parser.cpp"
    break;

  case 31: /* local_basic_type: T_BIT  */
#line 326 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Bit); }
#line 2314 "build/parser.cpp"
    break;

  case 32: /* local_basic_type: T_SHORT  */
#line 327 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Short); }
#line 2320 "build/parser.cpp"
    break;

  case 33: /* local_basic_type: T_UNSIGNED  */
#line 328 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Unsigned); }
#line 2326 "build/parser.cpp"
    break;

  case 34: /* local_basic_type: T_MTYPE  */
#line 329 "src/parser.y"
                           { (yyval.type) = make_basic(p2p::BasicTypeKind::Mtype); }
#line 2332 "build/parser.cpp"
    break;

  case 35: /* local_basic_type: T_MTYPE ':' IDENT  */
#line 331 "src/parser.y"
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.type) = t;
        }
#line 2343 "build/parser.cpp"
    break;

  case 36: /* local_basic_type: TYPENAME  */
#line 337 "src/parser.y"
                           { (yyval.type) = make_named((yyvsp[0].str_val)); free((yyvsp[0].str_val)); }
#line 2349 "build/parser.cpp"
    break;

  case 37: /* declarator_list: declarator  */
#line 342 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2359 "build/parser.cpp"
    break;

  case 38: /* declarator_list: declarator_list ',' declarator  */
#line 348 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2368 "build/parser.cpp"
    break;

  case 39: /* declarator: IDENT  */
#line 356 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2378 "build/parser.cpp"
    break;

  case 40: /* declarator: IDENT '=' expr  */
#line 362 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2389 "build/parser.cpp"
    break;

  case 41: /* declarator: IDENT '[' expr ']'  */
#line 369 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2400 "build/parser.cpp"
    break;

  case 42: /* declarator: IDENT '[' expr ']' '=' expr  */
#line 376 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            d->array_size.reset((yyvsp[-3].expr));
            d->init.reset((yyvsp[0].expr));
            (yyval.var_decl) = d;
        }
#line 2412 "build/parser.cpp"
    break;

  case 43: /* type_list: basic_type  */
#line 387 "src/parser.y"
        {
            auto* tl = new TypeList();
            tl->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = tl;
        }
#line 2422 "build/parser.cpp"
    break;

  case 44: /* type_list: type_list ',' basic_type  */
#line 393 "src/parser.y"
        {
            (yyvsp[-2].type_list)->items.emplace_back((yyvsp[0].type));
            (yyval.type_list) = (yyvsp[-2].type_list);
        }
#line 2431 "build/parser.cpp"
    break;

  case 45: /* typedef_decl: K_TYPEDEF IDENT '{' field_decl_list '}' ';'  */
#line 402 "src/parser.y"
        {
            auto* td = new p2p::TypedefDecl();
            td->name = (yyvsp[-4].str_val);
            p2p::typedef_register(td->name);   /* <-- добавь эту строку */
            free((yyvsp[-4].str_val));
            td->fields = std::move((yyvsp[-2].vardecl_list)->items);
            delete (yyvsp[-2].vardecl_list);
            (yyval.node) = td;
        }
#line 2445 "build/parser.cpp"
    break;

  case 46: /* field_decl_list: field_decl_stmt  */
#line 414 "src/parser.y"
                                               { (yyval.vardecl_list) = (yyvsp[0].vardecl_list); }
#line 2451 "build/parser.cpp"
    break;

  case 47: /* field_decl_list: field_decl_list ';' field_decl_stmt  */
#line 416 "src/parser.y"
        {
            for (auto& f : (yyvsp[0].vardecl_list)->items) (yyvsp[-2].vardecl_list)->items.emplace_back(std::move(f));
            delete (yyvsp[0].vardecl_list);
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2461 "build/parser.cpp"
    break;

  case 48: /* field_decl_stmt: basic_type field_decl_one_or_more  */
#line 425 "src/parser.y"
        {
            attach_type(*(yyvsp[0].vardecl_list), *(yyvsp[-1].type));
            delete (yyvsp[-1].type);
            (yyval.vardecl_list) = (yyvsp[0].vardecl_list);
        }
#line 2471 "build/parser.cpp"
    break;

  case 49: /* field_decl_one_or_more: field_one  */
#line 434 "src/parser.y"
        {
            auto* l = new VarDeclList();
            l->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = l;
        }
#line 2481 "build/parser.cpp"
    break;

  case 50: /* field_decl_one_or_more: field_decl_one_or_more ',' field_one  */
#line 440 "src/parser.y"
        {
            (yyvsp[-2].vardecl_list)->items.emplace_back((yyvsp[0].var_decl));
            (yyval.vardecl_list) = (yyvsp[-2].vardecl_list);
        }
#line 2490 "build/parser.cpp"
    break;

  case 51: /* field_one: IDENT  */
#line 448 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.var_decl) = d;
        }
#line 2500 "build/parser.cpp"
    break;

  case 52: /* field_one: IDENT '[' expr ']'  */
#line 454 "src/parser.y"
        {
            auto* d = new p2p::VarDecl();
            d->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            d->array_size.reset((yyvsp[-1].expr));
            (yyval.var_decl) = d;
        }
#line 2511 "build/parser.cpp"
    break;

  case 53: /* mtype_decl: T_MTYPE '=' '{' ident_list '}' ';'  */
#line 465 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2522 "build/parser.cpp"
    break;

  case 54: /* mtype_decl: T_MTYPE ':' IDENT '=' '{' ident_list '}' ';'  */
#line 472 "src/parser.y"
        {
            auto* m = new p2p::MtypeDecl();
            m->set_name = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            m->names = std::move((yyvsp[-2].ident_list)->items);
            delete (yyvsp[-2].ident_list);
            (yyval.node) = m;
        }
#line 2534 "build/parser.cpp"
    break;

  case 55: /* ident_list: IDENT  */
#line 483 "src/parser.y"
        {
            auto* il = new IdentList();
            il->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = il;
        }
#line 2545 "build/parser.cpp"
    break;

  case 56: /* ident_list: ident_list ',' IDENT  */
#line 490 "src/parser.y"
        {
            (yyvsp[-2].ident_list)->items.emplace_back((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.ident_list) = (yyvsp[-2].ident_list);
        }
#line 2555 "build/parser.cpp"
    break;

  case 57: /* ltl_decl: K_LTL IDENT '{' ltl_formula '}'  */
#line 500 "src/parser.y"
        {
            auto* l = new p2p::LtlDecl();
            l->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            l->formula.reset((yyvsp[-1].ltl));
            (yyval.node) = l;
        }
#line 2566 "build/parser.cpp"
    break;

  case 58: /* ltl_formula: ltl_unary  */
#line 509 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[0].ltl); }
#line 2572 "build/parser.cpp"
    break;

  case 59: /* ltl_formula: ltl_formula OP_AND ltl_formula  */
#line 511 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::And;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2583 "build/parser.cpp"
    break;

  case 60: /* ltl_formula: ltl_formula OP_OR ltl_formula  */
#line 518 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Or;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2594 "build/parser.cpp"
    break;

  case 61: /* ltl_formula: ltl_formula OP_ARROW ltl_formula  */
#line 525 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Implies;
            f->lhs.reset((yyvsp[-2].ltl)); f->rhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2605 "build/parser.cpp"
    break;

  case 62: /* ltl_unary: LTL_ALWAYS ltl_unary  */
#line 535 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Always;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2616 "build/parser.cpp"
    break;

  case 63: /* ltl_unary: LTL_EVENTUALLY ltl_unary  */
#line 542 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Eventually;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2627 "build/parser.cpp"
    break;

  case 64: /* ltl_unary: '!' ltl_unary  */
#line 549 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Not;
            f->lhs.reset((yyvsp[0].ltl));
            (yyval.ltl) = f;
        }
#line 2638 "build/parser.cpp"
    break;

  case 65: /* ltl_unary: '(' ltl_formula ')'  */
#line 555 "src/parser.y"
                                         { (yyval.ltl) = (yyvsp[-1].ltl); }
#line 2644 "build/parser.cpp"
    break;

  case 66: /* ltl_unary: ltl_atom  */
#line 557 "src/parser.y"
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Atom;
            f->atom.reset((yyvsp[0].expr));
            (yyval.ltl) = f;
        }
#line 2655 "build/parser.cpp"
    break;

  case 67: /* ltl_atom: INT_LITERAL  */
#line 566 "src/parser.y"
                                        { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 2661 "build/parser.cpp"
    break;

  case 68: /* ltl_atom: K_TRUE  */
#line 567 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 2667 "build/parser.cpp"
    break;

  case 69: /* ltl_atom: K_FALSE  */
#line 568 "src/parser.y"
                                        { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 2673 "build/parser.cpp"
    break;

  case 70: /* ltl_atom: IDENT  */
#line 569 "src/parser.y"
                                        {
                                          auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
                                          free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2683 "build/parser.cpp"
    break;

  case 71: /* ltl_atom: ltl_atom '[' ltl_atom ']'  */
#line 574 "src/parser.y"
                                        {
                                          auto* e = new p2p::IndexExpr();
                                          e->base.reset((yyvsp[-3].expr)); e->index.reset((yyvsp[-1].expr));
                                          (yyval.expr) = e;
                                        }
#line 2693 "build/parser.cpp"
    break;

  case 72: /* ltl_atom: ltl_atom '.' IDENT  */
#line 579 "src/parser.y"
                                        {
                                          auto* e = new p2p::FieldExpr();
                                          e->base.reset((yyvsp[-2].expr));
                                          e->field = (yyvsp[0].str_val); free((yyvsp[0].str_val));
                                          (yyval.expr) = e;
                                        }
#line 2704 "build/parser.cpp"
    break;

  case 73: /* ltl_atom: ltl_atom '+' ltl_atom  */
#line 585 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2710 "build/parser.cpp"
    break;

  case 74: /* ltl_atom: ltl_atom '-' ltl_atom  */
#line 586 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2716 "build/parser.cpp"
    break;

  case 75: /* ltl_atom: ltl_atom '*' ltl_atom  */
#line 587 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2722 "build/parser.cpp"
    break;

  case 76: /* ltl_atom: ltl_atom '/' ltl_atom  */
#line 588 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2728 "build/parser.cpp"
    break;

  case 77: /* ltl_atom: ltl_atom '%' ltl_atom  */
#line 589 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2734 "build/parser.cpp"
    break;

  case 78: /* ltl_atom: ltl_atom '<' ltl_atom  */
#line 590 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2740 "build/parser.cpp"
    break;

  case 79: /* ltl_atom: ltl_atom '>' ltl_atom  */
#line 591 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2746 "build/parser.cpp"
    break;

  case 80: /* ltl_atom: ltl_atom OP_LE ltl_atom  */
#line 592 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2752 "build/parser.cpp"
    break;

  case 81: /* ltl_atom: ltl_atom OP_GE ltl_atom  */
#line 593 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2758 "build/parser.cpp"
    break;

  case 82: /* ltl_atom: ltl_atom OP_EQ ltl_atom  */
#line 594 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2764 "build/parser.cpp"
    break;

  case 83: /* ltl_atom: ltl_atom OP_NEQ ltl_atom  */
#line 595 "src/parser.y"
                                        { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2770 "build/parser.cpp"
    break;

  case 84: /* ltl_atom: '-' ltl_atom  */
#line 596 "src/parser.y"
                                        { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 2776 "build/parser.cpp"
    break;

  case 85: /* proctype_decl: K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 607 "src/parser.y"
        {
            auto* p = new p2p::ProctypeDecl();
            p->name = (yyvsp[-4].str_val); free((yyvsp[-4].str_val));
            p->params = std::move((yyvsp[-2].param_list)->items);
            delete (yyvsp[-2].param_list);
            p->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = p;
        }
#line 2790 "build/parser.cpp"
    break;

  case 86: /* proctype_decl: K_ACTIVE K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 617 "src/parser.y"
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
#line 2805 "build/parser.cpp"
    break;

  case 87: /* proctype_decl: K_ACTIVE '[' INT_LITERAL ']' K_PROCTYPE IDENT '(' params_opt ')' stmt_block  */
#line 628 "src/parser.y"
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
#line 2820 "build/parser.cpp"
    break;

  case 88: /* inline_decl: K_INLINE IDENT '(' ident_list_opt ')' stmt_block  */
#line 644 "src/parser.y"
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
#line 2839 "build/parser.cpp"
    break;

  case 89: /* init_decl: K_INIT stmt_block  */
#line 663 "src/parser.y"
        {
            auto* d = new p2p::InitDecl();
            d->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.node) = d;
        }
#line 2850 "build/parser.cpp"
    break;

  case 90: /* params_opt: %empty  */
#line 675 "src/parser.y"
                               { (yyval.param_list) = new ParamList(); }
#line 2856 "build/parser.cpp"
    break;

  case 91: /* params_opt: param_list  */
#line 676 "src/parser.y"
                               { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2862 "build/parser.cpp"
    break;

  case 92: /* param_list: param_group  */
#line 680 "src/parser.y"
                               { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2868 "build/parser.cpp"
    break;

  case 93: /* param_list: param_list ';' param_group  */
#line 682 "src/parser.y"
        {
            for (auto& p : (yyvsp[0].param_list)->items) (yyvsp[-2].param_list)->items.push_back(std::move(p));
            delete (yyvsp[0].param_list);
            (yyval.param_list) = (yyvsp[-2].param_list);
        }
#line 2878 "build/parser.cpp"
    break;

  case 94: /* param_group: basic_type ident_list  */
#line 692 "src/parser.y"
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
#line 2895 "build/parser.cpp"
    break;

  case 95: /* param_group: chan_type ident_list  */
#line 705 "src/parser.y"
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
#line 2912 "build/parser.cpp"
    break;

  case 96: /* ident_list_opt: %empty  */
#line 721 "src/parser.y"
                               { (yyval.ident_list) = new IdentList(); }
#line 2918 "build/parser.cpp"
    break;

  case 97: /* ident_list_opt: ident_list  */
#line 722 "src/parser.y"
                               { (yyval.ident_list) = (yyvsp[0].ident_list); }
#line 2924 "build/parser.cpp"
    break;

  case 98: /* expr_body: expr ';'  */
#line 727 "src/parser.y"
                { g_expr_result = (yyvsp[-1].expr); }
#line 2930 "build/parser.cpp"
    break;

  case 99: /* stmt_body: stmt_block  */
#line 733 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2936 "build/parser.cpp"
    break;

  case 100: /* stmt_body: stmt_seq  */
#line 734 "src/parser.y"
                                        { g_stmt_result = (yyvsp[0].stmt_list); }
#line 2942 "build/parser.cpp"
    break;

  case 101: /* stmt_block: '{' '}'  */
#line 742 "src/parser.y"
        { (yyval.stmt_list) = new StmtList(); }
#line 2948 "build/parser.cpp"
    break;

  case 102: /* stmt_block: '{' stmt_seq '}'  */
#line 744 "src/parser.y"
        { (yyval.stmt_list) = (yyvsp[-1].stmt_list); }
#line 2954 "build/parser.cpp"
    break;

  case 103: /* stmt_block: '{' stmt_seq ';' '}'  */
#line 746 "src/parser.y"
        { (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 2960 "build/parser.cpp"
    break;

  case 104: /* stmt_seq: stmt  */
#line 755 "src/parser.y"
        {
            auto* l = new StmtList();
            l->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = l;
        }
#line 2970 "build/parser.cpp"
    break;

  case 105: /* stmt_seq: local_var_decl_stmt  */
#line 761 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2978 "build/parser.cpp"
    break;

  case 106: /* stmt_seq: local_chan_decl_stmt  */
#line 765 "src/parser.y"
        {
            (yyval.stmt_list) = (yyvsp[0].stmt_list);
        }
#line 2986 "build/parser.cpp"
    break;

  case 107: /* stmt_seq: local_var_decl_stmt stmt  */
#line 769 "src/parser.y"
        {
            auto* l = new StmtList();
            for (auto& s : (yyvsp[-1].stmt_list)->items) l->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            l->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = l;
        }
#line 2998 "build/parser.cpp"
    break;

  case 108: /* stmt_seq: local_chan_decl_stmt stmt  */
#line 777 "src/parser.y"
        {
            auto* l = new StmtList();
            for (auto& s : (yyvsp[-1].stmt_list)->items) l->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            l->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = l;
        }
#line 3010 "build/parser.cpp"
    break;

  case 109: /* stmt_seq: stmt_seq ';' stmt  */
#line 785 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3019 "build/parser.cpp"
    break;

  case 110: /* stmt_seq: stmt_seq OP_ARROW stmt  */
#line 790 "src/parser.y"
        {
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3028 "build/parser.cpp"
    break;

  case 111: /* stmt_seq: stmt_seq ';' local_var_decl_stmt  */
#line 795 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3038 "build/parser.cpp"
    break;

  case 112: /* stmt_seq: stmt_seq ';' local_chan_decl_stmt  */
#line 801 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3048 "build/parser.cpp"
    break;

  case 113: /* stmt_seq: stmt_seq ';' local_var_decl_stmt stmt  */
#line 807 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-3].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-3].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-3].stmt_list);
        }
#line 3059 "build/parser.cpp"
    break;

  case 114: /* stmt_seq: stmt_seq ';' local_chan_decl_stmt stmt  */
#line 814 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-3].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-3].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-3].stmt_list);
        }
#line 3070 "build/parser.cpp"
    break;

  case 115: /* stmt_seq: stmt_seq OP_ARROW local_var_decl_stmt  */
#line 821 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3080 "build/parser.cpp"
    break;

  case 116: /* stmt_seq: stmt_seq OP_ARROW local_chan_decl_stmt  */
#line 827 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3090 "build/parser.cpp"
    break;

  case 117: /* stmt_seq: stmt_seq OP_ARROW local_var_decl_stmt stmt  */
#line 833 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-3].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-3].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-3].stmt_list);
        }
#line 3101 "build/parser.cpp"
    break;

  case 118: /* stmt_seq: stmt_seq OP_ARROW local_chan_decl_stmt stmt  */
#line 840 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-3].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-3].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-3].stmt_list);
        }
#line 3112 "build/parser.cpp"
    break;

  case 119: /* stmt_seq: stmt_seq local_var_decl_stmt  */
#line 848 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 3122 "build/parser.cpp"
    break;

  case 120: /* stmt_seq: stmt_seq local_chan_decl_stmt  */
#line 854 "src/parser.y"
        {
            for (auto& s : (yyvsp[0].stmt_list)->items) (yyvsp[-1].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[0].stmt_list);
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        }
#line 3132 "build/parser.cpp"
    break;

  case 121: /* stmt_seq: stmt_seq local_var_decl_stmt stmt  */
#line 861 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3143 "build/parser.cpp"
    break;

  case 122: /* stmt_seq: stmt_seq local_chan_decl_stmt stmt  */
#line 868 "src/parser.y"
        {
            for (auto& s : (yyvsp[-1].stmt_list)->items) (yyvsp[-2].stmt_list)->items.emplace_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
            (yyvsp[-2].stmt_list)->items.emplace_back((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        }
#line 3154 "build/parser.cpp"
    break;

  case 123: /* local_var_decl_stmt: local_basic_type declarator_list ';'  */
#line 880 "src/parser.y"
        {
            attach_type(*(yyvsp[-1].vardecl_list), *(yyvsp[-2].type));
            delete (yyvsp[-2].type);
            auto* out = new StmtList();
            wrap_local_decls(*(yyvsp[-1].vardecl_list), *out);
            delete (yyvsp[-1].vardecl_list);
            (yyval.stmt_list) = out;
        }
#line 3167 "build/parser.cpp"
    break;

  case 124: /* local_chan_decl_stmt: chan_type IDENT ';'  */
#line 892 "src/parser.y"
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
#line 3182 "build/parser.cpp"
    break;

  case 125: /* local_chan_decl_stmt: chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'  */
#line 903 "src/parser.y"
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
#line 3205 "build/parser.cpp"
    break;

  case 126: /* stmt: simple_stmt  */
#line 925 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3211 "build/parser.cpp"
    break;

  case 127: /* stmt: if_stmt  */
#line 926 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3217 "build/parser.cpp"
    break;

  case 128: /* stmt: do_stmt  */
#line 927 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3223 "build/parser.cpp"
    break;

  case 129: /* stmt: atomic_stmt  */
#line 928 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3229 "build/parser.cpp"
    break;

  case 130: /* stmt: dstep_stmt  */
#line 929 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3235 "build/parser.cpp"
    break;

  case 131: /* stmt: for_stmt  */
#line 930 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3241 "build/parser.cpp"
    break;

  case 132: /* stmt: select_stmt  */
#line 931 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3247 "build/parser.cpp"
    break;

  case 133: /* stmt: send_stmt  */
#line 932 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3253 "build/parser.cpp"
    break;

  case 134: /* stmt: recv_stmt  */
#line 933 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3259 "build/parser.cpp"
    break;

  case 135: /* stmt: run_stmt  */
#line 934 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3265 "build/parser.cpp"
    break;

  case 136: /* stmt: break_stmt  */
#line 935 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3271 "build/parser.cpp"
    break;

  case 137: /* stmt: skip_stmt  */
#line 936 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3277 "build/parser.cpp"
    break;

  case 138: /* stmt: goto_stmt  */
#line 937 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3283 "build/parser.cpp"
    break;

  case 139: /* stmt: IDENT ':' stmt  */
#line 939 "src/parser.y"
        {
            auto* l = new p2p::LabeledStmt();
            l->label = (yyvsp[-2].str_val); free((yyvsp[-2].str_val));
            l->stmt.reset((yyvsp[0].stmt));
            (yyval.stmt) = l;
        }
#line 3294 "build/parser.cpp"
    break;

  case 140: /* assign_or_expr_stmt: expr '=' expr  */
#line 955 "src/parser.y"
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
#line 3312 "build/parser.cpp"
    break;

  case 141: /* assign_or_expr_stmt: IDENT '(' expr_args ')'  */
#line 969 "src/parser.y"
        {
            auto* c = new p2p::InlineCallStmt();
            c->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            c->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = c;
        }
#line 3324 "build/parser.cpp"
    break;

  case 142: /* assign_or_expr_stmt: expr  */
#line 977 "src/parser.y"
        {
            (yyval.stmt) = wrap_expr_stmt((yyvsp[0].expr));
        }
#line 3332 "build/parser.cpp"
    break;

  case 143: /* simple_stmt: assign_or_expr_stmt  */
#line 983 "src/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].stmt); }
#line 3338 "build/parser.cpp"
    break;

  case 144: /* if_stmt: K_IF branches K_FI  */
#line 989 "src/parser.y"
        {
            auto* s = new p2p::IfStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3349 "build/parser.cpp"
    break;

  case 145: /* do_stmt: K_DO branches K_OD  */
#line 1000 "src/parser.y"
        {
            auto* s = new p2p::DoStmt();
            s->branches = std::move((yyvsp[-1].branch_list)->items);
            delete (yyvsp[-1].branch_list);
            (yyval.stmt) = s;
        }
#line 3360 "build/parser.cpp"
    break;

  case 146: /* branches: branch  */
#line 1010 "src/parser.y"
        {
            auto* l = new BranchList();
            l->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = l;
        }
#line 3371 "build/parser.cpp"
    break;

  case 147: /* branches: branches branch  */
#line 1017 "src/parser.y"
        {
            (yyvsp[-1].branch_list)->items.emplace_back(std::move(*(yyvsp[0].branch)));
            delete (yyvsp[0].branch);
            (yyval.branch_list) = (yyvsp[-1].branch_list);
        }
#line 3381 "build/parser.cpp"
    break;

  case 148: /* branch: OP_DCOLON stmt_seq  */
#line 1029 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3393 "build/parser.cpp"
    break;

  case 149: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq  */
#line 1037 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.branch) = b;
        }
#line 3405 "build/parser.cpp"
    break;

  case 150: /* branch: OP_DCOLON K_ELSE OP_ARROW stmt_seq ';'  */
#line 1045 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3417 "build/parser.cpp"
    break;

  case 151: /* branch: OP_DCOLON stmt_seq ';'  */
#line 1053 "src/parser.y"
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move((yyvsp[-1].stmt_list)->items);
            delete (yyvsp[-1].stmt_list);
            (yyval.branch) = b;
        }
#line 3429 "build/parser.cpp"
    break;

  case 152: /* atomic_stmt: K_ATOMIC stmt_block  */
#line 1065 "src/parser.y"
        {
            auto* s = new p2p::AtomicStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3440 "build/parser.cpp"
    break;

  case 153: /* dstep_stmt: K_D_STEP stmt_block  */
#line 1075 "src/parser.y"
        {
            auto* s = new p2p::DStepStmt();
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3451 "build/parser.cpp"
    break;

  case 154: /* for_stmt: K_FOR '(' IDENT ':' expr OP_DOTDOT expr ')' stmt_block  */
#line 1086 "src/parser.y"
        {
            auto* s = new p2p::ForStmt();
            s->var = (yyvsp[-6].str_val); free((yyvsp[-6].str_val));
            s->low.reset((yyvsp[-4].expr));
            s->high.reset((yyvsp[-2].expr));
            s->body = std::move((yyvsp[0].stmt_list)->items);
            delete (yyvsp[0].stmt_list);
            (yyval.stmt) = s;
        }
#line 3465 "build/parser.cpp"
    break;

  case 155: /* select_stmt: K_SELECT '(' IDENT ':' expr OP_DOTDOT expr ')'  */
#line 1101 "src/parser.y"
        {
            auto* s = new p2p::SelectStmt();
            s->var = (yyvsp[-5].str_val); free((yyvsp[-5].str_val));
            s->low.reset((yyvsp[-3].expr));
            s->high.reset((yyvsp[-1].expr));
            (yyval.stmt) = s;
        }
#line 3477 "build/parser.cpp"
    break;

  case 156: /* send_stmt: expr '!' expr_args_nonempty  */
#line 1113 "src/parser.y"
        {
            auto* s = new p2p::SendStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3489 "build/parser.cpp"
    break;

  case 157: /* recv_stmt: expr '?' expr_args_nonempty  */
#line 1125 "src/parser.y"
        {
            auto* s = new p2p::RecvStmt();
            s->chan.reset((yyvsp[-2].expr));
            s->args = std::move((yyvsp[0].expr_list)->items);
            delete (yyvsp[0].expr_list);
            (yyval.stmt) = s;
        }
#line 3501 "build/parser.cpp"
    break;

  case 158: /* run_stmt: K_RUN IDENT '(' expr_args ')'  */
#line 1139 "src/parser.y"
        {
            auto* s = new p2p::RunStmt();
            s->name = (yyvsp[-3].str_val); free((yyvsp[-3].str_val));
            s->args = std::move((yyvsp[-1].expr_list)->items);
            delete (yyvsp[-1].expr_list);
            (yyval.stmt) = s;
        }
#line 3513 "build/parser.cpp"
    break;

  case 159: /* break_stmt: K_BREAK  */
#line 1148 "src/parser.y"
                            { (yyval.stmt) = new p2p::BreakStmt(); }
#line 3519 "build/parser.cpp"
    break;

  case 160: /* skip_stmt: K_SKIP  */
#line 1149 "src/parser.y"
                            { (yyval.stmt) = new p2p::SkipStmt(); }
#line 3525 "build/parser.cpp"
    break;

  case 161: /* goto_stmt: K_GOTO IDENT  */
#line 1151 "src/parser.y"
        {
            auto* g = new p2p::GotoStmt();
            g->label = (yyvsp[0].str_val); free((yyvsp[0].str_val));
            (yyval.stmt) = g;
        }
#line 3535 "build/parser.cpp"
    break;

  case 162: /* expr_args: %empty  */
#line 1160 "src/parser.y"
                                        { (yyval.expr_list) = new ExprList(); }
#line 3541 "build/parser.cpp"
    break;

  case 163: /* expr_args: expr_args_nonempty  */
#line 1161 "src/parser.y"
                                        { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 3547 "build/parser.cpp"
    break;

  case 164: /* expr_args_nonempty: expr_no_ternary  */
#line 1166 "src/parser.y"
        {
            auto* l = new ExprList();
            l->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = l;
        }
#line 3557 "build/parser.cpp"
    break;

  case 165: /* expr_args_nonempty: expr_args_nonempty ',' expr_no_ternary  */
#line 1172 "src/parser.y"
        {
            (yyvsp[-2].expr_list)->items.emplace_back((yyvsp[0].expr));
            (yyval.expr_list) = (yyvsp[-2].expr_list);
        }
#line 3566 "build/parser.cpp"
    break;

  case 166: /* expr: primary  */
#line 1181 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 3572 "build/parser.cpp"
    break;

  case 167: /* expr: expr '+' expr  */
#line 1182 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3578 "build/parser.cpp"
    break;

  case 168: /* expr: expr '-' expr  */
#line 1183 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3584 "build/parser.cpp"
    break;

  case 169: /* expr: expr '*' expr  */
#line 1184 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3590 "build/parser.cpp"
    break;

  case 170: /* expr: expr '/' expr  */
#line 1185 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3596 "build/parser.cpp"
    break;

  case 171: /* expr: expr '%' expr  */
#line 1186 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3602 "build/parser.cpp"
    break;

  case 172: /* expr: expr OP_SHL expr  */
#line 1187 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3608 "build/parser.cpp"
    break;

  case 173: /* expr: expr OP_SHR expr  */
#line 1188 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3614 "build/parser.cpp"
    break;

  case 174: /* expr: expr '<' expr  */
#line 1189 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3620 "build/parser.cpp"
    break;

  case 175: /* expr: expr '>' expr  */
#line 1190 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3626 "build/parser.cpp"
    break;

  case 176: /* expr: expr OP_LE expr  */
#line 1191 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Le,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3632 "build/parser.cpp"
    break;

  case 177: /* expr: expr OP_GE expr  */
#line 1192 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Ge,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3638 "build/parser.cpp"
    break;

  case 178: /* expr: expr OP_EQ expr  */
#line 1193 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Eq,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3644 "build/parser.cpp"
    break;

  case 179: /* expr: expr OP_NEQ expr  */
#line 1194 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3650 "build/parser.cpp"
    break;

  case 180: /* expr: expr OP_AND expr  */
#line 1195 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3656 "build/parser.cpp"
    break;

  case 181: /* expr: expr OP_OR expr  */
#line 1196 "src/parser.y"
                                         { (yyval.expr) = make_bin(p2p::BinaryOp::Or,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3662 "build/parser.cpp"
    break;

  case 182: /* expr: '-' expr  */
#line 1197 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 3668 "build/parser.cpp"
    break;

  case 183: /* expr: '!' expr  */
#line 1198 "src/parser.y"
                                         { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 3674 "build/parser.cpp"
    break;

  case 184: /* expr: expr OP_ARROW expr ':' expr  */
#line 1200 "src/parser.y"
        {
            auto* t = new p2p::TernaryExpr();
            t->cond.reset((yyvsp[-4].expr));
            t->then_expr.reset((yyvsp[-2].expr));
            t->else_expr.reset((yyvsp[0].expr));
            (yyval.expr) = t;
        }
#line 3686 "build/parser.cpp"
    break;

  case 185: /* expr_no_ternary: primary  */
#line 1214 "src/parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 3692 "build/parser.cpp"
    break;

  case 186: /* expr_no_ternary: expr_no_ternary '+' expr_no_ternary  */
#line 1215 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3698 "build/parser.cpp"
    break;

  case 187: /* expr_no_ternary: expr_no_ternary '-' expr_no_ternary  */
#line 1216 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3704 "build/parser.cpp"
    break;

  case 188: /* expr_no_ternary: expr_no_ternary '*' expr_no_ternary  */
#line 1217 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3710 "build/parser.cpp"
    break;

  case 189: /* expr_no_ternary: expr_no_ternary '/' expr_no_ternary  */
#line 1218 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3716 "build/parser.cpp"
    break;

  case 190: /* expr_no_ternary: expr_no_ternary '%' expr_no_ternary  */
#line 1219 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Mod, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3722 "build/parser.cpp"
    break;

  case 191: /* expr_no_ternary: expr_no_ternary OP_SHL expr_no_ternary  */
#line 1220 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Shl, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3728 "build/parser.cpp"
    break;

  case 192: /* expr_no_ternary: expr_no_ternary OP_SHR expr_no_ternary  */
#line 1221 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Shr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3734 "build/parser.cpp"
    break;

  case 193: /* expr_no_ternary: expr_no_ternary '<' expr_no_ternary  */
#line 1222 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Lt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3740 "build/parser.cpp"
    break;

  case 194: /* expr_no_ternary: expr_no_ternary '>' expr_no_ternary  */
#line 1223 "src/parser.y"
                                           { (yyval.expr) = make_bin(p2p::BinaryOp::Gt,  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3746 "build/parser.cpp"
    break;

  case 195: /* expr_no_ternary: expr_no_ternary OP_LE expr_no_ternary  */
#line 1224 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Le, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3752 "build/parser.cpp"
    break;

  case 196: /* expr_no_ternary: expr_no_ternary OP_GE expr_no_ternary  */
#line 1225 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Ge, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3758 "build/parser.cpp"
    break;

  case 197: /* expr_no_ternary: expr_no_ternary OP_EQ expr_no_ternary  */
#line 1226 "src/parser.y"
                                            { (yyval.expr) = make_bin(p2p::BinaryOp::Eq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3764 "build/parser.cpp"
    break;

  case 198: /* expr_no_ternary: expr_no_ternary OP_NEQ expr_no_ternary  */
#line 1227 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Neq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3770 "build/parser.cpp"
    break;

  case 199: /* expr_no_ternary: expr_no_ternary OP_AND expr_no_ternary  */
#line 1228 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3776 "build/parser.cpp"
    break;

  case 200: /* expr_no_ternary: expr_no_ternary OP_OR expr_no_ternary  */
#line 1229 "src/parser.y"
                                             { (yyval.expr) = make_bin(p2p::BinaryOp::Or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3782 "build/parser.cpp"
    break;

  case 201: /* expr_no_ternary: '-' expr_no_ternary  */
#line 1230 "src/parser.y"
                                           { (yyval.expr) = make_un(p2p::UnaryOp::Neg, (yyvsp[0].expr)); }
#line 3788 "build/parser.cpp"
    break;

  case 202: /* expr_no_ternary: '!' expr_no_ternary  */
#line 1231 "src/parser.y"
                                           { (yyval.expr) = make_un(p2p::UnaryOp::Not, (yyvsp[0].expr)); }
#line 3794 "build/parser.cpp"
    break;

  case 203: /* primary: INT_LITERAL  */
#line 1235 "src/parser.y"
                           { (yyval.expr) = new p2p::IntLiteral((long)(yyvsp[0].int_val)); }
#line 3800 "build/parser.cpp"
    break;

  case 204: /* primary: K_TRUE  */
#line 1236 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(true); }
#line 3806 "build/parser.cpp"
    break;

  case 205: /* primary: K_FALSE  */
#line 1237 "src/parser.y"
                           { (yyval.expr) = new p2p::BoolLiteral(false); }
#line 3812 "build/parser.cpp"
    break;

  case 206: /* primary: IDENT  */
#line 1239 "src/parser.y"
        {
            auto* e = new p2p::IdentExpr((yyvsp[0].str_val));
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3822 "build/parser.cpp"
    break;

  case 207: /* primary: '(' expr ')'  */
#line 1245 "src/parser.y"
        {
            auto* p = new p2p::ParenExpr();
            p->inner.reset((yyvsp[-1].expr));
            (yyval.expr) = p;
        }
#line 3832 "build/parser.cpp"
    break;

  case 208: /* primary: primary '[' expr ']'  */
#line 1251 "src/parser.y"
        {
            auto* e = new p2p::IndexExpr();
            e->base.reset((yyvsp[-3].expr));
            e->index.reset((yyvsp[-1].expr));
            (yyval.expr) = e;
        }
#line 3843 "build/parser.cpp"
    break;

  case 209: /* primary: primary '.' IDENT  */
#line 1258 "src/parser.y"
        {
            auto* e = new p2p::FieldExpr();
            e->base.reset((yyvsp[-2].expr));
            e->field = (yyvsp[0].str_val);
            free((yyvsp[0].str_val));
            (yyval.expr) = e;
        }
#line 3855 "build/parser.cpp"
    break;

  case 210: /* primary: primary OP_INC  */
#line 1265 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostInc, (yyvsp[-1].expr)); }
#line 3861 "build/parser.cpp"
    break;

  case 211: /* primary: primary OP_DEC  */
#line 1266 "src/parser.y"
                           { (yyval.expr) = make_un(p2p::UnaryOp::PostDec, (yyvsp[-1].expr)); }
#line 3867 "build/parser.cpp"
    break;

  case 212: /* primary: OP_INC primary  */
#line 1267 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreInc,  (yyvsp[0].expr)); }
#line 3873 "build/parser.cpp"
    break;

  case 213: /* primary: OP_DEC primary  */
#line 1268 "src/parser.y"
                                                { (yyval.expr) = make_un(p2p::UnaryOp::PreDec,  (yyvsp[0].expr)); }
#line 3879 "build/parser.cpp"
    break;

  case 214: /* primary: K_NEMPTY '(' expr ')'  */
#line 1269 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nempty, (yyvsp[-1].expr)); }
#line 3885 "build/parser.cpp"
    break;

  case 215: /* primary: K_EMPTY '(' expr ')'  */
#line 1270 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Empty,  (yyvsp[-1].expr)); }
#line 3891 "build/parser.cpp"
    break;

  case 216: /* primary: K_LEN '(' expr ')'  */
#line 1271 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Len,    (yyvsp[-1].expr)); }
#line 3897 "build/parser.cpp"
    break;

  case 217: /* primary: K_FULL '(' expr ')'  */
#line 1272 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Full,   (yyvsp[-1].expr)); }
#line 3903 "build/parser.cpp"
    break;

  case 218: /* primary: K_NFULL '(' expr ')'  */
#line 1273 "src/parser.y"
                             { (yyval.expr) = make_builtin(p2p::BuiltinKind::Nfull,  (yyvsp[-1].expr)); }
#line 3909 "build/parser.cpp"
    break;


#line 3913 "build/parser.cpp"

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

#line 1276 "src/parser.y"


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
