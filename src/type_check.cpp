#include "type_check.h"
#include "ast.h"
#include <unordered_map>

namespace p2p {

namespace {

/* Type predicates / helpers. */
bool is_integer(const Type& t) {
    switch (t.kind) {
        case BasicTypeKind::Byte:
        case BasicTypeKind::Int:
        case BasicTypeKind::Bit:
        case BasicTypeKind::Short:
        case BasicTypeKind::Unsigned:
            return true;
        default:
            return false;
    }
}

bool is_bool(const Type& t)  { return t.kind == BasicTypeKind::Bool; }
bool is_chan(const Type& t)  { return t.kind == BasicTypeKind::Chan; }
bool is_mtype(const Type& t) { return t.kind == BasicTypeKind::Mtype; }
bool is_named(const Type& t) { return t.kind == BasicTypeKind::Named; }

/* Two types are compatible-for-assignment if both numeric, both bool,
   both mtype, or both same named-type. */
bool assignment_compatible(const Type& lhs, const Type& rhs) {
    /* If either side's type couldn't be inferred, don't flag a mismatch —
       a real check will be possible once field/element types are tracked. */
    if (lhs.unknown || rhs.unknown) return true;

    if (is_integer(lhs) && is_integer(rhs)) return true;
    if (is_bool(lhs)    && is_bool(rhs))    return true;
    if (is_mtype(lhs)   && is_mtype(rhs))   return true;
    if (is_chan(lhs)    && is_chan(rhs))    return true;
    if (is_named(lhs)   && is_named(rhs)) {
        return lhs.named == rhs.named;
    }
    /* Numeric → bool implicit not allowed; explicit cases caught later. */
    return false;
}

std::string type_label(const Type& t) {
    if (t.unknown) return "<unknown>";
    switch (t.kind) {
        case BasicTypeKind::Byte:     return "byte";
        case BasicTypeKind::Int:      return "int";
        case BasicTypeKind::Bool:     return "bool";
        case BasicTypeKind::Bit:      return "bit";
        case BasicTypeKind::Short:    return "short";
        case BasicTypeKind::Unsigned: return "unsigned";
        case BasicTypeKind::Mtype:    return "mtype";
        case BasicTypeKind::Chan:     return "chan";
        case BasicTypeKind::Named:    return t.named;
    }
    return "?";
}

struct TypeChecker {
    std::vector<TypeError> errors;

    void err(int line, int col, std::string m) {
        errors.push_back({std::move(m), line, col});
    }

    /* Walk a Module. */
    void check_module(Module& m) {
        for (auto& d : m.declarations) check_decl(*d);
    }

    void check_decl(Node& d) {
        if (auto* v = dynamic_cast<VarDecl*>(&d)) {
            check_var_decl(*v);
        } else if (auto* p = dynamic_cast<ProctypeDecl*>(&d)) {
            for (auto& s : p->body) check_stmt(*s);
        } else if (auto* i = dynamic_cast<InitDecl*>(&d)) {
            for (auto& s : i->body) check_stmt(*s);
        }
        /* InlineDecl bodies are not checked here, same as in the resolver:
           Promela inlines are textual substitution and only meaningful at
           the call site, where types are known. */
        /* TypedefDecl, MtypeDecl, LtlDecl: nothing to type-check yet. */
    }

    void check_var_decl(VarDecl& v) {
        if (!v.init) return;
        Type init_ty = infer(*v.init);
        if (init_ty.kind == BasicTypeKind::Int && !v.type) {
            return;
        }
        if (v.type && !assignment_compatible(*v.type, init_ty)) {
            err(v.line, v.column,
                "cannot initialize '" + v.name + "' of type "
                + type_label(*v.type) + " with " + type_label(init_ty));
        }
    }

