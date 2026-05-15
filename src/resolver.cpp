#include "resolver.h"
#include <unordered_set>
extern "C" int p2p_define_known(const char* name);

namespace p2p {

namespace {

struct Resolver : Visitor {
    std::vector<ResolveError> errors;

    /* Global scope is owned by the resolver and used for all proctypes/
       inlines/init bodies as a parent of their inner scopes. */
    Scope global;

    /* Currently active scope; changes as we enter/leave proctypes etc. */
    Scope* cur = nullptr;

    /* Inside a body, labels live in a separate namespace from variables
       (so a label `loop:` doesn't conflict with a variable `loop`).
       Collected via a pre-pass on the body to allow forward `goto`. */
    std::unordered_map<std::string, LabeledStmt*> labels;

    void err(int line, int col, std::string msg) {
        errors.push_back({std::move(msg), line, col});
    }

    /* Pass 1: register all top-level names so the body pass can
           resolve forward references between proctypes/inlines/typedefs. */
    void register_top_level(Module& m) {
        for (auto& d : m.declarations) {
            if (auto* td = dynamic_cast<TypedefDecl*>(d.get())) {
                auto* dup = global.try_insert({td->name, SymKind::Typedef, td, td->line, td->column});
                if (dup) err(td->line, td->column,
                             "typedef '" + td->name + "' redeclared (first at line "
                             + std::to_string(dup->line) + ")");
            } else if (auto* mt = dynamic_cast<MtypeDecl*>(d.get())) {
                for (auto& name : mt->names) {
                    auto* dup = global.try_insert({name, SymKind::MtypeValue, mt, mt->line, mt->column});
                    if (dup) err(mt->line, mt->column,
                                 "mtype value '" + name + "' redeclared");
                }
            } else if (auto* p = dynamic_cast<ProctypeDecl*>(d.get())) {
                auto* dup = global.try_insert({p->name, SymKind::Proctype, p, p->line, p->column});
                if (dup) err(p->line, p->column,
                             "proctype '" + p->name + "' redeclared");
            } else if (auto* i = dynamic_cast<InlineDecl*>(d.get())) {
                auto* dup = global.try_insert({i->name, SymKind::Inline, i, i->line, i->column});
                if (dup) err(i->line, i->column,
                             "inline '" + i->name + "' redeclared");
            } else if (auto* v = dynamic_cast<VarDecl*>(d.get())) {
                auto* dup = global.try_insert({v->name, SymKind::Variable, v, v->line, v->column});
                if (dup) err(v->line, v->column,
                             "global variable '" + v->name + "' redeclared");
            }
            /* LtlDecl: names live in their own world; skip here. */
        }
    }

    /* Collect labels for a body before resolving stmts, so forward gotos work. */
    void collect_labels(const std::vector<StmtPtr>& body) {
        labels.clear();
        std::vector<const std::vector<StmtPtr>*> work;
        work.push_back(&body);
        while (!work.empty()) {
            auto* cur_body = work.back();
            work.pop_back();
            for (auto& s : *cur_body) {
                if (auto* lab = dynamic_cast<LabeledStmt*>(s.get())) {
                    labels[lab->label] = lab;
                    /* Recurse into the wrapped stmt in case it's a block. */
                    /* Simpler: we don't walk into nested blocks for labels;
                       Promela typically scopes labels to the whole body anyway. */
                }
                if (auto* a = dynamic_cast<AtomicStmt*>(s.get())) work.push_back(&a->body);
                if (auto* d = dynamic_cast<DStepStmt*>(s.get())) work.push_back(&d->body);
                if (auto* f = dynamic_cast<ForStmt*>(s.get()))   work.push_back(&f->body);
                /* if/do have branches with stmts inside */
                if (auto* i = dynamic_cast<IfStmt*>(s.get())) {
                    for (auto& br : i->branches) work.push_back(&br.stmts);
                }
                if (auto* d = dynamic_cast<DoStmt*>(s.get())) {
                    for (auto& br : d->branches) work.push_back(&br.stmts);
                }
            }
        }
    }

    /* Visitor overrides — actual work. */
    void visit(Module& m) override {
        cur = &global;
        register_top_level(m);
        for (auto& d : m.declarations) {
            d->accept(*this);
        }
    }

