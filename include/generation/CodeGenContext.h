#ifndef LUA_COMPILER_CODEGEN_CONTEXT_H
#define LUA_COMPILER_CODEGEN_CONTEXT_H

#include "RuntimeRefs.h"
#include "jvm/attribute-code.h"
#include "jvm/class.h"
#include "jvm/method.h"

using namespace jvm;

class CodeGenContext
{
public:
    CodeGenContext(Class* currentClass);

    void setMethod(Method* method);

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
    ConstantMethodref* getUnMinusMethodFromLuaValue();
    ConstantMethodref* getLengthMethodFromLuaValue();
    //endregion

    ConstantMethodref* getLuaValueByIdMethodFromContext();

    void setContextIndexInLocals(uint16_t index) { contextIndexInLocals_ = index; }
    uint16_t getContextIndexInLocals() const { return contextIndexInLocals_; }

private:
    Class* class_;
    Method* currentMethod_ = nullptr;
    AttributeCode* currentAttributeCode_ = nullptr;


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

    ConstantMethodref* luaValueUnMinus = nullptr;
    ConstantMethodref* luaValueLen = nullptr;

    ConstantMethodref* luaContextGetLuaValueById = nullptr;

    uint16_t contextIndexInLocals_ = 0;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H
