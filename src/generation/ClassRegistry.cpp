#include "generation/ClassRegistry.h"

#include "jvm/descriptor-method.h"

ClassRegistry::ClassRegistry(std::filesystem::path targetDirectory) : targetDirectory_(std::move(targetDirectory))
{
}

void ClassRegistry::build(BlockStmtNode* blockNode)
{
    auto builder = getBuilderForMain();
    builder->build(*blockNode);
    builder->getClass()->writeToProject(targetDirectory_);
}

MainBytecodeBuilder* ClassRegistry::getBuilderForMain()
{
    if (mainBuilder_ == nullptr)
    {
        auto* functionClass = new Class("Main", "java/lang/Object");
        auto* method = functionClass->getOrCreateMethod(
            "main",
            {
                std::nullopt,
                {{"java/lang/String", 1}}
            }
        );
        method->addFlag(Method::ACC_PUBLIC);
        method->addFlag(Method::ACC_STATIC);

        mainBuilder_ = new MainBytecodeBuilder(functionClass, method, this);
    }
    return mainBuilder_;
}

BytecodeBuilder* ClassRegistry::createNewFunction()
{
    auto* functionClass = new Class(newFunctionClassName(), "com/luajvm/LuaFunction");
    auto* method = functionClass->getOrCreateMethod(
        "apply",
        {
            DescriptorField("java/util/List"),
            {{"java/util/List"}}
        }
    );
    method->addFlag(Method::ACC_PUBLIC);

    return new BytecodeBuilder(functionClass, method, this);
}

std::string ClassRegistry::newFunctionClassName()
{
    return "LuaFunction_" + std::to_string(index_++);
}
