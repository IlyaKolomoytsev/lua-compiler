#include "Node.h"

Node::Node() : id(++maxId)
{
}

inline Node::node_id_t Node::getNodeId() const
{
    return id;
}

inline Node::node_id_t Node::getMaxNideId()
{
    return maxId;
}

Node::node_id_t Node::maxId = 0;
