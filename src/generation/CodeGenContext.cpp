#include "generation/CodeGenContext.h"
#define LUA_VALUE "com/luajvm/LuaValue"
#

DescriptorField luaValueDescriptor = DescriptorField("com/luajvm/LuaValue");

CodeGenContext::CodeGenContext(Class* currentClass) : class_(currentClass)
{
}

void CodeGenContext::setMethod(Method* method)
{
    currentMethod_ = method;
    currentAttributeCode_ = method->getCodeAttribute();
}

ConstantClass* CodeGenContext::getLuaValueClass()
{
    if (luaValueClass == nullptr)
    {
        luaValueClass = getClass()->getOrCreateClassConstant("com/luajvm/LuaValue");
    }
    return luaValueClass;
}

ConstantMethodref* CodeGenContext::getNilConstructorForLuaValue()
{
    if (luaValueCtorNil == nullptr)
    {
        luaValueCtorNil = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {}) // ()V
        );
    }
    return luaValueCtorNil;
}

ConstantMethodref* CodeGenContext::getIntConstructorForLuaValue()
{
    if (luaValueCtorInt == nullptr)
    {
        luaValueCtorInt = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Int})
        );
    }
    return luaValueCtorInt;
}

ConstantMethodref* CodeGenContext::getFloatConstructorForLuaValue()
{
    if (luaValueCtorFloat == nullptr)
    {
        luaValueCtorFloat = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Float})
        );
    }
    return luaValueCtorFloat;
}

ConstantMethodref* CodeGenContext::getBoolConstructorForLuaValue()
{
    if (luaValueCtorBool == nullptr)
    {
        luaValueCtorBool = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Boolean})
        );
    }
    return luaValueCtorBool;
}

ConstantMethodref* CodeGenContext::getStringConstructorForLuaValue()
{
    if (luaValueCtorString == nullptr)
    {
        luaValueCtorString = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorField("java/lang/String")})
        );
    }
    return luaValueCtorString;
}

ConstantMethodref* CodeGenContext::getAddMethodFromLuaValue()
{
    if (luaValueAdd == nullptr)
    {
        luaValueAdd = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "add",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueAdd;
}

ConstantMethodref* CodeGenContext::getSubMethodFromLuaValue()
{
    if (luaValueSub == nullptr)
    {
        luaValueSub = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "sub",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueSub;
}

ConstantMethodref* CodeGenContext::getMulMethodFromLuaValue()
{
    if (luaValueMul == nullptr)
    {
        luaValueMul = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "mul",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueMul;
}

ConstantMethodref* CodeGenContext::getDivMethodFromLuaValue()
{
    if (luaValueDiv == nullptr)
    {
        luaValueDiv = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "div",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueDiv;
}

ConstantMethodref* CodeGenContext::getIntegerDivMethodFromLuaValue()
{
    if (luaValueIntegerDiv == nullptr)
    {
        luaValueIntegerDiv = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "idiv",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueIntegerDiv;
}

ConstantMethodref* CodeGenContext::getModMethodFromLuaValue()
{
    if (luaValueMod == nullptr)
    {
        luaValueMod = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "mod",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueMod;
}

ConstantMethodref* CodeGenContext::getPowMethodFromLuaValue()
{
    if (luaValuePow == nullptr)
    {
        luaValuePow = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "pow",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValuePow;
}

ConstantMethodref* CodeGenContext::getConcatMethodFromLuaValue()
{
    if (luaValueConcat)
    {
        luaValueConcat = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "concat",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueConcat;
}

ConstantMethodref* CodeGenContext::getEqualMethodFromLuaValue()
{
    if (luaValueEqual == nullptr)
    {
        luaValueEqual = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "equal",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueEqual;
}

ConstantMethodref* CodeGenContext::getLessThenMethodFromLuaValue()
{
    if (luaValueLessThan == nullptr)
    {
        luaValueLessThan = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "lt",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueLessThan;
}

ConstantMethodref* CodeGenContext::getLessEqualMethodFromLuaValue()
{
    if (luaValueLessEqual == nullptr)
    {
        luaValueLessEqual = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "le",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueLessEqual;
}

ConstantMethodref* CodeGenContext::getNotMethodFromLuaValue()
{
    if (luaValueNot == nullptr)
    {
        luaValueNot = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "not",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueNot;
}

ConstantMethodref* CodeGenContext::getBoolValueFromLuaValue()
{
    if (luaValueGetBool == nullptr)
    {
        luaValueGetBool = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "getBoolValueSave",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {}
            )
        );
    }
    return luaValueGetBool;
}

ConstantMethodref* CodeGenContext::getFieldByKeyMethodFromLuaValue()
{
    if (luaValueGetFieldByKey == nullptr)
    {
        luaValueGetFieldByKey = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "index",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueGetFieldByKey;
}

ConstantMethodref* CodeGenContext::getUnMinusMethodFromLuaValue()
{
    if (luaValueUnMinus == nullptr)
    {
        luaValueUnMinus = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "unm",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueUnMinus;
}

ConstantMethodref* CodeGenContext::getLengthMethodFromLuaValue()
{
    if (luaValueLen == nullptr)
    {
        luaValueLen = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "len",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaValueLen;
}

ConstantMethodref* CodeGenContext::getLuaValueByIdMethodFromContext()
{
    if (luaContextGetLuaValueById == nullptr)
    {
        luaContextGetLuaValueById = getClass()->getOrCreateMethodrefConstant(
            "com/luajvm/LuaContext",
            "get",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {"java/lang/String"}
                }
            )
        );
    }
    return luaContextGetLuaValueById;
}
