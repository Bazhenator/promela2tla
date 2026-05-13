#pragma once
#include <string>

namespace p2p {

/* Tracks user-defined typedef names. Populated by the parser when it
   reduces a `typedef Name { ... }` declaration; consulted by the lexer
   to disambiguate IDENT vs TYPENAME so that named types can appear
   inside bodies without causing reduce/reduce conflicts. */
void typedef_register(const std::string& name);
bool typedef_is_known(const std::string& name);
void typedef_clear(); /* used between test runs */

} // namespace p2p