#include "node/statement/ForLoopClassicStmtNode.h"
#include "node/DotMacros.h"

ForLoopClassicStmtNode::ForLoopClassicStmtNode(IdExprNode* iteratorVariableId,
                                               ForRangeStruct range,
                                               BlockStmtNode* block) :
    StatementNode(Type::ForLoopClassic), iteratorVariableId_(iteratorVariableId), range_(range), block_(block)
{
}

void ForLoopClassicStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("ForLoopClassic");

    // Write children node info to dot file
    // write arcs
    os << DOT_ARC_THIS_OTHER_LABEL(iteratorVariableId_, "variable");
    os << DOT_ARC_THIS_OTHER_LABEL(range_.start, "range start");
    os << DOT_ARC_THIS_OTHER_LABEL(range_.finish, "range end");
    os << DOT_ARC_THIS_OTHER_LABEL(range_.step, "range step");
    os << DOT_ARC_THIS_OTHER_LABEL(block_, "block");

    // write nodes recursively
    os << *iteratorVariableId_;
    os << *range_.start;
    os << *range_.finish;
    os << *range_.step;
    os << *block_;
}
