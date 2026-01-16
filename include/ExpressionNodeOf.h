#ifndef LUA_COMPILER_EXPRESSION_NODE_OF_H
#define LUA_COMPILER_EXPRESSION_NODE_OF_H
#include "ExpressionNode.h"

template <ExpressionNode::Type T>
class ExpressionNodeOf : public ExpressionNode
{
public:
    ExpressionNodeOf() : ExpressionNode(T)
    {
    }
};

#endif //LUA_COMPILER_EXPRESSION_NODE_OF_H
