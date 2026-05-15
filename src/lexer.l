%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include "ast.h"
#include "parser.hpp"
#include "typedef_table.h"

/* Macro table populated by #define directives. */
static std::unordered_map<std::string, std::string> g_defines;

static bool trace_tokens() {
    static int v = -1;
    if (v < 0) {
        const char* e = getenv("P2P_TRACE_TOKENS");
        v = (e && *e) ? 1 : 0;
    }
    return v == 1;
}

#define yylex yylex_raw

#define TR(name) do { if (trace_tokens()) \
    fprintf(stderr, "[tok] line %d: %s '%s'\n", yylineno, #name, yytext); \
} while (0)

/* When set by main(), the lexer emits one START_* marker before the real
   token stream. This lets the grammar pick between two start symbols. */
extern int g_parse_mode;
#define PARSE_PROGRAM     0
#define PARSE_EXPR        1
#define PARSE_STMT_BLOCK  2
static bool g_start_emitted = false;

/* Tracks {} nesting depth so ASI in the parser wrapper applies only
   inside procedure bodies, not at the top level. */
int g_brace_depth = 0;

/* Set to 1 by newline matches; the parser's yylex wrapper reads and
   resets this to detect statement boundaries for ASI. */
int g_saw_newline = 0;

/* Reset between runs */
extern "C" void p2p_reset_lexer_state() {
    g_defines.clear();
    g_start_emitted = false;
}
%}

%option noyywrap
%option yylineno

%x BLOCK_COMMENT
%x DEFINE_NAME
%x DEFINE_VALUE

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*

%%

%{
    /* Emit the start-symbol marker before any other token. */
    if (!g_start_emitted) {
        g_start_emitted = true;
        if (g_parse_mode == PARSE_EXPR)       return START_EXPR;
        if (g_parse_mode == PARSE_STMT_BLOCK) return START_STMT_BLOCK;
        return START_PROGRAM;
    }
%}

    /* Whitespace */
[ \t\r]+        { /* skip */ }
\n              {
                    /* Track newlines for ASI in the parser's yylex wrapper. */
                    g_saw_newline = 1;
                }

    /* Comments */
