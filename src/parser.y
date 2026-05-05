%{
#include <cstdio>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

p2p::Module* g_root = nullptr;
%}

%define parse.error verbose

%%

program:
    /* empty */     { g_root = new p2p::Module(); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}