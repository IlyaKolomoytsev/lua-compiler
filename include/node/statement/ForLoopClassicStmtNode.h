#ifndef LUA_COMPILER_FOR_LOOP_CLASSIC_STMT_NODE_H
#define LUA_COMPILER_FOR_LOOP_CLASSIC_STMT_NODE_H
#include "StatementNode.h"
#include "BlockStmtNode.h"

struct ForRangeStruct
{
    ExpressionNode* start;
    ExpressionNode* finish;
    ExpressionNode* step;
};

class ForLoopClassicStmtNode : public StatementNode
{
public:
    ForLoopClassicStmtNode(ExpressionNode* iteratorVariableId, ForRangeStruct range, BlockStmtNode* block);

    [[nodiscard]] const ExpressionNode* getIteratorVariableId_() const { return iteratorVariableId_; }
    [[nodiscard]] ForRangeStruct getRange() const { return range_; }
    [[nodiscard]] const BlockStmtNode* getBlock() const { return block_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNode* iteratorVariableId_;
    ForRangeStruct range_;
    BlockStmtNode* block_;
};

#endif //LUA_COMPILER_FOR_LOOP_CLASSIC_STMT_NODE_H
