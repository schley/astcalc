#if !defined __TB_TOKEN_HXX__
#define      __TB_TOKEN_HXX__

#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <regex>

#include "Logger.hxx"
#include "TokenType.hxx"

namespace Tb
{
    class Token
    {
        public:
            Token() = delete;
            Token(std::string tokenstring, TokenType type);
            ~Token();
            std::string tokenString() const;
            TokenType tokenType() const;	
            std::string tokenTypeString(TokenType type) const;

            using UPtr = std::unique_ptr<Token>;
            // using ShPtr = std::shared_ptr<Token>;
            using Ptr = Token*;

            static std::string match_separators();
            static UPtr factory(std::string tokenString);

            void print(std::ostream& tokenOss) const;
        private:
            // tokenProperties() method is class method (static) because 
            // class method factory above relies on tokenProperties method.
            //
            static TokenProperties& tokenProperties();
            std::string tokenString_;
            TokenType tokenType_;
            // Logger logger_;
    }; // class Token

    using Tokens = std::vector<Token::UPtr>;
    std::ostream& operator<<(std::ostream& tokenOss, const Tb::Token& token);

} // namespace Tb 

#endif    // __TB_TOKEN_HXX__

