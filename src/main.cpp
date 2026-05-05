#include <cstdio>
#include "ast.h"

extern int yyparse();
extern FILE* yyin;
extern p2p::Module* g_root;

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.pml>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }
    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        return 1;
    }
    fprintf(stderr, "Parsing OK. Root module created.\n");
    fclose(yyin);
    delete g_root;
    return 0;
}