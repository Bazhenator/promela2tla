%code top {
    #include <memory>
    #include <string>
    #include <vector>
    #include "ast.h"
}

%code requires {
    #include "parser_types.h"
}

%{
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
%}

%define parse.error verbose

%code {
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
}

%union {
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

/* Special internal tokens used to switch start symbol. */
%token START_PROGRAM START_EXPR START_STMT_BLOCK

/* Non-terminal types */
%type <expr>         expr primary ltl_atom
%type <type>         basic_type chan_type local_basic_type
%type <var_decl>     declarator field_one
%type <node>         top_decl typedef_decl mtype_decl ltl_decl chan_decl_stmt
%type <type_list>    type_list
%type <ident_list>   ident_list
%type <vardecl_list> declarator_list var_decl_stmt
%type <vardecl_list> field_decl_list field_decl_stmt field_decl_one_or_more
%type <ltl>          ltl_formula ltl_unary

/* Statements */
%type <stmt>         stmt simple_stmt assign_or_expr_stmt
%type <stmt>         if_stmt do_stmt atomic_stmt dstep_stmt
%type <stmt>         for_stmt select_stmt
%type <stmt>         send_stmt recv_stmt run_stmt
%type <stmt>         break_stmt skip_stmt goto_stmt
%type <stmt_list>    stmt_seq stmt_block
%type <stmt_list>    local_var_decl_stmt local_chan_decl_stmt
%type <branch_list>  branches
%type <branch>       branch
%type <expr_list>    expr_args expr_args_nonempty

/* Operator precedence (lowest to highest).
   LOW_PREC sits above OP_ARROW so that, in statement context, an expr
   followed by '->' is reduced into an expr-stmt — letting OP_ARROW act
   as a separator between guard and body in a ::-branch — rather than
   being shifted as the start of a Promela ternary.
   '=', '!' and '?' stay above LOW_PREC so they shift after a bare expr
   in statement position (assignment, send, receive). */
%right OP_ARROW ':'
%nonassoc LOW_PREC
%right '='
%left  '!' '?'
%left  OP_OR
%left  OP_AND
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LE OP_GE
%left  OP_SHL OP_SHR
%left  '+' '-'
%left  '*' '/' '%'
%right UMINUS UNOT
%right PREFIX_INCDEC
%left  OP_INC OP_DEC '[' '.'

%%

start:
      START_PROGRAM     program_body   { if (!g_root) g_root = new p2p::Module(); }
    | START_EXPR        expr_body
    | START_STMT_BLOCK  stmt_body
    ;

program_body:
      /* empty */
    | program_body top_decl
        {
            if (!g_root) g_root = new p2p::Module();
            if ($2) g_root->declarations.emplace_back($2);
        }
    ;

top_decl:
      var_decl_stmt        { push_decls(*$1); delete $1; $$ = nullptr; }
    | chan_decl_stmt       { $$ = $1; }
    | typedef_decl         { $$ = $1; }
    | mtype_decl           { $$ = $1; }
    | ltl_decl             { $$ = $1; }
    ;

/* Regular variable declaration:  type d1, d2, d3; */
var_decl_stmt:
    basic_type declarator_list ';'
        {
            attach_type(*$2, *$1);
            delete $1;
            $$ = $2;
        }
    ;

/* Channel declaration is a top-level form of its own to avoid ambiguity
   with the regular declarator list. */
chan_decl_stmt:
      chan_type IDENT ';'
        {
            auto* d = new p2p::VarDecl();
            d->name = $2; free($2);
            d->type.reset($1);
            $$ = d;
        }
    | chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'
        {
            auto* d = new p2p::VarDecl();
            d->name = $2; free($2);
            d->type.reset($1);
            if (auto* lit = dynamic_cast<p2p::IntLiteral*>($5)) {
                d->type->chan_capacity = (int)lit->value;
            } else {
                d->type->chan_capacity = 0;
            }
            delete $5;
            d->type->chan_msg_types = std::move($9->items);
            delete $9;
            $$ = d;
        }
    ;

chan_type:
      T_CHAN               { $$ = make_basic(p2p::BasicTypeKind::Chan); }
    ;

basic_type:
      T_BYTE               { $$ = make_basic(p2p::BasicTypeKind::Byte); }
    | T_INT                { $$ = make_basic(p2p::BasicTypeKind::Int); }
    | T_BOOL               { $$ = make_basic(p2p::BasicTypeKind::Bool); }
    | T_BIT                { $$ = make_basic(p2p::BasicTypeKind::Bit); }
    | T_SHORT              { $$ = make_basic(p2p::BasicTypeKind::Short); }
    | T_UNSIGNED           { $$ = make_basic(p2p::BasicTypeKind::Unsigned); }
    | T_MTYPE              { $$ = make_basic(p2p::BasicTypeKind::Mtype); }
    | T_MTYPE ':' IDENT
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = $3;
            free($3);
            $$ = t;
        }
    | IDENT                { $$ = make_named($1); free($1); }
    ;

