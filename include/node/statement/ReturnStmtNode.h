#ifndef LUA_COMPILER_RETURN_STMT_NODE_H
#define LUA_COMPILER_RETURN_STMT_NODE_H
#include "StatementNode.h"
#include "node/expression/ExpressionNode.h"


class ReturnStmtNode : public StatementNode
{
public:
    ReturnStmtNode(ExpressionNodeList* returnExprList);

    [[nodiscard]] const ExpressionNodeList* getReturnExprList() const { return returnExprList_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNodeList* returnExprList_;
};


#endif //LUA_COMPILER_RETURN_STMT_NODE_H