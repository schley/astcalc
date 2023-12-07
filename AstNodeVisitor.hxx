#if !defined TB_AST_NODE_VISITOR_HXX
#define      TB_AST_NODE_VISITOR_HXX

#include <stack>
#include <vector>
#include <iostream>


namespace Tb
{
class NumberAstNode;
class OperatorAstNode;

class AstNodeVisitor
{
public:
    virtual void visitNumberAstNode(const NumberAstNode* element) const = 0;
    virtual void visitOperatorAstNode(const OperatorAstNode* element) const = 0;    
private:
}; // class AstNodeVisitor

class AstNodeCalculateVisitor: public AstNodeVisitor
{
public:
    virtual void visitNumberAstNode(const NumberAstNode* element) const;
    virtual void visitOperatorAstNode(const OperatorAstNode* element) const;
    virtual ~AstNodeCalculateVisitor() = default;
private:
}; // class AstNodeCalculateVisitor

class AstNodePrintVisitor: public AstNodeVisitor
{
public:
    void visitNumberAstNode(const NumberAstNode* element) const;
    void visitOperatorAstNode(const OperatorAstNode* element) const;
    virtual ~AstNodePrintVisitor() = default;
}; // NumberAstNodeVisitor

} // namespace Tb
#endif    // TB_AST_NODE_VISITOR_HXX
