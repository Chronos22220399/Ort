#include <parser/parser.h>
#include <sstream>

using namespace Ort::parser;

std::map<Token::Type, int> Parser::m_precedences = {
    {Token::Type::TOKEN_PLUS, SUM},
    {Token::Type::TOKEN_MINUS, SUM},
    {Token::Type::TOKEN_ASTERISK, PRODUCT},
    {Token::Type::TOKEN_SLASH, PRODUCT},
};

std::map<Token::Type, Parser::prefix_parse_fn> Parser::m_prefix_parse_fns = {
    {Token::Type::TOKEN_DIGIT, &Parser::parse_digit},
    {Token::Type::TOKEN_LPAREN, &Parser::parse_group},
};

std::map<Token::Type, Parser::infix_parse_fn> Parser::m_infix_parse_fns = {
    {Token::Type::TOKEN_PLUS, &Parser::parse_infix},
    {Token::Type::TOKEN_MINUS, &Parser::parse_infix},
    {Token::Type::TOKEN_ASTERISK, &Parser::parse_infix},
    {Token::Type::TOKEN_SLASH, &Parser::parse_infix},
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
    oss << "expected next token to be " << static_cast<int>(type) << ", got " << static_cast<int>(m_peek.type()) << " instead";
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
