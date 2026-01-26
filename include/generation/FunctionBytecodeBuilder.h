#ifndef LUA_COMPILER_FUNCTION_BYTECODE_BUILDER_H
#define LUA_COMPILER_FUNCTION_BYTECODE_BUILDER_H
#include <optional>

#include "generation/BytecodeBuilder.h"
#include "node/statement/BlockStmtNode.h"
#include "node/expression/ExpressionNode.h"


class ClassRegistry;

class FunctionBytecodeBuilder : public BytecodeBuilder
{
public:
    FunctionBytecodeBuilder(Class* currentClass, ClassRegistry* registry,
                            const std::filesystem::path& projectDirectory);

    void build(const BlockStmtNode& node, const ExpressionNodeList& arguments);

private:
    void buildApply(const BlockStmtNode& node, const ExpressionNodeList& arguments);
    void buildBridgeApply();
    void buildConstructor();

    Method* baseConstructor();
    Method* applyMethod();
    Method* bridgeApplyMethod();
    Field* contextField();

protected:
    void buildReturn(const StatementNode *node) override;

private:
    const std::string className_;
};


#endif //LUA_COMPILER_FUNCTION_BYTECODE_BUILDER_H
