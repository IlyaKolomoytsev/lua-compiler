#ifndef LUA_COMPILER_STATEMENT_NODE_H
#define LUA_COMPILER_STATEMENT_NODE_H
#include <cassert>
#include <functional>
#include <vector>

#include "node/expression/ExpressionNode.h"
#include "node/NodeExpressionModule.h"

class StatementNode;

using StatementNodeList = std::list<StatementNode*>;

enum class Scope
{
    Global,
    Local,
};

class StatementNode : public Node
{
public:
    enum class Type
    {
        Declaration,
        Assignment,
        FunctionCall,
        Branching,
        ForLoopClassic,
        ForLoopIterator,
        WhileLoop,
        RepeatLoop,
        Block,
        GoTo,
        Label,
        Break,
        Return,
    };

protected:
    explicit StatementNode(Type type);

    Type type_;
};

std::string to_string(Scope scope);

std::string to_string(StatementNode::Type type);


#endif //LUA_COMPILER_STATEMENT_NODE_H
