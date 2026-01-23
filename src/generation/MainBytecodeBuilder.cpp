#include "generation/MainBytecodeBuilder.h"

MainBytecodeBuilder::MainBytecodeBuilder(Class* currentClass, Method* currentMethod, ClassRegistry* registry) :
    BytecodeBuilder(currentClass, currentMethod, registry)
{
}

void MainBytecodeBuilder::build(const BlockStmtNode& node)
{
    auto* code = getAttributeCode();
    auto* contextIndex = registerNewLocal(Local::Size::one);

    // create new context
    *code
        << code->New(luaContext.classConstant())
        << code->Duplicate()
        << code->InvokeSpecial(luaContext.constructor.root())
        << code->StoreReference(contextIndex->getIndex());
    setContextIndexInLocals(contextIndex->getIndex());

    for (auto* stmt : *node.getList())
    {
        buildBytecode(stmt);
    }
    *code << code->ReturnVoid();

    delete contextIndex;
}