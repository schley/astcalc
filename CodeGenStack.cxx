#include "CodeGenStack.hxx"

// Tb::CodeGenStack::CodeGenStack(AstNode::ShPtr astroot)
// {
//     astTree_.setRoot(astroot);
// }

double Tb::CodeGenStack::stackPush(double t1)
{
    RpnStack& stack = get_stack();
    stack.push(t1);
    double t2 = stack.top();
    return t2;
}

double Tb::CodeGenStack::stackPop()
{
    RpnStack& stack = get_stack();
    double result = stack.top();
    stack.pop();
    return result;
}

double Tb::CodeGenStack::binOperator(Tb::TokenType tokenType)
{
    RpnStack& stack = get_stack();
    double rhs = stack.top();
    stack.pop();
    double lhs = stack.top();
    stack.pop();
    double result = 0.0;
    switch (tokenType)
    {
    case Tb::TokenType::OP_DIVIDE:
        result = lhs / rhs;
        break;
    case Tb::TokenType::OP_MINUS:
        result = lhs - rhs;
        break;
    case Tb::TokenType::OP_MULT:
        result = lhs * rhs;
        break;
    case Tb::TokenType::OP_PLUS:
        result = lhs + rhs;
        break;
    default:
        break;
    };
    stack.push(result);

    return result;
}

Tb::CodeGenStack::RpnStack& Tb::CodeGenStack::get_stack()
{
    static RpnStack rpnStack;
    return rpnStack;
}