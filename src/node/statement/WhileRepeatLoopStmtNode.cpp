#include "node/statement/WhileRepeatLoopStmtNode.h"

WhileRepeatLoopStmtNode::WhileRepeatLoopStmtNode(Type type, ExpressionNode* condition, BlockStmtNode* block) :
    StatementNode(type), condition_(condition), block_(block)
{
}

void WhileRepeatLoopStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    os << DOT_ARC_THIS_OTHER_LABEL(condition_, "condition");
    os << DOT_ARC_THIS_OTHER_LABEL(block_, "block");
    os << *condition_;
    os << *block_;
}
