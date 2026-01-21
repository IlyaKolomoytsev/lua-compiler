#include "node/expression/ExpressionNode.h"

#include <cassert>
#include <stdexcept>

#include "node/DotMacros.h"
#include "node/statement/StatementNode.h"

ExpressionNode::ExpressionNode(Type type) : type_(type)
{
}

std::string to_string(ExpressionNode::Type type)
{
    switch (type)
    {
    case ExpressionNode::Type::Integer:
        return "Integer";
    case ExpressionNode::Type::Float:
        return "Float";
    case ExpressionNode::Type::String:
        return "String";
    case ExpressionNode::Type::Boolean:
        return "Boolean";
    case ExpressionNode::Type::Nil:
        return "Nil";
    case ExpressionNode::Type::Vararg:
        return "Vararg";
    case ExpressionNode::Type::TableField:
        return "TableField";
    case ExpressionNode::Type::TableConstructor:
        return "TableConstructor";
    case ExpressionNode::Type::FunctionCall:
        return "FunctionCall";
    case ExpressionNode::Type::FunctionLiteral:
        return "FunctionLiteral";
    case ExpressionNode::Type::Summation:
        return "Summation";
    case ExpressionNode::Type::Subtraction:
        return "Subtraction";
    case ExpressionNode::Type::Multiplication:
        return "Multiplication";
    case ExpressionNode::Type::Division:
        return "Division";
    case ExpressionNode::Type::Modulo:
        return "Modulo";
    case ExpressionNode::Type::IntegerDivision:
        return "IntegerDivision";
    case ExpressionNode::Type::Exponentiation:
        return "Exponentiation";
    case ExpressionNode::Type::Less:
        return "Less";
    case ExpressionNode::Type::Greater:
        return "Greater";
    case ExpressionNode::Type::Equality:
        return "Equality";
    case ExpressionNode::Type::Unequality:
        return "Unequality";
    case ExpressionNode::Type::LessEqual:
        return "LessEqual";
    case ExpressionNode::Type::GreaterEqual:
        return "GreaterEqual";
    case ExpressionNode::Type::Or:
        return "Or";
    case ExpressionNode::Type::And:
        return "And";
    case ExpressionNode::Type::Concatenation:
        return "Concatenation";
    case ExpressionNode::Type::Length:
        return "Length";
    case ExpressionNode::Type::Negation:
        return "Negation";
    case ExpressionNode::Type::UnaryMinuses:
        return "UnaryMinuses";
    default:
        assert(false);
        return "Unknown";
    }
}
