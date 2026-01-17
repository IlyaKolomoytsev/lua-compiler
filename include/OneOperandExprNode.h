#ifndef LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#define LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#include "ExpressionNodeOf.h"

template <ExpressionNode::Type T, fixed_string N>
class OneOperandExprNode : public ExpressionNodeOf<T, N>
{
public:
    OneOperandExprNode(ExpressionNode* operand) : operand_(operand)
    {
    }

    [[nodiscard]] ExpressionNode* getOperand() const { return operand_; }

    void writeNodeInfoToDot(std::ostream& os) const override
    {
        ExpressionNodeOf<T, N>::writeNodeInfoToDot(os);
        os << DOT_ARC_THIS_OTHER_LABEL(operand_, "operand");
        os << *operand_;
    }

private:
    ExpressionNode* operand_;
};

#endif //LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
