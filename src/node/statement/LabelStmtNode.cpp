#include "node/statement/LabelStmtNode.h"

#include "node/DotMacros.h"

LabelStmtNode::LabelStmtNode(std::string* name) : StatementNode(Type::Label), name_(name)
{
}

void LabelStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("Label");

    // Write children node info to dot file
    os << DOT_NODE_THIS_WITH_LABEL("::" << *name_ << "::");
}
