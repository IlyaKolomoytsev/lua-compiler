#include "node/Node.h"

Node::Node() : id(++maxId)
{
}

Node::node_id_t Node::getNodeId() const
{
    return id;
}

inline Node::node_id_t Node::getMaxNodeId()
{
    return maxId;
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    node.writeNodeInfoToDot(os);
    return os;
}

Node::node_id_t Node::maxId = 0;
