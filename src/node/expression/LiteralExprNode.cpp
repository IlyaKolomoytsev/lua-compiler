#include "node/expression/LiteralExprNode.h"

#include "generation/ExpressionBytecodeBuilder.h"

template <typename V, exprType T>
void LiteralExprNode<V, T>::makeBytecode(ExpressionBytecodeBuilder& byteCodeBuilder) const
{
    switch (T)
    {
    case exprType::Integer:
        {
            // TODO разобраться с int64 и int32
            byteCodeBuilder.pushInt(value_);
            break;
        }
    case exprType::Float:
        {
            // TODO разобраться с float и double
            byteCodeBuilder.pushFloat(value_);
            break;
        }
    case exprType::String:
        {
            byteCodeBuilder.pushString(value_);
            break;
        }
    case exprType::Boolean:
        {
            byteCodeBuilder.pushBool(value_);
            break;
        }
    case exprType::Id:
        {
            byteCodeBuilder.id(value_);
            break;
        }
    default:
        {
            throw std::logic_error("Unsupported literal expression type");
        }
    }
}
