#include <memory>
#include <sstream>
#include <array>

#include "Token.hxx"

// Token class variable tokenProperties 
//
// Tb::TokenProperties Tb::Token::tokenProperties_;

Tb::TokenProperty::TokenProperty(Tb::TokenType type, std::string tstr, 
                                   std::string tregex)
        : tokenType_(type), tokenTypeString_(tstr), tokenRegex_(tregex)
{
}

Tb::TokenProperty::~TokenProperty()
{
}

Tb::TokenType Tb::TokenProperty::tokenType() const
{
    return tokenType_;
}

std::string Tb::TokenProperty::tokenTypeString() const
{
    return tokenTypeString_;
}

std::string Tb::TokenProperty::tokenRegex() const
{
    return tokenRegex_;
}

Tb::Token::Token(std::string tokenstr, TokenType type)
    : tokenString_(tokenstr),
      tokenType_(type)
{
    static const std::string METHOD = "Token::Token : ";
}

// void Tb::Token::addProperty(TokenType token_type, 
//                                std::string type_string,
//                                std::string type_regex)
// {    
//     TokenProperties& tprops = tokenProperties();    
//     tprops[(int) token_type] = 
//       std::make_unique<TokenProperty>(token_type, type_string, type_regex);
// }

Tb::Token::UPtr Tb::Token::factory(std::string token_string)
{
    std::regex current_matcher;
    Tb::Token::UPtr uptr_token {nullptr};
    TokenProperties& tprops = tokenProperties();
    for (const auto& reIter : tprops)
    {
        // current_matcher = (reIter.second)->getTokenRegex();
        current_matcher = reIter->tokenRegex();
        if (std::regex_match(token_string, current_matcher))
        {
	    // uptr_token = std::make_unique<Token>(token_string, reIter.first);
            uptr_token = std::make_unique<Token>(token_string, 
                                                 reIter->tokenType());
            break;
        }
    }
    return uptr_token;
}

Tb::Token::~Token()
{
}

std::string Tb::Token::tokenString() const
{
    return tokenString_;
}

Tb::TokenType Tb::Token::tokenType() const
{
    return tokenType_;
}

std::string Tb::Token::tokenTypeString(Tb::TokenType type) const
{
    // const std::string METHOD {"Token::getTokenTypeString"};
    TokenProperties& tprops = tokenProperties();
    std::string type_string = tprops[(int) type]->tokenTypeString();
              // tokenProperties_[(int) type]->tokenTypeString();
    return type_string;
}

Tb::TokenProperties& Tb::Token::tokenProperties()
{
    static TokenProperties properties;
    static bool initializationRequired = true;
    if (initializationRequired)
    {
        initializationRequired = false;

        // properties = std::make_array<TokenProperty::UPtr, 
        //                              (int) TokenType::NUMBER_TOKENS>
        //              {{ nullptr }};

        // TokenType::UNDEFINED
        //
        std::string type_string = "TokenType::UNDEFINED";
        std::string type_regex = "$a";
        TokenType tokenType = TokenType::UNDEFINED;
        properties[(int) TokenType::UNDEFINED ] = 
                std::make_unique<TokenProperty>(tokenType, 
                                                type_string, type_regex); 

        // TokenType::OP_PLUS
        //
        type_string = "TokenType::OP_PLUS";
        type_regex = "([\\+])";
        tokenType = TokenType::OP_PLUS;
        // addProperty8(tokenType, type_string, type_regex);
        properties[(int) TokenType::OP_PLUS ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);


        // TokenType::OP_MULT
        //
        type_string = "TokenType::OP_MULT";
        type_regex = "([\\*])";
        tokenType = TokenType::OP_MULT;
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::OP_MULT ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);

        // TokenType::OP_DIVIDE
        //
        type_string = "TokenType::OP_DIVIDE";
        type_regex = "([\\/])";
        tokenType = TokenType::OP_DIVIDE;
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::OP_DIVIDE ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);

        // TokenType::OP_MINUS
        //
        type_string = "TokenType::OP_MINUS";
        type_regex = "([\\-])";
        tokenType = TokenType::OP_MINUS;
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::OP_MINUS ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);

        // TokenType::FLOAT
        //
        type_string = "TokenType::FLOAT";
        tokenType = TokenType::FLOAT;
        type_regex = "([+|-]?([[:digit:]]+[.]?[[:digit:]]*|[.][[:digit:]]+)"
                     "([eE][+|-]?[[:digit:]]+)?)";
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::FLOAT ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);
 
        // TokenType::INTEGER
        //
        type_string = "TokenType::INTEGER";
        type_regex = "([[:digit:]]+)";
        tokenType = TokenType::INTEGER;
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::INTEGER ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);

        // TokenType::LEFT_PAREN
        // 
        type_string = "TokenType::LEFT_PAREN";
        tokenType = TokenType::LEFT_PAREN;
        type_regex = "([\\(])";
        properties[(int) TokenType::LEFT_PAREN ] =
             std::make_unique<TokenProperty>(tokenType,
                                             type_string, type_regex);

        // TokenType::RIGHT_PAREN
        //
        type_string = "TokenType::RIGHT_PAREN";
        tokenType = TokenType::RIGHT_PAREN;
        type_regex = "([\\)])";
        properties[(int) TokenType::RIGHT_PAREN ] =
              std::make_unique<TokenProperty>(tokenType,
                                              type_string, type_regex);

        // TokenType::END_INPUT
        // 
        // type_string = "TokenType::END_INPUT";
        // tokenType = TokenType::END_INPUT;
        // type_regex = "([/n])";
        // properties[(int) TokenType::END_INPUT ] = 
        //        std::make_unique<TokenProperty>(tokenType,
        //                                        type_string, type_regex);

        // TokenType::SEMICOLON
        // 
        type_string = "TokenType::SEMICOLON";
        type_regex = "([;])";
        tokenType = TokenType::SEMICOLON;
        // addProperty(tokenType, type_string, type_regex);
        properties[(int) TokenType::SEMICOLON ] =
                std::make_unique<TokenProperty>(tokenType,
                                                type_string, type_regex);

    }
    return properties;
}

