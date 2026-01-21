#include "node/statement/RepeatLoopStmtNode.h"

#include "node/DotMacros.h"

RepeatLoopStmtNode::RepeatLoopStmtNode(ExpressionNode* condition, BlockStmtNode* block) : WhileRepeatLoopStmtNode(
    Type::RepeatLoop, condition, block)
{
}

void RepeatLoopStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("RepeatUntilLoop");

    // Write children node info to dot file
    WhileRepeatLoopStmtNode::writeNodeInfoToDot(os);
}
