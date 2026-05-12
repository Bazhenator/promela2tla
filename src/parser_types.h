#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ast.h"

/* Heap-allocated helpers for non-AST lists carried through the parser.
   Lives in its own header so it can be included from parser.y (via
   %code top and %code requires), the lexer, main.cpp, and anywhere else
   that needs the parser's semantic value types. */

struct TypeList    { std::vector<p2p::TypePtr> items; };
struct IdentList   { std::vector<std::string>  items; };
struct VarDeclList { std::vector<std::unique_ptr<p2p::VarDecl>> items; };
struct StmtList    { std::vector<p2p::StmtPtr> items; };
struct ExprList    { std::vector<p2p::ExprPtr> items; };
struct BranchList  { std::vector<p2p::GuardedBranch> items; };