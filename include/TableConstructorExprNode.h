#ifndef LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
#define LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
#include "ExpressionNode.h"

class TableConstructorExprNode : public ExpressionNode
{
public:
    TableConstructorExprNode(TableFieldList* fields) : ExpressionNode(Type::TableConstructor), fields_(fields)
    {
    }

    [[nodiscard]] const TableFieldList& tableFields() const;

private:
    TableFieldList* fields_;
};

#endif //LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