    /* Statement checking */
    void check_stmt(Stmt& s) {
        if (auto* es = dynamic_cast<ExprStmt*>(&s)) {
            if (es->expr) infer(*es->expr);
        } else if (auto* a = dynamic_cast<AssignStmt*>(&s)) {
            check_assign(*a);
        } else if (auto* ifs = dynamic_cast<IfStmt*>(&s)) {
            for (auto& br : ifs->branches)
                for (auto& st : br.stmts) check_stmt(*st);
        } else if (auto* d = dynamic_cast<DoStmt*>(&s)) {
            for (auto& br : d->branches)
                for (auto& st : br.stmts) check_stmt(*st);
        } else if (auto* at = dynamic_cast<AtomicStmt*>(&s)) {
            for (auto& st : at->body) check_stmt(*st);
        } else if (auto* ds = dynamic_cast<DStepStmt*>(&s)) {
            for (auto& st : ds->body) check_stmt(*st);
        } else if (auto* f = dynamic_cast<ForStmt*>(&s)) {
            if (f->low)  infer(*f->low);
            if (f->high) infer(*f->high);
            for (auto& st : f->body) check_stmt(*st);
        } else if (auto* sel = dynamic_cast<SelectStmt*>(&s)) {
            if (sel->low)  infer(*sel->low);
            if (sel->high) infer(*sel->high);
        } else if (auto* send = dynamic_cast<SendStmt*>(&s)) {
            check_send(*send);
        } else if (auto* recv = dynamic_cast<RecvStmt*>(&s)) {
            check_recv(*recv);
        } else if (auto* run = dynamic_cast<RunStmt*>(&s)) {
            check_run(*run);
        } else if (auto* lab = dynamic_cast<LabeledStmt*>(&s)) {
            if (lab->stmt) check_stmt(*lab->stmt);
        } else if (auto* call = dynamic_cast<InlineCallStmt*>(&s)) {
            check_inline_call(*call);
        } else if (auto* ld = dynamic_cast<LocalVarDeclStmt*>(&s)) {
            if (ld->decl) check_var_decl(*ld->decl);
        }
        /* BreakStmt, SkipStmt, GotoStmt: nothing to check. */
    }

    void check_assign(AssignStmt& a) {
        if (!a.lhs || !a.rhs) return;
        Type lhs_ty = infer(*a.lhs);
        Type rhs_ty = infer(*a.rhs);
        if (!assignment_compatible(lhs_ty, rhs_ty)) {
            err(a.line, a.column,
                "cannot assign " + type_label(rhs_ty) + " to "
                + type_label(lhs_ty));
        }
    }

    void check_send(SendStmt& s) {
        Type chan_ty = s.chan ? infer(*s.chan) : Type{};
        if (!chan_ty.unknown && !is_chan(chan_ty)) {
            err(s.line, s.column,
                "'!' requires a channel on the left, got " + type_label(chan_ty));
            return;
        }
        if (chan_ty.unknown) return;
        check_chan_args(s.line, s.column, chan_ty, s.args, "send");
    }

    void check_recv(RecvStmt& s) {
        Type chan_ty = s.chan ? infer(*s.chan) : Type{};
        if (!chan_ty.unknown && !is_chan(chan_ty)) {
            err(s.line, s.column,
                "'?' requires a channel on the left, got " + type_label(chan_ty));
            return;
        }
        if (chan_ty.unknown) return;
        check_chan_args(s.line, s.column, chan_ty, s.args, "receive");
    }

    void check_chan_args(int line, int col, const Type& chan_ty,
                         std::vector<ExprPtr>& args, const char* op) {
        if (chan_ty.chan_msg_types.empty()) return;  /* untyped chan ref */
        if (args.size() != chan_ty.chan_msg_types.size()) {
            err(line, col,
                std::string(op) + " arity mismatch: channel expects "
                + std::to_string(chan_ty.chan_msg_types.size())
                + " field(s), got " + std::to_string(args.size()));
        }
        size_t n = std::min(args.size(), chan_ty.chan_msg_types.size());
        for (size_t i = 0; i < n; ++i) {
            if (!args[i]) continue;
            Type arg_ty = infer(*args[i]);
            const Type& expected = *chan_ty.chan_msg_types[i];
            if (!assignment_compatible(expected, arg_ty)) {
                err(args[i]->line, args[i]->column,
                    std::string(op) + " field " + std::to_string(i + 1)
                    + ": expected " + type_label(expected)
                    + ", got " + type_label(arg_ty));
            }
        }
    }

    void check_run(RunStmt& r) {
        for (auto& a : r.args) if (a) infer(*a);
        if (!r.resolved) return;
        auto* p = dynamic_cast<ProctypeDecl*>(r.resolved);
        if (!p) return;
        if (r.args.size() != p->params.size()) {
            err(r.line, r.column,
                "run " + r.name + " takes " + std::to_string(p->params.size())
                + " argument(s), got " + std::to_string(r.args.size()));
        }
    }

    void check_inline_call(InlineCallStmt& c) {
        for (auto& a : c.args) if (a) infer(*a);
        if (!c.resolved) return;
        auto* inl = dynamic_cast<InlineDecl*>(c.resolved);
        if (!inl) return;
        if (c.args.size() != inl->params.size()) {
            err(c.line, c.column,
                "inline " + c.name + " takes " + std::to_string(inl->params.size())
                + " argument(s), got " + std::to_string(c.args.size()));
        }
    }

