#ifndef LUA_COMPILER_FUNCTION_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_EXPR_NODE_H
#include "ExpressionNode.h"

class FunctionExprNode : public ExpressionNode
{
public:
    FunctionExprNode(NameList* parameters, ExpressionNode* body) :
        ExpressionNode(Type::FunctionLiteral), parameters_(parameters), body_(body)
    {
    }

    [[nodiscard]] const NameList& parameters() const { return *parameters_; };
    [[nodiscard]] ExpressionNode* body() const { return body_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;
private:
    NameList* parameters_;
    ExpressionNode* body_;
};

#endif //LUA_COMPILER_FUNCTION_EXPR_NODE_H