    void visit(VarDecl& v) override {
        /* Resolve named type. */
        if (v.type && v.type->kind == BasicTypeKind::Named) {
            auto* s = cur->lookup(v.type->named);
            if (!s) {
                err(v.line, v.column,
                    "unknown type '" + v.type->named + "'");
            } else if (s->kind != SymKind::Typedef) {
                err(v.line, v.column,
                    "'" + v.type->named + "' is a " + sym_kind_name(s->kind)
                    + ", not a type");
            } else {
                v.type->resolved = s->node;
            }
        }
        if (v.array_size) v.array_size->accept(*this);
        if (v.init)       v.init->accept(*this);
    }

    void visit(TypedefDecl& td) override {
        /* Field decls are like local var decls; type names there refer to
           the global scope. */
        for (auto& f : td.fields) f->accept(*this);
    }

    void visit(MtypeDecl&) override { /* nothing to resolve */ }
    void visit(LtlDecl&) override {
    /* LTL formulas reference global state and propositions; resolving
       them properly needs the full model plus claim-specific scoping.
       Deferred to Stage 5 (LTL translation). */
    }
    void visit(DefineDecl&) override { /* no-op: defines were expanded by the lexer */ }

    void visit(ProctypeDecl& p) override {
        Scope local;
        local.parent = &global;
        cur = &local;

        /* Params */
        for (auto& param : p.params) {
            Symbol sym;
            sym.name   = param.name;
            sym.kind   = SymKind::Variable;
            sym.node   = nullptr;
            sym.line   = p.line;
            sym.column = p.column;
            sym.param  = &param;          /* <-- back-pointer to the Param */
            auto* dup = local.try_insert(sym);
            if (dup) err(p.line, p.column,
                 "parameter '" + param.name + "' duplicated in proctype '"
                 + p.name + "'");
            /* type resolution as before */
            if (param.type && param.type->kind == BasicTypeKind::Named) {
                auto* s = global.lookup(param.type->named);
                if (!s) err(p.line, p.column, "unknown parameter type '" + param.type->named + "'");
                else if (s->kind == SymKind::Typedef) param.type->resolved = s->node;
                else err(p.line, p.column, "'" + param.type->named + "' is not a type");
            }
        }
        collect_labels(p.body);
        for (auto& s : p.body) s->accept(*this);

        cur = &global;
    }

    void visit(InlineDecl&) override {
    /* Inline bodies in Promela are textual substitution: identifiers used
       inside them are resolved at the call site, not at the inline's own
       scope. We intentionally skip walking the body here. Resolution of
       inline bodies will happen during code generation, when each call
       site is expanded with the surrounding scope visible. */
    }   

    void visit(InitDecl& i) override {
        Scope local;
        local.parent = &global;
        cur = &local;
        collect_labels(i.body);
        for (auto& s : i.body) s->accept(*this);
        cur = &global;
    }

    /* Expressions */
    void visit(IntLiteral&) override {}
    void visit(BoolLiteral&) override {}
    void visit(IdentExpr& e) override {
        auto* s = cur->lookup(e.name);
        if (!s) {
        /* Could be a #define name — those aren't declared in Promela
           but become CONSTANTS in the generated TLA+. The lexer's
           define table is the source of truth. */
            if (p2p_define_known(e.name.c_str())) {
                return;  /* leave resolved == nullptr; codegen treats it as a constant */
            }
            err(e.line, e.column, "unknown identifier '" + e.name + "'");
            return;
        }
        if (s->param) {
            e.resolved_param = s->param;
        } else {
            e.resolved = s->node;
        }
    }
    void visit(IndexExpr& e) override {
        if (e.base)  e.base->accept(*this);
        if (e.index) e.index->accept(*this);
    }
    void visit(FieldExpr& e) override {
        if (e.base) e.base->accept(*this);
        /* Field name resolves against the type's fields; deferred to 3b.2. */
    }
    void visit(UnaryExpr& e) override   { if (e.operand) e.operand->accept(*this); }
    void visit(BinaryExpr& e) override  { if (e.lhs) e.lhs->accept(*this); if (e.rhs) e.rhs->accept(*this); }
    void visit(TernaryExpr& e) override {
        if (e.cond)      e.cond->accept(*this);
        if (e.then_expr) e.then_expr->accept(*this);
        if (e.else_expr) e.else_expr->accept(*this);
    }
    void visit(BuiltinCallExpr& e) override { if (e.arg) e.arg->accept(*this); }
    void visit(ParenExpr& e) override   { if (e.inner) e.inner->accept(*this); }
    void visit(LtlFormula& f) override {
        if (f.lhs)  f.lhs->accept(*this);
        if (f.rhs)  f.rhs->accept(*this);
        if (f.atom) f.atom->accept(*this);
    }

