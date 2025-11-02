#include "Node.h"

Node::Node() : id(++maxId)
{
}

Node::node_id_t Node::getNodeId() const
{
    return id;
}

inline Node::node_id_t Node::getMaxNideId()
{
    return maxId;
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    node.writeNodeInfoToDot(os);
    return os;
}

Node::node_id_t Node::maxId = 0;
