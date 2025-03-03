#pragma once
#include <string>
#include <token/token.h>
//
// Created by 无铭 on 25-3-3.
//

namespace Ort::lexer
{

class Lexer {
public:
    Lexer() = default;
    explicit Lexer(const std::string &file);
    ~Lexer() = default;

    const std::string& input();

    token::Token next_token();

private:
    void skip_whitespace();
    void read_char();
    void unread_char();
    bool is_digit(char ch);
    std::string read_number();
    token::Token new_token(token::Token::Type type, const std::string &literal);

private:
    std::string     m_input;                // 分析的句子
    char            m_ch{};                   // 当前所指向的字符
    int             m_pos{};                  // 当前的位置
    int             m_next_pos{};             // 下一个字符的位置
};

}