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

    void PushInt(ExpressionNode* expression);
    void PushFloat(ExpressionNode* expression);
    void PushBool(ExpressionNode* expression);
    void PushString(ExpressionNode* expression);
    void PushNull(ExpressionNode* expression);

    ExpressionNodeList getChildren(ExpressionNode* expression);

    CodeGenContext* context_;
};

#endif //LUA_COMPILER_EXPRESSION_BYTECODE_BUILDER_H