#ifndef LUA_COMPILER_LITERAL_EXPR_NODE_H
#define LUA_COMPILER_LITERAL_EXPR_NODE_H

#include "node/expression/ExpressionNode.h"
#include "node/DotMacros.h"
#include "generation/ByteCodeBuilder.h"

template <typename V, ExpressionNode::Type T>
class LiteralExprNode : public ExpressionNode
{
public:
    explicit LiteralExprNode(V value) : ExpressionNode(T), value_(value)
    {
    }

    explicit LiteralExprNode(V* value) : ExpressionNode(T), value_(*value)
    {
    }

    [[nodiscard]] const V& getValue() const noexcept { return value_; }

    void writeNodeInfoToDot(std::ostream& os) const override
    {
        os << DOT_NODE_THIS_WITH_LABEL(value_);
    }

    void makeBytecode(ByteCodeBuilder& builder) const override;

private:
    V value_;
};

template <typename V, ExpressionNode::Type T>
void LiteralExprNode<V, T>::makeBytecode(ByteCodeBuilder& builder) const
{
    if constexpr (T == exprType::Integer)
    {
        builder.pushInt(value_);
    }
    else if constexpr (T == exprType::Float)
    {
        builder.pushFloat(value_);
    }
    else if constexpr (T == exprType::String)
    {
        builder.pushString(value_);
    }
    else if constexpr (T == exprType::Boolean)
    {
        builder.pushBool(value_);
    }
    else if constexpr (T == exprType::Id)
    {
        builder.id(value_);
    }
    else
    {
        static_assert(false, "Unsupported literal expression type");
    }
}

#endif //LUA_COMPILER_LITERAL_EXPR_NODE_H
