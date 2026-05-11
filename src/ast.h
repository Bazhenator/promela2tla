#pragma once
#include <memory>
#include <string>
#include <vector>

namespace p2p {

class Module;
class DefineDecl;
class ProctypeDecl;

/* Expressions */
class IntLiteral;
class BoolLiteral;
class IdentExpr;
class IndexExpr;
class FieldExpr;
class UnaryExpr;
class BinaryExpr;
class TernaryExpr;
class BuiltinCallExpr;
class ParenExpr;

/* Visitor — extended whenever a new AST node is introduced.
   Adding a new node forces every Visitor to handle it (compile error
   otherwise), which keeps all passes (printing, semantic analysis,
   code generation) in sync. */
class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit(Module&)       = 0;
    virtual void visit(DefineDecl&)   = 0;
    virtual void visit(ProctypeDecl&) = 0;

    /* Expressions */
    virtual void visit(IntLiteral&)      = 0;
    virtual void visit(BoolLiteral&)     = 0;
    virtual void visit(IdentExpr&)       = 0;
    virtual void visit(IndexExpr&)       = 0;
    virtual void visit(FieldExpr&)       = 0;
    virtual void visit(UnaryExpr&)       = 0;
    virtual void visit(BinaryExpr&)      = 0;
    virtual void visit(TernaryExpr&)     = 0;
    virtual void visit(BuiltinCallExpr&) = 0;
    virtual void visit(ParenExpr&)       = 0;
};

/* Base class for all AST nodes. */
class Node {
public:
    virtual ~Node() = default;
    virtual void accept(Visitor& v) = 0;

    /* Source position for diagnostics. */
    int line = 0;
    int column = 0;
};

using NodePtr = std::unique_ptr<Node>;

/* Expression base class. Split from Node so passes that only deal with
   expressions can take a more specific dispatch later. */
class Expr : public Node { };
using ExprPtr = std::unique_ptr<Expr>;

/* Concrete expression nodes */

class IntLiteral : public Expr {
public:
    long value = 0;
    IntLiteral() = default;
    explicit IntLiteral(long v) : value(v) {}
    void accept(Visitor& v) override { v.visit(*this); }
};

class BoolLiteral : public Expr {
public:
    bool value = false;
    explicit BoolLiteral(bool v) : value(v) {}
    void accept(Visitor& v) override { v.visit(*this); }
};

class IdentExpr : public Expr {
public:
    std::string name;
    explicit IdentExpr(std::string n) : name(std::move(n)) {}
    void accept(Visitor& v) override { v.visit(*this); }
};

/* arr[index] */
class IndexExpr : public Expr {
public:
    ExprPtr base;
    ExprPtr index;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* obj.field */
class FieldExpr : public Expr {
public:
    ExprPtr base;
    std::string field;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* Unary operators: -x  !x  ++x  x++  --x  x-- */
enum class UnaryOp {
    Neg,        /* -x */
    Not,        /* !x */
    PreInc,     /* ++x */
    PostInc,    /* x++ */
    PreDec,     /* --x */
    PostDec     /* x-- */
};

class UnaryExpr : public Expr {
public:
    UnaryOp op;
    ExprPtr operand;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* Binary operators. Names mirror Promela source operators. */
enum class BinaryOp {
    Add, Sub, Mul, Div, Mod,
    Shl, Shr,
    Lt, Le, Gt, Ge, Eq, Neq,
    And, Or
};

class BinaryExpr : public Expr {
public:
    BinaryOp op;
    ExprPtr lhs;
    ExprPtr rhs;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* (cond -> then_expr : else_expr)  — Promela conditional expression. */
class TernaryExpr : public Expr {
public:
    ExprPtr cond;
    ExprPtr then_expr;
    ExprPtr else_expr;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* Built-in calls: nempty(c), empty(c), len(c), full(c), nfull(c). */
enum class BuiltinKind {
    Nempty, Empty, Len, Full, Nfull
};

class BuiltinCallExpr : public Expr {
public:
    BuiltinKind kind;
    ExprPtr arg;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* (expr) — explicit parentheses, kept so the printer can round-trip. */
class ParenExpr : public Expr {
public:
    ExprPtr inner;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* AST root */
class Module : public Node {
public:
    std::vector<NodePtr> declarations;
    void accept(Visitor& v) override { v.visit(*this); }
};

/* Debug helper: print an AST as S-expressions. */
void print_ast(Node& root, FILE* out);

} // namespace p2p