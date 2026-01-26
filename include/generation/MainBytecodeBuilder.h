#ifndef LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
#define LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
#include "BytecodeBuilder.h"
#include "node/statement/BlockStmtNode.h"

class MainBytecodeBuilder : public BytecodeBuilder
{
public:
    MainBytecodeBuilder(Class* currentClass, ClassRegistry* registry, const std::filesystem::path& projectDirectory);
    void build(const BlockStmtNode& node);

protected:
    void buildReturn(const StatementNode *node) override;
};


#endif //LUA_COMPILER_MAIN_BYTECODE_BUILDER_H
