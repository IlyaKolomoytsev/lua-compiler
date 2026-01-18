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
            jvm::DescriptorMethod(
                DescriptorField("com/luajvm/LuaValue"),
                {{"java/lang/Object"}}
            )
        );
    }
};
#endif //LUA_COMPILER_RUNTIME_REFS_H
