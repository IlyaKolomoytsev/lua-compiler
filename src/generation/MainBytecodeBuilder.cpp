#include "generation/MainBytecodeBuilder.h"
#include "jvm/descriptor-method.h"

MainBytecodeBuilder::MainBytecodeBuilder(Class* currentClass, ClassRegistry* registry,
                                         const std::filesystem::path& projectDirectory) :
    BytecodeBuilder(currentClass, registry, projectDirectory)
{
    auto* method = getClass()->getOrCreateMethod(
        "main",
        {
            std::nullopt,
            {{"java/lang/String", 1}}
        }
    );
    method->addFlag(Method::ACC_PUBLIC);
    method->addFlag(Method::ACC_STATIC);

    updateContext(method);
}

void MainBytecodeBuilder::build(const BlockStmtNode& node)
{
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
    getClass()->writeToProject(projectDirectory_);
}

void MainBytecodeBuilder::buildReturn(const StatementNode *node) {
    auto* code = getAttributeCode();
    *code << code->ReturnVoid();
}
