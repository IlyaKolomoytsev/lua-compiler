#include "node/expression/TableFieldExprNode.h"

#include "generation/ByteCodeBuilder.h"
#include "node/DotMacros.h"

void TableFieldExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("TableField");

    // Write children node info to dot file
    os << DOT_ARC_THIS_OTHER_LABEL(table_, "table");
    os << DOT_ARC_THIS_OTHER_LABEL(key_, "key");
    os << *table_;
    os << *key_;
}

void TableFieldExprNode::makeBytecode(ByteCodeBuilder& builder) const
{
    table_->makeBytecode(builder); // ..., table
    key_->makeBytecode(builder); // ..., table, key

    builder.getFieldByKey(); // ..., LuaValue
}

