#include "node/statement/GotoStmtNode.h"

#include "node/DotMacros.h"

GotoStmtNode::GotoStmtNode(std::string* labelName) : StatementNode(Type::GoTo), labelName_(labelName)
{
}

void GotoStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("GoTo");

    // Write children node info to dot file
    os << DOT_NODE_THIS_WITH_LABEL("goto " << *labelName_);
}
