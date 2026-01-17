#ifndef LUA_COMPILER_EXPRESSION_NODE_OF_H
#define LUA_COMPILER_EXPRESSION_NODE_OF_H
#include "DotMacros.h"
#include "Node.h"
#include "FixedString.h"
#include "ExpressionNode.h"

template <ExpressionNode::Type T, fixed_string N>
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
};

#endif //LUA_COMPILER_EXPRESSION_NODE_OF_H
