#ifndef LUA_COMPILER_GOTO_STMT_NODE_H
#define LUA_COMPILER_GOTO_STMT_NODE_H
#include "StatementNode.h"


class GotoStmtNode : public StatementNode
{
public:
    GotoStmtNode(std::string* labelName);

    [[nodiscard]] const std::string& getLabelName() const { return *labelName_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    std::string* labelName_;
};


#endif //LUA_COMPILER_GOTO_STMT_NODE_H
