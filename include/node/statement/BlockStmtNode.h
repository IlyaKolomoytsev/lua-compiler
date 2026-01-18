#ifndef LUA_COMPILER_BLOCK_STATEMENT_NODE_H
#define LUA_COMPILER_BLOCK_STATEMENT_NODE_H
#include "StatementNode.h"

class BlockStmtNode : public StatementNode
{
public:
    explicit BlockStmtNode(StatementNodeList* list);

    [[nodiscard]] const StatementNodeList* getList() const { return list_; }

    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    StatementNodeList* list_;
};

#endif //LUA_COMPILER_BLOCK_STATEMENT_NODE_H
