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

CodeGenContext::CodeGenContext(Class* currentClass, Method* currentMethod) : LuaValue(this), LuaContext(this),
                                                                             LuaList(this), HashMap(this),
                                                                             class_(currentClass),
                                                                             currentMethod_(currentMethod)
{
    currentAttributeCode_ = currentMethod_->getCodeAttribute();
}

ConstantClass* CodeGenContext::LuaValue_base::getLuaValueClass()
{
    if (luaValueClass == nullptr)
    {
        luaValueClass = getContext()->getClass()->getOrCreateClassConstant(LUA_VALUE);
    }
    return luaValueClass;
}

ConstantClass* CodeGenContext::LuaContext_base::getLuaContextClass()
{
    if (luaContextClass == nullptr)
    {
        luaContextClass = getContext()->getClass()->getOrCreateClassConstant(LUA_CONTEXT);
    }
    return luaContextClass;
}

ConstantClass* CodeGenContext::LuaList_base::getLuaListClass()
{
    if (luaListClass == nullptr)
    {
        luaListClass = getContext()->getClass()->getOrCreateClassConstant(LUA_LIST);
    }
    return luaListClass;
}

ConstantClass* CodeGenContext::HashMap_base::getHashMapClass()
{
    if (hashMapClass == nullptr)
    {
        hashMapClass = getContext()->getClass()->getOrCreateClassConstant(HASH_MAP);
    }
    return hashMapClass;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getNilConstructorForLuaValue()
{
    if (luaValueCtorNil == nullptr)
    {
        luaValueCtorNil = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {}) // ()V
        );
    }
    return luaValueCtorNil;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getIntConstructorForLuaValue()
{
    if (luaValueCtorInt == nullptr)
    {
        luaValueCtorInt = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Long})
        );
    }
    return luaValueCtorInt;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getFloatConstructorForLuaValue()
{
    if (luaValueCtorFloat == nullptr)
    {
        luaValueCtorFloat = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Double})
        );
    }
    return luaValueCtorFloat;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getBoolConstructorForLuaValue()
{
    if (luaValueCtorBool == nullptr)
    {
        luaValueCtorBool = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorMethod::Boolean})
        );
    }
    return luaValueCtorBool;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getStringConstructorForLuaValue()
{
    if (luaValueCtorString == nullptr)
    {
        luaValueCtorString = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(std::nullopt, {DescriptorField(STRING)})
        );
    }
    return luaValueCtorString;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Constructors_base::getTableConstructorForLuaValue()
{
    if (luaValueCtorTable == nullptr)
    {
        luaValueCtorTable = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_VALUE,
            "<init>",
            DescriptorMethod(
                std::nullopt, {DescriptorField(MAP)}
            )
        );
    }
    return luaValueCtorTable;
}

ConstantMethodref* CodeGenContext::LuaContext_base::Constructors_base::getConstructorForLuaContext()
{
    if (luaContextCtor == nullptr)
    {
        luaContextCtor = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "<init>",
            DescriptorMethod(
                std::nullopt, {}
            )
        );
    }
    return luaContextCtor;
}

ConstantMethodref* CodeGenContext::LuaContext_base::Constructors_base::getConstructorForLuaContextWithParent()
{
    if (luaContextWithParentCtor == nullptr)
    {
        luaContextWithParentCtor = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "<init>",
            DescriptorMethod(
                std::nullopt, {{LUA_CONTEXT}}
            )
        );
    }
    return luaContextWithParentCtor;
}

ConstantMethodref* CodeGenContext::LuaList_base::Constructors_base::getLuaListConstructor()
{
    if (luaListCtor == nullptr)
    {
        luaListCtor = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "<init>",
            DescriptorMethod(std::nullopt, {})
        );
    }
    return luaListCtor;
}

