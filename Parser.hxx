#if !defined __TB_PARSER_HXX__
#define      __TB_PARSER_HXX__

#include "Token.hxx"
#include "AstNode.hxx"

namespace Tb
{
    class Parser
    {
    public:
        explicit Parser(Tokens& tokens);
        Parser() = delete;
        ~Parser();

        using AstPtr = AstNode::ShPtr;
        double start();
        AstPtr& treeRoot();
    private:
        Token::Ptr nextToken(); // advance
        Token::Ptr peekToken();


        double unsigned_factor(AstPtr& astptr); 
        double factor(AstPtr& astptr);
        double term(AstPtr& astptr);
        double expression(AstPtr& astptr);

        // AstNode::ShPtr& treeRoot();

        void errorReport(std::string errorstring);
    private:
        Tokens& tokens_;
        int numberTokens_;
        int tokenIndex_;
    };

} // namespace Tb

#endif // __TB_PARSER_HXX__:
