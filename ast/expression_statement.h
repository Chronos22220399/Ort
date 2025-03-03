#pragma once

#include <ast/node.h>

namespace Ort
{
namespace ast
{

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement() : Statement(NODE_EXPRESSION_STATEMENT)
    {
    }

    ~ExpressionStatement()
    {
    }

public:
};

} // namespace ast
} // namespace Ort
