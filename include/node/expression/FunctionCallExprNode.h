#ifndef LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#define LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
#include <complex>

#include "node/expression/ExpressionNode.h"
#include "node/expression/TableConstructorExprNode.h"

using FunctionArgumentsList = std::list<ExpressionNode*>;

class FunctionCallExprNode : public ExpressionNode
{
public:
    FunctionCallExprNode(ExpressionNode* function, FunctionArgumentsList* arguments, bool withSelf) :
        ExpressionNode(Type::FunctionCall), function_(function), arguments_(arguments), withSelf_(withSelf)
    {
    }

    [[nodiscard]] ExpressionNode* getFunctionExpression() const { return function_; }
    [[nodiscard]] const ExpressionNodeList& getFunctionArguments() const { return *arguments_; }
    [[nodiscard]] bool getWithSelf() const { return withSelf_; }

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;
    void makeBytecode(const ByteCodeBuilder& builder) const override;

private:
    ExpressionNode* function_;
    FunctionArgumentsList* arguments_;
    bool withSelf_;
};

#endif //LUA_COMPILER_FUNCTION_CALL_EXPR_NODE_H
