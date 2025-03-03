//
// Created by 无铭 on 25-3-3.
//
#include <fstream>
#include <iostream>
#include <sstream>

#include <lexer/lexer.h>
#include <token/token.h>

using namespace Ort::lexer;
using namespace Ort::token;

Lexer::Lexer(const std::string& file) : m_ch(0), m_pos(0), m_next_pos(0)
{
    std::ifstream ifs(file);
    if (!ifs.good())
    {
        std::cerr << "Not Found File: " << file << std::endl;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_input = oss.str();
}

const std::string& Lexer::input()
{
    return m_input;
}

Token Lexer::next_token()
{
    read_char();
    skip_whitespace();
    switch (m_ch)
    {
    case '+':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_PLUS, literal);
    }
    case '-':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_MINUS, literal);
    }
    case '*':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_ASTERISK, literal);
    }
    case '/':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_SLASH, literal);
    }
    case '(':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_LPAREN, literal);
    }
    case ')':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::TOKEN_RPAREN, literal);
    }
    case 0:
    {
        return new_token(Token::TOKEN_EOF, "");
    }
    default:
    {
        if (is_digit(m_ch))
        {
            std::string integer = read_number();
            unread_char(); // 让 m_ch 停留于数字尾部
            return new_token(Token::TOKEN_INTEGER, integer);
        }
        else
        {
            std::string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_ILLEGAL, literal);
        }
    }
    }
}

void Lexer::skip_whitespace()
{
    while (m_ch == ' ' || m_ch == '\t' || m_ch == '\n' || m_ch == '\r')
    {
        read_char();
    }
}

void Lexer::read_char()
{
    if (m_next_pos >= m_input.length())
    {
        m_ch = 0;
    }
    else
    {
        m_ch = m_input[m_next_pos];
    }
    m_pos = m_next_pos;
    m_next_pos++;
}

// 回退字符
void Lexer::unread_char()
{
    m_next_pos = m_pos;
    m_pos--;
}

bool Lexer::is_digit(char ch)
{
    return (m_ch >= '0' && m_ch <= '9');
}

std::string Lexer::read_number()
{
    int pos = m_pos;
    while (is_digit(m_input[m_pos]))
    {
        read_char();
    }
    return m_input.substr(pos, m_pos - pos);
}

Token Lexer::new_token(Token::Type type, const std::string& literal)
{
    Token token(type, literal);
    return token;
}