/* Same as basic_type, but without the `IDENT` (named-type) alternative.
   Used inside proctype bodies, where allowing identifiers as type names
   would create an ambiguity with statements that start with an identifier
   (assignments, inline calls, labels). The reference model doesn't use
   named types inside bodies; if that ever changes, a proper lexer hack
   to distinguish TYPENAME from IDENT will be needed. */
local_basic_type:
      T_BYTE               { $$ = make_basic(p2p::BasicTypeKind::Byte); }
    | T_INT                { $$ = make_basic(p2p::BasicTypeKind::Int); }
    | T_BOOL               { $$ = make_basic(p2p::BasicTypeKind::Bool); }
    | T_BIT                { $$ = make_basic(p2p::BasicTypeKind::Bit); }
    | T_SHORT              { $$ = make_basic(p2p::BasicTypeKind::Short); }
    | T_UNSIGNED           { $$ = make_basic(p2p::BasicTypeKind::Unsigned); }
    | T_MTYPE              { $$ = make_basic(p2p::BasicTypeKind::Mtype); }
    | T_MTYPE ':' IDENT
        {
            auto* t = make_basic(p2p::BasicTypeKind::Mtype);
            t->mtype_set = $3;
            free($3);
            $$ = t;
        }
    ;

declarator_list:
      declarator
        {
            auto* l = new VarDeclList();
            l->items.emplace_back($1);
            $$ = l;
        }
    | declarator_list ',' declarator
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
    ;

declarator:
      IDENT
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            $$ = d;
        }
    | IDENT '=' expr
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            d->init.reset($3);
            $$ = d;
        }
    | IDENT '[' expr ']'
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            d->array_size.reset($3);
            $$ = d;
        }
    | IDENT '[' expr ']' '=' expr
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            d->array_size.reset($3);
            d->init.reset($6);
            $$ = d;
        }
    ;

type_list:
      basic_type
        {
            auto* tl = new TypeList();
            tl->items.emplace_back($1);
            $$ = tl;
        }
    | type_list ',' basic_type
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
    ;

/* typedef Name { field_decl_list } ; */
typedef_decl:
    K_TYPEDEF IDENT '{' field_decl_list '}' ';'
        {
            auto* td = new p2p::TypedefDecl();
            td->name = $2; free($2);
            td->fields = std::move($4->items);
            delete $4;
            $$ = td;
        }
    ;

field_decl_list:
      field_decl_stmt                          { $$ = $1; }
    | field_decl_list ';' field_decl_stmt
        {
            for (auto& f : $3->items) $1->items.emplace_back(std::move(f));
            delete $3;
            $$ = $1;
        }
    ;

field_decl_stmt:
    basic_type field_decl_one_or_more
        {
            attach_type(*$2, *$1);
            delete $1;
            $$ = $2;
        }
    ;

field_decl_one_or_more:
      field_one
        {
            auto* l = new VarDeclList();
            l->items.emplace_back($1);
            $$ = l;
        }
    | field_decl_one_or_more ',' field_one
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
    ;

field_one:
      IDENT
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            $$ = d;
        }
    | IDENT '[' expr ']'
        {
            auto* d = new p2p::VarDecl();
            d->name = $1; free($1);
            d->array_size.reset($3);
            $$ = d;
        }
    ;