std::string Tb::Token::match_separators()
{
    static const std::string LOCATION { "Token::match_separators" };
    std::ostringstream logOss;
    std::ostringstream separators;
    const std::string RE_CONCATENATOR {"|"};
    bool concatenateRequired = false;
    int debug_counter = 0;
    TokenProperties& tprops = tokenProperties();
    for (auto& reiter : tprops)
    {
        if (concatenateRequired)
        {
            separators << RE_CONCATENATOR;
        }
        else
        {
            concatenateRequired = true;
        }
// #if defined BLOCK_OUT
        // std::cout << "Tb::Token::match_separators : "
        //           << static_cast<int>(reiter.first) << " : " 
        //           << reiter.second->getTokenRegex() << "\n";
        // separators << reiter.second->getTokenRegex();
        if (Logger::get().isDebugEnabled() )
        {
            logOss << LOCATION << ": "
                   << debug_counter++ 
                   << " : TokenType = " << reiter->tokenTypeString() 
                   << "; regex = " << reiter->tokenRegex();
	    Logger::get().debug(logOss);
        }
// #endif 
        separators << reiter->tokenRegex();
    }

/*
    for (int index = 0; 
         index < static_cast<int>(Tb::TokenType::NUMBER_TOKENS);
                                  ++index)
    {
        std::cout << "Tb::Token::match_separators : "
                  << index
                  << " : "
                  << tokenProperties_[static_cast<Tb::TokenType>(index)]->
                                      getTokenRegex() << "\n";
    } 
*/
    // std::cout << separators.str() << std::endl;

    return separators.str();
}

void Tb::Token::print(std::ostream& tokenOss) const
{
    tokenOss << "Tb::Token : " 
             << tokenTypeString(tokenType()) 
             << ": " << tokenString();
}

std::ostream& Tb::operator<<(std::ostream& tokenOss, const Tb::Token& token)
{
    token.print(tokenOss);
    return tokenOss;
}

// Just for debugging in the AstNodeOperatorVisitor which only has 
// access to the TokenType (not the actual token)
//
std::string Tb::TokenTypeRepr::tokenTypeString(TokenType tokenType)
{
    static std::array<std::string, (int)TokenType::NUMBER_TOKENS> tokenRepr 
    {
        "UNDEFINED",
        "OP_PLUS",
        "OP_MULT",
        "OP_DIVIDE",
        "OP_MINUS",
        "FLOAT", 
        "INTEGER", 
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "SEMICOLON"
    };
    return tokenRepr[(int) tokenType];
}
