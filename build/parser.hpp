/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "src/parser.y"

    #include "parser_types.h"
    #include "typedef_table.h"

#line 54 "build/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_LITERAL = 258,             /* INT_LITERAL  */
    IDENT = 259,                   /* IDENT  */
    TYPENAME = 260,                /* TYPENAME  */
    T_BYTE = 261,                  /* T_BYTE  */
    T_INT = 262,                   /* T_INT  */
    T_BOOL = 263,                  /* T_BOOL  */
    T_BIT = 264,                   /* T_BIT  */
    T_SHORT = 265,                 /* T_SHORT  */
    T_UNSIGNED = 266,              /* T_UNSIGNED  */
    T_MTYPE = 267,                 /* T_MTYPE  */
    T_CHAN = 268,                  /* T_CHAN  */
    K_PROCTYPE = 269,              /* K_PROCTYPE  */
    K_ACTIVE = 270,                /* K_ACTIVE  */
    K_INLINE = 271,                /* K_INLINE  */
    K_TYPEDEF = 272,               /* K_TYPEDEF  */
    K_LTL = 273,                   /* K_LTL  */
    K_INIT = 274,                  /* K_INIT  */
    K_DO = 275,                    /* K_DO  */
    K_OD = 276,                    /* K_OD  */
    K_IF = 277,                    /* K_IF  */
    K_FI = 278,                    /* K_FI  */
    K_ELSE = 279,                  /* K_ELSE  */
    K_BREAK = 280,                 /* K_BREAK  */
    K_GOTO = 281,                  /* K_GOTO  */
    K_SKIP = 282,                  /* K_SKIP  */
    K_ATOMIC = 283,                /* K_ATOMIC  */
    K_D_STEP = 284,                /* K_D_STEP  */
    K_UNLESS = 285,                /* K_UNLESS  */
    K_FOR = 286,                   /* K_FOR  */
    K_SELECT = 287,                /* K_SELECT  */
    K_RUN = 288,                   /* K_RUN  */
    K_OF = 289,                    /* K_OF  */
    K_LEN = 290,                   /* K_LEN  */
    K_NEMPTY = 291,                /* K_NEMPTY  */
    K_EMPTY = 292,                 /* K_EMPTY  */
    K_NFULL = 293,                 /* K_NFULL  */
    K_FULL = 294,                  /* K_FULL  */
    K_PRINTF = 295,                /* K_PRINTF  */
    K_ASSERT = 296,                /* K_ASSERT  */
    K_TRUE = 297,                  /* K_TRUE  */
    K_FALSE = 298,                 /* K_FALSE  */
    OP_ARROW = 299,                /* OP_ARROW  */
    OP_DCOLON = 300,               /* OP_DCOLON  */
    OP_DOTDOT = 301,               /* OP_DOTDOT  */
    OP_INC = 302,                  /* OP_INC  */
    OP_DEC = 303,                  /* OP_DEC  */
    OP_AND = 304,                  /* OP_AND  */
    OP_OR = 305,                   /* OP_OR  */
    OP_EQ = 306,                   /* OP_EQ  */
    OP_NEQ = 307,                  /* OP_NEQ  */
    OP_LE = 308,                   /* OP_LE  */
    OP_GE = 309,                   /* OP_GE  */
    OP_SHL = 310,                  /* OP_SHL  */
    OP_SHR = 311,                  /* OP_SHR  */
    LTL_ALWAYS = 312,              /* LTL_ALWAYS  */
    LTL_EVENTUALLY = 313,          /* LTL_EVENTUALLY  */
    LTL_UNTIL = 314,               /* LTL_UNTIL  */
    START_PROGRAM = 315,           /* START_PROGRAM  */
    START_EXPR = 316,              /* START_EXPR  */
    START_STMT_BLOCK = 317,        /* START_STMT_BLOCK  */
    LOW_PREC = 318,                /* LOW_PREC  */
    UMINUS = 319,                  /* UMINUS  */
    UNOT = 320,                    /* UNOT  */
    PREFIX_INCDEC = 321            /* PREFIX_INCDEC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 140 "src/parser.y"

    int                    int_val;
    char*                  str_val;
    p2p::Expr*             expr;
    p2p::Type*             type;
    p2p::VarDecl*          var_decl;
    p2p::Stmt*             stmt;
    p2p::Node*             node;
    TypeList*              type_list;
    IdentList*             ident_list;
    VarDeclList*           vardecl_list;
    StmtList*              stmt_list;
    ExprList*              expr_list;
    BranchList*            branch_list;
    p2p::GuardedBranch*    branch;
    p2p::LtlFormula*       ltl;
    ParamList*             param_list;

#line 156 "build/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_HPP_INCLUDED  */
