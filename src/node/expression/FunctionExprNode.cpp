#include "node/expression/FunctionExprNode.h"
#include "node/DotMacros.h"
#include "node/statement/StatementNode.h"

void FunctionExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("FunctionLiteral");

    // Write children node info to dot file
    int index = 0;
    for (auto* parameter : *parameters_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(parameter, "param " << index++);
        os << *parameter;
    }

    // Write function body
    os << DOT_ARC_THIS_OTHER_LABEL(body_, "body");
    os << *body_;
}

void FunctionExprNode::makeBytecode(ByteCodeBuilder& builder) const
{
}
