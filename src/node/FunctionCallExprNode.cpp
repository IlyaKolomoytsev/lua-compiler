#include "FunctionCallExprNode.h"
#include "DotMacros.h"

void FunctionCallExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("FunctionCall");

    // Write children node info to dot file
    os << DOT_ARC_THIS_OTHER_LABEL(function_, "Function");
    int index = 0;
    for (auto* arg: *arguments_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(arg, "argument №" << index++);
    }

    os << *function_;
    for (auto* arg: *arguments_)
    {
        os << *arg;
    }
}
