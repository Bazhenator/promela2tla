#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ast.h"
#include "resolver.h"
#include "type_check.h"

namespace p2p {

/* Which entry point of the grammar to use. Mirrors the START_* markers
   the lexer emits; kept as an enum so callers don't touch g_parse_mode. */
enum class ParseMode {
    Program,    /* a full .pml file */
    Expr,       /* a single expression (test mode) */
    StmtBlock,  /* a { ... } statement block (test mode) */
};

/* The outcome of running the front-end pipeline on one input.
   Owns the AST. All error lists are empty on full success. */
struct CompileResult {
    ParseMode mode = ParseMode::Program;

    bool parse_ok = false;

    /* Program mode: the module root. */
    std::unique_ptr<Module> module;

    /* Expr / StmtBlock test modes: the parsed fragment. */
    std::unique_ptr<Expr>            expr;
    std::vector<std::unique_ptr<Stmt>> stmts;

    /* Semantic phases (Program mode only). */
    std::vector<ResolveError> resolve_errors;
    std::vector<TypeError>    type_errors;

    bool ok() const {
        return parse_ok && resolve_errors.empty() && type_errors.empty();
    }
};

/* Runs the front-end on `path`:
   - Program mode: parse -> resolve names -> type check.
   - Expr / StmtBlock modes: parse only (semantic passes need a Module).
   Opens and closes the file itself. On a file-open failure, returns a
   result with parse_ok == false and an empty module. */
CompileResult compile_file(const std::string& path, ParseMode mode);

} // namespace p2p