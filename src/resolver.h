#pragma once

#include <vector>
#include <string>
#include "ast.h"
#include "symbol_table.h"

namespace p2p {

/* Diagnostic from the resolver: an error tied to a source location. */
struct ResolveError {
    std::string message;
    int         line;
    int         column;
};

/* Walks the module, builds scopes, attaches `resolved` pointers on every
   ident/call/goto/typename use. Returns the list of errors (empty == OK).
   Resolution is best-effort: an unresolved ref leaves `resolved == nullptr`
   and adds an error, but the walk continues so the user sees all problems. */
std::vector<ResolveError> resolve_names(Module& root);

} // namespace p2p