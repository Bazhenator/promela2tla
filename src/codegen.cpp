#include "codegen.h"
#include <sstream>
#include <string>
#include <vector>

namespace p2p {

namespace {

/* Indented text emitter. Keeps a stringstream and an indent counter;
   each call to line() prefixes the current indent and appends '\n'. */
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

/* Collect what we need from the module before emitting:
     - list of #define-style globals → CONSTANTS  (Stage 4a: empty for now,
       we don't yet model #defines in the AST; we'll wire them in 4b)
     - list of global variable declarations
     - list of mtype values (later → string constants)
     - list of proctypes (including active) and init
   The walk here is deliberately shallow; deep traversal of bodies
   begins in Stage 4c. */
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
        else if (auto* i = dynamic_cast<const InitDecl*>(d.get()))   s.inits.push_back(i);
        else if (auto* mt = dynamic_cast<const MtypeDecl*>(d.get()))  s.mtypes.push_back(mt);
        else if (auto* v  = dynamic_cast<const VarDecl*>(d.get()))    s.globals.push_back(v);
        else if (auto* td = dynamic_cast<const TypedefDecl*>(d.get())) s.typedefs.push_back(td);
        else if (auto* lt = dynamic_cast<const LtlDecl*>(d.get()))    s.ltls.push_back(lt);
        /* InlineDecl: not emitted at top level in TLA;
           reserved for Stage 4d (inline analysis). */
    }
    return s;
}

/* In Stage 4a we don't translate variable/declaration bodies. Stub
   placeholder for the `variables` block. 4b replaces this. */
void emit_variables_block(Emitter& e, const ModuleSummary& s) {
    (void)s;
    e.line("variables");
    e.indent();
    /* A single placeholder so the variables block isn't syntactically
       empty (PlusCal accepts empty variables, but seeing a placeholder
       makes the 4a output greppable). */
    e.line("placeholder = 0;");
    e.dedent();
}

/* Choose a stable PlusCal identifier for a Promela proctype.
   Promela uses lowercase by convention; PlusCal processes are typically
   capitalized. We capitalize the first letter and keep the rest. */
std::string proc_name(const std::string& s) {
    if (s.empty()) return s;
    std::string r = s;
    if (r[0] >= 'a' && r[0] <= 'z') r[0] = (char)(r[0] - 'a' + 'A');
    return r;
}

/* Emit one `process` block, body still empty in Stage 4a.

   For active proctypes we currently emit a single-process form
   (process X = "X" { ... }); a parametric proctype declared without
   `active` produces the same shape but is unreachable in Stage 4a
   because we don't translate `run` yet. That gets reworked in Stage 4e
   when topology analysis decides the real ProcSet for each process. */
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

/* Emit LTL placeholders after END TRANSLATION.
   Stage 4f handles real translation; for now we just list the names
   so the document mentions them. */
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

    /* Module header. */
    std::string bar(34, '-');
    e.line(bar + " MODULE " + module_name + " " + bar);
    e.line("EXTENDS Integers, Sequences, TLC");
    e.line();

    /* CONSTANTS block — empty for Stage 4a. 4b will fill it from any
       #define-style globals once we wire those into the AST. */
    e.line("CONSTANTS");
    e.indent();
    e.line("\\* (no constants extracted yet — Stage 4b)");
    e.dedent();
    e.line();

    /* PlusCal algorithm. */
    e.line("(*--algorithm Main {");
    e.indent();

    emit_variables_block(e, s);
    e.line();

    /* Processes: active proctypes first, then proctypes, then init.
       In Stage 4a all are stub-bodies; the order doesn't matter for
       correctness but keeps output readable. */
    for (auto* p : s.proctypes) {
        if (p->instance_count > 0) emit_proctype(e, *p);
    }
    for (auto* p : s.proctypes) {
        if (p->instance_count == 0) emit_proctype(e, *p);
    }
    for (auto* i : s.inits) emit_init(e, *i);

    e.dedent();
    e.line("} *)");

    /* End-of-translation marker the PlusCal translator expects. */
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