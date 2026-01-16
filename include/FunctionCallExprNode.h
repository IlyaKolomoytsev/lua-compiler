#ifndef LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#include "ExpressionNode.h"

class FunctionCallExprNode : public ExpressionNode
{
public:
    FunctionCallExprNode(ExpressionNode* functionExpr, FunctionArgumentsList* arguments) :
    ExpressionNode(Type::FunctionCall), functionExpr_(functionExpr), arguments_(arguments)
    {
    }

    [[nodiscard]] ExpressionNode* getFunctionExpression() const;
    [[nodiscard]] const ExpressionNodeList& getFunctionArguments() const;
private:
    ExpressionNode* functionExpr_;
    FunctionArgumentsList* arguments_;
};

#endif //LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
