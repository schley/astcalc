#if !defined TB_AST_NODE_HXX
#define      TB_AST_NODE_HXX

#include <memory>
#include <vector>
#include <stack>
#include <sstream>
#include "AstNodeVisitor.hxx"
#include "Token.hxx"

namespace Tb
{

enum class AstNodeType : int
{
    no_type,
    expression,
    number,
    operation,
    last_one
};

class AstNode
{
public:
    explicit AstNode(AstNodeType nodeType);
    AstNode() = delete;
    virtual ~AstNode() = default;
    virtual AstNodeType getType() const;
    virtual double getValue() const;
    virtual TokenType getOperator() const;
    using UPtr = std::unique_ptr<AstNode>;
    using ShPtr = std::shared_ptr<AstNode>;
    bool isRoot() const;
    bool isLeaf() const;
    virtual void accept(AstNodeVisitor* visitor) const = 0;
    virtual double negate();
    static ShPtr factory(double value = -99.0, TokenType tokenType = TokenType::UNDEFINED);
    static std::string showAstNodeType(AstNodeType astNodeType);
// protected:
    ShPtr right_;
    ShPtr left_;
    ShPtr parent_;

    void print(std::ostream& astNode) const;
private:
    AstNodeType astNodeType_;
};

using AstNodeStack = std::stack<AstNode::ShPtr>;

std::ostream& operator<<(std::ostream& astNodeOss, const AstNode& astNode);

class NumberAstNode : public AstNode
{
public:
    explicit NumberAstNode(double value);
    NumberAstNode() = delete;
    // virtual due to parent destructor 
    virtual ~NumberAstNode() = default;
    double getValue() const override;
    double negate() override;
    void accept(AstNodeVisitor* visitor) const override;
private:
    double value_;
}; // NumberAstNode 

class OperatorAstNode : public AstNode
{
public:
    explicit OperatorAstNode(TokenType tokenType);
    OperatorAstNode() = delete;
    virtual ~OperatorAstNode() = default;
    TokenType getOperator() const override;
    double negate() override;
    void accept(AstNodeVisitor* visitor) const override;
private:
    TokenType opType_;
}; // OperatorAstNode

} // TB_AST_NODE_HXX

#endif    // TB_AST_TREE_HXX
