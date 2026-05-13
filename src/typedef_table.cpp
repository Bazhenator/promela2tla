#include "typedef_table.h"
#include <unordered_set>

namespace p2p {

static std::unordered_set<std::string>& table() {
    static std::unordered_set<std::string> t;
    return t;
}

void typedef_register(const std::string& name) {
    table().insert(name);
}

bool typedef_is_known(const std::string& name) {
    return table().find(name) != table().end();
}

void typedef_clear() {
    table().clear();
}

} // namespace p2p