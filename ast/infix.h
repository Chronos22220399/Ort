#pragma once

#include <ast/node.h>

namespace Ort
{
namespace ast
{

class Infix : public Expression
{
public:
    Infix() : Expression(NODE_INFIX)
    {
    }

    ~Infix()
    {
    }

public:
    std::string                 m_operator;
    std::shared_ptr<Expression> m_left;
    std::shared_ptr<Expression> m_right;
};

} // namespace ast
} // namespace Ort
