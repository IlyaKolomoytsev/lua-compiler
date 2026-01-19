#include "generation/ExpressionBytecodeBuilder.h"

using type = ExpressionNode::Type;

void ExpressionBytecodeBuilder::buildExpression(ExpressionNode* expression)
{
    auto children = getChildren(expression);

    if (expression->getType() == type::And)
    {
        buildAnd(expression->getLeftOperand(), expression->getRightOperand());
    }
    else if (expression->getType() == type::Or)
    {
        buildOr(expression->getLeftOperand(), expression->getRightOperand());
    }
    else
    {
        for (auto child : children)
        {
            buildExpression(child);
        }
        build(expression);
    }
}

void ExpressionBytecodeBuilder::build(ExpressionNode* expression)
{
    switch (expression->getType())
    {
    case type::Integer:
        {
            pushInt(expression);
            break;
        }
    case type::Float:
        {
            pushFloat(expression);
            break;
        }
    case type::Boolean:
        {
            pushBool(expression);
            break;
        }
    case type::String:
        {
            pushString(expression);
            break;
        }
    case type::Nil:
        {
            pushNull();
            break;
        }
    case type::Summation:
        {
            sum();
            break;
        }
    case type::Subtraction:
        {
            sub();
            break;
        }
    case type::Multiplication:
        {
            mul();
            break;
        }
    case type::Division:
        {
            div();
            break;
        }
    case type::IntegerDivision:
        {
            idiv();
            break;
        }
    case type::Modulo:
        {
            mod();
            break;
        }
    case type::Exponentiation:
        {
            pow();
            break;
        }
    case type::Concatenation:
        {
            concat();
            break;
        }
    case type::Equality:
        {
            equal();
            break;
        }
    case type::Greater:
        {
            greaterThan();
            break;
        }
    case type::GreaterEqual:
        {
            greaterEqual();
            break;
        }
    case type::Less:
        {
            lessThan();
            break;
        }
    case type::LessEqual:
        {
            lessEqual();
            break;
        }
    case type::Length:
        {
            len();
            break;
        }
    case type::UnaryMinuses:
        {
            unm();
            break;
        }
    case type::Id:
        {
            id(expression);
            break;
        }
    case type::TableField:
    case type::TableFieldByIndex:
        {
            getFieldByKey();
            break;
        }
    case type::Unequality:
        {
            notEqual();
            break;
        }
    case type::Negation:
        {
            Not();
            break;
        }
    default:
        break;
    }
}

void ExpressionBytecodeBuilder::buildAnd(ExpressionNode* left, ExpressionNode* right)
{
    auto* code = context_->attributeCode_;
    const auto rt = context_->runtime_;

    auto* L_end   = code->CodeLabel();

    buildExpression(left);  // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->PushInt(1);  // ..., left, left, 1
    *code << code->InvokeVirtual(rt.luaValueGetBool);  // ..., left, bool
    *code << code->If(Instruction::Compare::Equal, L_end); // ..., left

    // true:
    *code << code->PopOne(); // ...
    buildExpression(right);  // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::buildOr(ExpressionNode* left, ExpressionNode* right)
{
    auto* code = context_->attributeCode_;
    auto rt = context_->runtime_;

    auto* L_end    = code->CodeLabel();

    buildExpression(left); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->PushInt(1); // ..., left, left, 1
    *code << code->InvokeVirtual(rt.luaValueGetBool); // ..., left, bool
    *code << code->If(Instruction::Compare::NotEqual, L_end); // ..., left

    // false
    *code << code->PopOne(); // ...
    buildExpression(right); // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::pushInt(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushInt(static_cast<int32_t>(expression->getInteger()))
        << code->InvokeSpecial(runtimeRefs.luaValueCtorInt);
}

void ExpressionBytecodeBuilder::pushFloat(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushFloat(static_cast<float>(expression->getFloat()))
        << code->InvokeSpecial(runtimeRefs.luaValueCtorFloat);
}

void ExpressionBytecodeBuilder::pushBool(const ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushInt(expression->getBool() ? 1 : 0)
        << code->InvokeSpecial(runtimeRefs.luaValueCtorBool);
}

void ExpressionBytecodeBuilder::pushString(ExpressionNode* expression) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushString(*expression->getString())
        << code->InvokeSpecial(runtimeRefs.luaValueCtorString);
}

void ExpressionBytecodeBuilder::pushNull() const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->InvokeSpecial(runtimeRefs.luaValueCtorNil);
}

void ExpressionBytecodeBuilder::id(ExpressionNode* expression) const
{
    // TODO Разобраться с тем, что мы храним контекст в 0 слоте локалов
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code-> LoadReference(0)
        << code->PushString(*expression->getString())
        << code->InvokeVirtual(runtimeRefs.luaContextGetLuaValueById);
}

void ExpressionBytecodeBuilder::sum() const
{
    emitStaticCall(context_->runtime_.luaValueAdd);
}

void ExpressionBytecodeBuilder::sub() const
{
    emitStaticCall(context_->runtime_.luaValueSub);
}

void ExpressionBytecodeBuilder::mul() const
{
    emitStaticCall(context_->runtime_.luaValueMul);
}

void ExpressionBytecodeBuilder::div() const
{
    emitStaticCall(context_->runtime_.luaValueDiv);
}

void ExpressionBytecodeBuilder::idiv() const
{
    emitStaticCall(context_->runtime_.luaValueIntegerDiv);
}

void ExpressionBytecodeBuilder::mod() const
{
    emitStaticCall(context_->runtime_.luaValueMod);
}

void ExpressionBytecodeBuilder::pow() const
{
    emitStaticCall(context_->runtime_.luaValuePow);
}

void ExpressionBytecodeBuilder::concat() const
{
    emitStaticCall(context_->runtime_.luaValueConcat);
}

void ExpressionBytecodeBuilder::equal() const
{
    emitStaticCall(context_->runtime_.luaValueEqual);
}

void ExpressionBytecodeBuilder::notEqual() const
{
    equal();
    Not();
}

void ExpressionBytecodeBuilder::lessThan() const
{
    emitStaticCall(context_->runtime_.luaValueLessThan);
}

void ExpressionBytecodeBuilder::lessEqual() const
{
    emitStaticCall(context_->runtime_.luaValueLessEqual);
}

void ExpressionBytecodeBuilder::greaterThan() const
{
    auto* code = context_->attributeCode_;
    *code << code->Swap();
    emitStaticCall(context_->runtime_.luaValueLessThan);
}

void ExpressionBytecodeBuilder::greaterEqual() const
{
    auto* code = context_->attributeCode_;
    *code << code->Swap();
    emitStaticCall(context_->runtime_.luaValueLessEqual);
}

void ExpressionBytecodeBuilder::getFieldByKey() const
{
    auto* code = context_->attributeCode_;
    const auto rt = context_->runtime_;
    *code
        << code->InvokeVirtual(rt.luaValueGetFieldByKey);
}

void ExpressionBytecodeBuilder::unm() const
{
    emitStaticCall(context_->runtime_.luaValueUnMinus);
}

void ExpressionBytecodeBuilder::len() const
{
    emitStaticCall(context_->runtime_.luaValueLen);
}

void ExpressionBytecodeBuilder::Not() const
{
    emitStaticCall(context_->runtime_.luaValueNot);
}


void ExpressionBytecodeBuilder::emitStaticCall(ConstantMethodref* methodref) const
{
    auto* code = context_->attributeCode_;
    *code << code->InvokeStatic(methodref);
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
