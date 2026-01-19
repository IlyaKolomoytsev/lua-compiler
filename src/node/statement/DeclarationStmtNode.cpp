#include "node/statement/DeclarationStmtNode.h"

DeclarationStmtNode::DeclarationStmtNode(ExpressionNodeList* names) : StatementNode(Type::Declaration), names_(names)
{
}

void DeclarationStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file noto_string(to_string(de info
    os << DOT_NODE_THIS_WITH_LABEL("Declaration");

    // Write children node info to dot file
    int indexVariables = 0;
    for (auto* name : *names_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(name, "declare №" << indexVariables++);
        os << *name;
    }
}
