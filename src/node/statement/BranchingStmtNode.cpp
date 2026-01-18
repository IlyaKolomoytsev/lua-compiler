#include "node/statement/BranchingStmtNode.h"

#include <cassert>

BranchingStmtNode::BranchingStmtNode(ExpressionNode* condition,
                                     BlockStmtNode* successBlock,
                                     StatementNode* failureBlock) :
    StatementNode(Type::Branching), condition_(condition), successBlock_(successBlock), failureBlock_(failureBlock)
{
}

BranchingStmtNode* BranchingStmtNode::appendElseToDeepestIf(StatementNode* elseIfOrElseBlock)
{
    BranchingStmtNode* current = this;
    while (current->failureBlock_ != nullptr)
    {
        assert(current->failureBlock_->getType() == Type::Branching);
        // use only in "if elseif elseif" constructions, method user provide branching node in current failure block
        current = static_cast<BranchingStmtNode*>(current->failureBlock_);
    }
    current->failureBlock_ = elseIfOrElseBlock;
    return this;
}

void BranchingStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // write this node
    os << DOT_NODE_THIS_WITH_LABEL("if");

    // write arcs
    os << DOT_ARC_THIS_OTHER_LABEL(condition_, "condition");
    os << DOT_ARC_THIS_OTHER_LABEL(successBlock_, "success");
    if (failureBlock_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(failureBlock_, "failure");
    }

    // write nodes recursively
    os << *condition_;
    os << *successBlock_;
    if (failureBlock_)
    {
        os << *failureBlock_;
    }
}
