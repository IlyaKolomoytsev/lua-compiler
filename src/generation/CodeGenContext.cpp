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

CodeGenContext::CodeGenContext(Class* currentClass, Method* currentMethod) : luaValue(this), luaContext(this),
                                                                             luaList(this), hashMap(this),
                                                                             class_(currentClass),
                                                                             currentMethod_(currentMethod)
{
    currentAttributeCode_ = currentMethod_->getCodeAttribute();
}

CodeGenContext::LuaValue_::LuaValue_(CodeGenContext* context) : ContextProvider(context), constructor(context),
                                                                method(context)
{
}

CodeGenContext::LuaValue_::Constructors_::Constructors_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::LuaValue_::Methods_::Methods_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::LuaList_::LuaList_(CodeGenContext* context) : ContextProvider(context), constructor(context),
                                                              method(context)
{
}

CodeGenContext::LuaList_::Constructors_::Constructors_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::LuaList_::Methods_::Methods_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::LuaContext_::LuaContext_(CodeGenContext* context) : ContextProvider(context), constructor(context),
                                                                    method(context)
{
}

CodeGenContext::LuaContext_::Constructors_::Constructors_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::LuaContext_::Methods_::Methods_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::HashMap_::HashMap_(CodeGenContext* context) : ContextProvider(context), constructor(context),
                                                              method(context)
{
}

CodeGenContext::HashMap_::Constructors_::Constructors_(CodeGenContext* context) : ContextProvider(context)
{
}

CodeGenContext::HashMap_::Methods_::Methods_(CodeGenContext* context) : ContextProvider(context)
{
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::nil_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(std::nullopt, {}) // ()V
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::integer_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(std::nullopt, {DescriptorMethod::Long})
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::floatNumber_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(std::nullopt, {DescriptorMethod::Double})
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::boolean_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(std::nullopt, {DescriptorMethod::Boolean})
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::string_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(std::nullopt, {DescriptorField(STRING)})
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Constructors_::table_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "<init>",
        DescriptorMethod(
            std::nullopt, {DescriptorField(MAP)}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::add_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::sub_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::mul_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::div_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::idiv_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::mod_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::pow_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::concat_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::equal_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::lessThan_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::lessEqual_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::boolNot_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::toBool_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_VALUE,
        "getBoolValueSave",
        DescriptorMethod(
            Descriptor::Boolean,
            {}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::fieldByKey_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::call_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::unMinus_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::length_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaValue_::Methods_::assigment_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantClass* CodeGenContext::LuaValue_::classConstant_impl()
{
    return getClass()->getOrCreateClassConstant(LUA_VALUE);
}

ConstantMethodref* CodeGenContext::LuaContext_::Constructors_::root_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_CONTEXT,
        "<init>",
        DescriptorMethod(
            std::nullopt, {}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaContext_::Constructors_::withParent_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_CONTEXT,
        "<init>",
        DescriptorMethod(
            std::nullopt, {{LUA_CONTEXT}}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaContext_::Methods_::getParent_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_CONTEXT,
        "getParent",
        DescriptorMethod(
            DescriptorField(LUA_CONTEXT),
            {}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaContext_::Methods_::getById_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_::Methods_::getByIdOrCreateNewGlobal_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_::Methods_::setValue_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantMethodref* CodeGenContext::LuaContext_::Methods_::declareLocalId_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_CONTEXT,
        "declareLocal",
        DescriptorMethod(
            DescriptorField(LUA_VALUE),
            {{STRING}}
        )
    );
}

ConstantClass* CodeGenContext::LuaContext_::classConstant_impl()
{
    return getClass()->getOrCreateClassConstant(LUA_CONTEXT);
}

ConstantMethodref* CodeGenContext::LuaList_::Constructors_::base_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "<init>",
        DescriptorMethod(std::nullopt, {})
    );
}


ConstantMethodref* CodeGenContext::LuaList_::Methods_::get_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "get",
        DescriptorMethod(
            DescriptorField(LUA_VALUE),
            {{Descriptor::Int}}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaList_::Methods_::subList_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "subList",
        DescriptorMethod(
            DescriptorField(LUA_LIST),
            {{Descriptor::Int}}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaList_::Methods_::getFirst_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "getFirst",
        DescriptorMethod(
            DescriptorField(OBJECT),
            {}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaList_::Methods_::add_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "add",
        DescriptorMethod(
            Descriptor::Boolean,
            {{OBJECT}}
        )
    );
}

ConstantMethodref* CodeGenContext::LuaList_::Methods_::addAll_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        LUA_LIST,
        "addAll",
        DescriptorMethod(
            Descriptor::Boolean,
            {{COLLECTION}}
        )
    );
}

ConstantClass* CodeGenContext::LuaList_::classConstant_impl()
{
    return getClass()->getOrCreateClassConstant(LUA_LIST);
}

ConstantMethodref* CodeGenContext::HashMap_::Constructors_::base_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
        HASH_MAP,
        "<init>",
        DescriptorMethod(std::nullopt, {})
    );
}

ConstantMethodref* CodeGenContext::HashMap_::Methods_::put_impl()
{
    return getClass()->getOrCreateMethodrefConstant(
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

ConstantClass* CodeGenContext::HashMap_::classConstant_impl()
{
    return getClass()->getOrCreateClassConstant(HASH_MAP);
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
