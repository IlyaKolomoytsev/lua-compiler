#ifndef LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H
#define LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H

#include "ByteCodeBuilder.h"
#include "CodeGenContext.h"
#include "node/NodeExpressionModule.h"

class ExpressionBytecodeBuilder : public ByteCodeBuilder
{
public:
    ExpressionBytecodeBuilder(CodeGenContext* context) : ByteCodeBuilder(context) {}

    void buildAnd(const ExpressionNode* left, const ExpressionNode* right);
    void buildOr(const ExpressionNode* left, const ExpressionNode* right);

    // Push on stack
    void pushInt(int64_t value) const;
    void pushFloat(double value) const;
    void pushBool(bool value) const;
    void pushString(const std::string& value) const;
    void pushNull() const;

    void id(const std::string& value) const;

    // Operations with two operands
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

    // Operations with one operand
    void unm() const;
    void len() const;
    void Not() const;

private:

    // Helpers
    void emitStaticCall(ConstantMethodref* methodref) const;

};

#endif //LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H