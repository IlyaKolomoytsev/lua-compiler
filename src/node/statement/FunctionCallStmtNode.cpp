#include "node/statement/FunctionCallStmtNode.h"

FunctionCallStmtNode::FunctionCallStmtNode(ExpressionNode* functionCall): StatementNode(Type::FunctionCall), functionCall_(functionCall)
{
}

void FunctionCallStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    os << DOT_NODE_THIS_WITH_LABEL("FunctionCallStmt");
    os << DOT_ARC_THIS_OTHER_LABEL(functionCall_, "expression");
    os << *functionCall_;
}
