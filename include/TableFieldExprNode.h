#ifndef LUA_COMPILER_TABLE_FIELD_EXPR_NODE_H
#define LUA_COMPILER_TABLE_FIELD_EXPR_NODE_H
#include "ExpressionNode.h"

class TableFieldExprNode : public ExpressionNode
{
public:
    explicit TableFieldExprNode(ExpressionNode* table, ExpressionNode* key)
        : ExpressionNode(Type::TableField), table_(table), key_(key)
    {
    }

    [[nodiscard]] ExpressionNode* getTable() const { return table_; }
    [[nodiscard]] ExpressionNode* getKey() const { return key_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;
private:
    ExpressionNode* table_;
    ExpressionNode* key_;
};

#endif //LUA_COMPILER_TABLE_FIELD_EXPR_NODE_H