/* mtype = { ... }  or  mtype : SET = { ... } */
mtype_decl:
      T_MTYPE '=' '{' ident_list '}' ';'
        {
            auto* m = new p2p::MtypeDecl();
            m->names = std::move($4->items);
            delete $4;
            $$ = m;
        }
    | T_MTYPE ':' IDENT '=' '{' ident_list '}' ';'
        {
            auto* m = new p2p::MtypeDecl();
            m->set_name = $3; free($3);
            m->names = std::move($6->items);
            delete $6;
            $$ = m;
        }
    ;

ident_list:
      IDENT
        {
            auto* il = new IdentList();
            il->items.emplace_back($1);
            free($1);
            $$ = il;
        }
    | ident_list ',' IDENT
        {
            $1->items.emplace_back($3);
            free($3);
            $$ = $1;
        }
    ;

/* ltl Name { formula } */
ltl_decl:
    K_LTL IDENT '{' ltl_formula '}'
        {
            auto* l = new p2p::LtlDecl();
            l->name = $2; free($2);
            l->formula.reset($4);
            $$ = l;
        }
    ;

ltl_formula:
      ltl_unary                          { $$ = $1; }
    | ltl_formula OP_AND ltl_formula
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::And;
            f->lhs.reset($1); f->rhs.reset($3);
            $$ = f;
        }
    | ltl_formula OP_OR ltl_formula
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Or;
            f->lhs.reset($1); f->rhs.reset($3);
            $$ = f;
        }
    | ltl_formula OP_ARROW ltl_formula
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Implies;
            f->lhs.reset($1); f->rhs.reset($3);
            $$ = f;
        }
    ;

ltl_unary:
      LTL_ALWAYS ltl_unary
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Always;
            f->lhs.reset($2);
            $$ = f;
        }
    | LTL_EVENTUALLY ltl_unary
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Eventually;
            f->lhs.reset($2);
            $$ = f;
        }
    | '!' ltl_unary
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Not;
            f->lhs.reset($2);
            $$ = f;
        }
    | '(' ltl_formula ')'                { $$ = $2; }
    | ltl_atom
        {
            auto* f = new p2p::LtlFormula();
            f->op = p2p::LtlOp::Atom;
            f->atom.reset($1);
            $$ = f;
        }
    ;

ltl_atom:
      INT_LITERAL                       { $$ = new p2p::IntLiteral((long)$1); }
    | K_TRUE                            { $$ = new p2p::BoolLiteral(true); }
    | K_FALSE                           { $$ = new p2p::BoolLiteral(false); }
    | IDENT                             {
                                          auto* e = new p2p::IdentExpr($1);
                                          free($1);
                                          $$ = e;
                                        }
    | ltl_atom '[' ltl_atom ']'         {
                                          auto* e = new p2p::IndexExpr();
                                          e->base.reset($1); e->index.reset($3);
                                          $$ = e;
                                        }
    | ltl_atom '.' IDENT                {
                                          auto* e = new p2p::FieldExpr();
                                          e->base.reset($1);
                                          e->field = $3; free($3);
                                          $$ = e;
                                        }
    | ltl_atom '+' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Add, $1, $3); }
    | ltl_atom '-' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Sub, $1, $3); }
    | ltl_atom '*' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Mul, $1, $3); }
    | ltl_atom '/' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Div, $1, $3); }
    | ltl_atom '%' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Mod, $1, $3); }
    | ltl_atom '<' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Lt,  $1, $3); }
    | ltl_atom '>' ltl_atom             { $$ = make_bin(p2p::BinaryOp::Gt,  $1, $3); }
    | ltl_atom OP_LE  ltl_atom          { $$ = make_bin(p2p::BinaryOp::Le,  $1, $3); }
    | ltl_atom OP_GE  ltl_atom          { $$ = make_bin(p2p::BinaryOp::Ge,  $1, $3); }
    | ltl_atom OP_EQ  ltl_atom          { $$ = make_bin(p2p::BinaryOp::Eq,  $1, $3); }
    | ltl_atom OP_NEQ ltl_atom          { $$ = make_bin(p2p::BinaryOp::Neq, $1, $3); }
    | '-' ltl_atom    %prec UMINUS      { $$ = make_un(p2p::UnaryOp::Neg, $2); }
    ;

