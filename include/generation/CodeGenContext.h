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
    // class
    ConstantClass* getLuaValueClass();


    // constructors
    ConstantMethodref* getNilConstructorForLuaValue();
    ConstantMethodref* getIntConstructorForLuaValue();
    ConstantMethodref* getFloatConstructorForLuaValue();
    ConstantMethodref* getBoolConstructorForLuaValue();
    ConstantMethodref* getStringConstructorForLuaValue();
    ConstantMethodref* getTableConstructorForLuaValue();

    // methods
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
    //endregion
    //region HashMap
    ConstantClass* getHashMapClass();
    ConstantMethodref* getHashMapConstructor();
    ConstantMethodref* getPutMethodFromHashMap();
    //endregion
    //region LuaContext
    ConstantClass* getLuaContextClass();
    ConstantMethodref* getConstructorForLuaContext();
    ConstantMethodref* getConstructorForLuaContextWithParent();
    ConstantMethodref* getParentContextMethodFromContext();
    ConstantMethodref* getLuaValueByIdMethodFromContext();
    ConstantMethodref* getLuaValueByIdOrCreateNewMethodFromContext();
    ConstantMethodref* setLuaValueByIdMethodFromContext();
    ConstantMethodref* getDeclareLocalByIdMethodFromContext();
    //endregion
    //region LuaList
    ConstantClass* getLuaListClass();
    ConstantMethodref* getLuaListConstructor();
    ConstantMethodref* getGetMethodFromLuaList();
    ConstantMethodref* getSubListMethodFromLuaList();
    ConstantMethodref* getFirstMethodFromLuaList();
    ConstantMethodref* getAddMethodFromLuaList();
    ConstantMethodref* getAddAllMethodFromLuaList();
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


    // classes
    ConstantClass* luaValueClass = nullptr;
    ConstantClass* hashMapClass = nullptr;
    ConstantClass* luaListClass = nullptr;
    ConstantClass* luaContextClass = nullptr;

    // constructors
    ConstantMethodref* luaValueCtorNil = nullptr;
    ConstantMethodref* luaValueCtorInt = nullptr;
    ConstantMethodref* luaValueCtorFloat = nullptr;
    ConstantMethodref* luaValueCtorBool = nullptr;
    ConstantMethodref* luaValueCtorString = nullptr;
    ConstantMethodref* luaValueCtorTable = nullptr;
    ConstantMethodref* hashMapCtor = nullptr;
    ConstantMethodref* luaListCtor = nullptr;
    ConstantMethodref* luaContextCtor = nullptr;
    ConstantMethodref* luaContextWithParentCtor = nullptr;

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
    ConstantMethodref* luaValueCall = nullptr;
    ConstantMethodref* hashMapPutMethod = nullptr;
    ConstantMethodref* luaListSubList = nullptr;
    ConstantMethodref* listGetFirstMethod = nullptr;
    ConstantMethodref* listGetMethod = nullptr;
    ConstantMethodref* luaListAddMethod = nullptr;
    ConstantMethodref* luaAssignmentMethod = nullptr;
    ConstantMethodref* listAddAllMethod = nullptr;

    ConstantMethodref* luaValueUnMinus = nullptr;
    ConstantMethodref* luaValueLen = nullptr;

    ConstantMethodref* luaContextGetLuaValueById = nullptr;
    ConstantMethodref* luaContextGetParent = nullptr;
    ConstantMethodref* luaContextGetLuaValueByIdOrCreateNew = nullptr;
    ConstantMethodref* luaContextSetLuaValueById = nullptr;
    ConstantMethodref* luaContextDeclareLocalById = nullptr;

    uint16_t contextIndexInLocals_ = 0;
    bool contextIndexIsInitialized_ = false;
    uint16_t argsIndexInLocals_ = 0;
    bool argsIndexIsInitialized_ = false;
    int32_t startIndexForVarargInListArgs_ = 0;
    bool startIndexForVarargIsInitialized_ = false;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H
