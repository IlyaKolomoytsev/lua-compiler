#ifndef LUA_COMPILER_FUNCTION_CALL_STATEMENT_NODE_H
#define LUA_COMPILER_FUNCTION_CALL_STATEMENT_NODE_H
#include "StatementNode.h"

class FunctionCallStmtNode : public StatementNode
{
public:
    FunctionCallStmtNode(ExpressionNode* functionCall);

    [[nodiscard]] ExpressionNode* getExpression() const { return functionCall_; }

    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNode* functionCall_;
};

#endif //LUA_COMPILER_FUNCTION_CALL_STATEMENT_NODE_H
