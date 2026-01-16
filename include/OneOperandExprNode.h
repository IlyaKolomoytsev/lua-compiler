#ifndef LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#define LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#include "ExpressionNode.h"

template <ExpressionNode::Type T>
class OneOperandExprNode : public ExpressionNode
{
public:
    OneOperandExprNode(ExpressionNode* operand) :
        ExpressionNode(T), operand_(operand)
    {
    }

    [[nodiscard]] ExpressionNode* getOperand() const { return operand_; }

private:
    ExpressionNode* operand_;
};

#endif //LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
