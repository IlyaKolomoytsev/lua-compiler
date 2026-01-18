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

    void pushInt(const ExpressionNode* expression) const;
    void pushFloat(const ExpressionNode* expression) const;
    void pushBool(const ExpressionNode* expression) const;
    void pushString(ExpressionNode* expression) const;
    void pushNull() const;

    ExpressionNodeList getChildren(ExpressionNode* expression);

    CodeGenContext* context_;
};

#endif //LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H