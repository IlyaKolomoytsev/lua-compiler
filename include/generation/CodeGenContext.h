#ifndef LUA_COMPILER_CODEGEN_CONTEXT_H
#define LUA_COMPILER_CODEGEN_CONTEXT_H
#include "jvm/class.h"
#include "jvm/attribute-code.h"

using namespace jvm;

class CodeGenContext
{
public:
    CodeGenContext(Class* currentClass, Method* currentMethod);

    [[nodiscard]] Class* getClass() const { return class_; }
    [[nodiscard]] Method* getMethod() const { return currentMethod_; }
    [[nodiscard]] AttributeCode* getAttributeCode() const { return currentAttributeCode_; }

    //region LuaValue
    struct LuaValue_base
    {
        explicit LuaValue_base(CodeGenContext* currentOwner)
            : owner(currentOwner), constructor(this), method(this)
        {
        }

        [[nodiscard]] CodeGenContext* getContext() { return owner; }

        ConstantClass* getLuaValueClass();

        struct Constructors_base
        {
            explicit Constructors_base(LuaValue_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaValue_base* getLuaValue() { return outer; }

            ConstantMethodref* getNilConstructorForLuaValue();
            ConstantMethodref* getIntConstructorForLuaValue();
            ConstantMethodref* getFloatConstructorForLuaValue();
            ConstantMethodref* getBoolConstructorForLuaValue();
            ConstantMethodref* getStringConstructorForLuaValue();
            ConstantMethodref* getTableConstructorForLuaValue();

        private:
            LuaValue_base* outer;

            ConstantMethodref* luaValueCtorNil = nullptr;
            ConstantMethodref* luaValueCtorInt = nullptr;
            ConstantMethodref* luaValueCtorFloat = nullptr;
            ConstantMethodref* luaValueCtorBool = nullptr;
            ConstantMethodref* luaValueCtorString = nullptr;
            ConstantMethodref* luaValueCtorTable = nullptr;
        } constructor;

        struct Methods_base
        {
            explicit Methods_base(LuaValue_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaValue_base* getLuaValue() { return outer; }

            ConstantMethodref* getAddMethodFromLuaValue();
            ConstantMethodref* getSubMethodFromLuaValue();
            ConstantMethodref* getMulMethodFromLuaValue();
            ConstantMethodref* getDivMethodFromLuaValue();
            ConstantMethodref* getIntegerDivMethodFromLuaValue();
            ConstantMethodref* getModMethodFromLuaValue();
            ConstantMethodref* getPowMethodFromLuaValue();
            ConstantMethodref* getConcatMethodFromLuaValue();
            ConstantMethodref* getEqualMethodFromLuaValue();
            ConstantMethodref* getLessThenMethodFromLuaValue();
            ConstantMethodref* getLessEqualMethodFromLuaValue();
            ConstantMethodref* getNotMethodFromLuaValue();
            ConstantMethodref* getBoolValueFromLuaValue();
            ConstantMethodref* getFieldByKeyMethodFromLuaValue();
            ConstantMethodref* getCallMethodFromLuaValue();
            ConstantMethodref* getUnMinusMethodFromLuaValue();
            ConstantMethodref* getLengthMethodFromLuaValue();
            ConstantMethodref* getAssignmentMethodFromLuaValue();

        private:
            LuaValue_base* outer;

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
            ConstantMethodref* luaValueCall = nullptr;
            ConstantMethodref* luaValueUnMinus = nullptr;
            ConstantMethodref* luaValueLen = nullptr;
            ConstantMethodref* luaValueAssignmentMethod = nullptr;
        } method;

    private:
        CodeGenContext* owner;

        // Class
        ConstantClass* luaValueClass = nullptr;
    } LuaValue;

    //endregion
    //region LuaContext
    struct LuaContext_base
    {
        explicit LuaContext_base(CodeGenContext* currentOwner)
            : owner(currentOwner), constructor(this), method(this)
        {
        }

        [[nodiscard]] CodeGenContext* getContext() { return owner; }

        ConstantClass* getLuaContextClass();

        struct Constructors_base
        {
            explicit Constructors_base(LuaContext_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaContext_base* getLuaContext() { return outer; }

            ConstantMethodref* getConstructorForLuaContext();
            ConstantMethodref* getConstructorForLuaContextWithParent();

        private:
            LuaContext_base* outer;

            ConstantMethodref* luaContextCtor = nullptr;
            ConstantMethodref* luaContextWithParentCtor = nullptr;
        } constructor;

