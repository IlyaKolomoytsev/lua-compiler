#ifndef LUA_COMPILER_UNTIL_STMT_NODE_H
#define LUA_COMPILER_UNTIL_STMT_NODE_H
#include "node/statement/WhileRepeatLoopStmtNode.h"


class RepeatLoopStmtNode : public WhileRepeatLoopStmtNode
{
public:
    RepeatLoopStmtNode(ExpressionNode* condition, BlockStmtNode* block);

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;
};


#endif //LUA_COMPILER_UNTIL_STMT_NODE_H