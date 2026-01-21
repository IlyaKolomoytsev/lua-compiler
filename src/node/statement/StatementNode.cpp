#include "node/statement/StatementNode.h"

#include <cassert>
#include "node/expression/FunctionCallExprNode.h"

StatementNode::StatementNode(Type type) : type_(type)
{
}

std::string to_string(Scope scope)
{
    switch (scope)
    {
    case Scope::Global:
        return "Global";
    case Scope::Local:
        return "Local";
    default:
        assert(false);
        return "Unknown";
    }
}

std::string to_string(StatementNode::Type type)
{
    switch (type)
    {
    case StatementNode::Type::Declaration:
        return "Declaration";
    case StatementNode::Type::Assignment:
        return "Assignment";
    case StatementNode::Type::FunctionCall:
        return "FunctionCall";
    case StatementNode::Type::Branching:
        return "Branching";
    case StatementNode::Type::ForLoopClassic:
        return "ForLoop";
    case StatementNode::Type::WhileLoop:
        return "WhileLoop";
    case StatementNode::Type::RepeatLoop:
        return "RepeatLoop";
    case StatementNode::Type::Block:
        return "Block";
    case StatementNode::Type::GoTo:
        return "GoTo";
    case StatementNode::Type::Label:
        return "Label";
    case StatementNode::Type::Break:
        return "Break";
    case StatementNode::Type::Return:
        return "Return";
    default:
        assert(false);
        return "Unknown";
    }
}
