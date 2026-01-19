#ifndef LUA_COMPILER_WHILE_LOOP_STMT_NODE_H
#define LUA_COMPILER_WHILE_LOOP_STMT_NODE_H
#include "node/statement/WhileRepeatLoopStmtNode.h"


class WhileLoopStmtNode : public WhileRepeatLoopStmtNode
{
public:
    WhileLoopStmtNode(ExpressionNode* condition, BlockStmtNode* block);

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;
};


#endif //LUA_COMPILER_WHILE_LOOP_STMT_NODE_H
