#ifndef LUA_COMPILER_LABEL_STMT_NODE_H
#define LUA_COMPILER_LABEL_STMT_NODE_H
#include "StatementNode.h"


class LabelStmtNode : public StatementNode
{
public:
    LabelStmtNode(std::string* name);

    [[nodiscard]] const std::string& getName() const { return *name_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    std::string* name_;
};

#endif //LUA_COMPILER_LABEL_STMT_NODE_H
