#ifndef LUA_COMPILER_WHILE_REPEAT_LOOP_STMT_NODE_H
#define LUA_COMPILER_WHILE_REPEAT_LOOP_STMT_NODE_H
#include "StatementNode.h"
#include "BlockStmtNode.h"

class WhileRepeatLoopStmtNode : public StatementNode
{
public:
    WhileRepeatLoopStmtNode(Type type, ExpressionNode* condition, BlockStmtNode* block);

    [[nodiscard]] const ExpressionNode* getCondition() const { return condition_; }
    [[nodiscard]] const BlockStmtNode* getBlock() const { return block_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNode* condition_;
    BlockStmtNode* block_;
};

#endif //LUA_COMPILER_WHILE_REPEAT_LOOP_STMT_NODE_H
