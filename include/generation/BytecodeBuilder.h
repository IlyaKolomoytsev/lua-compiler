#ifndef LUA_COMPILER_BYTE_CODE_BUILDER_H
#define LUA_COMPILER_BYTE_CODE_BUILDER_H
#include "CodeGenContext.h"
#include "MethodCodeGenContext.h"
#include "jvm/class.h"
#include "jvm/method.h"
#include "node/expression/ExpressionNode.h"
#include "node/expression/FunctionCallExprNode.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/BlockStmtNode.h"
#include "node/statement/FunctionCallStmtNode.h"

#define LOCAL_FIELD(name) \
public:                             \
inline uint16_t get##name()         \
{                                   \
    assert(name##_ != nullptr);     \
    return name##_->getIndex();     \
}                                   \
inline void set##name(Local* local) \
{                                   \
    name##_ = local;                \
}                                   \
inline void clear##name()           \
{                                   \
    if(name##_ != nullptr)          \
    {                               \
        delete name##_;             \
        name##_ = nullptr;          \
    }                               \
}                                   \
private:                            \
Local* name##_ = nullptr;

class ClassRegistry;

using namespace jvm;

class BytecodeBuilder : public MethodCodeGenContext
{
public:
    BytecodeBuilder(Class* currentClass, ClassRegistry* registry, const std::filesystem::path& projectDirectory) :
        MethodCodeGenContext(currentClass), classRegistry_(registry), projectDirectory_(projectDirectory)
    {
    }

protected:
    struct Locals
    {
        LOCAL_FIELD(This)
        LOCAL_FIELD(Args)
        LOCAL_FIELD(Context)
        LOCAL_FIELD(Vararg)
    } local;

    //region Build
    void buildBytecode(const ExpressionNode* node);
    void buildBytecode(const StatementNode* node);
    void buildBlock(const BlockStmtNode& block, bool needCreateNewContext = true, bool needSetParentContextAfter = true);
    //endregion
    //region Push LuaValue primitive on stack
    void emitPushNull();
    void emitPushInt(int64_t value);
    void emitPushFloat(double value);
    void emitPushBool(bool value);
    void emitPushString(const std::string& value);
    //endregion
    //region Load on stack
    void emitLoadId(const std::string& value);
    void emitLoadVararg();
    void emitLoadVarargList();
    //endregion
    //region Operations with two operands
    void emitBinarySum();
    void emitBinarySub();
    void emitBinaryMul();
    void emitBinaryDiv();
    void emitBinaryIntDiv();
    void emitBinaryMod();
    void emitBinaryPow();
    void emitBinaryConcat();
    void emitBinaryEqual();
    void emitBinaryNotEqual();
    void emitBinaryLessThan();
    void emitBinaryLessEqual();
    void emitBinaryGreaterThan();
    void emitBinaryGreaterEqual();
    void emitBinaryGetFieldByKey();
    void emitBinaryAnd(const ExpressionNode* left, const ExpressionNode* right);
    void emitBinaryOr(const ExpressionNode* left, const ExpressionNode* right);
    //endregion
    //region Operations with one operand
    void emitUnaryUnm();
    void emitUnaryLen();
    void emitUnaryBooleanNot();
    //endregion
    //region LuaList
    void emitNewLuaList();
    void emitAddToLuaList();
    void emitAddAllToLuaList();
    void emitLoadArgumentsToLuaList(const ExpressionNodeList& nodes, bool createListBeforeSet = true);
    //endregion
    //region Context
    void emitCreateChildrenContext();
    void emitGetParentContext();
    void emitAssigment(const AssignmentStmtNode& node);
    void emitDeclareLocalIds(ExpressionNodeList* ids);
    //endregion
    //region Work with functions
    void emitCall();
    void emitFunctionCallExpr(const FunctionCallExprNode& node);
    void emitFunctionCallExprList(const FunctionCallExprNode& node);
    void emitFunctionCallStmt(const FunctionCallStmtNode& node);
    void emitStaticCall(ConstantMethodref* methodref);
    //endregion
    //region Tables
    void emitTableConstructor(TableFieldList* fieldList);
    void emitCreateHashMap();
    //endregion

    ClassRegistry* classRegistry_;
    std::filesystem::path projectDirectory_;
};

#endif //LUA_COMPILER_BYTE_CODE_BUILDER_H
