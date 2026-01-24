#include "generation/MainBytecodeBuilder.h"
#include "jvm/descriptor-method.h"

MainBytecodeBuilder::MainBytecodeBuilder(Class* currentClass, Method* currentMethod, ClassRegistry* registry) :
    BytecodeBuilder(currentClass, registry)
{
}

void MainBytecodeBuilder::build(const BlockStmtNode& node)
{
    auto* method = getClass()->getOrCreateMethod(
        "main",
        {
            std::nullopt,
            {{"java/lang/String", 1}}
        }
    );
    method->addFlag(Method::ACC_PUBLIC);
    updateContext(method);

    auto* code = getAttributeCode();
    local.setContext(registerNewLocal(Local::Size::one));

    // create new context
    *code
        << code->New(luaContext.classConstant())
        << code->Duplicate()
        << code->InvokeSpecial(luaContext.constructor.root())
        << code->StoreReference(local.getContext());

    for (auto* stmt : *node.getList())
    {
        buildBytecode(stmt);
    }
    *code << code->ReturnVoid();

    local.clearContext();
}