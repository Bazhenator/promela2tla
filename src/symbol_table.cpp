#include "symbol_table.h"

namespace p2p {

const char* sym_kind_name(SymKind k) {
    switch (k) {
        case SymKind::Variable:   return "variable";
        case SymKind::Typedef:    return "typedef";
        case SymKind::MtypeValue: return "mtype value";
        case SymKind::Proctype:   return "proctype";
        case SymKind::Inline:     return "inline";
        case SymKind::Init:       return "init";
        case SymKind::Label:      return "label";
    }
    return "?";
}

const Symbol* Scope::try_insert(Symbol s) {
    auto it = table_.find(s.name);
    if (it != table_.end()) return &it->second;
    auto inserted = table_.emplace(s.name, std::move(s));
    return nullptr;
    (void)inserted;
}

const Symbol* Scope::lookup(const std::string& name) const {
    if (auto sym = lookup_local(name)) return sym;
    if (parent) return parent->lookup(name);
    return nullptr;
}

const Symbol* Scope::lookup_local(const std::string& name) const {
    auto it = table_.find(name);
    if (it == table_.end()) return nullptr;
    return &it->second;
}

} // namespace p2p