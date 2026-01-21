#include "generation/ClassRegistry.h"

#include "jvm/descriptor-method.h"

ByteCodeBuilder* ClassRegistry::getBuilderForMain()
{
    if (mainBuilder_ == nullptr)
    {
        auto* functionClass = new Class("Main", "java/lang/Object");
        auto* method = functionClass->getOrCreateMethod(
            "main",
            {std::nullopt, {}}
        );
        method->addFlag(Method::ACC_PUBLIC);
        method->addFlag(Method::ACC_STATIC);

        mainBuilder_ = new ByteCodeBuilder(functionClass, method);
    }
    return mainBuilder_;
}

ByteCodeBuilder* ClassRegistry::createNewFunction()
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

    return new ByteCodeBuilder(functionClass, method);
}

std::string ClassRegistry::newFunctionClassName()
{
    return "LuaFunction_" + std::to_string(index_++);
}
