#ifndef LUA_COMPILER_DOT_MACROS_H
#define LUA_COMPILER_DOT_MACROS_H

#define NODE_ID(node) \
    node->getNodeId()

#define DOT_LABEL(text) \
    "label=\"" << text << "\""

#define DOT_ARC(source, destination, properties) \
    source << " -> " << destination << " [" << properties << "]" << std::endl

#define DOT_ARC_WITH_LABEL(source, destination, label) \
    DOT_ARC(source, destination, DOT_LABEL(label))

#define DOT_ARC_NODE_ID(source, destination, properties) \
    DOT_ARC(NODE_ID(source), NODE_ID(destination), properties)

#define DOT_ARC_NODE_ID_WITH_LABEL(source, destination, label) \
    DOT_ARC_NODE_ID(source, destination, DOT_LABEL(label))

#endif //LUA_COMPILER_DOT_MACROS_H
