#pragma once
#include <map>
#include <string>

namespace Ort::token
{
    class Token
    {
    public:
        enum Type
        {
            TOKEN_ILLEGAL,      // illegal
            TOKEN_EOF,          // eof
            TOKEN_INTEGER,      // integer
            TOKEN_PLUS,         // +
            TOKEN_MINUS,        // -
            TOKEN_ASTERISK,     // *
            TOKEN_SLASH,        // /
            TOKEN_LPAREN,       // (
            TOKEN_RPAREN,       // )
            TOKEN_SEMICOLON,    // ;
        };

        Token();
        Token(Type type, const std::string& literal);
        ~Token() = default;

        Type type() const;
        std::string literal() const;
        std::string name() const;

        void show() const;

        Token& operator=(const Token& other);


    private:
        Type m_type;
        std::string m_literal;
        static std::map<Type, std::string> m_names;
    };
}

