#include <iostream>

#include "AstNodeVisitor.hxx"
#include "AstNode.hxx"
#include "Token.hxx"
#include "CodeGenStack.hxx"


void Tb::AstNodePrintVisitor::visitNumberAstNode(const Tb::NumberAstNode* element) const 
{
    static const std::string LOCATION { "AstNodePrintVisitor::visitNumberAstNode" };
    std::cout << LOCATION << ": NumberAstNode value = " << element->getValue() 
              << "; AstNodeType = " << AstNode::showAstNodeType(element->getType() )
              << "\n";
}

void Tb::AstNodePrintVisitor::visitOperatorAstNode(const Tb::OperatorAstNode* element) const
{
    static const std::string LOCATION { "AstNodePrintVisitor::visitOperatorAstNode"};
    std::cout << LOCATION << ": OperatorAstNode operator = " 
              << TokenTypeRepr::tokenTypeString(element->getOperator() )  
              << "; AstNodeType = " << AstNode::showAstNodeType(element->getType() )
              << "\n";
}

void Tb::AstNodeCalculateVisitor::visitNumberAstNode(const Tb::NumberAstNode* element) const
{
    static const std::string LOCATION {"AstNodeCalculateVisitor::visitNumberAstNode"};
    double t1 = element->getValue();
    CodeGenStack cgstack;
    // double t2 = 
    cgstack.stackPush(t1);
    // std::cout << LOCATION << ": result = " << t2 << '\n';
    // return t2;
    // RpnStack rpnStack = get_stack(); // push(t1);
}

void Tb::AstNodeCalculateVisitor::visitOperatorAstNode(const Tb::OperatorAstNode* element) const
{
    static const std::string LOCATION {"AstNodeCalculateVisitor::visitOperatorAstNode"};
    TokenType tokenType = element->getOperator();
    CodeGenStack cgstack;
    // double t3 = 
    cgstack.binOperator(tokenType);
    // std::cout << LOCATION << ": result = " << t3 << '\n';
    // return t3;
}

// Tb::AstNodeCalculateVisitor::RpnStack& Tb::AstNodeCalculateVisitor::get_stack()
// {
    // RpnStack& rpnStack = RpnStack;
    // return rpnStack;
// }
