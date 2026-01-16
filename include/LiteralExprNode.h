#ifndef LUA_COMPILER_LITERAL_EXPR_NODE_H
#define LUA_COMPILER_LITERAL_EXPR_NODE_H

#include "ExpressionNode.h"

template <typename V, ExpressionNode::Type T>
class LiteralExprNode : public ExpressionNode
{
public:
    explicit LiteralExprNode(V value) : ExpressionNode(T), value_(value)
    {
    }

    [[nodiscard]] const V& getValue() const noexcept { return value_; }

private:
    V value_;
};

#endif //LUA_COMPILER_LITERAL_EXPR_NODE_H