/* Expression-only parsing entry (test mode). */
expr_body:
    expr ';'    { g_expr_result = $1; }
    ;

/* Statement-block-only parsing entry (test mode).
   Accepts either a brace-delimited block or a bare sequence. */
stmt_body:
      stmt_block                        { g_stmt_result = $1; }
    | stmt_seq                          { g_stmt_result = $1; }
    ;

/* Statements */

/* A brace-delimited block. The trailing separator is optional. */
stmt_block:
      '{' '}'
        {
            $$ = new StmtList();
        }
    | '{' stmt_seq '}'
        {
            $$ = $2;
        }
    | '{' stmt_seq ';' '}'
        {
            $$ = $2;
        }
    ;

/* A non-empty sequence of statements separated by ';' or '->'.
   Local declarations may also chain without an explicit separator,
   because the trailing ';' is already consumed inside the declaration. */
stmt_seq:
      stmt
        {
            auto* l = new StmtList();
            l->items.emplace_back($1);
            $$ = l;
        }
    | stmt_seq ';' stmt
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
    | stmt_seq OP_ARROW stmt
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
    | local_var_decl_stmt
        {
            $$ = $1;
        }
    | local_chan_decl_stmt
        {
            $$ = $1;
        }
    | stmt_seq ';' local_var_decl_stmt
        {
            for (auto& s : $3->items) $1->items.emplace_back(std::move(s));
            delete $3;
            $$ = $1;
        }
    | stmt_seq ';' local_chan_decl_stmt
        {
            for (auto& s : $3->items) $1->items.emplace_back(std::move(s));
            delete $3;
            $$ = $1;
        }
    | stmt_seq OP_ARROW local_var_decl_stmt
        {
            for (auto& s : $3->items) $1->items.emplace_back(std::move(s));
            delete $3;
            $$ = $1;
        }
    | stmt_seq local_var_decl_stmt
        {
            for (auto& s : $2->items) $1->items.emplace_back(std::move(s));
            delete $2;
            $$ = $1;
        }
    | stmt_seq local_chan_decl_stmt
        {
            for (auto& s : $2->items) $1->items.emplace_back(std::move(s));
            delete $2;
            $$ = $1;
        }
    | stmt_seq local_var_decl_stmt stmt   %prec STMT_AFTER_DECL
        {
            for (auto& s : $2->items) $1->items.emplace_back(std::move(s));
            delete $2;
            $1->items.emplace_back($3);
            $$ = $1;
        }
    | stmt_seq local_chan_decl_stmt stmt   %prec STMT_AFTER_DECL
        {
            for (auto& s : $2->items) $1->items.emplace_back(std::move(s));
            delete $2;
            $1->items.emplace_back($3);
            $$ = $1;
        }
    ;

/* Local declarations: same shape as var_decl_stmt / chan_decl_stmt
   but produce LocalVarDeclStmt entries instead of pushing into g_root. */
local_var_decl_stmt:
    local_basic_type declarator_list ';'
        {
            attach_type(*$2, *$1);
            delete $1;
            auto* out = new StmtList();
            wrap_local_decls(*$2, *out);
            delete $2;
            $$ = out;
        }
    ;

local_chan_decl_stmt:
      chan_type IDENT ';'
        {
            auto* d = new p2p::VarDecl();
            d->name = $2; free($2);
            d->type.reset($1);
            auto* s = new p2p::LocalVarDeclStmt();
            s->decl.reset(d);
            auto* out = new StmtList();
            out->items.emplace_back(s);
            $$ = out;
        }
    | chan_type IDENT '=' '[' expr ']' K_OF '{' type_list '}' ';'
        {
            auto* d = new p2p::VarDecl();
            d->name = $2; free($2);
            d->type.reset($1);
            if (auto* lit = dynamic_cast<p2p::IntLiteral*>($5)) {
                d->type->chan_capacity = (int)lit->value;
            } else {
                d->type->chan_capacity = 0;
            }
            delete $5;
            d->type->chan_msg_types = std::move($9->items);
            delete $9;
            auto* s = new p2p::LocalVarDeclStmt();
            s->decl.reset(d);
            auto* out = new StmtList();
            out->items.emplace_back(s);
            $$ = out;
        }
    ;

