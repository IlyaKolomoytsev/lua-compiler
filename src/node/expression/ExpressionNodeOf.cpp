#include "node/expression/ExpressionNodeOf.h"

#include "generation/ExpressionBytecodeBuilder.h"

template <exprType T, fixed_string N>
void ExpressionNodeOf<T, N>::makeBytecode(ExpressionBytecodeBuilder& bytecodeBuilder) const
{
    switch (T)
    {
    case exprType::Nil:
        {
            bytecodeBuilder.pushNull();
            break;
        }
    case exprType::Vararg:
        {
            // TODO Работа vararg с байткодом
        }
    default:
        {
            throw std::logic_error("Unsupported expression node of type");
        }
    }
}
