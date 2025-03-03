#pragma once

#include <ast/node.h>
#include <list>

namespace Ort
{
namespace ast
{

class Program : public Statement
{
public:
    Program() : Statement(NODE_PROGRAM)
    {
    }

    ~Program()
    {
    }

public:
    std::list<std::shared_ptr<Statement>> m_statements;
};

} // namespace ast
} // namespace Ort
