#include "generation/ByteCodeBuilder.h"

#include <optional>

#include "node/NodeExpressionModule.h"


#include "jvm/descriptor-method.h"

void ByteCodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = getAttributeCode();

    auto* L_end = code->CodeLabel();

    left->makeBytecode(*this); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(getBoolValueFromLuaValue()); // ..., left, bool
    *code << code->If(Instruction::Compare::Equal, L_end); // ..., left

    // true:
    *code << code->PopOne(); // ...
    right->makeBytecode(*this); // ..., right

    *code << L_end;
}

void ByteCodeBuilder::buildOr(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = getAttributeCode();

    auto* L_end = code->CodeLabel();

    left->makeBytecode(*this); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(getBoolValueFromLuaValue()); // ..., left, bool
    *code << code->If(Instruction::Compare::NotEqual, L_end); // ..., left

    // false
    *code << code->PopOne(); // ...
    right->makeBytecode(*this); // ..., right

    *code << L_end;
}

void ByteCodeBuilder::pushInt(int64_t value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(getIntConstructorForLuaValue());
}

void ByteCodeBuilder::pushFloat(double value)
{
    auto* code = getAttributeCode();
    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(getFloatConstructorForLuaValue());
}

void ByteCodeBuilder::pushBool(bool value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(getBoolConstructorForLuaValue());
}

void ByteCodeBuilder::pushString(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(getStringConstructorForLuaValue());
}

void ByteCodeBuilder::pushNull()
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->InvokeSpecial(getNilConstructorForLuaValue());
}

void ByteCodeBuilder::id(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->LoadReference(getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(getLuaValueByIdMethodFromContext());
}

void ByteCodeBuilder::sum()
{
    emitStaticCall(getAddMethodFromLuaValue());
}

void ByteCodeBuilder::sub()
{
    emitStaticCall(getSubMethodFromLuaValue());
}

void ByteCodeBuilder::mul()
{
    emitStaticCall(getMulMethodFromLuaValue());
}

void ByteCodeBuilder::div()
{
    emitStaticCall(getDivMethodFromLuaValue());
}

void ByteCodeBuilder::idiv()
{
    emitStaticCall(getIntegerDivMethodFromLuaValue());
}

void ByteCodeBuilder::mod()
{
    emitStaticCall(getModMethodFromLuaValue());
}

void ByteCodeBuilder::pow()
{
    emitStaticCall(getPowMethodFromLuaValue());
}

void ByteCodeBuilder::concat()
{
    emitStaticCall(getConcatMethodFromLuaValue());
}

void ByteCodeBuilder::equal()
{
    emitStaticCall(getEqualMethodFromLuaValue());
}

void ByteCodeBuilder::notEqual()
{
    equal();
    booleanNot();
}

void ByteCodeBuilder::lessThan()
{
    emitStaticCall(getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::lessEqual()
{
    emitStaticCall(getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::greaterThan()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::greaterEqual()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::getFieldByKey()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(getFieldByKeyMethodFromLuaValue());
}

void ByteCodeBuilder::call()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(getCallMethodFromLuaValue());
}

void ByteCodeBuilder::unm()
{
    emitStaticCall(getUnMinusMethodFromLuaValue());
}

void ByteCodeBuilder::len()
{
    emitStaticCall(getLengthMethodFromLuaValue());
}

void ByteCodeBuilder::booleanNot()
{
    emitStaticCall(getNotMethodFromLuaValue());
}

void ByteCodeBuilder::tableConstructor(TableFieldList* fieldList)
{
    auto code = getAttributeCode();
    int64_t index = 0;

    *code
        << code->New(getLuaValueClass()) // ..., ref(LuaValue)
        << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue)

    createHashMap(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    for (auto field : *fieldList)
    {
        *code << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap)
        if (field.name != nullptr)
        {
            field.name->makeBytecode(*this);
            // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        else
        {
            pushInt(++index); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        field.value->makeBytecode(*this);
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue), ref(LuaValue)

        *code << code->InvokeVirtual(getPutMethodFromHashMap());
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    }

    *code << code->InvokeVirtual(getTableConstructorForLuaValue()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVararg()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(getGetMethodFromLuaList()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVarargList()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(getSubListMethodFromLuaList()); // ..., ref(List of vararg)
}

void ByteCodeBuilder::emitStaticCall(ConstantMethodref* methodref)
{
    auto* code = getAttributeCode();
    *code << code->InvokeStatic(methodref);
}

void ByteCodeBuilder::createHashMap()
{
    auto* code = getAttributeCode();

    *code
        << code->New(getHashMapClass()) // ..., objectref(HashMap)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(getHashMapConstructor()); // ..., objectref
}

void ByteCodeBuilder::createLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaListClass()) // ..., objectref(LuaList)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(getLuaListConstructor()); // ..., objectref
}

void ByteCodeBuilder::addToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(getAddMethodFromLuaList())
        << code->PopOne(); // отбросить bool
}
