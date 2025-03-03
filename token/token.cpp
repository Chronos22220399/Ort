//
// Created by 无铭 on 25-3-3.
//

#include <fmt/format.h>
#include <token/token.h>

using namespace Ort::token;

std::map<Token::Type, std::string> Token::m_names = {
    {TOKEN_ILLEGAL, "illegal"}, {TOKEN_EOF, "eof"},    {TOKEN_INTEGER, "integer"}, {TOKEN_PLUS, "+"},
    {TOKEN_MINUS, "-"},         {TOKEN_ASTERISK, "*"}, {TOKEN_SLASH, "/"},         {TOKEN_LPAREN, "("},
    {TOKEN_RPAREN, ")"},        {TOKEN_SEMICOLON, ";"}};

Token::Token() : m_type(TOKEN_ILLEGAL)
{
}

Token::Token(Type type, const std::string& literal) : m_type(type), m_literal(literal)
{
}

Token::Type Token::type() const
{
    return m_type;
}

std::string Token::literal() const
{
    return m_literal;
}

std::string Token::name() const
{
    auto it = m_names.find(m_type);
    if (it != m_names.end())
    {
        return it->second;
    }
    return "";
}

Token& Token::operator=(const Token& other)
{
    if (this != &other)
    {
        m_type = other.m_type;
        m_literal = other.m_literal;
    }
    return *this;
}

void Token::show() const
{
    fmt::println("type= {}\tname= {}\tliteral={}", static_cast<int>(m_type), name(), m_literal);
}

nlohmann::json Token::json() const
{
    nlohmann::json json;
    json["type"] = name();
    json["name"] = m_literal;
    return json;
}
