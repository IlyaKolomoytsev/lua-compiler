#ifndef LUA_COMPILER_LITERAL_EXPR_NODE_H
#define LUA_COMPILER_LITERAL_EXPR_NODE_H

#include "node/expression/ExpressionNode.h"
#include "node/DotMacros.h"

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

    void makeBytecode(ExpressionBytecodeBuilder& byteCodeBuilder) const override;

private:
    V value_;
};

#endif //LUA_COMPILER_LITERAL_EXPR_NODE_H
