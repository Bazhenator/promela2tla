#include "pipeline.h"
#include <cstdio>

/* bison/flex globals — implementation detail of this module. */
extern int   yyparse();
extern FILE* yyin;
extern int   g_parse_mode;
extern p2p::Module* g_root;
extern p2p::Expr*   g_expr_result;
/* g_stmt_result is a StmtList* (parser-internal struct). We declare it
   with the real type via parser_types.h. */
#include "parser_types.h"
extern StmtList* g_stmt_result;

/* Mirror of the #defines in parser.y — kept in sync deliberately.
   If these ever drift, parsing silently picks the wrong start symbol,
   so they're asserted below. */
#define PARSE_PROGRAM     0
#define PARSE_EXPR        1
#define PARSE_STMT_BLOCK  2

namespace p2p {

namespace {

int mode_to_int(ParseMode m) {
    switch (m) {
        case ParseMode::Program:   return PARSE_PROGRAM;
        case ParseMode::Expr:      return PARSE_EXPR;
        case ParseMode::StmtBlock: return PARSE_STMT_BLOCK;
    }
    return PARSE_PROGRAM;
}

} // namespace

CompileResult compile_file(const std::string& path, ParseMode mode) {
    CompileResult result;
    result.mode = mode;

    yyin = fopen(path.c_str(), "r");
    if (!yyin) {
        /* parse_ok stays false; caller reports the open failure. */
        return result;
    }

    /* Reset parser-facing globals before each run. */
    g_root          = nullptr;
    g_expr_result   = nullptr;
    g_stmt_result   = nullptr;
    g_parse_mode    = mode_to_int(mode);

    int rc = yyparse();
    fclose(yyin);
    yyin = nullptr;

    if (rc != 0) {
        /* Syntax error already printed by yyerror. */
        return result;
    }
    result.parse_ok = true;

    if (mode == ParseMode::Program) {
        if (!g_root) g_root = new Module();   /* empty file -> empty module */
        result.module.reset(g_root);
        g_root = nullptr;

        result.resolve_errors = resolve_names(*result.module);
        result.type_errors    = type_check(*result.module);
    } else if (mode == ParseMode::Expr) {
        if (g_expr_result) {
            result.expr.reset(g_expr_result);
            g_expr_result = nullptr;
        }
    } else { /* StmtBlock */
        if (g_stmt_result) {
            for (auto& s : g_stmt_result->items) {
                result.stmts.push_back(std::move(s));
            }
            delete g_stmt_result;
            g_stmt_result = nullptr;
        }
    }

    return result;
}

} // namespace p2p