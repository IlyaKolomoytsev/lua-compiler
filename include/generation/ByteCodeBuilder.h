#ifndef LUA_COMPILER_BYTE_CODE_BUILDER_H
#define LUA_COMPILER_BYTE_CODE_BUILDER_H

#include "generation/CodeGenContext.h"
#include "node/expression/ExpressionNode.h"

class ByteCodeBuilder: public CodeGenContext
{
public:
    ByteCodeBuilder(Class* currentClass, Method* currentMethod) : CodeGenContext(currentClass, currentMethod)
    {
    }

    //region Bool operation
    void buildAnd(const ExpressionNode* left, const ExpressionNode* right);
    void buildOr(const ExpressionNode* left, const ExpressionNode* right);
    //endregion
    //region Push LuaValue primitive on stack
    void pushInt(int64_t value);
    void pushFloat(double value);
    void pushBool(bool value);
    void pushString(const std::string& value);
    void pushNull();

    void id(const std::string& value);
    //endregion
    //region Operations with two operands
    void sum();
    void sub();
    void mul();
    void div();
    void idiv();
    void mod();
    void pow();
    void concat();
    void equal();
    void notEqual();
    void lessThan();
    void lessEqual();
    void greaterThan();
    void greaterEqual();
    void getFieldByKey();
    //endregion
    //region Operations with one operand
    void unm();
    void len();
    void booleanNot();
    //endregion
    //region Others
    void tableConstructor(TableFieldList* fieldList);
    void pushVararg();
    void pushVarargList();
    //endregion

private:
    //region Helpers
    void emitStaticCall(ConstantMethodref* methodref);
    void createHashMap();
    //endregion
};

#endif //LUA_COMPILER_BYTE_CODE_BUILDER_H
