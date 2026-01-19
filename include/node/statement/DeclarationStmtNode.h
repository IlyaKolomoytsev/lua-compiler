#ifndef LUA_COMPILER_DECLARATION_STMT_NODE_H
#define LUA_COMPILER_DECLARATION_STMT_NODE_H
#include "node/statement/StatementNode.h"

class DeclarationStmtNode : public StatementNode
{
public:
    DeclarationStmtNode(ExpressionNodeList* names);

    [[nodiscard]] ExpressionNodeList* getNames() const { return names_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNodeList* names_;
};
#endif //LUA_COMPILER_DECLARATION_STMT_NODE_H
