#ifndef LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
#define LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
#include "BytecodeBuilder.h"


class MainBytecodeBuilder : public BytecodeBuilder
{
public:
    MainBytecodeBuilder(Class* currentClass, Method* currentMethod, ClassRegistry* registry);
    void build(const BlockStmtNode& node);
};


#endif //LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
