#ifndef LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H
#define LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H

#include "ExpressionNode.h"
#include "CodeGenContext.h"

class ExpressionBytecodeBuilder
{
public:
    ExpressionBytecodeBuilder(CodeGenContext* context)
        : context_(context){}

    void buildExpression(ExpressionNode* expression);

private:
    void build(ExpressionNode* expression);
    void buildAnd(ExpressionNode* left, ExpressionNode* right);
    void buildOr(ExpressionNode* left, ExpressionNode* right);

    // Push on stack
    void pushInt(const ExpressionNode* expression) const;
    void pushFloat(const ExpressionNode* expression) const;
    void pushBool(const ExpressionNode* expression) const;
    void pushString(ExpressionNode* expression) const;
    void pushNull() const;

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

    // Operations with one operand
    void unm() const;
    void len() const;
    void Not() const;

    // Helpers
    void emitStaticCall(ConstantMethodref* methodref) const;
    ExpressionNodeList getChildren(ExpressionNode* expression);

    CodeGenContext* context_;
};

#endif //LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H