"//"[^\n]*      { /* line comment */ }
"/*"            { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>{
    "*/"        { BEGIN(INITIAL); }
    \n          { /* track lines */ }
    .           { /* skip */ }
}

    /* Preprocessor: #define NAME VALUE */
"#define"       { BEGIN(DEFINE_NAME); }
<DEFINE_NAME>{
    [ \t]+      { /* skip */ }
    {ID}        {
                    static std::string name;
                    name = yytext;
                    g_defines[name] = "";
                    BEGIN(DEFINE_VALUE);
                }
    \n          { BEGIN(INITIAL); }
}
<DEFINE_VALUE>{
    [ \t]+      { /* leading whitespace */ }
    [^\n]+      {
                    for (auto& kv : g_defines) {
                        if (kv.second.empty()) {
                            kv.second = yytext;
                            auto pos = kv.second.find("//");
                            if (pos != std::string::npos)
                                kv.second.resize(pos);
                            while (!kv.second.empty() &&
                                  (kv.second.back() == ' ' || kv.second.back() == '\t'))
                                kv.second.pop_back();
                            break;
                        }
                    }
                }
    \n          { BEGIN(INITIAL); }
}

    /* Multi-character operators */
"->"            { TR(ARROW);       return OP_ARROW; }
"::"            { TR(DCOLON);      return OP_DCOLON; }
".."            { TR(DOTDOT);      return OP_DOTDOT; }
"++"            { TR(INC);         return OP_INC; }
"--"            { TR(DEC);         return OP_DEC; }
"&&"            { TR(AND);         return OP_AND; }
"||"            { TR(OR);          return OP_OR; }
"=="            { TR(EQ);          return OP_EQ; }
"!="            { TR(NEQ);         return OP_NEQ; }
"<="            { TR(LE);          return OP_LE; }
">="            { TR(GE);          return OP_GE; }
"<<"            { TR(SHL);         return OP_SHL; }
">>"            { TR(SHR);         return OP_SHR; }

    /* LTL operators */
"[]"            { TR(LTL_ALWAYS);     return LTL_ALWAYS; }
"<>"            { TR(LTL_EVENTUALLY); return LTL_EVENTUALLY; }

    /* Type keywords */
"byte"          { TR(T_BYTE);     return T_BYTE; }
"int"           { TR(T_INT);      return T_INT; }
"bool"          { TR(T_BOOL);     return T_BOOL; }
"bit"           { TR(T_BIT);      return T_BIT; }
"short"         { TR(T_SHORT);    return T_SHORT; }
"unsigned"      { TR(T_UNSIGNED); return T_UNSIGNED; }
"mtype"         { TR(T_MTYPE);    return T_MTYPE; }
"chan"          { TR(T_CHAN);     return T_CHAN; }

    /* Top-level keywords */
"proctype"      { TR(K_PROCTYPE); return K_PROCTYPE; }
"active"        { TR(K_ACTIVE);   return K_ACTIVE; }
"inline"        { TR(K_INLINE);   return K_INLINE; }
"typedef"       { TR(K_TYPEDEF);  return K_TYPEDEF; }
"ltl"           { TR(K_LTL);      return K_LTL; }
"init"          { TR(K_INIT);     return K_INIT; }

    /* Control-flow keywords */
"do"            { TR(K_DO);       return K_DO; }
"od"            { TR(K_OD);       return K_OD; }
"if"            { TR(K_IF);       return K_IF; }
"fi"            { TR(K_FI);       return K_FI; }
"else"          { TR(K_ELSE);     return K_ELSE; }
"break"         { TR(K_BREAK);    return K_BREAK; }
"goto"          { TR(K_GOTO);     return K_GOTO; }
"skip"          { TR(K_SKIP);     return K_SKIP; }
"atomic"        { TR(K_ATOMIC);   return K_ATOMIC; }
"d_step"        { TR(K_D_STEP);   return K_D_STEP; }
"unless"        { TR(K_UNLESS);   return K_UNLESS; }


"for"           { TR(K_FOR);      return K_FOR; }
"select"        { TR(K_SELECT);   return K_SELECT; }
"run"           { TR(K_RUN);      return K_RUN; }
"of"            { TR(K_OF);       return K_OF; }
"len"           { TR(K_LEN);      return K_LEN; }
"nempty"        { TR(K_NEMPTY);   return K_NEMPTY; }
"empty"         { TR(K_EMPTY);    return K_EMPTY; }
"nfull"         { TR(K_NFULL);    return K_NFULL; }
"full"          { TR(K_FULL);     return K_FULL; }
"printf"        { TR(K_PRINTF);   return K_PRINTF; }
"assert"        { TR(K_ASSERT);   return K_ASSERT; }
"true"          { TR(K_TRUE);     return K_TRUE; }
"false"         { TR(K_FALSE);    return K_FALSE; }

    /* Literals */
{DIGIT}+        {
                    yylval.int_val = atoi(yytext);
                    TR(INT_LITERAL);
                    return INT_LITERAL;
                }

{ID}            {
                    auto it = g_defines.find(yytext);
                    if (it != g_defines.end()) {
                        const std::string& val = it->second;
                        for (auto rit = val.rbegin(); rit != val.rend(); ++rit) {
                            unput(*rit);
                        }
                    } else {
                        yylval.str_val = strdup(yytext);
                        /* Disambiguate IDENT vs TYPENAME:
                           an identifier previously introduced by a typedef
                           is returned as TYPENAME so the parser can use it
                           as a type without ambiguity with statement-leading
                           identifiers. */
                        if (p2p::typedef_is_known(yytext)) {
                            TR(TYPENAME);
                            return TYPENAME;
                        }
                        TR(IDENT);
                        return IDENT;
                    }
                }

    /* Single-character tokens */
[!?=+\-*/%<>(){}\[\],;:@.]  {
                                if (yytext[0] == '{') g_brace_depth++;
                                else if (yytext[0] == '}' && g_brace_depth > 0) g_brace_depth--;
                                if (trace_tokens())
                                    fprintf(stderr, "[tok] line %d: CHAR '%c'\n",
                                            yylineno, yytext[0]);
                                return yytext[0];
                            }
\"[^\"]*\"      {
                    /* String literal — used only inside printf().
                       We store the text (without surrounding quotes) into
                       yylval.str_val so the parser can attach it to a
                       PrintfStmt. */
                    int n = (int)strlen(yytext);
                    /* trim surrounding quotes */
                    char* s = (char*)malloc(n - 1);
                    memcpy(s, yytext + 1, n - 2);
                    s[n - 2] = '\0';
                    yylval.str_val = s;
                    if (trace_tokens())
                        fprintf(stderr, "[tok] line %d: STRING_LITERAL\n", yylineno);
                    return STRING_LITERAL;
                }

.               {
                    fprintf(stderr, "Lexer error at line %d: unexpected char '%c' (0x%02x)\n",
                            yylineno, yytext[0], (unsigned char)yytext[0]);
                }

%%