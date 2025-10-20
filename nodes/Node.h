#ifndef LUA_COMPILER_NODE_H
#define LUA_COMPILER_NODE_H
#include <sys/types.h>


class Node
{
    using node_id_t = uint;

public:
    Node();

    node_id_t getNodeId() const;

    static node_id_t getMaxNideId();

private:
    const node_id_t id;
    static node_id_t maxId;
};

#endif //LUA_COMPILER_NODE_H
