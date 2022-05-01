#include <sstream>

#include "Logger.hxx"
#include "Parser.hxx"
#include "AstNode.hxx"
#include "AstTree.hxx"


Tb::Parser::Parser(Tokens& tokens) 
    : tokens_(tokens),
      tokenIndex_(0)
{
    static const std::string LOCATION {"Parser ctor"};
    std::ostringstream logOss;

    numberTokens_ = tokens_.size();
    
    int tokenCount = 0;
    if (Tb::Logger::get().isDebugEnabled() )
    {
        for (auto& tokenIter : tokens_)
        {
            logOss << LOCATION << ": " 
                   << tokenCount++ << " : " << *tokenIter;
            Tb::Logger::get().debug(logOss);
        }
    }
}

Tb::Parser::~Parser()
{
    tokens_.clear();
}

double Tb::Parser::start()
{
    double result = 0.0;
    static const std::string LOCATION {"Parser::start"};
    AstNode::ShPtr astptr = nullptr;
    
    // first time through, the treeRoot_ == nullptr
    //
    result = expression(astptr);

    AstTree astTree(astptr);
    astTree.inorder(astptr);

   return result;
}

// advance to get next token.  Discard (destructor will actually delete tokens) previous token.
// 
Tb::Token::Ptr Tb::Parser::nextToken()
{
    const std::string LOCATION { "Parser::nextToken" };
    std::ostringstream logOss;

    if (Logger::get().isDebugEnabled() )
    {
        Token::Ptr tempTokenp = peekToken();
        logOss << LOCATION << ": finished processing token = "
               << *tempTokenp;
        Logger::get().debug(logOss);
    }

    tokenIndex_++;   

    if (Logger::get().isDebugEnabled() )
    {
        logOss << LOCATION << ": tokenIndex_ = " << tokenIndex_
               << "; numberTokens_ = " << numberTokens_;
        Logger::get().debug(logOss);
    }

    Token::Ptr tokenp = peekToken(); // tokens_[tokenIndex_].get();
    return tokenp;
}

// Look at token without affecting the token list.
//
Tb::Token::Ptr Tb::Parser::peekToken() 
{
    const std::string LOCATION { "Parser::peekToken" };
    std::ostringstream logOss;
    if (Tb::Logger::get().isDebugEnabled() )
    {
        logOss << LOCATION << ": tokenIndex = " << tokenIndex_
               << "; numberTokens = " << numberTokens_;
        Tb::Logger::get().debug(logOss);
    }
    Token::Ptr tokenp = nullptr;
    if (tokenIndex_ < numberTokens_)
    {
        tokenp = tokens_[tokenIndex_].get();
    }
    return tokenp;
}

// Attempt to process unitary plus/minus operators.  Not ideal as of 20211209.
//
double Tb::Parser::unsigned_factor(AstPtr& astptr)
{
    const std::string LOCATION {"Parser::unsigned_factor"};
    std::ostringstream logOss;
    double response = 0;
    AstNode::ShPtr currnode = nullptr;
    Token::Ptr look_ahead = peekToken();
    if (look_ahead == nullptr)
    {
        return response;
    }
    
    // Note: only number and operator tokens "graduate" into the
    // AST nodes.  Other non-terminal parser nodes are simply 
    // dropped and not used in the context of the AST.

    switch (look_ahead->tokenType() ) 
    {
    case TokenType::INTEGER:
    case TokenType::FLOAT:
        response = std::atof(look_ahead->tokenString().c_str() );

        look_ahead = peekToken();

        currnode = AstNode::factory(response, TokenType::UNDEFINED);

        // if (look_ahead->tokenType() == TokenType::OP_MINUS) 
        // {
        //     look_ahead = nextToken();

            // Already know that currnode is number ast 
            //
        //     response = currnode->negate();
        // }

        astptr = currnode;
        if (Logger::get().isDebugEnabled() )
        {
            logOss << LOCATION << ": response = " << response 
                   << "; " << *look_ahead;
            Logger::get().debug(logOss);
        } 
        
        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            return response;
        }       
        break;

    case TokenType::LEFT_PAREN:

        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            std::cerr << LOCATION << ": ERROR no token remaining after LEFT_PAREN ?? \n";
            return response;
        }
        response = expression(astptr);
        look_ahead = peekToken();		   
        if (look_ahead == nullptr)
        {
            return response;
        }
        if (look_ahead->tokenType() == TokenType::RIGHT_PAREN)
        {
            // ... nothing to do 
        }
        else
        {
            std::string errstr = "missing RIGHT_PAREN ) ";
            errorReport("missing ')'");
        }

        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            return response;
        }
        break;

    default:
        std::string errstr = "unexpected token";
        errorReport(errstr);
        std::cerr << LOCATION << ": ERROR line=" << __LINE__ << "; unexpected token ?? \n";
    };

    return response;
}

