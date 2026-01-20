#include "generation/ExpressionBytecodeBuilder.h"

void ExpressionBytecodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = context_->attributeCode_;
    const auto rt = context_->runtime_;

    auto* L_end   = code->CodeLabel();

    left->makeBytecode(*this);  // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->PushInt(1);  // ..., left, left, 1
    *code << code->InvokeVirtual(rt.luaValueGetBool);  // ..., left, bool
    *code << code->If(Instruction::Compare::Equal, L_end); // ..., left

    // true:
    *code << code->PopOne(); // ...
    right->makeBytecode(*this);  // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::buildOr(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = context_->attributeCode_;
    auto rt = context_->runtime_;

    auto* L_end    = code->CodeLabel();

    left->makeBytecode(*this); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->PushInt(1); // ..., left, left, 1
    *code << code->InvokeVirtual(rt.luaValueGetBool); // ..., left, bool
    *code << code->If(Instruction::Compare::NotEqual, L_end); // ..., left

    // false
    *code << code->PopOne(); // ...
    right->makeBytecode(*this); // ..., right

    *code << L_end;
}

void ExpressionBytecodeBuilder::pushInt(int64_t value) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushInt(static_cast<int32_t>(value))
        << code->InvokeSpecial(runtimeRefs.luaValueCtorInt);
}

void ExpressionBytecodeBuilder::pushFloat(double value) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushFloat(static_cast<float>(value))
        << code->InvokeSpecial(runtimeRefs.luaValueCtorFloat);
}

void ExpressionBytecodeBuilder::pushBool(bool value) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(runtimeRefs.luaValueCtorBool);
}

void ExpressionBytecodeBuilder::pushString(const std::string& value) const
{
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code->New(runtimeRefs.luaValueClass)
        << code->Duplicate()
        << code->PushString(value)
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

void ExpressionBytecodeBuilder::id(const std::string& value) const
{
    // TODO Разобраться с тем, что мы храним контекст в 0 слоте локалов
    auto* code = context_->attributeCode_;
    auto runtimeRefs = context_->runtime_;

    *code
        << code-> LoadReference(0)
        << code->PushString(value)
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
