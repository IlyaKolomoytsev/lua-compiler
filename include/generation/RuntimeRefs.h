#ifndef LUA_COMPILER_RUNTIME_REFS_H
#define LUA_COMPILER_RUNTIME_REFS_H

#include "jvm/constant-methodref.h"
#include "jvm/constant-class.h"
#include "jvm/class.h"
#include "jvm/descriptor-method.h"
#include "jvm/descriptor-field.h"

using namespace jvm;

struct RuntimeRefs
{
    // classes
    ConstantClass* luaValueClass = nullptr;

    // constructors
    ConstantMethodref* luaValueCtorNil = nullptr;
    ConstantMethodref* luaValueCtorInt = nullptr;
    ConstantMethodref* luaValueCtorFloat = nullptr;
    ConstantMethodref* luaValueCtorBool = nullptr;
    ConstantMethodref* luaValueCtorString = nullptr;

    // methods
    ConstantMethodref* luaValueCreate = nullptr;
    ConstantMethodref* luaValueAdd = nullptr;
    ConstantMethodref* luaValueSub = nullptr;
    ConstantMethodref* luaValueMul = nullptr;
    ConstantMethodref* luaValueDiv = nullptr;
    ConstantMethodref* luaValueIntegerDiv = nullptr;
    ConstantMethodref* luaValueMod = nullptr;
    ConstantMethodref* luaValuePow = nullptr;
    ConstantMethodref* luaValueConcat = nullptr;
    ConstantMethodref* luaValueEqual = nullptr;
    ConstantMethodref* luaValueLessThan = nullptr;
    ConstantMethodref* luaValueLessEqual = nullptr;
    ConstantMethodref* luaValueNot = nullptr;
    ConstantMethodref* luaValueGetBool = nullptr;
    ConstantMethodref* luaValueGetFieldByKey = nullptr;

    ConstantMethodref* luaValueUnMinus = nullptr;
    ConstantMethodref* luaValueLen = nullptr;

    ConstantMethodref* luaContextGetLuaValueById = nullptr;

    // Field descriptors
    DescriptorField luaValueDescriptor = DescriptorField("com/luajvm/LuaValue");


    void init(Class* owner)
    {
        luaValueClass = owner->getOrCreateClassConstant("com/luajvm/LuaValue");

        luaValueCtorNil = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "<init>",
            DescriptorMethod(std::nullopt, {}) // ()V
        );

        luaValueCtorInt = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Int})
        );

        luaValueCtorFloat = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Float})
        );

        luaValueCtorBool = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Boolean})
        );

        luaValueCtorString = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorField("java/lang/String")})
        );

        // LuaValue.create(Object) : LuaValue
        luaValueCreate = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "create",
            DescriptorMethod(
                DescriptorField("com/luajvm/LuaValue"),
                {{"java/lang/Object"}}
            )
        );

        // LuaValue.add(LuaValue, LuaValue): LuaValue
        luaValueAdd = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "add",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.sub(LuaValue, LuaValue): LuaValue
        luaValueSub = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "sub",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.mul(LuaValue, LuaValue): LuaValue
        luaValueMul = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "mul",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.div(LuaValue, LuaValue): LuaValue
        luaValueDiv = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "div",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.idiv(LuaValue, LuaValue): LuaValue
        luaValueIntegerDiv = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "idiv",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.mod(LuaValue, LuaValue): LuaValue
        luaValueMod = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "mod",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.pow(LuaValue, LuaValue): LuaValue
        luaValuePow = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "pow",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.concat(LuaValue, LuaValue): LuaValue
        luaValueConcat = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "concat",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.eq(LuaValue, LuaValue): LuaValue
        luaValueEqual = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "eq",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.le(LuaValue, LuaValue): LuaValue
        luaValueLessEqual = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "le",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.lt(LuaValue, LuaValue): LuaValue
        luaValueLessThan = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "lt",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}, {luaValueDescriptor}}));

        // LuaValue.unm(LuaValue): LuaValue
        luaValueUnMinus = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "unm",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}}));

        // LuaValue.len(LuaValue): LuaValue
        luaValueLen = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "len",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}}));

        // LuaValue.not(LuaValue): LuaValue
        luaValueNot = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "not",
            DescriptorMethod(
                luaValueDescriptor,
                {{luaValueDescriptor}}));

        // LuaValue.getBoolValue(LuaValue): boolean
        luaValueGetBool = owner->getOrCreateMethodrefConstant(
            "com/luajvm/LuaValue",
            "getBoolValue",
            DescriptorMethod(
                DescriptorField::Boolean,
                {{DescriptorField::Boolean}}));

    }
};
#endif //LUA_COMPILER_RUNTIME_REFS_H
