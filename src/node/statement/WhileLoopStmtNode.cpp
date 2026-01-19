#include "node/statement/WhileLoopStmtNode.h"

WhileLoopStmtNode::WhileLoopStmtNode(ExpressionNode* condition, BlockStmtNode* block) : WhileRepeatLoopStmtNode(
    Type::WhileLoop, condition, block)
{
}

void WhileLoopStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("WhileLoop");

    // Write children node info to dot file
    WhileRepeatLoopStmtNode::writeNodeInfoToDot(os);
}
