#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ast.h"

extern int yyparse();
extern int yylex();
extern FILE* yyin;
extern p2p::Module* g_root;

int main(int argc, char** argv) {
    bool lex_only = false;
    const char* path = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--lex-only") == 0) {
            lex_only = true;
            setenv("P2P_TRACE_TOKENS", "1", 1);
        } else {
            path = argv[i];
        }
    }
    if (!path) {
        fprintf(stderr, "Usage: %s [--lex-only] <file.pml>\n", argv[0]);
        return 1;
    }

    yyin = fopen(path, "r");
    if (!yyin) { perror(path); return 1; }

    if (lex_only) {
        int tok;
        while ((tok = yylex()) != 0) {
        }
        fprintf(stderr, "Lexing done.\n");
    } else {
        if (yyparse() != 0) {
            fprintf(stderr, "Parsing failed\n");
            return 1;
        }
        fprintf(stderr, "Parsing OK. Root module created.\n");
        delete g_root;
    }

    fclose(yyin);
    return 0;
}