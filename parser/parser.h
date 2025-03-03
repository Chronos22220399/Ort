#pragma once

#include "ast/node.h"
#include <ast/header.h>
#include <lexer/lexer.h>
#include <token/token.h>

using namespace Ort::lexer;
using namespace Ort::token;

namespace Ort
{

namespace parser
{

class Parser
{
public:
    enum Precedence
    {
        LOWEST = 0,
        SUM,     // +, -
        PRODUCT, // *, /
    };

    Parser();
    Parser(const std::shared_ptr<Lexer>& lexer);
    ~Parser();

    // 前缀表达式构建函数原型定义
    using prefix_parse_fn = std::shared_ptr<ast::Expression> (Parser::*)(void);
    // 中缀表达式构建函数原型定义
    using infix_parse_fn = std::shared_ptr<ast::Expression> (Parser::*)(const std::shared_ptr<ast::Expression>&);
    // 后缀表达式构建函数原型定义
    using suffix_parse_fn = std::shared_ptr<ast::Expression> (Parser::*)(void);

    void next_token();
    bool curr_token_is(Token::Type type) const;
    bool peek_token_is(Token::Type type) const;
    bool expect_peek_token(Token::Type type);
    void peek_error(Token::Type type);

    int curr_token_precedence();
    int peek_token_precedence();

private:
    std::shared_ptr<Lexer>            m_lexer;
    Token                             m_curr;
    Token                             m_peek;
    std::list<std::string>            m_errors;
    static std::map<Token::Type, int> m_precedences;
};

} // namespace parser

} // namespace Ort
