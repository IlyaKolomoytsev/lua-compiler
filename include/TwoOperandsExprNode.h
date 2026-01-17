#ifndef LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#define LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#include "ExpressionNodeOf.h"
#include "FixedString.h"
#include "DotMacros.h"

template <ExpressionNode::Type T, fixed_string N>
class TwoOperandsExprNode : public ExpressionNodeOf<T, N>
{
public:
    TwoOperandsExprNode(ExpressionNode* left, ExpressionNode* right) : left_(left), right_(right)
    {
    }

    [[nodiscard]] ExpressionNode* getLeft() const { return left_; }
    [[nodiscard]] ExpressionNode* getRight() const { return right_; }

    void writeNodeInfoToDot(std::ostream& os) const override
    {
        ExpressionNodeOf<T, N>::writeNodeInfoToDot(os);
        os << DOT_ARC_THIS_OTHER_LABEL(left_, "left");
        os << DOT_ARC_THIS_OTHER_LABEL(right_, "right");
        os << *left_;
        os << *right_;
    }

private:
    ExpressionNode* left_;
    ExpressionNode* right_;
};

#endif //LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
