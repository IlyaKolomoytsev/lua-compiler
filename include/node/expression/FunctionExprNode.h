#ifndef LUA_COMPILER_FUNCTION_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_EXPR_NODE_H
#include "node/expression/ExpressionNode.h"

class FunctionExprNode : public ExpressionNode
{
public:
    FunctionExprNode(ExpressionNodeList* parameters, StatementNode* body) :
        ExpressionNode(Type::FunctionLiteral), parameters_(parameters), body_(body)
    {
    }

    [[nodiscard]] const ExpressionNodeList& parameters() const { return *parameters_; };
    [[nodiscard]] StatementNode* body() const { return body_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;
    void makeBytecode(const ByteCodeBuilder& builder) const override;

private:
    ExpressionNodeList* parameters_;
    StatementNode* body_;
};

#endif //LUA_COMPILER_FUNCTION_EXPR_NODE_H