/* A single statement (used inside stmt_seq and inside branches). */
stmt:
      simple_stmt                       { $$ = $1; }
    | if_stmt                           { $$ = $1; }
    | do_stmt                           { $$ = $1; }
    | atomic_stmt                       { $$ = $1; }
    | dstep_stmt                        { $$ = $1; }
    | for_stmt                          { $$ = $1; }
    | select_stmt                       { $$ = $1; }
    | send_stmt                         { $$ = $1; }
    | recv_stmt                         { $$ = $1; }
    | run_stmt                          { $$ = $1; }
    | break_stmt                        { $$ = $1; }
    | skip_stmt                         { $$ = $1; }
    | goto_stmt                         { $$ = $1; }
    | IDENT ':' stmt
        {
            auto* l = new p2p::LabeledStmt();
            l->label = $1; free($1);
            l->stmt.reset($3);
            $$ = l;
        }
    ;

/* `expr` can be:
     expr '=' expr        — assignment (with a runtime lvalue check)
     IDENT '(' args ')'   — inline call
     expr                 — guard / side-effect (wrapped in ExprStmt)
   Bison prefers shifting '=', '!' and '?' over reducing to a bare
   expression statement (see the precedence table above). */
assign_or_expr_stmt:
      expr '=' expr
        {
            if (!dynamic_cast<p2p::IdentExpr*>($1)
             && !dynamic_cast<p2p::IndexExpr*>($1)
             && !dynamic_cast<p2p::FieldExpr*>($1)) {
                yyerror("left side of '=' is not assignable");
                delete $1; delete $3;
                YYERROR;
            }
            auto* a = new p2p::AssignStmt();
            a->lhs.reset($1);
            a->rhs.reset($3);
            $$ = a;
        }
    | IDENT '(' expr_args ')'
        {
            auto* c = new p2p::InlineCallStmt();
            c->name = $1; free($1);
            c->args = std::move($3->items);
            delete $3;
            $$ = c;
        }
    | expr   %prec LOW_PREC
        {
            $$ = wrap_expr_stmt($1);
        }
    ;

simple_stmt:
    assign_or_expr_stmt                 { $$ = $1; }
    ;

/* if :: branch :: branch ... fi */
if_stmt:
    K_IF branches K_FI
        {
            auto* s = new p2p::IfStmt();
            s->branches = std::move($2->items);
            delete $2;
            $$ = s;
        }
    ;

/* do :: branch :: branch ... od */
do_stmt:
    K_DO branches K_OD
        {
            auto* s = new p2p::DoStmt();
            s->branches = std::move($2->items);
            delete $2;
            $$ = s;
        }
    ;

branches:
      branch
        {
            auto* l = new BranchList();
            l->items.emplace_back(std::move(*$1));
            delete $1;
            $$ = l;
        }
    | branches branch
        {
            $1->items.emplace_back(std::move(*$2));
            delete $2;
            $$ = $1;
        }
    ;

/* :: guard -> rest  /  :: stmt; stmt; ...  /  :: else -> rest
   The grammar accepts any sequence of statements after ::, with either
   ; or -> as separator. */
branch:
      OP_DCOLON stmt_seq
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move($2->items);
            delete $2;
            $$ = b;
        }
    | OP_DCOLON K_ELSE OP_ARROW stmt_seq
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move($4->items);
            delete $4;
            $$ = b;
        }
    | OP_DCOLON K_ELSE OP_ARROW stmt_seq ';'
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = true;
            b->stmts = std::move($4->items);
            delete $4;
            $$ = b;
        }
    | OP_DCOLON stmt_seq ';'
        {
            auto* b = new p2p::GuardedBranch();
            b->is_else = false;
            b->stmts = std::move($2->items);
            delete $2;
            $$ = b;
        }
    ;

