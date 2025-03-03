#pragma once

#include <ast/node.h>

namespace Ort
{
namespace ast
{

class Integer : public Expression
{
public:
    Integer() : Expression(NODE_INTEGER)
    {
    }

    ~Integer()
    {
    }

public:
    int64_t m_value;
};

} // namespace ast
} // namespace Ort
