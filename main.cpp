#include <fstream>
#include <iostream>
#include <lexer/lexer.h>
#include <nlohmann/json.hpp>
#include <token/token.h>

std::string handle(int argc, char* argv[])
{
    using namespace std;
    if (argc != 2)
    {
        cout << "Usage: Ort <filename>" << endl;
    }

    return {argv[1]};
}

int main(int argc, char* argv[])
{
    using namespace Ort::token;
    using namespace nlohmann;
    auto filename = handle(argc, argv);
    json tokens;

    Ort::lexer::Lexer lexer {filename};
    while (true)
    {
        auto token = lexer.next_token();
        tokens.push_back(token.json());
        if (token.type() == Token::TOKEN_EOF)
        {
            break;
        }
    }
    json j;
    j["tokens"] = tokens;

    std::ofstream ofs("./token.json");
    ofs << j.dump();
    ofs.close();
    return 0;
}
