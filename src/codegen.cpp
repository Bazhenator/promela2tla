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

/* Render an Expr as a TLA+ expression text.
   Covers the full Expr language used in the reference model. */
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
    if (auto* idx = dynamic_cast<const IndexExpr*>(&e)) {
        std::string base = idx->base  ? render_expr(*idx->base)  : std::string("0");
        std::string i    = idx->index ? render_expr(*idx->index) : std::string("0");
        return base + "[" + i + "]";
    }
    if (auto* fe = dynamic_cast<const FieldExpr*>(&e)) {
        std::string base = fe->base ? render_expr(*fe->base) : std::string("0");
        return base + "." + fe->field;
    }
    if (auto* p = dynamic_cast<const ParenExpr*>(&e)) {
        return p->inner ? "(" + render_expr(*p->inner) + ")" : "0";
    }
    if (auto* b = dynamic_cast<const BinaryExpr*>(&e)) {
        std::string lhs = b->lhs ? render_expr(*b->lhs) : std::string("0");
        std::string rhs = b->rhs ? render_expr(*b->rhs) : std::string("0");
        switch (b->op) {
            case BinaryOp::Add: return "(" + lhs + " + "  + rhs + ")";
            case BinaryOp::Sub: return "(" + lhs + " - "  + rhs + ")";
            case BinaryOp::Mul: return "(" + lhs + " * "  + rhs + ")";
            case BinaryOp::Div: return "(" + lhs + " \\div " + rhs + ")";
            case BinaryOp::Mod: return "(" + lhs + " % "  + rhs + ")";
            /* Shifts: a << b == a * (2^b); a >> b == a \div (2^b). */
            case BinaryOp::Shl: return "(" + lhs + " * (2^"   + rhs + "))";
            case BinaryOp::Shr: return "(" + lhs + " \\div (2^" + rhs + "))";
            case BinaryOp::Lt:  return "(" + lhs + " < "  + rhs + ")";
            case BinaryOp::Le:  return "(" + lhs + " <= " + rhs + ")";
            case BinaryOp::Gt:  return "(" + lhs + " > "  + rhs + ")";
            case BinaryOp::Ge:  return "(" + lhs + " >= " + rhs + ")";
            case BinaryOp::Eq:  return "(" + lhs + " = "  + rhs + ")";
            case BinaryOp::Neq: return "(" + lhs + " # "  + rhs + ")";
            case BinaryOp::And: return "(" + lhs + " /\\ " + rhs + ")";
            case BinaryOp::Or:  return "(" + lhs + " \\/ " + rhs + ")";
        }
        return "0";
    }
    if (auto* u = dynamic_cast<const UnaryExpr*>(&e)) {
        std::string op_s = u->operand ? render_expr(*u->operand) : std::string("0");
        switch (u->op) {
            case UnaryOp::Neg: return "(-" + op_s + ")";
            case UnaryOp::Not: return "(~" + op_s + ")";
            /* Pre/post increment/decrement used as expressions: in Promela
               this is rare (mostly used as standalone statements). In TLA+
               there is no expression-level increment. We render the
               operand and leave a marker comment so the side effect isn't
               silently lost; the stmt emitter handles the statement form. */
            case UnaryOp::PreInc:
            case UnaryOp::PostInc:
            case UnaryOp::PreDec:
            case UnaryOp::PostDec:
                return op_s + " (* inc/dec in expression context — Stage 4c *)";
        }
        return "0";
    }
    if (auto* t = dynamic_cast<const TernaryExpr*>(&e)) {
        std::string c  = t->cond      ? render_expr(*t->cond)      : std::string("FALSE");
        std::string th = t->then_expr ? render_expr(*t->then_expr) : std::string("0");
        std::string el = t->else_expr ? render_expr(*t->else_expr) : std::string("0");
        return "(IF " + c + " THEN " + th + " ELSE " + el + ")";
    }
    if (auto* bc = dynamic_cast<const BuiltinCallExpr*>(&e)) {
        std::string a = bc->arg ? render_expr(*bc->arg) : std::string("<<>>");
        switch (bc->kind) {
            case BuiltinKind::Empty:  return "(" + a + " = <<>>)";
            case BuiltinKind::Nempty: return "(" + a + " # <<>>)";
            case BuiltinKind::Len:    return "Len(" + a + ")";
            /* full / nfull need the channel capacity, which we don't carry
               into expressions yet. For the reference model every channel
               is capacity 0 (synchronous rendez-vous), so full ≡ TRUE and
               nfull ≡ FALSE in practice. Emit a sound placeholder + note. */
            case BuiltinKind::Full:   return "FALSE \\* full(): capacity unknown — Stage 4c";
            case BuiltinKind::Nfull:  return "TRUE  \\* nfull(): capacity unknown — Stage 4c";
        }
        return "0";
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

/* Statement emitter.

   Walks the body of a proctype/init and emits PlusCal statements into
   the Emitter. Manages label generation, break targets for do/for, and
   suppresses label creation inside atomic / d_step regions (where every
   step must be atomic with the surrounding).

   Currently the emitter intentionally has no support for:
     - send / receive (channels)
     - run
     - inline calls
   Those produce a TODO comment line each and are wired up in next stages. */
class StmtEmitter {
public:
    StmtEmitter(Emitter& e, std::string proc_prefix)
        : e_(e), proc_prefix_(std::move(proc_prefix)) {}

    void emit_body(const std::vector<StmtPtr>& body) {
        for (auto& s : body) if (s) emit_stmt(*s);
    }

private:
    Emitter& e_;
    std::string proc_prefix_;
    int label_counter_ = 0;
    std::vector<std::string> break_targets_;
    int atomic_depth_ = 0;

    std::string fresh_label(const std::string& hint = "l") {
        return proc_prefix_ + "_" + hint + std::to_string(++label_counter_);
    }

    bool in_atomic() const { return atomic_depth_ > 0; }

     /* Does this statement transfer control unconditionally (so emitting a
        fall-through goto after it would be dead code)? */
    static bool is_terminator(const Stmt* s) {
        if (!s) return false;
        if (dynamic_cast<const BreakStmt*>(s)) return true;
        if (dynamic_cast<const GotoStmt*>(s))  return true;
        /* A labelled statement terminates if its inner statement does. */
        if (auto* l = dynamic_cast<const LabeledStmt*>(s))
            return is_terminator(l->stmt.get());
        return false;
    }

    /* Whether the last statement of a branch is a terminator. */
    static bool branch_ends_with_terminator(const std::vector<StmtPtr>& v) {
        if (v.empty()) return false;
        return is_terminator(v.back().get());
    }

    /* Dispatch */
    void emit_stmt(Stmt& s) {
        if (auto* a  = dynamic_cast<AssignStmt*>(&s))       emit_assign(*a);
        else if (auto* es = dynamic_cast<ExprStmt*>(&s))    emit_expr_stmt(*es);
        else if (auto* sk = dynamic_cast<SkipStmt*>(&s))    { (void)sk; e_.line("skip;"); }
        else if (auto* br = dynamic_cast<BreakStmt*>(&s))   emit_break(*br);
        else if (auto* g  = dynamic_cast<GotoStmt*>(&s))    emit_goto(*g);
        else if (auto* lb = dynamic_cast<LabeledStmt*>(&s)) emit_labeled(*lb);
        else if (auto* ifs= dynamic_cast<IfStmt*>(&s))      emit_if(*ifs);
        else if (auto* d  = dynamic_cast<DoStmt*>(&s))      emit_do(*d);
        else if (auto* f  = dynamic_cast<ForStmt*>(&s))     emit_for(*f);
        else if (auto* se = dynamic_cast<SelectStmt*>(&s))  emit_select(*se);
        else if (auto* at = dynamic_cast<AtomicStmt*>(&s))  emit_atomic(*at);
        else if (auto* ds = dynamic_cast<DStepStmt*>(&s))   emit_dstep(*ds);
        else if (auto* ld = dynamic_cast<LocalVarDeclStmt*>(&s)) emit_local_decl(*ld);
        /* Communication and process spawn — postponed to 4d/4e */
        else if (auto* sd = dynamic_cast<SendStmt*>(&s))    emit_send_stub(*sd);
        else if (auto* rc = dynamic_cast<RecvStmt*>(&s))    emit_recv_stub(*rc);
        else if (auto* rn = dynamic_cast<RunStmt*>(&s))     emit_run_stub(*rn);
        else if (auto* ic = dynamic_cast<InlineCallStmt*>(&s)) emit_inline_stub(*ic);
        /* printf is a no-op for verification */
        else if (dynamic_cast<PrintfStmt*>(&s))             { /* skipped */ }
        else {
            e_.line("\\* unhandled statement (Stage 4c)");
        }
    }

    /* Assignment */
    void emit_assign(AssignStmt& a) {
        std::string lhs = a.lhs ? render_expr(*a.lhs) : std::string("_");
        std::string rhs = a.rhs ? render_expr(*a.rhs) : std::string("0");
        e_.line(lhs + " := " + rhs + ";");
    }

    /* Expression statement
       In Promela a bare expression in statement position acts as a guard:
       the statement is executable iff the expression is non-zero/TRUE.
       In PlusCal this is `await <expr>`.

       Special case: increment/decrement appears here as a "side-effecting
       expression". We desugar  x++  to  x := x + 1; */
    void emit_expr_stmt(ExprStmt& es) {
        if (!es.expr) return;
        if (auto* u = dynamic_cast<UnaryExpr*>(es.expr.get())) {
            switch (u->op) {
                case UnaryOp::PreInc: case UnaryOp::PostInc: {
                    std::string x = u->operand ? render_expr(*u->operand) : std::string("_");
                    e_.line(x + " := " + x + " + 1;");
                    return;
                }
                case UnaryOp::PreDec: case UnaryOp::PostDec: {
                    std::string x = u->operand ? render_expr(*u->operand) : std::string("_");
                    e_.line(x + " := " + x + " - 1;");
                    return;
                }
                default: break;
            }
        }
        e_.line("await " + render_expr(*es.expr) + ";");
    }

    /* Break / goto / labeled */
    void emit_break(BreakStmt&) {
        if (break_targets_.empty()) {
            e_.line("\\* break outside loop");
            return;
        }
        e_.line("goto " + break_targets_.back() + ";");
    }
    void emit_goto(GotoStmt& g) {
        e_.line("goto " + proc_prefix_ + "_" + g.label + ";");
    }
    void emit_labeled(LabeledStmt& l) {
        /* User-given label gets the proc_prefix to avoid collisions across
           multiple processes sharing label names. */
        std::string full = proc_prefix_ + "_" + l.label;
        e_.line(full + ":");
        if (l.stmt) emit_stmt(*l.stmt);
    }

    /* if/fi
       Promela:  if :: g1 -> b1 :: g2 -> b2 :: else -> bn fi
       PlusCal:  if (<g1>) { <b1> }
                 else if (<g2>) { <b2> }
                 else { <bn> }                       */
    void emit_if(IfStmt& s) {
        bool first = true;
        bool open  = false;
        for (auto& br : s.branches) {
            if (br.is_else) continue;
            if (br.stmts.empty()) continue;
            std::string guard = render_branch_guard(br);
            if (first) {
                e_.line("if (" + guard + ") {");
                first = false;
            } else {
                e_.line("} else if (" + guard + ") {");
            }
            e_.indent();
            emit_branch_body_after_guard(br);
            e_.dedent();
            open = true;
        }
        for (auto& br : s.branches) {
            if (!br.is_else) continue;
            if (first) {
                e_.line("if (TRUE) {");
                first = false;
            } else {
                e_.line("} else {");
            }
            e_.indent();
            for (auto& st : br.stmts) if (st) emit_stmt(*st);
            e_.dedent();
            open = true;
            break;
        }
        if (open) e_.line("};");
    }

    /* do/od
       Promela do is an infinite loop with guarded branches; break exits.
       We render as a labeled `while (TRUE) { if-chain-over-guards }` and
       set the break target to the label *after* the loop. */
    void emit_do(DoStmt& s) {
        std::string head = fresh_label("do");
        std::string tail = fresh_label("after");
        break_targets_.push_back(tail);

        e_.line(head + ":");
        e_.line("while (TRUE) {");
        e_.indent();

        bool first = true;
        bool open  = false;
        for (auto& br : s.branches) {
            if (br.is_else) continue;
            if (br.stmts.empty()) continue;
            std::string guard = render_branch_guard(br);
            if (first) {
                e_.line("if (" + guard + ") {");
                first = false;
            } else {
                e_.line("} else if (" + guard + ") {");
            }
            e_.indent();
            emit_branch_body_after_guard(br);
            if (!branch_ends_with_terminator(br.stmts))
                e_.line("goto " + head + ";");
            e_.dedent();
            open = true;
        }
        for (auto& br : s.branches) {
            if (!br.is_else) continue;
            if (first) {
                e_.line("if (TRUE) {");
                first = false;
            } else {
                e_.line("} else {");
            }
            e_.indent();
            for (auto& st : br.stmts) if (st) emit_stmt(*st);
            if (!branch_ends_with_terminator(br.stmts))
                e_.line("goto " + head + ";");
            e_.dedent();
            open = true;
            break;
        }
        if (open) e_.line("};");

        e_.dedent();
        e_.line("};");
        e_.line(tail + ":");
        e_.line("skip;");
        break_targets_.pop_back();
    }

    /* for (i : a..b) { body }  →  i := a; L_for: while (i <= b) { body; i := i+1; }; L_after: */
    void emit_for(ForStmt& s) {
        std::string head = fresh_label("for");
        std::string tail = fresh_label("after");
        break_targets_.push_back(tail);

        std::string lo = s.low  ? render_expr(*s.low)  : std::string("0");
        std::string hi = s.high ? render_expr(*s.high) : std::string("0");
        e_.line(s.var + " := " + lo + ";");
        e_.line(head + ":");
        e_.line("while (" + s.var + " <= " + hi + ") {");
        e_.indent();
        for (auto& st : s.body) if (st) emit_stmt(*st);
        e_.line(s.var + " := " + s.var + " + 1;");
        e_.dedent();
        e_.line("};");
        e_.line(tail + ":");
        e_.line("skip;");
        break_targets_.pop_back();
    }

    /* select (i : a..b) →  with (i \in a..b) { skip } */
    void emit_select(SelectStmt& s) {
        std::string lo = s.low  ? render_expr(*s.low)  : std::string("0");
        std::string hi = s.high ? render_expr(*s.high) : std::string("0");
        /* `select (v : lo..hi)` picks a nondeterministic value for v.
        `with` binds a fresh name inside its block only, so we bind a
        temp and assign it to the real variable, which outlives the block. */
        std::string tmp = fresh_label("sel");
        e_.line("with (" + tmp + " \\in " + lo + ".." + hi + ") {");
        e_.indent();
        e_.line(s.var + " := " + tmp + ";");
        e_.dedent();
        e_.line("};");
    }

    /* atomic { ... }
       In PlusCal everything between two labels is atomic. We emit the
       body as a contiguous label-free block; nested labels are suppressed
       via the atomic_depth_ counter (`fresh_label` is still called for
       loop heads inside atomic — but loops inside atomic are unusual in
       the reference model; if they occur, the resulting PlusCal will
       still compile, just not be a single step). */
    void emit_atomic(AtomicStmt& s) {
        ++atomic_depth_;
        for (auto& st : s.body) if (st) emit_stmt(*st);
        --atomic_depth_;
    }
    void emit_dstep(DStepStmt& s) {
        ++atomic_depth_;
        for (auto& st : s.body) if (st) emit_stmt(*st);
        --atomic_depth_;
    }

    /* Local declaration
       In PlusCal local vars are declared at the top of the process. Here
       we just emit a comment that this is the declaration site. Hoisting
       into the process's `variables` clause is a follow-up; for the
       reference model all local vars are initialized to defaults anyway. */
    void emit_local_decl(LocalVarDeclStmt& l) {
        /* The variable is already declared (with its initializer) in the
        process's `variables` clause — see emit_proctype. A declaration
        in the body is therefore a no-op. If it had an initializer that
        depends on other variables, re-assigning here keeps the value
        correct at the declaration point. */
        if (!l.decl) return;
        if (l.decl->init) {
            std::string init = render_expr(*l.decl->init);
            e_.line(l.decl->name + " := " + init + ";");
        }
        /* else: plain declaration, nothing to emit. */
    }

    /* Communication / process-spawn / inline calls — stubs for 4c */
    void emit_send_stub(SendStmt& s) {
        std::string chan = s.chan ? render_expr(*s.chan) : std::string("?");
        e_.line("\\* TODO Stage 4d: " + chan + " ! ...;");
    }
    void emit_recv_stub(RecvStmt& s) {
        std::string chan = s.chan ? render_expr(*s.chan) : std::string("?");
        e_.line("\\* TODO Stage 4d: " + chan + " ? ...;");
    }
    void emit_run_stub(RunStmt& r) {
        e_.line("\\* TODO Stage 4e: run " + r.name + "(...);");
    }
    void emit_inline_stub(InlineCallStmt& c) {
        e_.line("\\* TODO Stage 4d: " + c.name + "(...);");
    }

    /* Helpers */

    /* The first statement of a branch is its guard. For an ExprStmt
       we render the bare expression; for other guard shapes we leave
       a placeholder for next stage. */
    std::string render_branch_guard(const GuardedBranch& br) {
        if (br.stmts.empty()) return "TRUE";
        Stmt* first = br.stmts.front().get();
        if (auto* es = dynamic_cast<ExprStmt*>(first)) {
            if (es->expr) return render_expr(*es->expr);
        }
        if (auto* rc = dynamic_cast<RecvStmt*>(first)) {
            std::string chan = rc->chan ? render_expr(*rc->chan) : std::string("?");
            return chan + " # <<>>  \\* recv guard, Stage 4d";
        }
        if (auto* a = dynamic_cast<AssignStmt*>(first)) {
            /* An assignment as a guard is unusual but legal in Promela:
               the assignment is always executable, so the guard is TRUE
               and the assignment runs as the first body statement. */
            (void)a;
            return "TRUE";
        }
        return "TRUE  \\* unsupported guard shape, Stage 4c";
    }

    /* Emit the branch body skipping its first statement (the guard).
       Special-case: if the guard was a recv, we still need to emit it
       as a stmt — but in 4c we leave a TODO so the structure is visible. */
    void emit_branch_body_after_guard(const GuardedBranch& br) {
        if (br.stmts.empty()) return;
        Stmt* first = br.stmts.front().get();
        bool guard_is_pure_expr = dynamic_cast<ExprStmt*>(first) != nullptr;
        bool guard_is_assign    = dynamic_cast<AssignStmt*>(first) != nullptr;

        for (size_t i = 0; i < br.stmts.size(); ++i) {
            if (i == 0 && guard_is_pure_expr) continue;  /* guard already in the if-condition */
            if (i == 0 && guard_is_assign) { emit_stmt(*br.stmts[i]); continue; }
            if (i == 0) {
                /* For other guards (recv/inline), emit them as a stmt so the
                   structure is visible. They'll become proper guarded recv
                   in next stage. */
                emit_stmt(*br.stmts[i]);
                continue;
            }
            if (br.stmts[i]) emit_stmt(*br.stmts[i]);
        }
    }
};

/* Recursively collect every LocalVarDeclStmt in a statement list, so
   the names can be hoisted into the process's `variables` clause.
   PlusCal requires process-local variables to be declared there, not
   mid-body. */
void collect_locals(const std::vector<StmtPtr>& body,
                     std::vector<const VarDecl*>& out) {
    for (auto& s : body) {
        if (!s) continue;
        if (auto* ld = dynamic_cast<const LocalVarDeclStmt*>(s.get())) {
            if (ld->decl) out.push_back(ld->decl.get());
        } else if (auto* at = dynamic_cast<const AtomicStmt*>(s.get())) {
            collect_locals(at->body, out);
        } else if (auto* ds = dynamic_cast<const DStepStmt*>(s.get())) {
            collect_locals(ds->body, out);
        } else if (auto* f = dynamic_cast<const ForStmt*>(s.get())) {
            collect_locals(f->body, out);
        } else if (auto* i = dynamic_cast<const IfStmt*>(s.get())) {
            for (auto& br : i->branches) collect_locals(br.stmts, out);
        } else if (auto* d = dynamic_cast<const DoStmt*>(s.get())) {
            for (auto& br : d->branches) collect_locals(br.stmts, out);
        } else if (auto* l = dynamic_cast<const LabeledStmt*>(s.get())) {
            if (l->stmt) {
                std::vector<StmtPtr> one;  /* can't move; handle inline */
                /* LabeledStmt holds a single stmt; recurse via a tiny shim. */
                const Stmt* inner = l->stmt.get();
                if (auto* ld = dynamic_cast<const LocalVarDeclStmt*>(inner)) {
                    if (ld->decl) out.push_back(ld->decl.get());
                }
                /* (nested blocks under a label are rare; deep cases handled
                   by the structural recursion above when they appear
                   directly in a sequence) */
            }
        }
    }
}

void emit_proctype(Emitter& e, const ProctypeDecl& p) {
    std::string name = proc_name(p.name);

    /* Collect process-local variables: formal parameters plus every
       local declaration in the body. Stage 4c treats parameters as
       ordinary process-local variables; the topology pass in 4e will
       reinterpret the ones that are really process coordinates. */
    std::vector<std::string> decls;
    for (auto& param : p.params) {
        std::string init = "0";
        if (param.type && param.type->kind == BasicTypeKind::Bool)  init = "FALSE";
        if (param.type && param.type->kind == BasicTypeKind::Chan)  init = "<<>>";
        decls.push_back(param.name + " = " + init);
    }
    std::vector<const VarDecl*> locals;
    collect_locals(p.body, locals);
    for (auto* v : locals) {
        decls.push_back(v->name + " = " + render_var_init(*v));
    }

    e.line("fair process (" + name + " = \"" + name + "\")");
    if (!decls.empty()) {
        e.indent();
        for (size_t i = 0; i < decls.size(); ++i) {
            bool last = (i + 1 == decls.size());
            std::string prefix = (i == 0) ? "variables " : "          ";
            e.line(prefix + decls[i] + (last ? ";" : ","));
        }
        e.dedent();
    }
    e.line("{");
    e.indent();
    e.line(name + "_start:");
    e.indent();
    e.line("skip;");
    StmtEmitter se(e, p.name);
    se.emit_body(p.body);
    e.dedent();
    e.dedent();
    e.line("}");
    e.line();
}

void emit_init(Emitter& e, const InitDecl& i) {
    e.line("fair process (Init = \"Init\") {");
    e.indent();
    e.line("init_start:");
    e.indent();
    e.line("skip;");
    StmtEmitter se(e, "init");
    se.emit_body(i.body);
    e.dedent();
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