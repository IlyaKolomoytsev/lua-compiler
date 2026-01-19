#include "node/statement/ReturnStmtNode.h"

ReturnStmtNode::ReturnStmtNode(ExpressionNodeList* returnExprList) : StatementNode(Type::Return),
                                                                     returnExprList_(returnExprList)
{
}

void ReturnStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("Return");

    // Write children node info to dot file
    int index = 0;
    for (auto* returnExpr : *returnExprList_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(returnExpr, "expression №" << index++);
        os << *returnExpr;
    }
}
