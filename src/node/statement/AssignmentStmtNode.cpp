#include "node/statement/AssignmentStmtNode.h"

AssignmentStmtNode::AssignmentStmtNode(Scope scope, ExpressionNodeList* names, ExpressionNodeList* values) :
    StatementNode(Type::Assignment), scope_(scope), names_(names), values_(values)
{
}

void AssignmentStmtNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file info
    os << DOT_NODE_THIS_WITH_LABEL("Assignment" << "\n" << to_string(scope_));

    // Write children node info to dot file
    int indexVariables = 0;
    for (auto* name : *names_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(name, "variable №" << indexVariables++);
        os << *name;
    }

    int indexValues = 0;
    for (auto* value : *values_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(value, "value №" << indexValues++);
        os << *value;
    }
}
