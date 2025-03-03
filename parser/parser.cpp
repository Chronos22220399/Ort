#include <parser/parser.h>
#include <sstream>

using namespace Ort::parser;

std::map<Token::Type, int> Parser::m_precedences = {
    {Token::TOKEN_PLUS, SUM},
    {Token::TOKEN_MINUS, SUM},
    {Token::TOKEN_ASTERISK, PRODUCT},
    {Token::TOKEN_SLASH, PRODUCT},
};

Parser::Parser() = default;

Parser::Parser(const std::shared_ptr<Lexer>& lexer) : m_lexer(lexer)
{
    // 设置当前符号和下一个符号
    next_token();
    next_token();
}

Parser::~Parser() = default;

void Parser::next_token()
{
    m_curr = m_peek;
    m_peek = m_lexer->next_token();
}

bool Parser::curr_token_is(Token::Type type) const
{
    return m_curr.type() == type;
}

bool Parser::peek_token_is(Token::Type type) const
{
    return m_peek.type() == type;
}

bool Parser::expect_peek_token(Token::Type type)
{
    if (peek_token_is(type))
    {
        next_token();
        return true;
    }
    else
    {
        peek_error(type);
        return false;
    }
}

void Parser::peek_error(Token::Type type)
{
    std::ostringstream oss;
    oss << "expected next token to be " << type << ", got " << m_peek.type() << " instead";
    m_errors.push_back(oss.str());
}

int Parser::curr_token_precedence()
{
    auto it = m_precedences.find(m_curr.type());
    if (it == m_precedences.end())
    {
        return LOWEST;
    }
    return it->second;
}

int Parser::peek_token_precedence()
{
    auto it = m_precedences.find(m_peek.type());
    if (it == m_precedences.end())
    {
        return LOWEST;
    }
    return it->second;
}
