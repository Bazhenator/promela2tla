%{
#include <cstdio>
#include "parser.hpp"
%}

%option noyywrap
%option yylineno

%%
[ \t\r\n]+      { /* skip whitespace */ }
.               { /**/ }
%%