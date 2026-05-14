#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "ast.h"

namespace p2p {

/* What kind of named entity a symbol points to.
   Used by the resolver to enforce that, e.g., a goto target is a label
   and not a variable, or that an inline-call name is actually an inline. */
enum class SymKind {
    Variable,       /* VarDecl, Param, LocalVarDeclStmt::decl */
    Typedef,        /* TypedefDecl */
    MtypeValue,     /* one of the names inside `mtype = { a, b, c }` */
    Proctype,       /* ProctypeDecl (regular or active) */
    Inline,         /* InlineDecl */
    Init,           /* the singleton init { ... } */
    Label,          /* LabeledStmt label inside a proctype/inline body */
};

const char* sym_kind_name(SymKind k);

/* A single entry in a scope table. The AST `node` is the declaration the
   name refers to; the `kind` tells the resolver how to verify usage. */
struct Symbol {
    std::string name;
    SymKind     kind;
    Node*       node;
    int         line;
    int         column;
    Param*      param = nullptr;   /* only for parameter symbols */
};

/* A flat lexical scope: a map from name to Symbol.
   Lookups also walk the parent chain. */
class Scope {
public:
    Scope* parent = nullptr;

    /* Returns the existing Symbol if a name is redeclared in *this* scope
       (so the caller can emit a duplicate-declaration error and skip
       the insertion). Returns nullptr on success. */
    const Symbol* try_insert(Symbol s);

    /* Walks self then parent. Returns nullptr if not found anywhere. */
    const Symbol* lookup(const std::string& name) const;

    /* Same as lookup but only in this scope. */
    const Symbol* lookup_local(const std::string& name) const;

private:
    std::unordered_map<std::string, Symbol> table_;
};

} // namespace p2p