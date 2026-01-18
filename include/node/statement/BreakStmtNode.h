#ifndef LUA_COMPILER_BREAKSTMTNODE_H
#define LUA_COMPILER_BREAKSTMTNODE_H
#include "StatementNode.h"

class BreakStmtNode : public StatementNode
{
public:
    BreakStmtNode();

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;
};
#endif //LUA_COMPILER_BREAKSTMTNODE_H
