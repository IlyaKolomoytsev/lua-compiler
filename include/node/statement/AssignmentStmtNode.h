#ifndef LUA_COMPILER_ASSIGNMENT_STMT_NODE_H
#define LUA_COMPILER_ASSIGNMENT_STMT_NODE_H
#include "node/statement/StatementNode.h"

class AssignmentStmtNode : public StatementNode
{
public:
    AssignmentStmtNode(Scope scope, ExpressionNodeList* names, ExpressionNodeList* values);

    [[nodiscard]] Scope getScope() const { return scope_; }
    [[nodiscard]] const ExpressionNodeList& getNameList() const { return *names_; }
    [[nodiscard]] const ExpressionNodeList& getValues() const { return *values_; }

    /* Overridden methods */
    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    Scope scope_;
    ExpressionNodeList* names_;
    ExpressionNodeList* values_;
};
#endif //LUA_COMPILER_ASSIGNMENT_STMT_NODE_H
