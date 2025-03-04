//
// Created by 无铭 on 25-3-3.
//

#include <fmt/format.h>
#include <token/token.h>

using namespace Ort::token;

std::map<Token::Type, std::string> Token::m_names = {
    {Type::TOKEN_ILLEGAL, "illegal"}, // illegal
    {Type::TOKEN_BEGIN, "begin"},     // begin
    {Type::TOKEN_IF, "if"},           // if
    {Type::TOKEN_THEN, "then"},       // then
    {Type::TOKEN_WHILE, "while"},     // while
    {Type::TOKEN_DO, "do"},           // do
    {Type::TOKEN_END, "end"},         // end
    {Type::TOKEN_LETTER, "letter"},   // letter
    {Type::TOKEN_EOF, "eof"},         // eof
    {Type::TOKEN_DIGIT, "integer"},   // integer
    {Type::TOKEN_PLUS, "+"},          // +
    {Type::TOKEN_MINUS, "-"},         // -
    {Type::TOKEN_ASTERISK, "*"},      // *
    {Type::TOKEN_SLASH, "/"},         // /
    {Type::TOKEN_COLON, ":"},         // :
    {Type::TOKEN_EQUAL, "="},         // =
    {Type::TOKEN_LESS, "<"},          // <
    {Type::TOKEN_NOTEQUAL, "!="},     // !=
    {Type::TOKEN_LESSEQUAL, "<="},    // <=
    {Type::TOKEN_GREATE, ">"},        // >
    {Type::TOKEN_GREATEEQUAL, ">="},  // >=
    {Type::TOKEN_EQUALEQUAL, "=="},   // ==
    {Type::TOKEN_LPAREN, "("},        // (
    {Type::TOKEN_RPAREN, ")"},        // )
    {Type::TOKEN_SEMICOLON, ";"},     // ;
    {Type::TOKEN_COMMA, "#"}          // #
};

Token::Token() : m_type(Type::TOKEN_ILLEGAL)
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
    fmt::println("type= {}\tname= {}\tliteral= {}", static_cast<int>(m_type), name(), m_literal);
}

nlohmann::json Token::json() const
{
    nlohmann::json json;
    json["type"] = name();
    json["name"] = m_literal;
    return json;
}
