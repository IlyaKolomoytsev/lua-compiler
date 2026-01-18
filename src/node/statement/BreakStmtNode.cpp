#include "node/statement/BreakStmtNode.h"

BreakStmtNode::BreakStmtNode() : StatementNode(Type::Break)
{
}

void BreakStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("Break");
}
