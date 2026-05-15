#pragma once

#include <string>
#include "ast.h"

namespace p2p {

/* Generate a PlusCal/TLA+ document from a fully-checked Module.
   Returns the document text. The Module is read but not modified.

   The generator assumes the module has passed name resolution and type
   checking; it does not re-validate semantics. */
std::string generate_tla(const Module& m, const std::string& module_name);

} // namespace p2p