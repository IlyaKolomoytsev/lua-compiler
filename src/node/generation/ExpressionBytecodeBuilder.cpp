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
        }
    case ExpressionNode::Type::Boolean:
        {
            PushBool(expression);
        }
    case ExpressionNode::Type::String:
        {
            PushString(expression);
        }
    case ExpressionNode::Type::Nil:
        {
            PushNull(expression);
        }
    default:
        break;
    }
}

void ExpressionBytecodeBuilder::PushInt(ExpressionNode* expression)
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushInt(static_cast<int32_t>(expression->getInteger()))
        << code->InvokeStatic(runtimeRefs.integerValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushFloat(ExpressionNode* expression)
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushFloat(static_cast<float>(expression->getFloat()))
        << code->InvokeStatic(runtimeRefs.floatValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushBool(ExpressionNode* expression)
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushInt(expression->getBool() ? 1 : 0)
        << code->InvokeStatic(runtimeRefs.booleanValueOf)
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushString(ExpressionNode* expression)
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushString(*expression->getString())
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

void ExpressionBytecodeBuilder::PushNull(ExpressionNode* expression)
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->PushNull()
        << code->InvokeStatic(runtimeRefs.luaValueCreate);
}

ExpressionNodeList ExpressionBytecodeBuilder::getChildren(ExpressionNode* e)
{
    ExpressionNodeList children;

    switch (e->getType())
    {
    case ExpressionNode::Type::TableConstructor:
        {
            for (const auto& field : *e->getTableConstructor())
            {
                if (field.name) children.push_back(field.name);
                if (field.value) children.push_back(field.value);
            }
            break;
        }

    case ExpressionNode::Type::TableField:
        {
            children.push_back(e->getTableId());
            children.push_back(e->getTableFieldKey());
            break;
        }

    case ExpressionNode::Type::FunctionCall:
        {
            children.push_back(e->getFunctionId());
            for (auto* arg : *e->getFunctionArguments())
                children.push_back(arg);
            break;
        }

    case ExpressionNode::Type::Length:
    case ExpressionNode::Type::Negation:
    case ExpressionNode::Type::UnaryMinuses:
        {
            children.push_back(e->getOperand());
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
            children.push_back(e->getLeftOperand());
            children.push_back(e->getRightOperand());
            break;
        }

    default:
        break;
    }

    return children;
}
