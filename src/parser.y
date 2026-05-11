%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
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

/* Helpers for building expression nodes. */
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
%}

%define parse.error verbose

/* AST nodes are passed via raw pointers in the union.
   Once a pointer becomes a child of another node, ownership is transferred
   into a unique_ptr and the parser stops worrying about it. */
%union {
    int          int_val;
    char*        str_val;
    p2p::Expr*   expr;
}

/* Literals */
%token <int_val> INT_LITERAL
%token <str_val> IDENT

/* Type keywords */
%token T_BYTE T_INT T_BOOL T_BIT T_SHORT T_UNSIGNED
%token T_MTYPE T_CHAN

/* Top-level declarations */
%token K_PROCTYPE K_ACTIVE K_INLINE K_TYPEDEF K_LTL K_INIT

/* Control flow */
%token K_DO K_OD K_IF K_FI K_ELSE K_BREAK K_GOTO K_SKIP
%token K_ATOMIC K_D_STEP K_UNLESS

%token K_FOR K_SELECT K_RUN K_OF K_LEN
%token K_NEMPTY K_EMPTY K_NFULL K_FULL
%token K_PRINTF K_ASSERT K_TRUE K_FALSE

/* Multi-character operators */
%token OP_ARROW OP_DCOLON OP_DOTDOT
%token OP_INC OP_DEC
%token OP_AND OP_OR
%token OP_EQ OP_NEQ OP_LE OP_GE
%token OP_SHL OP_SHR

/* LTL */
%token LTL_ALWAYS LTL_EVENTUALLY LTL_UNTIL

/* Special internal tokens used to switch start symbol.
   Emitted by the lexer when prompted by g_parse_mode. */
%token START_PROGRAM START_EXPR

/* Non-terminal types */
%type <expr> expr
%type <expr> primary

/* Operator precedence (lowest to highest) */
%right OP_ARROW ':'
%left  OP_OR
%left  OP_AND
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LE OP_GE
%left  OP_SHL OP_SHR
%left  '+' '-'
%left  '*' '/' '%'
%right UMINUS UNOT         /* unary - and ! */

%%

/* The lexer emits a START_* token first, telling the parser which
   start symbol to use. This is the standard Bison trick for multiple
   entry points without a GLR parser. */
start:
      START_PROGRAM program_body   { g_root = new p2p::Module(); }
    | START_EXPR    expr_body
    ;

program_body:
      /* empty */
    | program_body any_token
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

/* Expression-only parsing entry (test mode). */
expr_body:
    expr ';'    { g_expr_result = $1; }
    ;

/* Expressions */

expr:
      primary                            { $$ = $1; }
    | expr '+' expr                      { $$ = make_bin(p2p::BinaryOp::Add, $1, $3); }
    | expr '-' expr                      { $$ = make_bin(p2p::BinaryOp::Sub, $1, $3); }
    | expr '*' expr                      { $$ = make_bin(p2p::BinaryOp::Mul, $1, $3); }
    | expr '/' expr                      { $$ = make_bin(p2p::BinaryOp::Div, $1, $3); }
    | expr '%' expr                      { $$ = make_bin(p2p::BinaryOp::Mod, $1, $3); }
    | expr OP_SHL expr                   { $$ = make_bin(p2p::BinaryOp::Shl, $1, $3); }
    | expr OP_SHR expr                   { $$ = make_bin(p2p::BinaryOp::Shr, $1, $3); }
    | expr '<' expr                      { $$ = make_bin(p2p::BinaryOp::Lt,  $1, $3); }
    | expr '>' expr                      { $$ = make_bin(p2p::BinaryOp::Gt,  $1, $3); }
    | expr OP_LE expr                    { $$ = make_bin(p2p::BinaryOp::Le,  $1, $3); }
    | expr OP_GE expr                    { $$ = make_bin(p2p::BinaryOp::Ge,  $1, $3); }
    | expr OP_EQ expr                    { $$ = make_bin(p2p::BinaryOp::Eq,  $1, $3); }
    | expr OP_NEQ expr                   { $$ = make_bin(p2p::BinaryOp::Neq, $1, $3); }
    | expr OP_AND expr                   { $$ = make_bin(p2p::BinaryOp::And, $1, $3); }
    | expr OP_OR  expr                   { $$ = make_bin(p2p::BinaryOp::Or,  $1, $3); }
    | '-' expr           %prec UMINUS    { $$ = make_un(p2p::UnaryOp::Neg, $2); }
    | '!' expr           %prec UNOT      { $$ = make_un(p2p::UnaryOp::Not, $2); }
    | expr OP_ARROW expr ':' expr        {
                                            auto* t = new p2p::TernaryExpr();
                                            t->cond.reset($1);
                                            t->then_expr.reset($3);
                                            t->else_expr.reset($5);
                                            $$ = t;
                                          }
    ;

primary:
      INT_LITERAL          { $$ = new p2p::IntLiteral((long)$1); }
    | K_TRUE               { $$ = new p2p::BoolLiteral(true); }
    | K_FALSE              { $$ = new p2p::BoolLiteral(false); }
    | IDENT                {
                              auto* e = new p2p::IdentExpr($1);
                              free($1);
                              $$ = e;
                           }
    | '(' expr ')'         {
                              auto* p = new p2p::ParenExpr();
                              p->inner.reset($2);
                              $$ = p;
                           }
    | primary '[' expr ']' {
                              auto* e = new p2p::IndexExpr();
                              e->base.reset($1);
                              e->index.reset($3);
                              $$ = e;
                           }
    | primary '.' IDENT    {
                              auto* e = new p2p::FieldExpr();
                              e->base.reset($1);
                              e->field = $3;
                              free($3);
                              $$ = e;
                           }
    | primary OP_INC       { $$ = make_un(p2p::UnaryOp::PostInc, $1); }
    | primary OP_DEC       { $$ = make_un(p2p::UnaryOp::PostDec, $1); }
    | OP_INC primary       { $$ = make_un(p2p::UnaryOp::PreInc,  $2); }
    | OP_DEC primary       { $$ = make_un(p2p::UnaryOp::PreDec,  $2); }
    | K_NEMPTY '(' expr ')'  { $$ = make_builtin(p2p::BuiltinKind::Nempty, $3); }
    | K_EMPTY '(' expr ')'   { $$ = make_builtin(p2p::BuiltinKind::Empty,  $3); }
    | K_LEN '(' expr ')'     { $$ = make_builtin(p2p::BuiltinKind::Len,    $3); }
    | K_FULL '(' expr ')'    { $$ = make_builtin(p2p::BuiltinKind::Full,   $3); }
    | K_NFULL '(' expr ')'   { $$ = make_builtin(p2p::BuiltinKind::Nfull,  $3); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}