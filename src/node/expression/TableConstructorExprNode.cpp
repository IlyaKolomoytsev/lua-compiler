#include "node/expression/TableConstructorExprNode.h"
#include "node/DotMacros.h"

void TableConstructorExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("TableConstructor");

    // Write children node info to dot file
    int index = 0;
    for (auto field: *fields_)
    {
        if (field.name)
        {
            os << DOT_ARC_THIS_OTHER_LABEL(field.name, "key " << index);
        }
        os << DOT_ARC_THIS_OTHER_LABEL(field.value, "value " << index);
        index++;
    }

    for (auto field : *fields_)
    {
        if (field.name)
            os << *field.name;
        os << *field.value;
    }

}