ConstantMethodref* CodeGenContext::HashMap_base::Constructors_base::getHashMapConstructor()
{
    if (hashMapCtor == nullptr)
    {
        hashMapCtor = getHashMap()->getContext()->getClass()->getOrCreateMethodrefConstant(
            HASH_MAP,
            "<init>",
            DescriptorMethod(std::nullopt, {})
        );
    }
    return hashMapCtor;
}

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getAddMethodFromLuaValue()
{
    if (luaValueAdd == nullptr)
    {
        luaValueAdd = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getSubMethodFromLuaValue()
{
    if (luaValueSub == nullptr)
    {
        luaValueSub = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getMulMethodFromLuaValue()
{
    if (luaValueMul == nullptr)
    {
        luaValueMul = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getDivMethodFromLuaValue()
{
    if (luaValueDiv == nullptr)
    {
        luaValueDiv = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getIntegerDivMethodFromLuaValue()
{
    if (luaValueIntegerDiv == nullptr)
    {
        luaValueIntegerDiv = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getModMethodFromLuaValue()
{
    if (luaValueMod == nullptr)
    {
        luaValueMod = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getPowMethodFromLuaValue()
{
    if (luaValuePow == nullptr)
    {
        luaValuePow = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getConcatMethodFromLuaValue()
{
    if (luaValueConcat)
    {
        luaValueConcat = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getEqualMethodFromLuaValue()
{
    if (luaValueEqual == nullptr)
    {
        luaValueEqual = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getLessThenMethodFromLuaValue()
{
    if (luaValueLessThan == nullptr)
    {
        luaValueLessThan = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getLessEqualMethodFromLuaValue()
{
    if (luaValueLessEqual == nullptr)
    {
        luaValueLessEqual = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getNotMethodFromLuaValue()
{
    if (luaValueNot == nullptr)
    {
        luaValueNot = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getBoolValueFromLuaValue()
{
    if (luaValueGetBool == nullptr)
    {
        luaValueGetBool = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getFieldByKeyMethodFromLuaValue()
{
    if (luaValueGetFieldByKey == nullptr)
    {
        luaValueGetFieldByKey = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getCallMethodFromLuaValue()
{
    if (luaValueCall == nullptr)
    {
        luaValueCall = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getUnMinusMethodFromLuaValue()
{
    if (luaValueUnMinus == nullptr)
    {
        luaValueUnMinus = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getLengthMethodFromLuaValue()
{
    if (luaValueLen == nullptr)
    {
        luaValueLen = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_base::Methods_base::getAssignmentMethodFromLuaValue()
{
    if (luaValueAssignmentMethod == nullptr)
    {
        luaValueAssignmentMethod = getLuaValue()->getContext()->getClass()->getOrCreateMethodrefConstant(
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
    return luaValueAssignmentMethod;
}

ConstantMethodref* CodeGenContext::LuaList_base::Methods_base::getGetMethodFromLuaList()
{
    if (luaListGetMethod == nullptr)
    {
        luaListGetMethod = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "get",
            DescriptorMethod(
                DescriptorField(LUA_VALUE),
                {{Descriptor::Int}}
            )
        );
    }
    return luaListGetMethod;
}

ConstantMethodref* CodeGenContext::LuaList_base::Methods_base::getSubListMethodFromLuaList()
{
    if (luaListSubList == nullptr)
    {
        luaListSubList = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaList_base::Methods_base::getFirstMethodFromLuaList()
{
    if (luaListGetFirstMethod == nullptr)
    {
        luaListGetFirstMethod = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "getFirst",
            DescriptorMethod(
                DescriptorField(OBJECT),
                {}
            )
        );
    }
    return luaListGetFirstMethod;
}

ConstantMethodref* CodeGenContext::LuaList_base::Methods_base::getAddMethodFromLuaList()
{
    if (luaListAddMethod == nullptr)
    {
        luaListAddMethod = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaList_base::Methods_base::getAddAllMethodFromLuaList()
{
    if (luaListAddAllMethod == nullptr)
    {
        luaListAddAllMethod = getLuaList()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_LIST,
            "addAll",
            DescriptorMethod(
                Descriptor::Boolean,
                {{COLLECTION}}
            )
        );
    }
    return luaListAddAllMethod;
}

ConstantMethodref* CodeGenContext::HashMap_base::Methods_base::getPutMethodFromHashMap()
{
    if (hashMapPutMethod == nullptr)
    {
        hashMapPutMethod = getHashMap()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_base::Methods_base::getParentContextMethodFromContext()
{
    if (luaContextGetParent == nullptr)
    {
        luaContextGetParent = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
            LUA_CONTEXT,
            "getParent",
            DescriptorMethod(
                DescriptorField(LUA_CONTEXT),
                {}
            )
        );
    }
    return luaContextGetParent;
}

ConstantMethodref* CodeGenContext::LuaContext_base::Methods_base::getLuaValueByIdMethodFromContext()
{
    if (luaContextGetLuaValueById == nullptr)
    {
        luaContextGetLuaValueById = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_base::Methods_base::getLuaValueByIdOrCreateNewMethodFromContext()
{
    if (luaContextGetLuaValueByIdOrCreateNew == nullptr)
    {
        luaContextGetLuaValueByIdOrCreateNew = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_base::Methods_base::setLuaValueByIdMethodFromContext()
{
    if (luaContextSetLuaValueById == nullptr)
    {
        luaContextSetLuaValueById = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_base::Methods_base::getDeclareLocalByIdMethodFromContext()
{
    if (luaContextDeclareLocalById == nullptr)
    {
        luaContextDeclareLocalById = getLuaContext()->getContext()->getClass()->getOrCreateMethodrefConstant(
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
