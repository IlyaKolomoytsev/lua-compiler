#ifndef LUA_COMPILER_FOR_LOOP_ITERATOR_STMT_NODE_H
#define LUA_COMPILER_FOR_LOOP_ITERATOR_STMT_NODE_H

#include "StatementNode.h"
#include "BlockStmtNode.h"
#include "node/expression/ExpressionNode.h"

class ForLoopIteratorStmtNode : public StatementNode
{
public:
    explicit ForLoopIteratorStmtNode(ExpressionNodeList* names, ExpressionNodeList* iteratorExprList, BlockStmtNode* block);

    [[nodiscard]] const ExpressionNodeList* getNameList() const { return names_; }
    [[nodiscard]] const ExpressionNodeList* getIterator() const { return iteratorExprList_; }
    [[nodiscard]] const BlockStmtNode* getBlock() const { return block_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;
private:
    ExpressionNodeList* names_;
    ExpressionNodeList* iteratorExprList_;
    BlockStmtNode* block_;
};


#endif //LUA_COMPILER_FOR_LOOP_ITERATOR_STMT_NODE_H