#include "AstNode.hxx"

    
Tb::AstNode::AstNode(AstNodeType nodeType)
    : astNodeType_(nodeType)
{
}

Tb::AstNodeType Tb::AstNode::getType() const
{
    return astNodeType_;
}

double Tb::AstNode::getValue() const
{
    // error reporting
    return 0.0;
}

Tb::TokenType Tb::AstNode::getOperator() const
{
    // error reporting
    return TokenType::UNDEFINED;
}

bool Tb::AstNode::isRoot() const
{
    bool root = parent_ == nullptr;
    return root;
}

bool Tb::AstNode::isLeaf() const
{
    bool childless = (right_ == nullptr) && (left_ == nullptr);
    return childless;
}

double Tb::AstNode::negate()
{
    double result = 0.0;
    return result;
}

void Tb::AstNode::print(std::ostream& astNodeOss) const
{
    TokenType tokenType = getOperator();
    if (tokenType != TokenType::UNDEFINED)
    {
        astNodeOss << "operation = " << TokenTypeRepr::tokenTypeString(tokenType);
    }
    else
    {
        astNodeOss << "number = " << getValue();
    }
}

std::ostream& Tb::operator<<(std::ostream& astNodeOss, const Tb::AstNode& astNode)
{
    astNode.print(astNodeOss);
    return astNodeOss;
}

Tb::AstNode::ShPtr Tb::AstNode::factory(double value, TokenType tokenType)
{
    ShPtr shPtr = nullptr;
    if (tokenType == TokenType::UNDEFINED)
    {
       shPtr = std::make_shared<NumberAstNode>(value);
    }
    else
    {
        shPtr = std::make_shared<OperatorAstNode>(tokenType);
    }

    return shPtr;
}

std::string Tb::AstNode::showAstNodeType(Tb::AstNodeType astNodeType)
{
    static std::array<std::string, 
                      (int)Tb::AstNodeType::last_one + 1> astNodeTypes = 
    {{ "no_type",
      "expression",
      "number",
      "operation",
      "last_one"
    }};
    return astNodeTypes[(int) astNodeType];
}


Tb::NumberAstNode::NumberAstNode(double value)
    : AstNode(AstNodeType::number),
      value_(value)
{

}
double Tb::NumberAstNode::getValue() const
{
    return value_;
} 
 
double Tb::NumberAstNode::negate()
{
    double result = getValue();
    result = -result;
    this->value_ = result;
    return result;
} 

void Tb::NumberAstNode::accept(AstNodeVisitor* visitor) const
{
    visitor->visitNumberAstNode(this);
}

Tb::OperatorAstNode::OperatorAstNode(TokenType tokenType)
    : AstNode(AstNodeType::operation),
      opType_(tokenType)
{

}

Tb::TokenType Tb::OperatorAstNode::getOperator() const
{
    return opType_;
}

double Tb::OperatorAstNode::negate()
{
    double result = 0.0;
    return result;
}

void Tb::OperatorAstNode::accept(AstNodeVisitor* visitor) const
{
    visitor->visitOperatorAstNode(this);
}    
