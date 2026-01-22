#ifndef LUA_COMPILER_BYTE_CODE_BUILDER_H
#define LUA_COMPILER_BYTE_CODE_BUILDER_H
#include "CodeGenContext.h"
#include "jvm/class.h"
#include "jvm/method.h"
#include "node/expression/ExpressionNode.h"
#include "node/expression/FunctionCallExprNode.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/BlockStmtNode.h"
#include "node/statement/FunctionCallStmtNode.h"


class ClassRegistry;

using namespace jvm;

class ByteCodeBuilder : public CodeGenContext
{
public:
    ByteCodeBuilder(Class* currentClass, Method* currentMethod, ClassRegistry* registry) :
        CodeGenContext(currentClass, currentMethod), classRegistry_(registry)
    {
    }
    void build(const BlockStmtNode& node);

private:
    void buildBytecode(const ExpressionNode* node);
    void buildBytecode(const StatementNode* node);

    //region Bool operation
    void buildAnd(const ExpressionNode* left, const ExpressionNode* right);
    void buildOr(const ExpressionNode* left, const ExpressionNode* right);
    //endregion
    //region Push LuaValue primitive on stack
    void pushInt(int64_t value);
    void pushFloat(double value);
    void pushBool(bool value);
    void pushString(const std::string& value);
    void pushNull();

    void id(const std::string& value);
    //endregion
    //region Operations with two operands
    void sum();
    void sub();
    void mul();
    void div();
    void idiv();
    void mod();
    void pow();
    void concat();
    void equal();
    void notEqual();
    void lessThan();
    void lessEqual();
    void greaterThan();
    void greaterEqual();
    void getFieldByKey();
    void call();
    //endregion
    //region Operations with one operand
    void unm();
    void len();
    void booleanNot();
    //endregion
    //region Others
    void tableConstructor(TableFieldList* fieldList);
    void pushVararg();
    void pushVarargList();
    //endregion

    void createLuaList();
    void addToLuaList();
    void addAllToList();

    void declareIds(ExpressionNodeList* ids);

    //region Helpers
    void emitStaticCall(ConstantMethodref* methodref);
    void createHashMap();
    void buildBlock(const BlockStmtNode& block, bool needCreateNewContext = true, bool needSetParentContextAfter = true);
    void createChildrenContext();
    void getParentContext();
    //endregion

    void functionCallExpr(const FunctionCallExprNode& node);
    void functionCallExprList(const FunctionCallExprNode& node);
    void functionCallStmt(const FunctionCallStmtNode& node);
    void assigment(const AssignmentStmtNode& node);
    void pushArgumentsList(const ExpressionNodeList& nodes, bool createListBeforeSet = true);
    ClassRegistry* classRegistry_;
};

#endif //LUA_COMPILER_BYTE_CODE_BUILDER_H
