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

    void PushInt(const ExpressionNode* expression) const;
    void PushFloat(const ExpressionNode* expression) const;
    void PushBool(const ExpressionNode* expression) const;
    void PushString(ExpressionNode* expression) const;
    void PushNull(const ExpressionNode* expression) const;

    ExpressionNodeList getChildren(ExpressionNode* expression);

    CodeGenContext* context_;
};

#endif //LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H