    /* Type inference */
    Type infer(Expr& e) {
        if (dynamic_cast<IntLiteral*>(&e)) {
            Type t; t.kind = BasicTypeKind::Int; return t;
        }
        if (dynamic_cast<BoolLiteral*>(&e)) {
            Type t; t.kind = BasicTypeKind::Bool; return t;
        }
        if (auto* id = dynamic_cast<IdentExpr*>(&e)) {
            return type_of_ident(*id);
        }
        if (auto* idx = dynamic_cast<IndexExpr*>(&e)) {
            if (idx->index) infer(*idx->index);
            if (idx->base) {
                Type base_ty = infer(*idx->base);
                /* Element type of an array isn't tracked separately yet; fall back
                to the base type, propagating 'unknown' if present. */
                return base_ty;
            }
            Type t; t.unknown = true; return t;
        }
        if (auto* fe = dynamic_cast<FieldExpr*>(&e)) {
            if (fe->base) infer(*fe->base);
            /* Field type resolution deferred to return an unknown type
            so checks stay lenient instead of guessing 'int'. */
            Type t; t.unknown = true; return t;
        }
        if (auto* u = dynamic_cast<UnaryExpr*>(&e)) {
            Type op_ty = u->operand ? infer(*u->operand) : Type{};
            switch (u->op) {
                case UnaryOp::Neg:
                case UnaryOp::PreInc: case UnaryOp::PostInc:
                case UnaryOp::PreDec: case UnaryOp::PostDec: {
                    if (!is_integer(op_ty)) {
                        err(u->line, u->column,
                            "unary arithmetic op requires integer, got "
                            + type_label(op_ty));
                    }
                    Type t; t.kind = BasicTypeKind::Int; return t;
                }
                case UnaryOp::Not: {
                    if (!is_bool(op_ty) && !is_integer(op_ty)) {
                        err(u->line, u->column,
                            "'!' requires bool/int, got " + type_label(op_ty));
                    }
                    Type t; t.kind = BasicTypeKind::Bool; return t;
                }
            }
        }
        if (auto* b = dynamic_cast<BinaryExpr*>(&e)) {
            Type l = b->lhs ? infer(*b->lhs) : Type{};
            Type r = b->rhs ? infer(*b->rhs) : Type{};
            switch (b->op) {
                case BinaryOp::And: case BinaryOp::Or: {
                    Type t; t.kind = BasicTypeKind::Bool; return t;
                }
                case BinaryOp::Eq: case BinaryOp::Neq:
                case BinaryOp::Lt: case BinaryOp::Le:
                case BinaryOp::Gt: case BinaryOp::Ge: {
                    Type t; t.kind = BasicTypeKind::Bool; return t;
                }
                default: {
                    if (!is_integer(l) || !is_integer(r)) {
                        /* mild: only error if we're sure both are non-integer */
                    }
                    Type t; t.kind = BasicTypeKind::Int; return t;
                }
            }
        }
        if (auto* t3 = dynamic_cast<TernaryExpr*>(&e)) {
            if (t3->cond)      infer(*t3->cond);
            Type then_ty = t3->then_expr ? infer(*t3->then_expr) : Type{};
            if (t3->else_expr) infer(*t3->else_expr);
            return then_ty;
        }
        if (auto* bc = dynamic_cast<BuiltinCallExpr*>(&e)) {
            Type arg_ty = bc->arg ? infer(*bc->arg) : Type{};
            if (!arg_ty.unknown && !is_chan(arg_ty)) {
                const char* name = "?";
                switch (bc->kind) {
                    case BuiltinKind::Nempty: name = "nempty"; break;
                    case BuiltinKind::Empty:  name = "empty";  break;
                    case BuiltinKind::Len:    name = "len";    break;
                    case BuiltinKind::Full:   name = "full";   break;
                    case BuiltinKind::Nfull:  name = "nfull";  break;
                }
                err(bc->line, bc->column,
                    std::string(name) + "() requires a channel, got "
                    + type_label(arg_ty));
            }
            Type t;
            t.kind = (bc->kind == BuiltinKind::Len)
                     ? BasicTypeKind::Int : BasicTypeKind::Bool;
            return t;
        }
        if (auto* p = dynamic_cast<ParenExpr*>(&e)) {
            if (p->inner) return infer(*p->inner);
            return Type{};
        }
        return Type{};
    }

    Type type_of_ident(IdentExpr& id) {
        if (id.resolved_param) {
            if (id.resolved_param->type) return *id.resolved_param->type;
            Type t; t.kind = BasicTypeKind::Int; return t;
        }
        if (!id.resolved) {
            return Type{};
        }
        if (auto* v = dynamic_cast<VarDecl*>(id.resolved)) {
            if (v->type) {
                return *v->type;
            }
            return Type{};
        }
        if (dynamic_cast<MtypeDecl*>(id.resolved)) {
            Type t; t.kind = BasicTypeKind::Mtype; return t;
        }
        return Type{};
    }
};

} // namespace

std::vector<TypeError> type_check(Module& root) {
    TypeChecker tc;
    tc.check_module(root);
    return std::move(tc.errors);
}

} // namespace p2p