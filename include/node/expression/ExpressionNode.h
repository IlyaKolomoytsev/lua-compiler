#ifndef LUA_COMPILER_EXPRESSION_NODE_H
#define LUA_COMPILER_EXPRESSION_NODE_H
#include <list>
#include <string>
#include <sys/types.h>
#include "node/Node.h"


class ExpressionNode;


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
        TableConstructor,
        FunctionCall,
        FunctionLiteral,
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

    Type getType() const { return type_; }

protected:
    explicit ExpressionNode(Type type);

private:
    Type type_;
};

using exprType = ExpressionNode::Type;
std::string to_string(ExpressionNode::Type type);

#endif