double Tb::Parser::factor(AstPtr& astptr)
{
    const std::string LOCATION { "Parser::factor" };
    double response = 0.0;

    // If there is a leading minus...

    Token::Ptr look_ahead = peekToken();

    if (look_ahead->tokenType() == TokenType::OP_MINUS) 
    {

        look_ahead = nextToken();
        response = unsigned_factor(astptr);
        response = astptr->negate();
        // std::cout << LOCATION << ": working response = " << response << "; bad response = " << negResponse << "\n";
    }
    else
    {
        response = unsigned_factor(astptr);
    }

    return response;
} // method Parser::factor

double Tb::Parser::term(AstPtr& astptr)
{
    const std::string LOCATION { "Parser::term" };
    std::ostringstream logOss;
    AstNode::ShPtr currnode = nullptr;
    Token::Ptr look_ahead = peekToken();

    if (Logger::get().isDebugEnabled() )
    {
        logOss << LOCATION << ": call factor "
               << *look_ahead << "\n";
        Logger::get().debug(logOss);
    }    

    // correct ... https://web.cs.wpi.edu/~kal/PLT/PLT6.3.6.html
    //
    double response = factor(astptr);
    look_ahead = peekToken();
        
    if (Logger::get().isDebugEnabled() )
    {
        if (look_ahead == nullptr)
        {
            logOss << LOCATION << ": response = " << response
                   << " after factor with look_ahead == nullptr";
        }
        else
        {
            logOss << LOCATION << ": response = " << response 
                   << "; " << *look_ahead << "\n";
        }
        Logger::get().debug(logOss);
    }

    while (look_ahead != nullptr)
    {
        if (look_ahead->tokenType() == TokenType::OP_MULT) // :
        {
            AstNode::ShPtr multast = AstNode::factory(0.0, TokenType::OP_MULT);
            multast->left_ = astptr;
            look_ahead = nextToken(); 
            if (look_ahead == nullptr)
            {
                return response;
            }
            double mult_response = factor(astptr->right_);
            astptr = multast;
            response = response * mult_response;

            look_ahead = peekToken();
            continue;
        } 
        if (look_ahead->tokenType() == TokenType::OP_DIVIDE) // 
        {
            AstNode::ShPtr divideast = AstNode::factory(0.0, TokenType::OP_DIVIDE);
            divideast->left_ = astptr;
            look_ahead = nextToken(); 
            if (look_ahead == nullptr)
            {
                return response;
            }
            double div_response =  factor(astptr->right_);
            astptr = divideast;
            response = response / div_response;
            look_ahead = peekToken();
            continue;
        }
        break;
    }
    return response;
} // method Parser::term

double Tb::Parser::expression(AstPtr& astptr)
{
    const std::string LOCATION { "Parser::expr" };
    std::ostringstream logOss;
    double answer = 0.0;
    bool initializedAnswer = false;
    Token::Ptr look_ahead = peekToken();

    if (Logger::get().isDebugEnabled() )
    {
        logOss << LOCATION << ": call term " << *look_ahead << "\n";
        Logger::get().debug(logOss);
    }

    // correct ... see https://web.cs.wpi.edu/~kal/PLT/PLT6.3.6.html
    //
    double response = term(astptr);

    look_ahead = peekToken();

    if (Logger::get().isDebugEnabled() && (look_ahead != nullptr))
    {
        logOss << LOCATION << ": back term " << *look_ahead << "\n";
        Logger::get().debug(logOss);
    }
    
    while (look_ahead != nullptr)
    {
	    if (look_ahead->tokenType() == TokenType::OP_PLUS) 
	    { 
            AstNode::ShPtr plusptr = AstNode::factory(0.0, TokenType::OP_PLUS);
            plusptr->left_ = astptr;
            look_ahead = nextToken(); // advance();
            if (look_ahead == nullptr)
            { 
                answer = response;
                initializedAnswer = true;
                continue;
            }
            if (Logger::get().isDebugEnabled() )
            {
                logOss << LOCATION << ": OP_PLUS to term";
                Logger::get().debug(logOss);
            }
            double plus_response = term(astptr->right_);
            response = response + plus_response;
            astptr = plusptr; 
            look_ahead = peekToken();
            if (look_ahead == nullptr)
            {
                answer = response;
                initializedAnswer = true;
            }
            continue;
        }
        if (look_ahead->tokenType() == TokenType::OP_MINUS)
        {
            AstNode::ShPtr minusast = AstNode::factory(0.0, TokenType::OP_MINUS);
            minusast->left_ = astptr;
            look_ahead = nextToken(); // advance();
            if (look_ahead == nullptr)
            {
                answer = response;
                initializedAnswer = true;
                continue;
            }
            double minus_response = term(astptr->right_);
            response = response - minus_response;
            astptr = minusast;
            look_ahead = peekToken();
            continue;
        }
        break;
    } // while look_ahead

    if (!initializedAnswer)
    {
        answer = response;
        initializedAnswer = true;
    }
    return answer;
} // Parser::expr

void Tb::Parser::errorReport(std::string errstr)
{
     std::cerr << "ERROR REPORT : " << errstr << "\n";
     // throw ParseEx;
}

