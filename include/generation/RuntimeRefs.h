#ifndef LUA_COMPILER_RUNTIME_REFS_H
#define LUA_COMPILER_RUNTIME_REFS_H

#include "jvm/constant-methodref.h"
#include "jvm/constant-class.h"
#include "jvm/class.h"
#include "jvm/descriptor-method.h"
#include "jvm/descriptor-field.h"

using namespace jvm;

struct RuntimeRefs {
    // methods
    ConstantMethodref* luaValueCreate = nullptr;
    ConstantMethodref* integerValueOf = nullptr;
    ConstantMethodref* floatValueOf = nullptr;
    ConstantMethodref* booleanValueOf = nullptr;

    void init(jvm::Class* owner) {
        // Integer.valueOf(int) : Integer
        integerValueOf = owner->getOrCreateMethodrefConstant(
            "java/lang/Integer",
            "valueOf",
            DescriptorMethod(
                DescriptorField("java/lang/Integer"),
                {{DescriptorMethod::Int}}
            )
        );

        // Float.valueOf(float) : Float
        integerValueOf = owner->getOrCreateMethodrefConstant(
            "java/lang/Float",
            "valueOf",
            DescriptorMethod(
                DescriptorField("java/lang/Float"),
                {{DescriptorMethod::Float}}
            )
        );

        // Boolean.valueOf(boolean) : Boolean
        integerValueOf = owner->getOrCreateMethodrefConstant(
            "java/lang/Boolean",
            "valueOf",
            DescriptorMethod(
                DescriptorField("java/lang/Boolean"),
                {{DescriptorMethod::Boolean}}
            )
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