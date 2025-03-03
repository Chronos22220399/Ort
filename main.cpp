#include <filesystem>
#include <iostream>
#include <token/token.h>
#include <lexer/lexer.h>

int main()
{
    // Ort::token::Token token {};
    // std::cout<<token.name()<<std::endl;
    using namespace Ort::token;

    Ort::lexer::Lexer lexer {"/Users/wuming/ClionProjects/Ort/code.ess"};
    while (true)
    {
        auto token = lexer.next_token();
        token.show();
        if (token.type() == Token::TOKEN_EOF)
        {
            break;
        }
    }
    return 0;
}