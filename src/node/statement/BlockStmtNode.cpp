#include "node/statement/BlockStmtNode.h"
#include "node/DotMacros.h"

BlockStmtNode::BlockStmtNode(StatementNodeList* list) : StatementNode(Type::Block), list_(list)
{
}

void BlockStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // write this node
    os << DOT_NODE_THIS_WITH_LABEL("Block");

    // write arcs
    int index = 0;
    for (auto* statement : *list_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(statement, "element №" << index++);
    }

    // write nodes recursively
    for (auto* statement : *list_)
    {
        os << *statement;
    }
}
