#ifndef LUA_COMPILER_BYTE_CODE_BUILDER_H
#define LUA_COMPILER_BYTE_CODE_BUILDER_H

#include "generation/CodeGenContext.h"
#include "node/NodeExpressionModule.h"

class ByteCodeBuilder
{
public:
    ByteCodeBuilder(CodeGenContext* context)
        : context_(context)
    {
    }

    [[nodiscard]] const CodeGenContext* getContext() const { return context_; }

    //region Bool operation
    void buildAnd(const ExpressionNode* left, const ExpressionNode* right);
    void buildOr(const ExpressionNode* left, const ExpressionNode* right);
    //endregion
    //region Push on stack
    void pushInt(int64_t value) const;
    void pushFloat(double value) const;
    void pushBool(bool value) const;
    void pushString(const std::string& value) const;
    void pushNull() const;

    void id(const std::string& value) const;
    //endregion
    //region Operations with two operands
    void sum() const;
    void sub() const;
    void mul() const;
    void div() const;
    void idiv() const;
    void mod() const;
    void pow() const;
    void concat() const;
    void equal() const;
    void notEqual() const;
    void lessThan() const;
    void lessEqual() const;
    void greaterThan() const;
    void greaterEqual() const;
    void getFieldByKey() const;
    void setFieldByKey() const;
    void tableConstructor() const;
    //endregion
    //region Operations with one operand
    void unm() const;
    void len() const;
    void booleanNot() const;
    //endregion

private:
    //region Helpers
    void emitStaticCall(ConstantMethodref* methodref) const;
    //endregion

    CodeGenContext* context_;
};

#endif //LUA_COMPILER_BYTE_CODE_BUILDER_H
