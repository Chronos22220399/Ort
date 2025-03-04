#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include <string>

namespace Ort
{
namespace token
{

class Token
{
public:
    enum class Type
    {
        TOKEN_ILLEGAL = -1, // illegal
        TOKEN_EOF,          // eof
        TOKEN_BEGIN,        // begin
        TOKEN_IF,           // if
        TOKEN_THEN,         // then
        TOKEN_WHILE,        // while
        TOKEN_DO,           // do
        TOKEN_END,          // end
        TOKEN_LETTER,       // letter
        TOKEN_DIGIT,        // digit
        TOKEN_PLUS,         // +
        TOKEN_MINUS,        // -
        TOKEN_ASTERISK,     // *
        TOKEN_SLASH,        // /
        TOKEN_COLON,        // :
        TOKEN_EQUAL,        // =
        TOKEN_LESS,         // <
        TOKEN_NOTEQUAL,     // !=
        TOKEN_LESSEQUAL,    // <=
        TOKEN_GREATE,       // >
        TOKEN_GREATEEQUAL, // >=
        TOKEN_EQUALEQUAL,   // ==
        TOKEN_LPAREN,       // (
        TOKEN_RPAREN,       // )
        TOKEN_SEMICOLON,    // ;
        TOKEN_COMMA,        // #
    };

    Token();
    Token(Type type, const std::string& literal);
    ~Token() = default;

    Type        type() const;
    std::string literal() const;
    std::string name() const;

    void           show() const;
    nlohmann::json json() const;

    Token& operator=(const Token& other);

private:
    Type                               m_type;
    std::string                        m_literal;
    static std::map<Type, std::string> m_names;
};

} // namespace token

} // namespace Ort
