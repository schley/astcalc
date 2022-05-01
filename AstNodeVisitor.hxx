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
    // std::stack<double> rpnStack_;
private:
}; // class AstNodeVisitor

class AstNodeCalculateVisitor: public AstNodeVisitor
{
public:
    virtual void visitNumberAstNode(const NumberAstNode* element) const;
    virtual void visitOperatorAstNode(const OperatorAstNode* element) const;
private:
    // using RpnStack = std::stack<double>;
    // RpnStack rpnStack_;
    // static std::stack<double> rpnStack_;
    // static RpnStack& get_stack();
}; // class AstNodeCalculateVisitor

class AstNodePrintVisitor: public AstNodeVisitor
{
    void visitNumberAstNode(const NumberAstNode* element) const;
    void visitOperatorAstNode(const OperatorAstNode* element) const;

}; // NumberAstNodeVisitor

} // namespace Tb
#endif    // TB_AST_NODE_VISITOR_HXX