/* atomic { ... }   and   d_step { ... } */
atomic_stmt:
    K_ATOMIC stmt_block
        {
            auto* s = new p2p::AtomicStmt();
            s->body = std::move($2->items);
            delete $2;
            $$ = s;
        }
    ;

dstep_stmt:
    K_D_STEP stmt_block
        {
            auto* s = new p2p::DStepStmt();
            s->body = std::move($2->items);
            delete $2;
            $$ = s;
        }
    ;

/* for (var : low .. high) { body } */
for_stmt:
    K_FOR '(' IDENT ':' expr OP_DOTDOT expr ')' stmt_block
        {
            auto* s = new p2p::ForStmt();
            s->var = $3; free($3);
            s->low.reset($5);
            s->high.reset($7);
            s->body = std::move($9->items);
            delete $9;
            $$ = s;
        }
    ;

/* select (var : low .. high)
   Promela's `select` is itself a statement (no body). */
select_stmt:
    K_SELECT '(' IDENT ':' expr OP_DOTDOT expr ')'
        {
            auto* s = new p2p::SelectStmt();
            s->var = $3; free($3);
            s->low.reset($5);
            s->high.reset($7);
            $$ = s;
        }
    ;

/* chan ! e1, e2, ... */
send_stmt:
    expr '!' expr_args_nonempty
        {
            auto* s = new p2p::SendStmt();
            s->chan.reset($1);
            s->args = std::move($3->items);
            delete $3;
            $$ = s;
        }
    ;

/* chan ? e1, e2, ... */
recv_stmt:
    expr '?' expr_args_nonempty
        {
            auto* s = new p2p::RecvStmt();
            s->chan.reset($1);
            s->args = std::move($3->items);
            delete $3;
            $$ = s;
        }
    ;

/* run name(args)
   Note: bare `run` without arguments would still need parentheses
   in Promela, so the inner expr_args may be empty. */
run_stmt:
    K_RUN IDENT '(' expr_args ')'
        {
            auto* s = new p2p::RunStmt();
            s->name = $2; free($2);
            s->args = std::move($4->items);
            delete $4;
            $$ = s;
        }
    ;

break_stmt: K_BREAK         { $$ = new p2p::BreakStmt(); } ;
skip_stmt:  K_SKIP          { $$ = new p2p::SkipStmt(); } ;
goto_stmt:  K_GOTO IDENT
        {
            auto* g = new p2p::GotoStmt();
            g->label = $2; free($2);
            $$ = g;
        }
    ;

/* Possibly-empty comma-separated list of expressions. */
expr_args:
      /* empty */                       { $$ = new ExprList(); }
    | expr_args_nonempty                { $$ = $1; }
    ;

expr_args_nonempty:
      expr
        {
            auto* l = new ExprList();
            l->items.emplace_back($1);
            $$ = l;
        }
    | expr_args_nonempty ',' expr
        {
            $1->items.emplace_back($3);
            $$ = $1;
        }
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
    | expr OP_ARROW expr ':' expr
        {
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
    | IDENT
        {
            auto* e = new p2p::IdentExpr($1);
            free($1);
            $$ = e;
        }
    | '(' expr ')'
        {
            auto* p = new p2p::ParenExpr();
            p->inner.reset($2);
            $$ = p;
        }
    | primary '[' expr ']'
        {
            auto* e = new p2p::IndexExpr();
            e->base.reset($1);
            e->index.reset($3);
            $$ = e;
        }
    | primary '.' IDENT
        {
            auto* e = new p2p::FieldExpr();
            e->base.reset($1);
            e->field = $3;
            free($3);
            $$ = e;
        }
    | primary OP_INC       { $$ = make_un(p2p::UnaryOp::PostInc, $1); }
    | primary OP_DEC       { $$ = make_un(p2p::UnaryOp::PostDec, $1); }
    | OP_INC primary       %prec PREFIX_INCDEC  { $$ = make_un(p2p::UnaryOp::PreInc,  $2); }
    | OP_DEC primary       %prec PREFIX_INCDEC  { $$ = make_un(p2p::UnaryOp::PreDec,  $2); }
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