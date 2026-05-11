#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ast.h"

extern int yyparse();
extern int yylex();
extern FILE* yyin;
extern p2p::Module* g_root;

/* Defined in parser.y; selected by main() before yyparse(). */
extern int g_parse_mode;
extern p2p::Expr* g_expr_result;
#define PARSE_PROGRAM 0
#define PARSE_EXPR    1

static int run_program(const char* path, bool print_tree) {
    yyin = fopen(path, "r");
    if (!yyin) { perror(path); return 1; }
    g_parse_mode = PARSE_PROGRAM;
    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        fclose(yyin);
        return 1;
    }
    fprintf(stderr, "Parsing OK. Root module created.\n");
    if (print_tree && g_root) {
        p2p::print_ast(*g_root, stdout);
    }
    delete g_root;
    g_root = nullptr;
    fclose(yyin);
    return 0;
}

static int run_expr(const char* path) {
    yyin = fopen(path, "r");
    if (!yyin) { perror(path); return 1; }
    g_parse_mode = PARSE_EXPR;
    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        fclose(yyin);
        return 1;
    }
    if (g_expr_result) {
        p2p::print_ast(*g_expr_result, stdout);
        delete g_expr_result;
        g_expr_result = nullptr;
    } else {
        fprintf(stderr, "No expression parsed.\n");
    }
    fclose(yyin);
    return 0;
}

int main(int argc, char** argv) {
    bool lex_only = false;
    bool expr_mode = false;
    bool print_tree = false;
    const char* path = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--lex-only") == 0) {
            lex_only = true;
            setenv("P2P_TRACE_TOKENS", "1", 1);
        } else if (strcmp(argv[i], "--print-ast") == 0) {
            print_tree = true;
        } else if (strcmp(argv[i], "--expr") == 0) {
            expr_mode = true;
        } else {
            path = argv[i];
        }
    }
    if (!path) {
        fprintf(stderr,
            "Usage: %s [--lex-only|--print-ast|--expr] <file.pml>\n",
            argv[0]);
        return 1;
    }

    if (lex_only) {
        yyin = fopen(path, "r");
        if (!yyin) { perror(path); return 1; }
        g_parse_mode = PARSE_PROGRAM;  /* swallow start marker normally */
        int tok;
        while ((tok = yylex()) != 0) {}
        fprintf(stderr, "Lexing done.\n");
        fclose(yyin);
        return 0;
    }
    if (expr_mode) {
        return run_expr(path);
    }
    return run_program(path, print_tree);
}