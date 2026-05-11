#include "ast.h"
#include <cstdio>
#include <sstream>

namespace p2p {

namespace {

const char* unary_op_name(UnaryOp op) {
    switch (op) {
        case UnaryOp::Neg:     return "-";
        case UnaryOp::Not:     return "!";
        case UnaryOp::PreInc:  return "++pre";
        case UnaryOp::PostInc: return "++post";
        case UnaryOp::PreDec:  return "--pre";
        case UnaryOp::PostDec: return "--post";
    }
    return "?";
}

const char* binary_op_name(BinaryOp op) {
    switch (op) {
        case BinaryOp::Add: return "+";
        case BinaryOp::Sub: return "-";
        case BinaryOp::Mul: return "*";
        case BinaryOp::Div: return "/";
        case BinaryOp::Mod: return "%";
        case BinaryOp::Shl: return "<<";
        case BinaryOp::Shr: return ">>";
        case BinaryOp::Lt:  return "<";
        case BinaryOp::Le:  return "<=";
        case BinaryOp::Gt:  return ">";
        case BinaryOp::Ge:  return ">=";
        case BinaryOp::Eq:  return "==";
        case BinaryOp::Neq: return "!=";
        case BinaryOp::And: return "&&";
        case BinaryOp::Or:  return "||";
    }
    return "?";
}

const char* builtin_name(BuiltinKind k) {
    switch (k) {
        case BuiltinKind::Nempty: return "nempty";
        case BuiltinKind::Empty:  return "empty";
        case BuiltinKind::Len:    return "len";
        case BuiltinKind::Full:   return "full";
        case BuiltinKind::Nfull:  return "nfull";
    }
    return "?";
}

const char* ltl_op_name(LtlOp op) {
    switch (op) {
        case LtlOp::Atom:       return "atom";
        case LtlOp::Always:     return "[]";
        case LtlOp::Eventually: return "<>";
        case LtlOp::Not:        return "!";
        case LtlOp::And:        return "&&";
        case LtlOp::Or:         return "||";
        case LtlOp::Implies:    return "->";
        case LtlOp::Until:      return "U";
    }
    return "?";
}

} // namespace

std::string type_to_string(const Type& t) {
    std::ostringstream os;
    switch (t.kind) {
        case BasicTypeKind::Byte:     os << "byte";     break;
        case BasicTypeKind::Int:      os << "int";      break;
        case BasicTypeKind::Bool:     os << "bool";     break;
        case BasicTypeKind::Bit:      os << "bit";      break;
        case BasicTypeKind::Short:    os << "short";    break;
        case BasicTypeKind::Unsigned: os << "unsigned"; break;
        case BasicTypeKind::Named:    os << t.named;    break;
        case BasicTypeKind::Mtype:
            os << "mtype";
            if (!t.mtype_set.empty()) os << ":" << t.mtype_set;
            break;
        case BasicTypeKind::Chan:
            os << "chan";
            if (t.chan_capacity >= 0) os << "[" << t.chan_capacity << "]";
            if (!t.chan_msg_types.empty()) {
                os << "{";
                for (size_t i = 0; i < t.chan_msg_types.size(); ++i) {
                    if (i) os << ",";
                    os << type_to_string(*t.chan_msg_types[i]);
                }
                os << "}";
            }
            break;
    }
    return os.str();
}

namespace {
/* The printer is itself a Visitor: every node type has its own visit(). */
class AstPrinter : public Visitor {
public:
    explicit AstPrinter(FILE* out) : out_(out) {}

    void print(Node& n) { n.accept(*this); fputc('\n', out_); }

    void visit(Module& m) override {
        indent(); fputs("(module", out_);
        if (m.declarations.empty()) {
            fputs(")", out_);
            return;
        }
        fputc('\n', out_);
        ++depth_;
        for (auto& d : m.declarations) {
            indent();
            if (d) d->accept(*this); else fputs("(null)", out_);
            fputc('\n', out_);
        }
        --depth_;
        indent(); fputs(")", out_);
    }

