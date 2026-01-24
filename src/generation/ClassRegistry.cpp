#include "generation/ClassRegistry.h"

#include "jvm/descriptor-method.h"

ClassRegistry::ClassRegistry(std::filesystem::path targetDirectory) : targetDirectory_(std::move(targetDirectory))
{
}

void ClassRegistry::build(BlockStmtNode* blockNode)
{
    auto builder = getBuilderForMain();
    builder->build(*blockNode);
}

MainBytecodeBuilder* ClassRegistry::getBuilderForMain()
{
    if (mainBuilder_ == nullptr)
    {
        auto* functionClass = new Class("Main", "java/lang/Object");

        mainBuilder_ = new MainBytecodeBuilder(functionClass, this, targetDirectory_);
    }
    return mainBuilder_;
}

FunctionBytecodeBuilder* ClassRegistry::createNewFunction()
{
    auto* functionClass = new Class(newFunctionClassName(), "java/lang/Object");
    functionClass->addInterface(functionClass->getOrCreateClassConstant("java/util/function/Function"));
    return new FunctionBytecodeBuilder(functionClass, this, targetDirectory_);
}

std::string ClassRegistry::newFunctionClassName()
{
    return "LuaFunction_" + std::to_string(index_++);
}
