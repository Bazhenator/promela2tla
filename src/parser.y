%{
#include <cstdio>
#include <string>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

p2p::Module* g_root = nullptr;
%}

%define parse.error verbose

/* Semanthic tokens' values */
%union {
    int         int_val;
    char*       str_val;
}

/* Literals */
%token <int_val> INT_LITERAL
%token <str_val> IDENT

/* Types */
%token T_BYTE T_INT T_BOOL T_BIT T_SHORT T_UNSIGNED
%token T_MTYPE T_CHAN

/* Top-level definitions */
%token K_PROCTYPE K_ACTIVE K_INLINE K_TYPEDEF K_LTL K_INIT

/* Control structs */
%token K_DO K_OD K_IF K_FI K_ELSE K_BREAK K_GOTO K_SKIP
%token K_ATOMIC K_D_STEP K_UNLESS

%token K_FOR K_SELECT K_RUN K_OF K_LEN
%token K_NEMPTY K_EMPTY K_NFULL K_FULL
%token K_PRINTF K_ASSERT K_TRUE K_FALSE

/* Preprocessor */
%token P_DEFINE

/* Multisymbol operators */
%token OP_ARROW       /* -> */
%token OP_DCOLON      /* :: */
%token OP_DOTDOT      /* .. */
%token OP_INC         /* ++ */
%token OP_DEC         /* -- */
%token OP_AND         /* && */
%token OP_OR          /* || */
%token OP_EQ          /* == */
%token OP_NEQ         /* != */
%token OP_LE          /* <= */
%token OP_GE          /* >= */
%token OP_SHL         /* << */
%token OP_SHR         /* >> */

/* LTL */
%token LTL_ALWAYS     /* [] */
%token LTL_EVENTUALLY /* <> */
%token LTL_UNTIL      /* U */

/* '!' '?' '=' '+' '-' '*' '/' '%' '<' '>' '(' ')' '{' '}' '[' ']' ',' ';' ':' '@' */

%%

program:
    token_stream    { g_root = new p2p::Module(); }
    ;

token_stream:
      /* empty */
    | token_stream any_token
    ;

any_token:
      INT_LITERAL | IDENT
    | T_BYTE | T_INT | T_BOOL | T_BIT | T_SHORT | T_UNSIGNED
    | T_MTYPE | T_CHAN
    | K_PROCTYPE | K_ACTIVE | K_INLINE | K_TYPEDEF | K_LTL | K_INIT
    | K_DO | K_OD | K_IF | K_FI | K_ELSE | K_BREAK | K_GOTO | K_SKIP
    | K_ATOMIC | K_D_STEP | K_UNLESS
    | K_FOR | K_SELECT | K_RUN | K_OF | K_LEN
    | K_NEMPTY | K_EMPTY | K_NFULL | K_FULL
    | K_PRINTF | K_ASSERT | K_TRUE | K_FALSE
    | OP_ARROW | OP_DCOLON | OP_DOTDOT | OP_INC | OP_DEC
    | OP_AND | OP_OR | OP_EQ | OP_NEQ | OP_LE | OP_GE | OP_SHL | OP_SHR
    | LTL_ALWAYS | LTL_EVENTUALLY | LTL_UNTIL
    | '!' | '?' | '=' | '+' | '-' | '*' | '/' | '%'
    | '<' | '>' | '(' | ')' | '{' | '}' | '[' | ']'
    | ',' | ';' | ':' | '@' | '.'
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}