#ifndef LUA_COMPILER_FUNCTION_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_EXPR_NODE_H
#include "node/expression/ExpressionNode.h"

class BlockStmtNode;

class FunctionExprNode : public ExpressionNode
{
public:
    FunctionExprNode(ExpressionNodeList* parameters, BlockStmtNode* body) :
        ExpressionNode(Type::FunctionLiteral), parameters_(parameters), body_(body)
    {
    }

    [[nodiscard]] const ExpressionNodeList& parameters() const { return *parameters_; };
    [[nodiscard]] BlockStmtNode* body() const { return body_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;

private:
    ExpressionNodeList* parameters_;
    BlockStmtNode* body_;
};

#endif //LUA_COMPILER_FUNCTION_EXPR_NODE_H
