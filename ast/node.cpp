#pragma once
#include <ast/node.h>
#include <token/token.h>

using namespace Ort::ast;

std::map<Node::Type, std::string> Node::m_names = {
    {Node::NODE_INTEGER, "Integer"},
    {Node::NODE_INFIX, "Infix"},
    {Node::NODE_EXPRESSION_STATEMENT, "ExpressionStatement"},
    {Node::NODE_PROGRAM, "Program"},
};

Node::Node()
{
}

Node::Node(Type type) : m_type(type)
{
}

Node::~Node()
{
}

Node::Type Node::type() const
{
    return m_type;
}

std::string Node::name() const
{
    auto it = m_names.find(m_type);
    if (it == m_names.end())
    {
        return "";
    }
    return it->second;
};

/*
 * ------- Expression -----------
 */
Expression::Expression()
{
}

Expression::Expression(Type type) : Node(type)
{
}

Expression::~Expression()
{
}

/*
 * ------- Statement -----------
 */
Statement::Statement()
{
}

Statement::Statement(Type type) : Node(type)
{
}

Statement::~Statement()
{
}
