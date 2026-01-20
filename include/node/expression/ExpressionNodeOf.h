#ifndef LUA_COMPILER_EXPRESSION_NODE_OF_H
#define LUA_COMPILER_EXPRESSION_NODE_OF_H
#include "node/DotMacros.h"
#include "node/Node.h"
#include "FixedString.h"
#include "ExpressionNode.h"
#include "generation/ByteCodeBuilder.h"

template <exprType T, fixed_string N>
class ExpressionNodeOf : public ExpressionNode
{
public:
    ExpressionNodeOf() : ExpressionNode(T)
    {
    }

    void writeNodeInfoToDot(std::ostream& os) const override
    {
        os << DOT_NODE_THIS_WITH_LABEL(N.value);
    }

    void makeBytecode(const ByteCodeBuilder& builder) const override;
};

template <exprType T, fixed_string N>
void ExpressionNodeOf<T, N>::makeBytecode(const ByteCodeBuilder& builder) const
{
    if constexpr (T == exprType::Nil)
    {
        builder.pushNull();
    }
    else if constexpr (T == exprType::Vararg)
    {
        // TODO Работа vararg с байткодом
    }
    else
    {
        static_assert(
            T == exprType::Nil || T == exprType::Vararg,
            "Unsupported expression node of type"
        );
    }
}

#endif //LUA_COMPILER_EXPRESSION_NODE_OF_H
