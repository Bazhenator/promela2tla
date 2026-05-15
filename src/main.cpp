#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "ast.h"
#include "pipeline.h"

/* Print all diagnostics from a CompileResult. Returns true if any error
   was printed. */
static bool report_diagnostics(const char* path, const p2p::CompileResult& r) {
    bool had_error = false;

    for (auto& e : r.resolve_errors) {
        fprintf(stderr, "%s:%d:%d: error: %s\n",
                path, e.line, e.column, e.message.c_str());
        had_error = true;
    }
    if (!r.resolve_errors.empty()) {
        fprintf(stderr, "Name resolution: %zu error(s)\n", r.resolve_errors.size());
    } else if (r.parse_ok && r.mode == p2p::ParseMode::Program) {
        fprintf(stderr, "Name resolution OK.\n");
    }

    for (auto& e : r.type_errors) {
        fprintf(stderr, "%s:%d:%d: type error: %s\n",
                path, e.line, e.column, e.message.c_str());
        had_error = true;
    }
    if (!r.type_errors.empty()) {
        fprintf(stderr, "Type check: %zu error(s)\n", r.type_errors.size());
    } else if (r.parse_ok && r.mode == p2p::ParseMode::Program) {
        fprintf(stderr, "Type check OK.\n");
    }

    return had_error;
}

static int run(const char* path, p2p::ParseMode mode,
               bool print_tree, bool emit_tla) {
    p2p::CompileResult r = p2p::compile_file(path, mode);

    if (!r.parse_ok) {
        /* Distinguish "file not found" from "syntax error": if the module
           is empty and nothing parsed, it's likely a parse failure already
           reported by yyerror, or an open failure. */
        fprintf(stderr, "Parsing failed\n");
        return 1;
    }

    if (mode == p2p::ParseMode::Program) {
        fprintf(stderr, "Parsing OK. Root module created.\n");
        report_diagnostics(path, r);
        if (print_tree && r.module) {
            p2p::print_ast(*r.module, stdout);
        }
        if (emit_tla && r.ok()) {
            /* Derive module name from the file path: basename without extension. */
            std::string mod_name = path;
            auto slash = mod_name.find_last_of('/');
            if (slash != std::string::npos) mod_name = mod_name.substr(slash + 1);
            auto dot = mod_name.find_last_of('.');
            if (dot != std::string::npos) mod_name = mod_name.substr(0, dot);
            std::string tla = p2p::emit_tla(r, mod_name);
            fputs(tla.c_str(), stdout);
        }
    } else if (mode == p2p::ParseMode::Expr) {
        if (r.expr) {
            p2p::print_ast(*r.expr, stdout);
        } else {
            fprintf(stderr, "No expression parsed.\n");
        }
    } else { /* StmtBlock */
        fputs("(block\n", stdout);
        for (auto& s : r.stmts) {
            fputs("  ", stdout);
            if (s) p2p::print_ast(*s, stdout);
            else   fputs("(null)\n", stdout);
        }
        fputs(")\n", stdout);
    }

    return 0;
}

int main(int argc, char** argv) {
    bool lex_only   = false;
    bool expr_mode  = false;
    bool stmt_mode  = false;
    bool print_tree = false;
    bool emit_tla = false;
    const char* path = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--lex-only") == 0) {
            lex_only = true;
            setenv("P2P_TRACE_TOKENS", "1", 1);
        } else if (strcmp(argv[i], "--print-ast") == 0) {
            print_tree = true;
        } else if (strcmp(argv[i], "--expr") == 0) {
            expr_mode = true;
        } else if (strcmp(argv[i], "--stmt") == 0) {
            stmt_mode = true;
        } else if (strcmp(argv[i], "--emit-tla") == 0) {
            emit_tla = true;
        } else {
            path = argv[i];
        }
    }

    if (!path) {
        fprintf(stderr,
            "Usage: %s [--lex-only|--print-ast|--expr|--stmt] <file.pml>\n",
            argv[0]);
        return 1;
    }

    if (lex_only) {
        /* Lex-only mode still needs the raw lexer loop; keep it here. */
        extern FILE* yyin;
        extern int   yylex();
        extern int   g_parse_mode;
        yyin = fopen(path, "r");
        if (!yyin) { perror(path); return 1; }
        g_parse_mode = 0;
        while (yylex() != 0) {}
        fprintf(stderr, "Lexing done.\n");
        fclose(yyin);
        return 0;
    }

    p2p::ParseMode mode = p2p::ParseMode::Program;
    if (expr_mode) mode = p2p::ParseMode::Expr;
    if (stmt_mode) mode = p2p::ParseMode::StmtBlock;

    return run(path, mode, print_tree, emit_tla);
}
