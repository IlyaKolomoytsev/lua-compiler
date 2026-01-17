#ifndef LUA_COMPILER_EXPRESSION_NODE_H
#define LUA_COMPILER_EXPRESSION_NODE_H
#include <list>
#include <string>
#include <sys/types.h>

#include "Node.h"

class ExpressionNode;


using NameList = std::list<ExpressionNode*>;
using ExpressionNodeList = std::list<ExpressionNode*>;

struct TableField
{
    ExpressionNode* name;
    ExpressionNode* value;
};

using TableFieldList = std::list<TableField>;

class StatementNode;

class ExpressionNode : public Node
{
public:
    enum class Type
    {
        Integer,
        Float,
        String,
        Boolean,
        Nil,
        Vararg,
        Id,
        TableField,
        TableFieldByIndex,
        TableConstructor,
        FunctionCall,
        FunctionLiteral,
        ExpressionList,
        Summation,
        Subtraction,
        Multiplication,
        Division,
        Modulo,
        IntegerDivision,
        Exponentiation,
        Less,
        Greater,
        Equality,
        Unequality,
        LessEqual,
        GreaterEqual,
        Or,
        And,
        Concatenation,
        Length,
        Negation,
        UnaryMinuses,
    };

protected:
    explicit ExpressionNode(Type type);

    Type type_;
};

std::string to_string(ExpressionNode::Type type);

#endif