    /* Statements */
    void visit(ExprStmt& s) override   { if (s.expr) s.expr->accept(*this); }
    void visit(AssignStmt& s) override { if (s.lhs) s.lhs->accept(*this); if (s.rhs) s.rhs->accept(*this); }
    void visit(IfStmt& s) override {
        for (auto& br : s.branches) for (auto& st : br.stmts) if (st) st->accept(*this);
    }
    void visit(DoStmt& s) override {
        for (auto& br : s.branches) for (auto& st : br.stmts) if (st) st->accept(*this);
    }
    void visit(AtomicStmt& s) override { for (auto& st : s.body) if (st) st->accept(*this); }
    void visit(DStepStmt& s) override  { for (auto& st : s.body) if (st) st->accept(*this); }
    void visit(ForStmt& s) override {
        /* The loop variable is a fresh binding inside the body. Promela's
           `for (i : a..b)` binds `i`. We register it in a child scope. */
        Scope inner;
        inner.parent = cur;
        inner.try_insert({s.var, SymKind::Variable, nullptr, s.line, s.column});
        if (s.low)  s.low->accept(*this);
        if (s.high) s.high->accept(*this);
        Scope* saved = cur;
        cur = &inner;
        for (auto& st : s.body) if (st) st->accept(*this);
        cur = saved;
    }
    void visit(SelectStmt& s) override {
        /* `select (i : a..b)` binds `i` for the rest of the proctype.
           For simplicity we insert into the current scope. */
        cur->try_insert({s.var, SymKind::Variable, nullptr, s.line, s.column});
        if (s.low)  s.low->accept(*this);
        if (s.high) s.high->accept(*this);
    }
    void visit(SendStmt& s) override {
        if (s.chan) s.chan->accept(*this);
        for (auto& a : s.args) if (a) a->accept(*this);
    }
    void visit(RecvStmt& s) override {
        if (s.chan) s.chan->accept(*this);
        for (auto& a : s.args) if (a) a->accept(*this);
    }
    void visit(RunStmt& s) override {
        auto* sym = cur->lookup(s.name);
        if (!sym) {
            err(s.line, s.column, "unknown proctype '" + s.name + "' in run");
        } else if (sym->kind != SymKind::Proctype) {
            err(s.line, s.column,
                "'" + s.name + "' is a " + sym_kind_name(sym->kind) + ", not a proctype");
        } else {
            s.resolved = sym->node;
        }
        for (auto& a : s.args) if (a) a->accept(*this);
    }
    void visit(BreakStmt&) override {}
    void visit(SkipStmt&)  override {}
    void visit(PrintfStmt& s) override {
        /* printf is opaque to semantic analysis. Walk arguments only so
        that any identifier inside them is still resolved (catches typos). */
        for (auto& a : s.args) if (a) a->accept(*this);
    }
    void visit(GotoStmt& g) override {
        auto it = labels.find(g.label);
        if (it == labels.end()) {
            err(g.line, g.column, "goto target '" + g.label + "' not found");
        } else {
            g.resolved = it->second;
        }
    }
    void visit(LabeledStmt& l) override {
        if (l.stmt) l.stmt->accept(*this);
    }
    void visit(InlineCallStmt& s) override {
        auto* sym = cur->lookup(s.name);
        if (!sym) {
            err(s.line, s.column, "unknown inline '" + s.name + "'");
        } else if (sym->kind != SymKind::Inline) {
            err(s.line, s.column,
                "'" + s.name + "' is a " + sym_kind_name(sym->kind) + ", not an inline");
        } else {
            s.resolved = sym->node;
        }
        for (auto& a : s.args) if (a) a->accept(*this);
    }
    void visit(LocalVarDeclStmt& s) override {
        if (s.decl) {
            auto* dup = cur->try_insert({s.decl->name, SymKind::Variable, s.decl.get(), s.decl->line, s.decl->column});
            if (dup) err(s.decl->line, s.decl->column,
                         "local variable '" + s.decl->name + "' redeclared");
            s.decl->accept(*this);   /* resolve its type and init */
        }
    }
};

} // namespace

std::vector<ResolveError> resolve_names(Module& root) {
    Resolver r;
    r.visit(root);
    return std::move(r.errors);
}

} // namespace p2p