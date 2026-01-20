#include "generation/CodeGenContext.h"

#include <optional>

#include "jvm/descriptor-field.h"
#include "jvm/descriptor-method.h"
#define LUA_VALUE "com/luajvm/LuaValue"
#define LUA_LIST "com/luajvm/LuaValue"

#define HASH_MAP "java/util/HashMap"
#define OBJECT "java/lang/Object"
#define STRING "java/lang/String"
#define LIST "java/util/List"


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
            DescriptorMethod(std::nullopt, {DescriptorField(STRING)})
        );
    }
    return luaValueCtorString;
}

ConstantMethodref* CodeGenContext::getTableConstructorForLuaValue()
{
    if (luaValueCtorTable == nullptr)
    {
        luaValueCtorTable = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(
                std::nullopt, {DescriptorField(HASH_MAP)}
            )
        );
    }
    return luaValueCtorTable;
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

ConstantClass* CodeGenContext::getHashMapClass()
{
    if (hashMapClass == nullptr)
    {
        hashMapClass = getClass()->getOrCreateClassConstant(HASH_MAP);
    }
    return hashMapClass;
}

ConstantMethodref* CodeGenContext::getHashMapConstructor()
{
    if (hashMapCtor == nullptr)
    {
        hashMapCtor = getClass()->getOrCreateMethodrefConstant(
            HASH_MAP,
            "<init>",
            DescriptorMethod(std::nullopt, {})
        );
    }
    return hashMapCtor;
}

ConstantMethodref* CodeGenContext::getPutMethodFromHashMap()
{
    if (hashMapPutMethod == nullptr)
    {
        hashMapPutMethod = getClass()->getOrCreateMethodrefConstant(
            HASH_MAP,
            "put",
            DescriptorMethod(
                DescriptorField(OBJECT),
                {
                    {OBJECT},
                    {OBJECT}
                }
            )
        );
    }
    return hashMapPutMethod;
}

ConstantClass* CodeGenContext::getLuaListClass()
{
    if (luaListClass == nullptr)
    {
        luaListClass = getClass()->getOrCreateClassConstant(LUA_LIST);
    }
    return luaListClass;
}

ConstantMethodref* CodeGenContext::getLuaListConstructor()
{
    if (luaListCtor == nullptr)
    {
        luaListCtor = getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "<init>",
            DescriptorMethod(std::nullopt, {})
        );
    }
    return luaListCtor;
}

ConstantMethodref* CodeGenContext::getGetMethodFromLuaList()
{
    if (listGetMethod == nullptr)
    {
        listGetMethod = getClass()->getOrCreateMethodrefConstant(
            LIST,
            "get",
            DescriptorMethod(
                DescriptorField(OBJECT),
                {{Descriptor::Int}}
            )
        );
    }
    return listGetMethod;
}

ConstantMethodref* CodeGenContext::getSubListMethodFromLuaList()
{
    if (luaListSubList == nullptr)
    {
        luaListSubList = getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "subList",
            DescriptorMethod(
                DescriptorField(LUA_LIST),
                {{Descriptor::Int}}
            )
        );
    }
    return luaListSubList;
}

ConstantMethodref* CodeGenContext::getFirstMethodFromList()
{
    if (listGetFirstMethod == nullptr)
    {
        listGetFirstMethod = getClass()->getOrCreateMethodrefConstant(
            LIST,
            "getFirst",
            DescriptorMethod(
                DescriptorField(OBJECT),
                {}
            )
        );
    }
    return listGetFirstMethod;
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
                    {STRING}
                }
            )
        );
    }
    return luaContextGetLuaValueById;
}
