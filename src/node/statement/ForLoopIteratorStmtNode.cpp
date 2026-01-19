#include "node/statement/ForLoopIteratorStmtNode.h"
#include "node/DotMacros.h"


ForLoopIteratorStmtNode::ForLoopIteratorStmtNode(ExpressionNodeList* names,
                                                 ExpressionNodeList* iteratorExprList,
                                                 BlockStmtNode* block) :
    StatementNode(Type::ForLoopIterator), names_(names), iteratorExprList_(iteratorExprList), block_(block)
{
}

void ForLoopIteratorStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("ForLoopIterator");

    // Write children node info to dot file
    int indexName = 0;
    for (auto* name : *names_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(name, "name " << indexName++);
        os << *name;
    }

    int indexIteratorExpr = 0;
    for (auto* iteratorExpr : *iteratorExprList_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(iteratorExpr, "iteratorExpr " << indexIteratorExpr++);
        os << *iteratorExpr;
    }

    os << DOT_ARC_THIS_OTHER_LABEL(block_, "block");
    os << *block_;
}
