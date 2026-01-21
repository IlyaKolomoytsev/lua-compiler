#ifndef LUA_COMPILER_CODEGEN_CONTEXT_H
#define LUA_COMPILER_CODEGEN_CONTEXT_H

#include "jvm/attribute-code.h"
#include "jvm/class.h"
#include "jvm/method.h"

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
    ConstantMethodref* getLuaValueByIdMethodFromContext();
    ConstantMethodref* setLuaValueByIdMethodFromContext();
    ConstantMethodref* getDeclareLocalByIdMethodFromContext();
    ConstantMethodref* getDeclareLocalByIdAndLuaValueMethodFromContext();
    //endregion
    //region LuaList
    ConstantClass* getLuaListClass();
    ConstantMethodref* getLuaListConstructor();
    ConstantMethodref* getGetMethodFromLuaList();
    ConstantMethodref* getSubListMethodFromLuaList();
    ConstantMethodref* getFirstMethodFromList();
    ConstantMethodref* getAddMethodFromLuaList();
    //endregion

    void setContextIndexInLocals(uint16_t index) { contextIndexInLocals_ = index; }
    uint16_t getContextIndexInLocals() const { return contextIndexInLocals_; }

    void setArgsIndexInLocals(uint16_t index) { contextIndexInLocals_ = index; }
    uint16_t getArgsIndexInLocals() const { return contextIndexInLocals_; }

    void setStartIndexForVarargInListArgs(int32_t index) { startIndexForVarargInListArgs_ = index; }
    int32_t getStartIndexForVarargInListArgs() const { return startIndexForVarargInListArgs_; }

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

    ConstantMethodref* luaValueUnMinus = nullptr;
    ConstantMethodref* luaValueLen = nullptr;

    ConstantMethodref* luaContextGetLuaValueById = nullptr;
    ConstantMethodref* luaContextSetLuaValueById = nullptr;
    ConstantMethodref* luaContextDeclareLocalById = nullptr;
    ConstantMethodref* luaContextDeclareLocalByIdAndLuaValue = nullptr;

    uint16_t contextIndexInLocals_ = 0;
    uint16_t argsIndexInLocals_ = 0;
    int32_t startIndexForVarargInListArgs_ = 0;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H
