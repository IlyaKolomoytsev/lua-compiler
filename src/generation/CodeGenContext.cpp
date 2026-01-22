#include "generation/CodeGenContext.h"

#include <optional>

#include "jvm/descriptor-field.h"
#include "jvm/descriptor-method.h"
#include "jvm/method.h"
#define LUA_VALUE "com/luajvm/LuaValue"
#define LUA_LIST "com/luajvm/LuaList"
#define LUA_CONTEXT "com/luajvm/LuaContext"

#define HASH_MAP "java/util/HashMap"
#define MAP "java/util/Map"
#define OBJECT "java/lang/Object"
#define STRING "java/lang/String"
#define LIST "java/util/List"
#define COLLECTION "java/util/Collection"


DescriptorField luaValueDescriptor = DescriptorField("com/luajvm/LuaValue");

CodeGenContext::CodeGenContext(Class* currentClass, Method* currentMethod) : class_(currentClass),
                                                                             currentMethod_(currentMethod)
{
    currentAttributeCode_ = currentMethod_->getCodeAttribute();
}

ConstantClass* CodeGenContext::getLuaValueClass()
{
    if (luaValueClass == nullptr)
    {
        luaValueClass = getClass()->getOrCreateClassConstant(LUA_VALUE);
    }
    return luaValueClass;
}

ConstantClass* CodeGenContext::getLuaContextClass()
{
    if (luaContextClass == nullptr)
    {
        luaContextClass = getClass()->getOrCreateClassConstant(LUA_CONTEXT);
    }
    return luaContextClass;
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
            DescriptorMethod(std::nullopt, {DescriptorMethod::Long})
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
            DescriptorMethod(std::nullopt, {DescriptorMethod::Double})
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
                std::nullopt, {DescriptorField(MAP)}
            )
        );
    }
    return luaValueCtorTable;
}

ConstantMethodref* CodeGenContext::getConstructorForLuaContext()
{
    if (luaContextCtor == nullptr)
    {
        luaContextCtor = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "<init>",
            DescriptorMethod(
                std::nullopt, {}
            )
        );
    }
    return luaContextCtor;
}

ConstantMethodref* CodeGenContext::getConstructorForLuaContextWithParent()
{
    if (luaContextWithParentCtor == nullptr)
    {
        luaContextWithParentCtor = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "<init>",
            DescriptorMethod(
                std::nullopt, {{LUA_CONTEXT}}
            )
        );
    }
    return luaContextWithParentCtor;
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
            "eq",
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
                Descriptor::Boolean,
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

ConstantMethodref* CodeGenContext::getCallMethodFromLuaValue()
{
    if (luaValueCall == nullptr)
    {
        luaValueCall = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "call",
            DescriptorMethod(
                DescriptorField(LUA_LIST),
                {
                    {LUA_LIST}
                }
            )
        );
    }
    return luaValueCall;
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

ConstantMethodref* CodeGenContext::getAssignmentMethodFromLuaValue()
{
    if (luaAssignmentMethod == nullptr)
    {
        luaAssignmentMethod = getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "assignment",
            DescriptorMethod(
                std::nullopt,
                {
                    {LUA_LIST},
                    {LUA_LIST}
                }
            )
        );
    }
    return luaAssignmentMethod;
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
            LUA_LIST,
            "get",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
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

ConstantMethodref* CodeGenContext::getFirstMethodFromLuaList()
{
    if (listGetFirstMethod == nullptr)
    {
        listGetFirstMethod = getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "getFirst",
            DescriptorMethod(
                DescriptorField(OBJECT),
                {}
            )
        );
    }
    return listGetFirstMethod;
}

ConstantMethodref* CodeGenContext::getAddMethodFromLuaList()
{
    if (luaListAddMethod == nullptr)
    {
        luaListAddMethod = getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "add",
            DescriptorMethod(
                Descriptor::Boolean,
                {{OBJECT}}
            )
        );
    }
    return luaListAddMethod;
}

ConstantMethodref* CodeGenContext::getAddAllMethodFromLuaList()
{
    if (listAddAllMethod == nullptr)
    {
        listAddAllMethod = getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "addAll",
            DescriptorMethod(
                Descriptor::Boolean,
                {{COLLECTION}}
            )
        );
    }
    return listAddAllMethod;
}

void CodeGenContext::setContextIndexInLocals(uint16_t index)
{
    contextIndexInLocals_ = index;
    contextIndexIsInitialized_ = true;
}

uint16_t CodeGenContext::getContextIndexInLocals() const
{
    if (!contextIndexIsInitialized_)
    {
        throw std::logic_error("Index of context instance not initialized");
    }
    return contextIndexInLocals_;
}

void CodeGenContext::setArgsIndexInLocals(uint16_t index)
{
    argsIndexInLocals_ = index;
    argsIndexIsInitialized_ = true;
}

uint16_t CodeGenContext::getArgsIndexInLocals() const
{
    if (!argsIndexIsInitialized_)
    {
        throw std::logic_error("Index of args list not initialized");
    }
    return contextIndexInLocals_;
}

void CodeGenContext::setStartIndexForVarargInListArgs(int32_t index)
{
    startIndexForVarargInListArgs_ = index;
    startIndexForVarargIsInitialized_ = true;
}

int32_t CodeGenContext::getStartIndexForVarargInListArgs() const
{
    if (!startIndexForVarargIsInitialized_)
    {
        throw std::logic_error("Index of vararg start index not initialized");
    }
    return startIndexForVarargInListArgs_;
}

ConstantMethodref* CodeGenContext::getLuaValueByIdMethodFromContext()
{
    if (luaContextGetLuaValueById == nullptr)
    {
        luaContextGetLuaValueById = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
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

ConstantMethodref* CodeGenContext::getLuaValueByIdOrCreateNewMethodFromContext()
{
    if (luaContextGetLuaValueByIdOrCreateNew == nullptr)
    {
        luaContextGetLuaValueByIdOrCreateNew = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "getOrCreateGlobal",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {
                    {STRING}
                }
            )
        );
    }
    return luaContextGetLuaValueByIdOrCreateNew;
}

ConstantMethodref* CodeGenContext::setLuaValueByIdMethodFromContext()
{
    if (luaContextSetLuaValueById == nullptr)
    {
        luaContextSetLuaValueById = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "set",
            DescriptorMethod(
                std::nullopt,
                {
                    {STRING},
                    {LUA_VALUE}
                }
            )
        );
    }
    return luaContextSetLuaValueById;
}

ConstantMethodref* CodeGenContext::getDeclareLocalByIdMethodFromContext()
{
    if (luaContextDeclareLocalById == nullptr)
    {
        luaContextDeclareLocalById = getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "declareLocal",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {{STRING}}
            )
        );
    }
    return luaContextDeclareLocalById;
}
