#include "node/expression/TwoOperandsExprNode.h"

#include "generation/ExpressionBytecodeBuilder.h"
#include "node/NodeExpressionModule.h"

template <exprType T, fixed_string N>
void TwoOperandsExprNode<T, N>::makeBytecode(ExpressionBytecodeBuilder& bytecodeBuilder) const
{
    if (T != exprType::And && T != exprType::Or)
    {
        left_->makeBytecode(bytecodeBuilder);
        right_->makeBytecode(bytecodeBuilder);
    }

    switch (T)
    {
    case exprType::Summation:
        {
            bytecodeBuilder.sum();
            break;
        }
    case exprType::Subtraction:
        {
            bytecodeBuilder.sub();
            break;
        }
    case exprType::Multiplication:
        {
            bytecodeBuilder.mul();
            break;
        }
    case exprType::Division:
        {
            bytecodeBuilder.div();
            break;
        }
    case exprType::Modulo:
        {
            bytecodeBuilder.mod();
            break;
        }
    case exprType::IntegerDivision:
        {
            bytecodeBuilder.idiv();
            break;
        }
    case exprType::Exponentiation:
        {
            bytecodeBuilder.pow();
            break;
        }
    case exprType::Less:
        {
            bytecodeBuilder.lessThan();
            break;
        }
    case exprType::LessEqual:
        {
            bytecodeBuilder.lessEqual();
            break;
        }
    case exprType::Greater:
        {
            bytecodeBuilder.greaterThan();
            break;
        }
    case exprType::GreaterEqual:
        {
            bytecodeBuilder.greaterEqual();
            break;
        }
    case exprType::Equality:
        {
            bytecodeBuilder.equal();
            break;
        }
    case exprType::Unequality:
        {
            bytecodeBuilder.notEqual();
            break;
        }
    case exprType::And:
        {
            bytecodeBuilder.buildAnd(left_, right_);
            break;
        }
    case exprType::Or:
        {
            bytecodeBuilder.buildOr(left_, right_);
        }
    case exprType::Concatenation:
        {
            bytecodeBuilder.concat();
            break;
        }
    default:
        {
            throw std::logic_error("Unsupported two operands expression type");
        }
    }
}
