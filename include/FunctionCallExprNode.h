#ifndef LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#include "ExpressionNode.h"

class FunctionCallExprNode : public ExpressionNode
{
public:
    FunctionCallExprNode(ExpressionNode* function, FunctionArgumentsList* arguments) :
    ExpressionNode(Type::FunctionCall), function_(function), arguments_(arguments)
    {
    }

    [[nodiscard]] ExpressionNode* getFunctionExpression() const;
    [[nodiscard]] const ExpressionNodeList& getFunctionArguments() const;

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;
private:
    ExpressionNode* function_;
    FunctionArgumentsList* arguments_;
};

#endif //LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
