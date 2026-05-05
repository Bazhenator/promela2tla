#pragma once
#include <memory>
#include <string>
#include <vector>

namespace p2p {

// AST nodes
class Module;
class DefineDecl;
class ProctypeDecl;

// Visitor: emulates each AST step
// (print, semantic analyze, codegen)
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Module&)        = 0;
    virtual void visit(DefineDecl&)    = 0;
    virtual void visit(ProctypeDecl&)  = 0;
};

// Base class of each AST node
class Node {
public:
    virtual ~Node() = default;
    virtual void accept(Visitor& v) = 0;

    // Src position (for errMsgs)
    int line = 0;
    int column = 0;
};

using NodePtr = std::unique_ptr<Node>;

// AST root: Promela prog
class Module : public Node {
public:
    std::vector<NodePtr> declarations; // top-level
    void accept(Visitor& v) override { v.visit(*this); }
};

}