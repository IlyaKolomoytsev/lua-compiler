#ifndef LUA_COMPILER_CLASS_REGISTRY_H
#define LUA_COMPILER_CLASS_REGISTRY_H
#include <utility>

#include "BytecodeBuilder.h"
#include "MainBytecodeBuilder.h"


class ClassRegistry
{
public:
    ClassRegistry(std::filesystem::path targetDirectory);

    void build(BlockStmtNode* blockNode);
    MainBytecodeBuilder* getBuilderForMain();
    BytecodeBuilder* createNewFunction();

private:
    [[nodiscard]] std::string newFunctionClassName();

    MainBytecodeBuilder* mainBuilder_ = nullptr;
    size_t index_ = 0;
    std::filesystem::path targetDirectory_;
};


#endif //LUA_COMPILER_CLASS_REGISTRY_H
