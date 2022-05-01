#if !defined TB_CODE_GEN_STACK_HXX_
#define      TB_CODE_GEN_STACK_HXX_

#include <stack>

#include "TokenType.hxx"
// #include "AstTree.hxx"

namespace Tb
{
class CodeGenStack
{
public:
    // explicit CodeGenStack(AstNode::ShPtr treeRoot);
    CodeGenStack() = default;
    ~CodeGenStack() = default;
    void generate();
    double stackPush(double);
    double stackPop();
    double binOperator(TokenType tokenType);
private:
    using RpnStack = std::stack<double>;
    RpnStack& get_stack();
    // AstTree astTree_;
}; // class CodeGenStack
} // namespace Tb

#endif    // TB_CODE_GEN_STACK_HXX_