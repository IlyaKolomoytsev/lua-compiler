#ifndef LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#define LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
#include "ExpressionNodeOf.h"

template <exprType T, fixed_string N>
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

    void makeBytecode(ByteCodeBuilder& builder) const override;

private:
    ExpressionNode* operand_;
};

template <exprType T, fixed_string N>
void OneOperandExprNode<T, N>::makeBytecode(ByteCodeBuilder& builder) const
{
    operand_->makeBytecode(builder);
    if constexpr (T == exprType::Length)
    {
        builder.len();
    }
    else if constexpr (T == exprType::UnaryMinuses)
    {
        builder.unm();
    }
    else if constexpr (T == exprType::Negation)
    {
        builder.booleanNot();
    }
    else
    {
        static_assert(
            T == exprType::Length ||
            T == exprType::UnaryMinuses ||
            T == exprType::Negation,
            "Unsupported one operand expression type"
        );
    }
}

#endif //LUA_COMPILER_ONE_OPERAND_EXPRESSION_NODE_H