    /* Stubs for nodes added in later sub-stages. */
    void visit(DefineDecl&)   override { fputs("(define-decl)", out_); }
    void visit(ProctypeDecl&) override { fputs("(proctype-decl)", out_); }

    void visit(IntLiteral& e) override  { fprintf(out_, "(int %ld)", e.value); }
    void visit(BoolLiteral& e) override { fprintf(out_, "(bool %s)", e.value ? "true" : "false"); }
    void visit(IdentExpr& e) override   { fprintf(out_, "(id %s)", e.name.c_str()); }

    void visit(IndexExpr& e) override {
        fputs("(index ", out_);
        if (e.base)  e.base->accept(*this);  else fputs("?", out_);
        fputc(' ', out_);
        if (e.index) e.index->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(FieldExpr& e) override {
        fputs("(field ", out_);
        if (e.base) e.base->accept(*this); else fputs("?", out_);
        fprintf(out_, " %s)", e.field.c_str());
    }

    void visit(UnaryExpr& e) override {
        fprintf(out_, "(%s ", unary_op_name(e.op));
        if (e.operand) e.operand->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(BinaryExpr& e) override {
        fprintf(out_, "(%s ", binary_op_name(e.op));
        if (e.lhs) e.lhs->accept(*this); else fputs("?", out_);
        fputc(' ', out_);
        if (e.rhs) e.rhs->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(TernaryExpr& e) override {
        fputs("(?: ", out_);
        if (e.cond)      e.cond->accept(*this);      else fputs("?", out_);
        fputc(' ', out_);
        if (e.then_expr) e.then_expr->accept(*this); else fputs("?", out_);
        fputc(' ', out_);
        if (e.else_expr) e.else_expr->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(BuiltinCallExpr& e) override {
        fprintf(out_, "(%s ", builtin_name(e.kind));
        if (e.arg) e.arg->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(ParenExpr& e) override {
        fputs("(paren ", out_);
        if (e.inner) e.inner->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    /* Declarations */
    void visit(VarDecl& d) override {
        fprintf(out_, "(var %s :type %s",
                d.name.c_str(),
                d.type ? type_to_string(*d.type).c_str() : "?");
        if (d.array_size) {
            fputs(" :size ", out_);
            d.array_size->accept(*this);
        }
        if (d.init) {
            fputs(" :init ", out_);
            d.init->accept(*this);
        }
        fputc(')', out_);
    }

    void visit(TypedefDecl& d) override {
        fprintf(out_, "(typedef %s", d.name.c_str());
        if (d.fields.empty()) { fputc(')', out_); return; }
        fputc('\n', out_);
        ++depth_;
        for (auto& f : d.fields) {
            indent();
            f->accept(*this);
            fputc('\n', out_);
        }
        --depth_;
        indent(); fputs(")", out_);
    }

    void visit(MtypeDecl& d) override {
        fputs("(mtype ", out_);
        if (!d.set_name.empty()) fprintf(out_, ":%s ", d.set_name.c_str());
        fputc('{', out_);
        for (size_t i = 0; i < d.names.size(); ++i) {
            if (i) fputs(", ", out_);
            fputs(d.names[i].c_str(), out_);
        }
        fputs("})", out_);
    }

    void visit(LtlDecl& d) override {
        fprintf(out_, "(ltl %s ", d.name.c_str());
        if (d.formula) d.formula->accept(*this); else fputs("?", out_);
        fputc(')', out_);
    }

    void visit(LtlFormula& f) override {
        fprintf(out_, "(%s", ltl_op_name(f.op));
        if (f.op == LtlOp::Atom) {
            fputc(' ', out_);
            if (f.atom) f.atom->accept(*this); else fputs("?", out_);
        } else {
            if (f.lhs) { fputc(' ', out_); f.lhs->accept(*this); }
            if (f.rhs) { fputc(' ', out_); f.rhs->accept(*this); }
        }
        fputc(')', out_);
    }

private:
    void indent() { for (int i = 0; i < depth_; ++i) fputs("  ", out_); }
    FILE* out_;
    int depth_ = 0;
};

} // anonymous namespace

void print_ast(Node& root, FILE* out) {
    AstPrinter p(out);
    p.print(root);
}

} // namespace p2p