        struct Methods_base
        {
            explicit Methods_base(LuaContext_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaContext_base* getLuaContext() { return outer; }

            ConstantMethodref* getParentContextMethodFromContext();
            ConstantMethodref* getLuaValueByIdMethodFromContext();
            ConstantMethodref* getLuaValueByIdOrCreateNewMethodFromContext();
            ConstantMethodref* setLuaValueByIdMethodFromContext();
            ConstantMethodref* getDeclareLocalByIdMethodFromContext();

        private:
            LuaContext_base* outer;

            ConstantMethodref* luaContextGetLuaValueById = nullptr;
            ConstantMethodref* luaContextGetParent = nullptr;
            ConstantMethodref* luaContextGetLuaValueByIdOrCreateNew = nullptr;
            ConstantMethodref* luaContextSetLuaValueById = nullptr;
            ConstantMethodref* luaContextDeclareLocalById = nullptr;
        } method;

    private:
        CodeGenContext* owner;

        // Class
        ConstantClass* luaContextClass = nullptr;
    } LuaContext;

    //endregion
    //region LuaList
    struct LuaList_base
    {
        explicit LuaList_base(CodeGenContext* currentOwner)
            : owner(currentOwner), constructor(this), method(this)
        {
        }

        [[nodiscard]] CodeGenContext* getContext() { return owner; }

        ConstantClass* getLuaListClass();

        struct Constructors_base
        {
            explicit Constructors_base(LuaList_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaList_base* getLuaList() { return outer; }

            ConstantMethodref* getLuaListConstructor();

        private:
            LuaList_base* outer;

            ConstantMethodref* luaListCtor = nullptr;
        } constructor;

        struct Methods_base
        {
            explicit Methods_base(LuaList_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] LuaList_base* getLuaList() { return outer; }

            ConstantMethodref* getGetMethodFromLuaList();
            ConstantMethodref* getSubListMethodFromLuaList();
            ConstantMethodref* getFirstMethodFromLuaList();
            ConstantMethodref* getAddMethodFromLuaList();
            ConstantMethodref* getAddAllMethodFromLuaList();

        private:
            LuaList_base* outer;

            ConstantMethodref* luaListSubList = nullptr;
            ConstantMethodref* luaListGetFirstMethod = nullptr;
            ConstantMethodref* luaListGetMethod = nullptr;
            ConstantMethodref* luaListAddMethod = nullptr;
            ConstantMethodref* luaListAddAllMethod = nullptr;
        } method;

    private:
        CodeGenContext* owner;

        // Class
        ConstantClass* luaListClass = nullptr;
    } LuaList;

    //endregion
    //region HashMap
    struct HashMap_base
    {
        explicit HashMap_base(CodeGenContext* currentOwner)
            : owner(currentOwner), constructor(this), method(this)
        {
        }

        [[nodiscard]] CodeGenContext* getContext() { return owner; }

        ConstantClass* getHashMapClass();

        struct Constructors_base
        {
            explicit Constructors_base(HashMap_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] HashMap_base* getHashMap() { return outer; }

            ConstantMethodref* getHashMapConstructor();

        private:
            HashMap_base* outer;

            ConstantMethodref* hashMapCtor = nullptr;
        } constructor;

        struct Methods_base
        {
            explicit Methods_base(HashMap_base* currentOuter)
                : outer(currentOuter)
            {
            }

            [[nodiscard]] HashMap_base* getHashMap() { return outer; }

            ConstantMethodref* getPutMethodFromHashMap();

        private:
            HashMap_base* outer;

            ConstantMethodref* hashMapPutMethod = nullptr;
        } method;

    private:
        CodeGenContext* owner;

        ConstantClass* hashMapClass = nullptr;
    } HashMap;

    //endregion

    void setContextIndexInLocals(uint16_t index);
    uint16_t getContextIndexInLocals() const;

    void setArgsIndexInLocals(uint16_t index);
    uint16_t getArgsIndexInLocals() const;

    void setStartIndexForVarargInListArgs(int32_t index);
    int32_t getStartIndexForVarargInListArgs() const;

private:
    Class* class_;
    Method* currentMethod_ = nullptr;
    AttributeCode* currentAttributeCode_ = nullptr;

    uint16_t contextIndexInLocals_ = 0;
    bool contextIndexIsInitialized_ = false;
    uint16_t argsIndexInLocals_ = 0;
    bool argsIndexIsInitialized_ = false;
    int32_t startIndexForVarargInListArgs_ = 0;
    bool startIndexForVarargIsInitialized_ = false;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H
