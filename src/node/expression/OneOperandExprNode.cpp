#include "node/expression/OneOperandExprNode.h"

#include "generation/ExpressionBytecodeBuilder.h"

template <exprType T, fixed_string N>
void OneOperandExprNode<T, N>::makeBytecode(ExpressionBytecodeBuilder& bytecodeBuilder) const
{
    operand_->makeBytecode(bytecodeBuilder);

    switch (T)
    {
    case exprType::Length:
        {
            bytecodeBuilder.len();
            break;
        }
    case exprType::UnaryMinuses:
        {
            bytecodeBuilder.unm();
            break;
        }
    case exprType::Negation:
        {
            bytecodeBuilder.Not();
            break;
        }
    default:
        {
            throw std::logic_error("Unsupported one operand expression type");
        }
    }
}
