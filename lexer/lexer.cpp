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
        return new_token(Token::Type::TOKEN_PLUS, literal);
    }
    case '-':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_MINUS, literal);
    }
    case '*':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_ASTERISK, literal);
    }
    case '/':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_SLASH, literal);
    }
    case '(':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_LPAREN, literal);
    }
    case ')':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_RPAREN, literal);
    }
    case ':':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_COLON, literal);
    }
    case ';':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_SEMICOLON, literal);
    }
    case '=':
    {
        std::string literal;
        literal += m_ch;
        if (m_input[m_next_pos] == '=')
        {
            read_char();
            literal += m_ch;
            return new_token(Token::Type::TOKEN_EQUALEQUAL, literal);
        }
        return new_token(Token::Type::TOKEN_EQUAL, literal);
    }
    case '<':
    {
        std::string literal;
        literal += m_ch;
        if (m_input[m_next_pos] == '=')
        {
            read_char();
            literal += m_ch;
            return new_token(Token::Type::TOKEN_LESSEQUAL, literal);
        }
        return new_token(Token::Type::TOKEN_LESS, literal);
    }
    case '>':
    {
        std::string literal;
        literal += m_ch;
        if (m_input[m_next_pos] == '=')
        {
            read_char();
            literal += m_ch;
            return new_token(Token::Type::TOKEN_GREATEEQUAL, literal);
        }
        return new_token(Token::Type::TOKEN_GREATE, literal);
    }
    case '#':
    {
        std::string literal;
        literal += m_ch;
        return new_token(Token::Type::TOKEN_COMMA, literal);
    }
    case 0:
    {
        return new_token(Token::Type::TOKEN_EOF, "");
    }
    default:
    {
        if (is_digit(m_ch))
        {
            std::string integer = read_number();
            unread_char(); // 让 m_ch 停留于数字尾部
            return new_token(Token::Type::TOKEN_DIGIT, integer);
        }
        else if (is_alpha(m_ch))
        {
            std::string literal;
            if (is_begin(m_ch))
            {
                literal += read_begin();
                return new_token(Token::Type::TOKEN_BEGIN, literal);
            }
            else if (is_do(m_ch))
            {
                literal += read_do();
                return new_token(Token::Type::TOKEN_DO, literal);
            }
            else if (is_end(m_ch))
            {
                literal += read_end();
                return new_token(Token::Type::TOKEN_END, literal);
            }
            else if (is_then(m_ch))
            {
                literal += read_then();
                return new_token(Token::Type::TOKEN_THEN, literal);
            }
            else if (is_while(m_ch))
            {
                literal += read_while();
                return new_token(Token::Type::TOKEN_WHILE, literal);
            }
            else if (is_if(m_ch))
            {
                literal += read_if();
                return new_token(Token::Type::TOKEN_IF, literal);
            }
            std::string letter = read_letter();
            unread_char(); // 让 m_ch 停留于letter的尾部
            return new_token(Token::Type::TOKEN_LETTER, letter);
        }
        else
        {
            std::string literal;
            literal += m_ch;
            return new_token(Token::Type::TOKEN_ILLEGAL, literal);
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

constexpr bool Lexer::is_blank(char ch) const
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

constexpr bool Lexer::is_digit(char ch) const
{
    return (ch >= '0' && ch <= '9');
}

constexpr bool Lexer::is_alpha(char ch) const
{
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

constexpr bool Lexer::generic_compare(char ch, const std::string &str) const
{
    auto len = m_input.length();
    auto s_len = str.length();
    if (ch == str[0] && m_pos+s_len-1 < len && m_input.substr(m_pos, s_len) == str)
    {
        auto next_pos = m_pos + s_len;
        if (next_pos >= len)
        {
            return is_blank(m_input[next_pos]);
        }
        return true;
    }
    return false;
}

constexpr bool Lexer::is_begin(char ch) const
{
    return generic_compare(ch, "begin");
}

constexpr bool Lexer::is_if(char ch) const
{
    return generic_compare(ch, "if");
}

constexpr bool Lexer::is_then(char ch) const
{
    return generic_compare(ch, "then");
}

constexpr bool Lexer::is_while(char ch) const
{
    return generic_compare(ch, "while");
}

constexpr bool Lexer::is_do(char ch) const
{
    return generic_compare(ch, "do");
}

constexpr bool Lexer::is_end(char ch) const
{
    return generic_compare(ch, "end");
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

std::string Lexer::read_letter()
{
    int pos = m_pos;
    read_char();
    while (is_digit(m_input[m_pos]) || m_input[m_pos] == '_' || is_alpha(m_input[m_pos]))
    {
        read_char();
    }
    return m_input.substr(pos, m_pos - pos);
}

std::string Lexer::generic_read(const std::string &str)
{
    m_pos += str.length();
    m_next_pos = m_pos + 1;
    return str;
}

std::string Lexer::read_begin()
{
    return generic_read("begin");
}

std::string Lexer::read_if()
{
    return generic_read("if");
}

std::string  Lexer::read_then()
{
    return generic_read("then");
}

std::string  Lexer::read_while()
{
    return generic_read("while");
}

std::string  Lexer::read_do()
{
    return generic_read("do");
}

std::string  Lexer::read_end()
{
    return generic_read("end");
}

Token Lexer::new_token(Token::Type type, const std::string& literal) const
{
    Token token(type, literal);
    return token;
}
