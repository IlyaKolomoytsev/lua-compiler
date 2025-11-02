#ifndef LUA_COMPILER_NODE_H
#define LUA_COMPILER_NODE_H
#include <sys/types.h>
#include <ostream>


class Node
{
    using node_id_t = uint;

public:
    Node();

    virtual ~Node() = default;

    node_id_t getNodeId() const;

    static node_id_t getMaxNideId();

    virtual void writeNodeInfoToDot(std::ostream& os) const = 0;

private:
    const node_id_t id;
    static node_id_t maxId;
};

std::ostream& operator<<(std::ostream& os, const Node& node);

#endif //LUA_COMPILER_NODE_H
