#ifndef LUA_COMPILER_BRANCHING_STMT_NODE_H
#define LUA_COMPILER_BRANCHING_STMT_NODE_H
#include "node/statement/StatementNode.h"
#include "node/statement/BlockStmtNode.h"

class BranchingStmtNode : public StatementNode
{
public:
    BranchingStmtNode(ExpressionNode* condition, BlockStmtNode* successBlock, StatementNode* failureBlock = nullptr);

    BranchingStmtNode* appendElseToDeepestIf(StatementNode* elseIfOrElseBlock);

    [[nodiscard]] ExpressionNode* getCondition() const { return condition_; };
    [[nodiscard]] BlockStmtNode* getSuccessBlock() const { return successBlock_; };
    [[nodiscard]] StatementNode* getFailureBlock() const { return failureBlock_; }

    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNode* condition_;
    BlockStmtNode* successBlock_;
    StatementNode* failureBlock_;
};

#endif //LUA_COMPILER_BRANCHING_STMT_NODE_H
