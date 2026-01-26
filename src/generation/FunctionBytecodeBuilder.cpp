#include "generation/FunctionBytecodeBuilder.h"

#include "jvm/constant-class.h"
#include "jvm/descriptor-method.h"
#include "jvm/field.h"
#include "node/NodeExpressionModule.h"
#include "node/statement/ReturnStmtNode.h"

class ReturnStmtNode;

FunctionBytecodeBuilder::FunctionBytecodeBuilder(Class* currentClass, ClassRegistry* registry,
                                                 const std::filesystem::path& projectDirectory) :
    BytecodeBuilder(currentClass, registry, projectDirectory),
    className_(currentClass->getThisClassConstant()->getName()->getString())
{
    // create class members
    auto constructor = baseConstructor();
    constructor->addFlag(Method::ACC_PUBLIC);
    auto method = applyMethod();
    method->addFlag(Method::ACC_PUBLIC);
    auto bridgeMethod = bridgeApplyMethod();
    bridgeMethod->addFlag(Method::ACC_PUBLIC);
    bridgeMethod->addFlag(Method::ACC_BRIDGE);
    bridgeMethod->addFlag(Method::ACC_SYNTHETIC);
    auto field = contextField();
    field->addFlag(Field::ACC_PRIVATE);
}

void FunctionBytecodeBuilder::build(const BlockStmtNode& node, const ExpressionNodeList& arguments)
{
    // build constructor
    updateContext(baseConstructor());
    buildConstructor();
    // build bridge apply method
    updateContext(bridgeApplyMethod());
    buildBridgeApply();
    // build apply method
    updateContext(applyMethod());
    buildApply(node, arguments);
    // write to project
    getClass()->writeToProject(projectDirectory_);
}

void FunctionBytecodeBuilder::buildApply(const BlockStmtNode& node, const ExpressionNodeList& arguments)
{
    auto* code = getAttributeCode();

    // declare locals by function signature
    auto thisLocal = registerNewLocal(Local::Size::one);
    local.setArgs(registerNewLocal(Local::Size::one));

    /* move context from field to locals */
    // get context field from class
    *code
        << code->New(luaContext.classConstant()) // ..., LuaContext
        << code->Duplicate() // ..., LuaContext, LuaContext
        << code->LoadReference(thisLocal->getIndex()) // ..., LuaContext, LuaContext, this
        << code->GetField(customFunction.field.context(className_)) // ..., LuaContext, LuaContext, context
        << code->InvokeSpecial(luaContext.constructor.withParent()); // ..., LuaContext
    // write context instead of this in locals
    delete thisLocal;
    local.setContext(registerNewLocal(Local::Size::one));
    *code << code->StoreReference(local.getContext());

    /* move arguments to context */
    int32_t index = 0;
    for (auto* argument : arguments)
    {
        auto type = argument->getType();
        if (type == ExpressionNode::Type::Id)
        {
            auto argumentName = static_cast<IdExprNode*>(argument)->getValue();
            *code
                << code->LoadReference(local.getContext()) // ..., context
                << code->PushString(argumentName) // ..., context, string
                << code->LoadReference(local.getArgs()) // ..., context, string, args
                << code->PushInt(index) // ..., context, string, args, int
                << code->InvokeVirtual(luaList.method.get()) // ..., context, string, value
                << code->InvokeVirtual(luaContext.method.declareLocalValueById()); // ...
        }
        else if (type == ExpressionNode::Type::Vararg)
        {
            // only one argument can be vararg
            varargIndexInArguments_ = index;
        }
        index++;
    }

    // function call
    buildBlock(node, false, false);

    // return empty list
    *code
        << code->New(luaList.classConstant()) // ..., LuaList
        << code->Duplicate() // ..., LuaList, LuaList
        << code->InvokeSpecial(luaList.constructor.base()) // ..., LuaList
        << code->ReturnReference(); // ...

    // free locals
    local.clearArgs();
    local.clearContext();
    // reset vararg
    varargIndexInArguments_ = -1;
}

void FunctionBytecodeBuilder::buildBridgeApply()
{
    auto thisLocal = registerNewLocal(Local::Size::one);
    auto argsLocal = registerNewLocal(Local::Size::one);

    auto code = getAttributeCode();
    *code
        << code->LoadReference(thisLocal->getIndex()) // ..., this
        << code->LoadReference(argsLocal->getIndex()) // ..., this, Object
        << code->CheckCast(luaList.classConstant()) // ..., this, LuaList
        << code->InvokeVirtual(customFunction.method.apply(className_)) // ..., LuaList
        << code->ReturnReference(); // ...

    delete thisLocal;
    delete argsLocal;
}

void FunctionBytecodeBuilder::buildConstructor()
{
    // create locals
    auto thisLocal = registerNewLocal(Local::Size::one);
    auto contextArgumentLocal = registerNewLocal(Local::Size::one);

    auto code = getAttributeCode();
    *code
        << code->LoadReference(thisLocal->getIndex()) // ..., this
        << code->InvokeSpecial(object.constructor.base()) // ...
        << code->LoadReference(thisLocal->getIndex()) // ..., this
        << code->LoadReference(contextArgumentLocal->getIndex()) // ..., this, context
        << code->PutField(customFunction.field.context(className_)) // ...
        << code->ReturnVoid();

    // free locals
    delete thisLocal;
    delete contextArgumentLocal;
}

Method* FunctionBytecodeBuilder::baseConstructor()
{
    return getClass()->getOrCreateMethod(
        "<init>",
        DescriptorMethod(
            std::nullopt,
            {{"com/luajvm/LuaContext"}}
        )
    );
}

Method* FunctionBytecodeBuilder::applyMethod()
{
    return getClass()->getOrCreateMethod(
        "apply",
        DescriptorMethod(
            DescriptorField("com/luajvm/LuaList"),
            {{"com/luajvm/LuaList"}}
        )
    );
}

Method* FunctionBytecodeBuilder::bridgeApplyMethod()
{
    return getClass()->getOrCreateMethod(
        "apply",
        DescriptorMethod(
            DescriptorField("java/lang/Object"),
            {{"java/lang/Object"}}
        )
    );
}

Field* FunctionBytecodeBuilder::contextField()
{
    return getClass()->getOrCreateField(
        "context",
        {"com/luajvm/LuaContext"}
    );
}

void FunctionBytecodeBuilder::buildReturn(const StatementNode *node) {
    auto* code = getAttributeCode();
    auto* castNode = static_cast<const ReturnStmtNode*>(node);

    emitLoadArgumentsToLuaList(*castNode->getReturnExprList()); // ..., LuaList

    *code << code->ReturnReference();
}
