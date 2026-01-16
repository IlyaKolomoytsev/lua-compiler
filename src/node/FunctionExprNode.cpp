#include "FunctionExprNode.h"
#include "DotMacros.h"

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
}
