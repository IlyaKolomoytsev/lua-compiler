#include "generation/ByteCodeBuilder.h"

void ByteCodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
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

void ByteCodeBuilder::buildOr(const ExpressionNode* left, const ExpressionNode* right)
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

void ByteCodeBuilder::pushInt(int64_t value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(context_->getIntConstructorForLuaValue());
}

void ByteCodeBuilder::pushFloat(double value) const
{
    auto* code = context_->getAttributeCode();
    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(context_->getFloatConstructorForLuaValue());
}

void ByteCodeBuilder::pushBool(bool value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(context_->getBoolConstructorForLuaValue());
}

void ByteCodeBuilder::pushString(const std::string& value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(context_->getStringConstructorForLuaValue());
}

void ByteCodeBuilder::pushNull() const
{
    auto* code = context_->getAttributeCode();

    *code
        << code->New(context_->getLuaValueClass())
        << code->Duplicate()
        << code->InvokeSpecial(context_->getNilConstructorForLuaValue());
}

void ByteCodeBuilder::id(const std::string& value) const
{
    auto* code = context_->getAttributeCode();

    *code
        << code-> LoadReference(context_->getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(context_->getLuaValueByIdMethodFromContext());
}

void ByteCodeBuilder::sum() const
{
    emitStaticCall(context_->getAddMethodFromLuaValue());
}

void ByteCodeBuilder::sub() const
{
    emitStaticCall(context_->getSubMethodFromLuaValue());
}

void ByteCodeBuilder::mul() const
{
    emitStaticCall(context_->getMulMethodFromLuaValue());
}

void ByteCodeBuilder::div() const
{
    emitStaticCall(context_->getDivMethodFromLuaValue());
}

void ByteCodeBuilder::idiv() const
{
    emitStaticCall(context_->getIntegerDivMethodFromLuaValue());
}

void ByteCodeBuilder::mod() const
{
    emitStaticCall(context_->getModMethodFromLuaValue());
}

void ByteCodeBuilder::pow() const
{
    emitStaticCall(context_->getPowMethodFromLuaValue());
}

void ByteCodeBuilder::concat() const
{
    emitStaticCall(context_->getConcatMethodFromLuaValue());
}

void ByteCodeBuilder::equal() const
{
    emitStaticCall(context_->getEqualMethodFromLuaValue());
}

void ByteCodeBuilder::notEqual() const
{
    equal();
    booleanNot();
}

void ByteCodeBuilder::lessThan() const
{
    emitStaticCall(context_->getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::lessEqual() const
{
    emitStaticCall(context_->getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::greaterThan() const
{
    auto* code = context_->getAttributeCode();
    *code << code->Swap();
    emitStaticCall(context_->getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::greaterEqual() const
{
    auto* code = context_->getAttributeCode();
    *code << code->Swap();
    emitStaticCall(context_->getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::getFieldByKey() const
{
    auto* code = context_->getAttributeCode();
    *code
        << code->InvokeVirtual(context_->getFieldByKeyMethodFromLuaValue());
}

void ByteCodeBuilder::setFieldByKey() const
{
    // TODO реализовать метод setFieldByKey
}

void ByteCodeBuilder::tableConstructor() const
{
    // TODO реализовать метод tableConstructor
}

void ByteCodeBuilder::unm() const
{
    emitStaticCall(context_->getUnMinusMethodFromLuaValue());
}

void ByteCodeBuilder::len() const
{
    emitStaticCall(context_->getLengthMethodFromLuaValue());
}

void ByteCodeBuilder::booleanNot() const
{
    emitStaticCall(context_->getNotMethodFromLuaValue());
}


void ByteCodeBuilder::emitStaticCall(ConstantMethodref* methodref) const
{
    auto* code = context_->getAttributeCode();
    *code << code->InvokeStatic(methodref);
}
