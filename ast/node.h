#pragma once
#include <memory>
#include <token/token.h>

namespace Ort
{

namespace ast
{

class Node
{
public:
    enum Type
    {
        NODE_INTEGER = 0,
        NODE_INFIX,                // 中缀表达式
        NODE_EXPRESSION_STATEMENT, // 表达式语句,用于将表达式转换为语句
        NODE_PROGRAM,              // 根节点
    };

    Node();
    Node(Type type);

    virtual ~Node();

    Type type() const;

    std::string name() const;

public:
    Type                               m_type;
    token::Token                       m_token;
    static std::map<Type, std::string> m_names;
};

class Expression : public Node
{
public:
    Expression();
    Expression(Type type);
    ~Expression();
};

class Statement : public Node
{
public:
    Statement();
    Statement(Type type);
    ~Statement();
};

} // namespace ast

} // namespace Ort
