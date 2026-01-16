#ifndef LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#define LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#include "ExpressionNode.h"

template <ExpressionNode::Type T>
class TwoOperandsExprNode : public ExpressionNode
{
public:
    TwoOperandsExprNode(ExpressionNode* left, ExpressionNode* right) :
        ExpressionNode(T), left_(left), right_(right)
    {
    }

    [[nodiscard]] ExpressionNode* getLeft() const { return left_; }
    [[nodiscard]] ExpressionNode* getRight() const { return right_; }

private:
    ExpressionNode* left_;
    ExpressionNode* right_;
};

#endif //LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
