#include "codegen.h"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

extern "C" void p2p_defines_names(std::vector<std::string>*);

namespace p2p {

namespace {

class Emitter {
public:
    void line(const std::string& s = "") {
        for (int i = 0; i < indent_; ++i) out_ << "    ";
        out_ << s << "\n";
    }
    void raw(const std::string& s) { out_ << s; }
    void indent()   { ++indent_; }
    void dedent()   { if (indent_ > 0) --indent_; }
    std::string str() const { return out_.str(); }
private:
    std::ostringstream out_;
    int indent_ = 0;
};

struct ModuleSummary {
    std::vector<const ProctypeDecl*> proctypes;
    std::vector<const InitDecl*>     inits;
    std::vector<const MtypeDecl*>    mtypes;
    std::vector<const VarDecl*>      globals;
    std::vector<const TypedefDecl*>  typedefs;
    std::vector<const LtlDecl*>      ltls;
};

ModuleSummary summarize(const Module& m) {
    ModuleSummary s;
    for (auto& d : m.declarations) {
        if (auto* p  = dynamic_cast<const ProctypeDecl*>(d.get())) s.proctypes.push_back(p);
        else if (auto* i  = dynamic_cast<const InitDecl*>(d.get()))    s.inits.push_back(i);
        else if (auto* mt = dynamic_cast<const MtypeDecl*>(d.get()))   s.mtypes.push_back(mt);
        else if (auto* v  = dynamic_cast<const VarDecl*>(d.get()))     s.globals.push_back(v);
        else if (auto* td = dynamic_cast<const TypedefDecl*>(d.get())) s.typedefs.push_back(td);
        else if (auto* lt = dynamic_cast<const LtlDecl*>(d.get()))     s.ltls.push_back(lt);
    }
    return s;
}

std::string proc_name(const std::string& s) {
    if (s.empty()) return s;
    std::string r = s;
    if (r[0] >= 'a' && r[0] <= 'z') r[0] = (char)(r[0] - 'a' + 'A');
    return r;
}

std::string mtype_const(const std::string& s) {
    std::string r = s;
    for (auto& c : r) c = (char)std::toupper((unsigned char)c);
    return r;
}

/* Render an Expr as a TLA+ expression text. Subset sufficient for
   initializers in Stage 4b. */
std::string render_expr(const Expr& e) {
    if (auto* lit = dynamic_cast<const IntLiteral*>(&e)) {
        return std::to_string(lit->value);
    }
    if (auto* lit = dynamic_cast<const BoolLiteral*>(&e)) {
        return lit->value ? "TRUE" : "FALSE";
    }
    if (auto* id = dynamic_cast<const IdentExpr*>(&e)) {
        if (id->resolved) {
            if (dynamic_cast<const MtypeDecl*>(id->resolved)) {
                return mtype_const(id->name);
            }
        }
        return id->name;
    }
    if (auto* b = dynamic_cast<const BinaryExpr*>(&e)) {
        std::string op;
        switch (b->op) {
            case BinaryOp::Add: op = "+"; break;
            case BinaryOp::Sub: op = "-"; break;
            case BinaryOp::Mul: op = "*"; break;
            case BinaryOp::Div: op = "\\div"; break;
            case BinaryOp::Mod: op = "%"; break;
            case BinaryOp::Shl: op = "*"; break;
            case BinaryOp::Shr: op = "\\div"; break;
            case BinaryOp::Lt:  op = "<"; break;
            case BinaryOp::Le:  op = "<="; break;
            case BinaryOp::Gt:  op = ">"; break;
            case BinaryOp::Ge:  op = ">="; break;
            case BinaryOp::Eq:  op = "="; break;
            case BinaryOp::Neq: op = "#"; break;
            case BinaryOp::And: op = "/\\"; break;
            case BinaryOp::Or:  op = "\\/"; break;
        }
        return "(" + (b->lhs ? render_expr(*b->lhs) : std::string("0"))
             + " " + op + " "
             + (b->rhs ? render_expr(*b->rhs) : std::string("0")) + ")";
    }
    if (auto* u = dynamic_cast<const UnaryExpr*>(&e)) {
        if (u->op == UnaryOp::Neg) return "(-" + (u->operand ? render_expr(*u->operand) : std::string("0")) + ")";
        if (u->op == UnaryOp::Not) return "(~" + (u->operand ? render_expr(*u->operand) : std::string("FALSE")) + ")";
        return "0";
    }
    if (auto* p = dynamic_cast<const ParenExpr*>(&e)) {
        return p->inner ? "(" + render_expr(*p->inner) + ")" : "0";
    }
    return "0";
}

std::string default_init(const Type& t) {
    switch (t.kind) {
        case BasicTypeKind::Bool:  return "FALSE";
        case BasicTypeKind::Chan:  return "<<>>";
        case BasicTypeKind::Mtype: return "0";
        case BasicTypeKind::Named: return "0";
        default:                   return "0";
    }
}

std::string render_var_init(const VarDecl& v) {
    if (v.array_size) {
        std::string n = render_expr(*v.array_size);
        std::string elem = v.type ? default_init(*v.type) : "0";
        return "[i \\in 0..((" + n + ") - 1) |-> " + elem + "]";
    }
    if (v.type && v.type->kind == BasicTypeKind::Chan) {
        return "<<>>";
    }
    if (v.init) {
        return render_expr(*v.init);
    }
    return v.type ? default_init(*v.type) : "0";
}

void emit_constants(Emitter& e) {
    std::vector<std::string> names;
    p2p_defines_names(&names);
    e.line("CONSTANTS");
    e.indent();
    if (names.empty()) {
        e.line("\\* (no #define directives in source)");
    } else {
        for (size_t i = 0; i < names.size(); ++i) {
            bool last = (i + 1 == names.size());
            e.line(names[i] + (last ? "" : ","));
        }
    }
    e.dedent();
}

void emit_variables_block(Emitter& e, const ModuleSummary& s) {
    e.line("variables");
    e.indent();

    bool had_mtypes = false;
    for (auto* m : s.mtypes) {
        for (auto& name : m->names) {
            std::string uc = mtype_const(name);
            e.line(uc + " = \"" + uc + "\",");
            had_mtypes = true;
        }
    }
    if (had_mtypes) e.line();

    for (size_t i = 0; i < s.globals.size(); ++i) {
        const VarDecl& v = *s.globals[i];
        bool last_of_all = (i + 1 == s.globals.size());
        std::string init = render_var_init(v);
        e.line(v.name + " = " + init + (last_of_all ? ";" : ","));
    }

    if (!had_mtypes && s.globals.empty()) {
        e.line("placeholder = 0;");
    }

    e.dedent();
}

void emit_proctype(Emitter& e, const ProctypeDecl& p) {
    std::string name = proc_name(p.name);
    e.line("fair process (" + name + " = \"" + name + "\") {");
    e.indent();
    e.line(name + "_start: skip;");
    e.dedent();
    e.line("}");
    e.line();
}

void emit_init(Emitter& e, const InitDecl&) {
    e.line("fair process (Init = \"Init\") {");
    e.indent();
    e.line("init_start: skip;");
    e.dedent();
    e.line("}");
    e.line();
}

void emit_ltl_stubs(Emitter& e, const ModuleSummary& s) {
    if (s.ltls.empty()) return;
    e.line();
    e.line("(* LTL properties (translation pending — Stage 4f) *)");
    for (auto* l : s.ltls) {
        e.line("\\* ltl " + l->name + " — not yet translated");
    }
}

} // namespace

std::string generate_tla(const Module& m, const std::string& module_name) {
    Emitter e;
    auto s = summarize(m);

    std::string bar(34, '-');
    e.line(bar + " MODULE " + module_name + " " + bar);
    e.line("EXTENDS Integers, Sequences, TLC");
    e.line();

    emit_constants(e);
    e.line();

    e.line("(*--algorithm Main {");
    e.indent();
    emit_variables_block(e, s);
    e.line();

    for (auto* p : s.proctypes) if (p->instance_count > 0)  emit_proctype(e, *p);
    for (auto* p : s.proctypes) if (p->instance_count == 0) emit_proctype(e, *p);
    for (auto* i : s.inits) emit_init(e, *i);

    e.dedent();
    e.line("} *)");

    e.line();
    e.line("\\* BEGIN TRANSLATION");
    e.line("\\* (will be filled by the PlusCal translator)");
    e.line("\\* END TRANSLATION");

    emit_ltl_stubs(e, s);

    e.line();
    e.line(std::string(77, '='));

    return e.str();
}

} // namespace p2p