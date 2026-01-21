#ifndef LUA_COMPILER_STATEMENT_NODE_H
#define LUA_COMPILER_STATEMENT_NODE_H
#include <list>

#include "node/Node.h"

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

    Type getType() const { return type_; }

protected:
    explicit StatementNode(Type type);

private:
    Type type_;
};

std::string to_string(Scope scope);

std::string to_string(StatementNode::Type type);


#endif //LUA_COMPILER_STATEMENT_NODE_H
