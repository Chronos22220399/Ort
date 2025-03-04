#pragma once
#include <string>
#include <token/token.h>
//
// Created by 无铭 on 25-3-3.
//

namespace Ort
{
    namespace lexer
    {
        class Lexer
        {
        public:
            Lexer() = default;

            explicit Lexer(const std::string &file);

            ~Lexer() = default;

            token::Token next_token();

        private:
            void skip_whitespace();

            void read_char();

            void unread_char();

            constexpr bool generic_compare(char ch, const std::string &str) const;

            constexpr bool is_blank(char ch) const;

            constexpr bool is_digit(char ch) const;

            constexpr bool is_alpha(char ch) const;

            constexpr bool is_begin(char ch) const;

            constexpr bool is_if(char ch) const;

            constexpr bool is_then(char ch) const;

            constexpr bool is_while(char ch) const;

            constexpr bool is_do(char ch) const;

            constexpr bool is_end(char ch) const;

            std::string generic_read(const std::string &str);

            std::string read_begin();

            std::string read_do();

            std::string read_end();

            std::string read_if();

            std::string read_then();

            std::string read_while();

            std::string read_letter();

            std::string read_number();

            token::Token new_token(token::Token::Type type, const std::string &literal) const;

        private:
            std::string m_input; // 分析的句子
            char m_ch{}; // 当前所指向的字符
            int m_pos{}; // 当前的位置
            int m_next_pos{}; // 下一个字符的位置
        };
    } // namespace lexer
} // namespace Ort
