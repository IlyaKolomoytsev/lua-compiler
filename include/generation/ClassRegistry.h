#ifndef LUA_COMPILER_CLASS_REGISTRY_H
#define LUA_COMPILER_CLASS_REGISTRY_H
#include "ByteCodeBuilder.h"


class ClassRegistry
{
public:
    ClassRegistry() = default;

    ByteCodeBuilder* getBuilderForMain();
    ByteCodeBuilder* createNewFunction();

private:
    [[nodiscard]] std::string newFunctionClassName();

    ByteCodeBuilder* mainBuilder_ = nullptr;
    size_t index_ = 0;
};


#endif //LUA_COMPILER_CLASS_REGISTRY_H
