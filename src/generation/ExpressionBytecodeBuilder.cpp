#include "generation/ExpressionBytecodeBuilder.h"

void ExpressionBytecodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = context_->getAttributeCode();

    auto* L_end   = code->CodeLabel();

    left->makeBytecode(*this);  // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(context_->getBoolValueFromLuaValue());  // ..., left, bool
    *code << code->If(Instruction::Compare::Equal, L_end); // ..., left

    // true:
    *code << code->PopOne(); // ...
    right->makeBytecode(*this);  // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::buildOr(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = context_->getAttributeCode();

    auto* L_end    = code->CodeLabel();

    left->makeBytecode(*this); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(context_->getBoolValueFromLuaValue()); // ..., left, bool
    *code << code->If(Instruction::Compare::NotEqual, L_end); // ..., left

    // false
    *code << code->PopOne(); // ...
    right->makeBytecode(*this); // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::pushInt(int64_t value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(context_->getIntConstructorForLuaValue());
}

void ExpressionBytecodeBuilder::pushFloat(double value) const
{
    auto* code = context_->getAttributeCode();
    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(context_->getFloatConstructorForLuaValue());
}

void ExpressionBytecodeBuilder::pushBool(bool value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(context_->getBoolConstructorForLuaValue());
}

void ExpressionBytecodeBuilder::pushString(const std::string& value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(context_->getStringConstructorForLuaValue());
}

void ExpressionBytecodeBuilder::pushNull() const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->InvokeSpecial(context_->getNilConstructorForLuaValue());
}

void ExpressionBytecodeBuilder::id(const std::string& value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code-> LoadReference(context_->getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(context_->getLuaValueByIdMethodFromContext());
}

void ExpressionBytecodeBuilder::sum() const
{
    emitStaticCall(context_->getAddMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::sub() const
{
    emitStaticCall(context_->getSubMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::mul() const
{
    emitStaticCall(context_->getMulMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::div() const
{
    emitStaticCall(context_->getDivMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::idiv() const
{
    emitStaticCall(context_->getIntegerDivMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::mod() const
{
    emitStaticCall(context_->getModMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::pow() const
{
    emitStaticCall(context_->getPowMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::concat() const
{
    emitStaticCall(context_->getConcatMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::equal() const
{
    emitStaticCall(context_->getEqualMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::notEqual() const
{
    equal();
    booleanNot();
}

void ExpressionBytecodeBuilder::lessThan() const
{
    emitStaticCall(context_->getLessThenMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::lessEqual() const
{
    emitStaticCall(context_->getLessEqualMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::greaterThan() const
{
    auto* code = context_->getAttributeCode();
    *code << code->Swap();
    emitStaticCall(context_->getLessThenMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::greaterEqual() const
{
    auto* code = context_->getAttributeCode();
    *code << code->Swap();
    emitStaticCall(context_->getLessEqualMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::getFieldByKey() const
{
    auto* code = context_->getAttributeCode();
    *code
        << code->InvokeVirtual(context_->getFieldByKeyMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::setFieldByKey() const
{
    // TODO реализовать метод setFieldByKey
}

void ExpressionBytecodeBuilder::tableConstructor() const
{
    // TODO реализовать метод tableConstructor
}

void ExpressionBytecodeBuilder::unm() const
{
    emitStaticCall(context_->getUnMinusMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::len() const
{
    emitStaticCall(context_->getLengthMethodFromLuaValue());
}

void ExpressionBytecodeBuilder::booleanNot() const
{
    emitStaticCall(context_->getNotMethodFromLuaValue());
}


void ExpressionBytecodeBuilder::emitStaticCall(ConstantMethodref* methodref) const
{
    auto* code = context_->getAttributeCode();
    *code << code->InvokeStatic(methodref);
}
