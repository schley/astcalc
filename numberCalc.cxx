#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <memory>

#include "Token.hxx"
#include "Parser.hxx"
#include "AstNode.hxx"

// Parse expressions, one per line. 

int main(int, char** )
{
    int status = 0;
    Tb::Tokens tokens;
    std::ostringstream regexOss;
    std::ostringstream tlOss;

    regexOss << Tb::Token::match_separators();
    
    std::string patstr = regexOss.str().c_str();
    std::regex re_exit { "(^exit$)" };
    std::regex pattern(patstr.begin(), patstr.end(), std::regex::ECMAScript);
     
    std::string input;
    
    int lineCount = 0;

    const std::string PROMPT {" > "};
    bool keepCalculating = true;

    while (keepCalculating) 
    {
        std::cout << (lineCount + 1) << PROMPT;
        std::getline(std::cin, input);
        if (std::regex_match(input, re_exit) )
        {
            keepCalculating = false;
            continue;
        }   
        auto iter_begin = std::sregex_iterator
                          (input.begin(), input.end(), pattern);
        auto iter_end = std::sregex_iterator();
        for (auto it = iter_begin; it != iter_end; ++it)
        {
            std::smatch match = *it;
            tokens.emplace_back(Tb::Token::factory(match.str() ));
        }
        ++lineCount;
        if (tokens.empty() )
        {
            tlOss << "unrecognized input, try again ...";
           
            std::cout << input << " = " << tlOss.str().c_str() << "\n";
            tlOss.str("");
            continue;
        }
        Tb::Parser parser(tokens);
        double response = parser.start();
        std::cout << "astcalc: " << input << " = " << response << "\n\n";

        tokens.clear();

    } // while keepCalculating

    return status;
}

