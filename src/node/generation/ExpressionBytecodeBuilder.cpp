#include "generation/ExpressionBytecodeBuilder.h"

#include <optional>

#include "jvm/descriptor-method.h"

void ExpressionBytecodeBuilder::buildExpression(ExpressionNode* expression)
{
    auto children = getChildren(expression);

    for (auto child : children)
    {
        build(child);
    }

    build(expression);
}

void ExpressionBytecodeBuilder::build(ExpressionNode* expression)
{
    switch (expression->getType())
    {
    case ExpressionNode::Type::Integer:
        {
            PushInt(expression);
            break;
        }
    case ExpressionNode::Type::Float:
        {
            PushFloat(expression);
            break;
        }
    case ExpressionNode::Type::Boolean:
        {
            PushBool(expression);
            break;
        }
    case ExpressionNode::Type::String:
        {
            PushString(expression);
            break;
        }
    case ExpressionNode::Type::Nil:
        {
            PushNull(expression);
            break;
        }
    default:
        break;
    }
}

void ExpressionBytecodeBuilder::PushInt(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushInt(static_cast<int32_t>(expression->getInteger()))
        << code->InvokeStatic(runtimeRefs.integerValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushFloat(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushFloat(static_cast<float>(expression->getFloat()))
        << code->InvokeStatic(runtimeRefs.floatValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushBool(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushInt(expression->getBool() ? 1 : 0)
        << code->InvokeStatic(runtimeRefs.booleanValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushString(ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushString(*expression->getString())
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushNull(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushNull()
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

ExpressionNodeList ExpressionBytecodeBuilder::getChildren(ExpressionNode* expression)
{
    ExpressionNodeList children;

    switch (expression->getType())
    {
    case ExpressionNode::Type::TableConstructor:
        {
            for (const auto& field : *expression->getTableConstructor())
            {
                if (field.name) children.push_back(field.name);
                if (field.value) children.push_back(field.value);
            }
            break;
        }

    case ExpressionNode::Type::TableField:
        {
            children.push_back(expression->getTableId());
            children.push_back(expression->getTableFieldKey());
            break;
        }

    case ExpressionNode::Type::FunctionCall:
        {
            children.push_back(expression->getFunctionId());
            for (auto* arg : *expression->getFunctionArguments())
                children.push_back(arg);
            break;
        }

    case ExpressionNode::Type::Length:
    case ExpressionNode::Type::Negation:
    case ExpressionNode::Type::UnaryMinuses:
        {
            children.push_back(expression->getOperand());
            break;
        }

    case ExpressionNode::Type::Summation:
    case ExpressionNode::Type::Subtraction:
    case ExpressionNode::Type::Multiplication:
    case ExpressionNode::Type::Division:
    case ExpressionNode::Type::Modulo:
    case ExpressionNode::Type::IntegerDivision:
    case ExpressionNode::Type::Exponentiation:
    case ExpressionNode::Type::Less:
    case ExpressionNode::Type::Greater:
    case ExpressionNode::Type::Equality:
    case ExpressionNode::Type::Unequality:
    case ExpressionNode::Type::LessEqual:
    case ExpressionNode::Type::GreaterEqual:
    case ExpressionNode::Type::Or:
    case ExpressionNode::Type::And:
    case ExpressionNode::Type::Concatenation:
        {
            children.push_back(expression->getLeftOperand());
            children.push_back(expression->getRightOperand());
            break;
        }

    default:
        break;
    }

    return children;
}
