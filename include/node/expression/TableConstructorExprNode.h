#ifndef LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
#define LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
#include "node/expression/ExpressionNode.h"

class TableConstructorExprNode : public ExpressionNode
{
public:
    TableConstructorExprNode(TableFieldList* fields) : ExpressionNode(Type::TableConstructor), fields_(fields)
    {
    }

    [[nodiscard]] TableFieldList* getTableFields() const { return fields_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    TableFieldList* fields_;
};

#endif //LUA_COMPILER_TABLE_CONSTRUCTOR_EXPR_NODE_H
