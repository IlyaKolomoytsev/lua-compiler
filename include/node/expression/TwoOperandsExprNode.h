#ifndef LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#define LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
#include "ExpressionNodeOf.h"
#include "FixedString.h"
#include "node/DotMacros.h"

template <exprType T, fixed_string N>
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

    void makeBytecode(ByteCodeBuilder& builder) const override;

private:
    ExpressionNode* left_;
    ExpressionNode* right_;
};

template <exprType T, fixed_string N>
void TwoOperandsExprNode<T, N>::makeBytecode(ByteCodeBuilder& builder) const
{
    if constexpr (T != exprType::And && T != exprType::Or)
        {
        left_->makeBytecode(builder);
        right_->makeBytecode(builder);
        }

        if constexpr (T == exprType::Summation)
        {
            builder.sum();
        }
        else if constexpr (T == exprType::Subtraction)
        {
            builder.sub();
        }
        else if constexpr (T == exprType::Multiplication)
        {
            builder.mul();
        }
        else if constexpr (T == exprType::Division)
        {
            builder.div();
        }
        else if constexpr (T == exprType::Modulo)
        {
            builder.mod();
        }
        else if constexpr (T == exprType::IntegerDivision)
        {
            builder.idiv();
        }
        else if constexpr (T == exprType::Exponentiation)
        {
            builder.pow();
        }
        else if constexpr (T == exprType::Less)
        {
            builder.lessThan();
        }
        else if constexpr (T == exprType::LessEqual)
        {
            builder.lessEqual();
        }
        else if constexpr (T == exprType::Greater)
        {
            builder.greaterThan();
        }
        else if constexpr (T == exprType::GreaterEqual)
        {
            builder.greaterEqual();
        }
        else if constexpr (T == exprType::Equality)
        {
            builder.equal();
        }
        else if constexpr (T == exprType::Unequality)
        {
            builder.notEqual();
        }
        else if constexpr (T == exprType::And)
        {
            builder.buildAnd(left_, right_);
        }
        else if constexpr (T == exprType::Or)
        {
            builder.buildOr(left_, right_);
        }
        else if constexpr (T == exprType::Concatenation)
        {
            builder.concat();
        }
        else
        {
            static_assert(
                T == exprType::Summation ||
                T == exprType::Subtraction ||
                T == exprType::Multiplication ||
                T == exprType::Division ||
                T == exprType::Modulo ||
                T == exprType::IntegerDivision ||
                T == exprType::Exponentiation ||
                T == exprType::Less ||
                T == exprType::LessEqual ||
                T == exprType::Greater ||
                T == exprType::GreaterEqual ||
                T == exprType::Equality ||
                T == exprType::Unequality ||
                T == exprType::And ||
                T == exprType::Or ||
                T == exprType::Concatenation,
                "Unsupported two operands expression type"
            );
        }
}

#endif //LUA_COMPILER_TWO_OPERANDS_EXPR_NODE_H
