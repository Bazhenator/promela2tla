#pragma once

#include <vector>
#include <string>
#include "ast.h"

namespace p2p {

struct TypeError {
    std::string message;
    int         line;
    int         column;
};

/* Walks the module, infers types of expressions, and reports any type
   errors found (incompatible assignments, wrong built-in arguments,
   send/recv mismatches, inline arity, etc.). Returns the list of errors
   (empty == OK). Best-effort: errors don't abort the walk. */
std::vector<TypeError> type_check(Module& root);

} // namespace p2p