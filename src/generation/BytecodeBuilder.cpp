#include "generation/BytecodeBuilder.h"

#include <optional>

#include "generation/ClassRegistry.h"
#include "jvm/constant-class.h"
#include "node/NodeExpressionModule.h"


#include "jvm/descriptor-method.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/BlockStmtNode.h"
#include "node/statement/BranchingStmtNode.h"
#include "node/statement/DeclarationStmtNode.h"
#include "node/statement/ForLoopClassicStmtNode.h"
#include "node/statement/StatementNode.h"
#include "node/statement/WhileLoopStmtNode.h"
#include "node/statement/ReturnStmtNode.h"

void BytecodeBuilder::buildBytecode(const ExpressionNode* node)
{
    switch (node->getType())
    {
    case ExpressionNode::Type::Integer:
        {
            auto castNode = static_cast<const IntegerExprNode*>(node);
            emitPushInt(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Float:
        {
            auto castNode = static_cast<const FloatExprNode*>(node);
            emitPushFloat(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::String:
        {
            auto castNode = static_cast<const StringExprNode*>(node);
            emitPushString(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Boolean:
        {
            auto castNode = static_cast<const BoolExprNode*>(node);
            emitPushBool(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Nil:
        emitPushNull();
        break;
    case ExpressionNode::Type::Vararg:
        emitLoadVararg();
        break;
    case ExpressionNode::Type::Id:
        {
            auto castNode = static_cast<const IdExprNode*>(node);
            emitLoadId(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::TableField:
        {
            auto castField = static_cast<const TableFieldExprNode*>(node);
            buildBytecode(castField->getTable());
            buildBytecode(castField->getKey());
            emitBinaryGetFieldByKey();
            break;
        }
    case ExpressionNode::Type::TableConstructor:
        {
            auto* castValue = static_cast<const TableConstructorExprNode*>(node);
            emitTableConstructor(castValue->getTableFields());
            break;
        }
    case ExpressionNode::Type::FunctionCall:
        emitFunctionCallExpr(*static_cast<const FunctionCallExprNode*>(node));
        break;
    case ExpressionNode::Type::FunctionLiteral:
        {
            auto castNode = static_cast<const FunctionExprNode*>(node);
            auto functionBuilder = classRegistry_->createNewFunction();
            functionBuilder->build(*castNode->body(), castNode->parameters());

            std::string newFunctionClassName = functionBuilder->getClass()->getThisClassConstant()->getName()->getString();
            auto classConstant = getClass()->getOrCreateClassConstant(newFunctionClassName);

            auto code = getAttributeCode();
            *code
                << code->New(luaValue.classConstant()) // ..., LuaValue
                << code->Duplicate() // ..., LuaValue, LuaValue
                << code->New(classConstant) // ..., LuaValue, LuaValue, Function
                << code->Duplicate() // ..., LuaValue, LuaValue, Function, Function
                << code->LoadReference(local.getContext()) // ..., LuaValue, LuaValue, Function, Function, context
                << code->InvokeSpecial(customFunction.constructor.base(newFunctionClassName)) // ..., LuaValue, LuaValue, Function
                << code->InvokeSpecial(luaValue.constructor.function()); // ..., LuaValue

            break;
        }
    case ExpressionNode::Type::Summation:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinarySum();
            break;
        }
    case ExpressionNode::Type::Subtraction:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinarySub();
            break;
        }
    case ExpressionNode::Type::Multiplication:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryMul();
            break;
        }
    case ExpressionNode::Type::Division:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryDiv();
            break;
        }
    case ExpressionNode::Type::Modulo:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryMod();
            break;
        }
    case ExpressionNode::Type::IntegerDivision:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryIntDiv();
            break;
        }
    case ExpressionNode::Type::Exponentiation:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryPow();
            break;
        }
    case ExpressionNode::Type::Less:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryLessThan();
            break;
        }
    case ExpressionNode::Type::Greater:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryGreaterThan();
            break;
        }
    case ExpressionNode::Type::Equality:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryEqual();
            break;
        }
    case ExpressionNode::Type::Unequality:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryNotEqual();
            break;
        }
    case ExpressionNode::Type::LessEqual:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryLessEqual();
            break;
        }
    case ExpressionNode::Type::GreaterEqual:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryGreaterEqual();
            break;
        }
    case ExpressionNode::Type::Or:
        {
            auto* castValue = static_cast<const OrExprNode*>(node);
            emitBinaryOr(castValue->getLeft(), castValue->getRight());
            break;
        }
    case ExpressionNode::Type::And:
        {
            auto* castValue = static_cast<const AndExprNode*>(node);
            emitBinaryAnd(castValue->getLeft(), castValue->getRight());
            break;
        }
    case ExpressionNode::Type::Concatenation:
        {
            auto* castValue = static_cast<const ConcatenationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            emitBinaryConcat();
            break;
        }
    case ExpressionNode::Type::Length:
        {
            auto* castValue = static_cast<const LengthExprNode*>(node);
            buildBytecode(castValue->getOperand());
            emitUnaryLen();
            break;
        }
    case ExpressionNode::Type::Negation:
        {
            auto* castValue = static_cast<const NegationExprNode*>(node);
            buildBytecode(castValue->getOperand());
            emitUnaryBooleanNot();
            break;
        }
    case ExpressionNode::Type::UnaryMinuses:
        {
            auto* castValue = static_cast<const UnaryMinusExprNode*>(node);
            buildBytecode(castValue->getOperand());
            emitUnaryUnm();
            break;
        }
    }
}

void BytecodeBuilder::buildBytecode(const StatementNode* node)
{
    switch (node->getType())
    {
    case StatementNode::Type::Declaration:
        {
            auto* castNode = static_cast<const DeclarationStmtNode*>(node);
            emitDeclareLocalIds(castNode->getNames());
            break;
        }
    case StatementNode::Type::Assignment:
        {
            emitAssigment(*static_cast<const AssignmentStmtNode*>(node));
            break;
        }
    case StatementNode::Type::FunctionCall:
        {
            emitFunctionCallStmt(*static_cast<const FunctionCallStmtNode*>(node));
            break;
        }
    case StatementNode::Type::Branching:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const BranchingStmtNode*>(node);
            auto* L_else = code->CodeLabel();
            auto* L_end = code->CodeLabel();

            buildBytecode(castNode->getCondition()); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., bool
                << code->If(Instruction::Compare::Equal, L_else); // if 0 -> L_else

            buildBytecode(castNode->getSuccessBlock());
            *code << code->GoTo(L_end);

            *code << L_else;
            auto* fail = castNode->getFailureBlock();
            if (fail != nullptr)
            {
                buildBytecode(fail);
            }

            *code << L_end;

            break;
        }
    case StatementNode::Type::ForLoopClassic:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const ForLoopClassicStmtNode*>(node);
            auto range = castNode->getRange();

            buildBytecode(range.start);
            auto currentLocal = registerNewLocal(Local::Size::one);
            *code << code->StoreReference(currentLocal->getIndex());

            buildBytecode(range.finish);
            auto finishLocal = registerNewLocal(Local::Size::one);
            *code << code->StoreReference(finishLocal->getIndex());

            buildBytecode(range.step);
            auto stepLocal = registerNewLocal(Local::Size::one);
            *code << code->StoreReference(stepLocal->getIndex());

            auto StartLoop_L = code->CodeLabel();
            auto EndLoop_L = code->CodeLabel();
            auto stepLessThanZeroPrepare = code->CodeLabel();
            auto stepLessThanZeroContinue = code->CodeLabel();

            // if step < 0 goto stepLessThanZeroPrepare
            *code
                << code->LoadReference(stepLocal->getIndex());
            emitPushInt(0);
            emitBinaryLessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, stepLessThanZeroPrepare);

            // if finish < start goto end
            *code
                << code->LoadReference(finishLocal->getIndex())
                << code->LoadReference(currentLocal->getIndex());
            emitBinaryLessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, EndLoop_L)
                << code->GoTo(StartLoop_L);

            *code << stepLessThanZeroPrepare;

            // if finish > start goto end
            *code
                << code->LoadReference(finishLocal->getIndex())
                << code->LoadReference(currentLocal->getIndex());
            emitBinaryLessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::Equal, EndLoop_L);


            *code << StartLoop_L;

            // prepare block context
            emitCreateChildrenContext();
            *code
                << code->LoadReference(local.getContext()) // ..., LuaContext
                << code->PushString(castNode->getIteratorVariableId()->getValue()) // ..., LuaContext, String
                << code->New(luaValue.classConstant()) // ..., LuaContext, String, LuaValue
                << code->Duplicate() // ..., LuaContext, String, LuaValue, LuaValue
                << code->LoadReference(currentLocal->getIndex())
                // ..., LuaContext, String, LuaValue, LuaValue, LuaValue
                << code->InvokeSpecial(luaValue.constructor.anotherLuaValue()) // ..., LuaContext, String, LuaValue
                << code->InvokeVirtual(luaContext.method.declareLocalValueById()); // ...

            // block
            buildBlock(*castNode->getBlock(), false);

            // update loop value
            *code
                << code->LoadReference(currentLocal->getIndex()) // ..., LuaValue
                << code->LoadReference(stepLocal->getIndex()); // ..., LuaValue, LuaValue
            emitBinarySum(); // ..., LuaValue
            *code << code->StoreReference(currentLocal->getIndex()); // ...

            // if step < 0 goto stepLessThanZeroContinue
            *code
                << code->LoadReference(stepLocal->getIndex());
            emitPushInt(0);
            emitBinaryLessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, stepLessThanZeroContinue);

            // if current <= finish goto start
            *code
                << code->LoadReference(finishLocal->getIndex()) // ..., LuaValue
                << code->LoadReference(currentLocal->getIndex()); // ..., LuaValue, LuaValue
            emitBinaryLessThan(); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., boolean
                << code->If(Instruction::Equal, StartLoop_L) // ...
                << code->GoTo(EndLoop_L);


            *code << stepLessThanZeroContinue;

            // if current >= finish goto start
            *code
                << code->LoadReference(finishLocal->getIndex()) // ..., LuaValue
                << code->LoadReference(currentLocal->getIndex()); // ..., LuaValue, LuaValue
            emitBinaryLessEqual(); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., boolean
                << code->If(Instruction::NotEqual, StartLoop_L); // ...

            *code << EndLoop_L;

            // free local variables
            delete currentLocal;
            delete finishLocal;
            delete stepLocal;
            break;
        }
    case StatementNode::Type::ForLoopIterator:
        break;
    case StatementNode::Type::WhileLoop:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const WhileLoopStmtNode*>(node);
            auto* L_cond = code->CodeLabel();
            auto* L_end = code->CodeLabel();

            *code << L_cond;
            buildBytecode(castNode->getCondition()); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., bool
                << code->If(Instruction::Compare::Equal, L_end); // if 0 -> L_end

            buildBytecode(castNode->getBlock());
            *code << code->GoTo(L_cond);

            *code << L_end;
            break;
        }
    case StatementNode::Type::RepeatLoop:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const WhileLoopStmtNode*>(node);
            auto* L_body = code->CodeLabel();
            auto* L_end = code->CodeLabel();

            *code << L_body;
            buildBytecode(castNode->getBlock());

            buildBytecode(castNode->getCondition()); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., bool
                << code->If(Instruction::Compare::Equal, L_body); // if 0 -> L_body

            *code << L_end;
            break;
        }
    case StatementNode::Type::Block:
        {
            buildBlock(*static_cast<const BlockStmtNode*>(node));
            break;
        }
    case StatementNode::Type::GoTo:
        break;
    case StatementNode::Type::Label:
        break;
    case StatementNode::Type::Break:
        break;
    case StatementNode::Type::Return:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const ReturnStmtNode*>(node);

            emitLoadArgumentsToLuaList(*castNode->getReturnExprList()); // ..., LuaList

            *code << code->ReturnReference();
            break;
        }
    }
}

void BytecodeBuilder::emitBinaryAnd(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = getAttributeCode();

    auto* L_end = code->CodeLabel();

    buildBytecode(left); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(luaValue.method.toBool()); // ..., left, bool
    *code << code->If(Instruction::Compare::Equal, L_end); // ..., left

    // true:
    *code << code->PopOne(); // ...
    buildBytecode(right); // ..., right

    *code << L_end;
}

void BytecodeBuilder::emitBinaryOr(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = getAttributeCode();

    auto* L_end = code->CodeLabel();

    buildBytecode(left); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(luaValue.method.toBool()); // ..., left, bool
    *code << code->If(Instruction::Compare::NotEqual, L_end); // ..., left

    // false
    *code << code->PopOne(); // ...
    buildBytecode(right); // ..., right

    *code << L_end;
}

void BytecodeBuilder::emitPushInt(int64_t value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushLong(value)
        << code->InvokeSpecial(luaValue.constructor.integer());
}

void BytecodeBuilder::emitPushFloat(double value)
{
    auto* code = getAttributeCode();
    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(luaValue.constructor.floatNumber());
}

void BytecodeBuilder::emitPushBool(bool value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(luaValue.constructor.boolean());
}

void BytecodeBuilder::emitPushString(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(luaValue.constructor.string());
}

void BytecodeBuilder::emitPushNull()
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->InvokeSpecial(luaValue.constructor.nil());
}

void BytecodeBuilder::emitLoadId(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->LoadReference(local.getContext())
        << code->PushString(value)
        << code->InvokeVirtual(luaContext.method.getById());
}

void BytecodeBuilder::emitBinarySum()
{
    emitStaticCall(luaValue.method.add());
}

void BytecodeBuilder::emitBinarySub()
{
    emitStaticCall(luaValue.method.sub());
}

void BytecodeBuilder::emitBinaryMul()
{
    emitStaticCall(luaValue.method.mul());
}

void BytecodeBuilder::emitBinaryDiv()
{
    emitStaticCall(luaValue.method.div());
}

void BytecodeBuilder::emitBinaryIntDiv()
{
    emitStaticCall(luaValue.method.idiv());
}

void BytecodeBuilder::emitBinaryMod()
{
    emitStaticCall(luaValue.method.mod());
}

void BytecodeBuilder::emitBinaryPow()
{
    emitStaticCall(luaValue.method.pow());
}

void BytecodeBuilder::emitBinaryConcat()
{
    emitStaticCall(luaValue.method.concat());
}

void BytecodeBuilder::emitBinaryEqual()
{
    emitStaticCall(luaValue.method.equal());
}

void BytecodeBuilder::emitBinaryNotEqual()
{
    emitBinaryEqual();
    emitUnaryBooleanNot();
}

void BytecodeBuilder::emitBinaryLessThan()
{
    emitStaticCall(luaValue.method.lessThan());
}

void BytecodeBuilder::emitBinaryLessEqual()
{
    emitStaticCall(luaValue.method.lessEqual());
}

void BytecodeBuilder::emitBinaryGreaterThan()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(luaValue.method.lessThan());
}

void BytecodeBuilder::emitBinaryGreaterEqual()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(luaValue.method.lessEqual());
}

void BytecodeBuilder::emitBinaryGetFieldByKey()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(luaValue.method.fieldByKey());
}

void BytecodeBuilder::emitCall()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(luaValue.method.call());
}

void BytecodeBuilder::emitUnaryUnm()
{
    emitStaticCall(luaValue.method.unMinus());
}

void BytecodeBuilder::emitUnaryLen()
{
    emitStaticCall(luaValue.method.length());
}

void BytecodeBuilder::emitUnaryBooleanNot()
{
    emitStaticCall(luaValue.method.boolNot());
}

void BytecodeBuilder::emitTableConstructor(TableFieldList* fieldList)
{
    auto code = getAttributeCode();
    int64_t index = 0;

    *code
        << code->New(luaValue.classConstant()) // ..., ref(LuaValue)
        << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue)

    emitCreateHashMap(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    for (auto field : *fieldList)
    {
        *code << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap)
        if (field.name != nullptr)
        {
            buildBytecode(field.name); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        else
        {
            emitPushInt(++index); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        buildBytecode(field.value);
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue), ref(LuaValue)

        *code
            << code->InvokeVirtual(hashMap.method.put())
            << code->PopOne();
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    }

    *code << code->InvokeSpecial(luaValue.constructor.table()); // ..., ref(LuaValue)
}

void BytecodeBuilder::emitLoadVararg()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(local.getArgs()) // ..., ref(List of args)
        << code->PushInt(local.getVararg()) // ..., ref(List of args), int
        << code->InvokeVirtual(luaList.method.get()); // ..., ref(LuaValue)
}

void BytecodeBuilder::emitLoadVarargList()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(local.getArgs()) // ..., ref(List of args)
        << code->PushInt(local.getVararg()) // ..., ref(List of args), int
        << code->InvokeVirtual(luaList.method.subList()); // ..., ref(List of vararg)
}

void BytecodeBuilder::emitStaticCall(ConstantMethodref* methodref)
{
    auto* code = getAttributeCode();
    *code << code->InvokeStatic(methodref);
}

void BytecodeBuilder::emitCreateHashMap()
{
    auto* code = getAttributeCode();

    *code
        << code->New(hashMap.classConstant()) // ..., objectref(HashMap)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(hashMap.constructor.base()); // ..., objectref
}

void BytecodeBuilder::buildBlock(const BlockStmtNode& block, bool needCreateNewContext, bool needSetParentContextAfter)
{
    if (needCreateNewContext)
    {
        emitCreateChildrenContext();
    }
    for (auto* stmt : *block.getList())
    {
        buildBytecode(stmt);
    }
    if (needSetParentContextAfter)
    {
        emitGetParentContext();
    }
}

void BytecodeBuilder::emitCreateChildrenContext()
{
    auto code = getAttributeCode();
    const auto contextIndex = local.getContext();
    *code
        << code->New(luaContext.classConstant()) // ..., LuaContext
        << code->Duplicate() // ..., LuaContext, LuaContext
        << code->LoadReference(contextIndex) // ..., LuaContext, LuaContext, LuaContext
        << code->InvokeSpecial(luaContext.constructor.withParent()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void BytecodeBuilder::emitGetParentContext()
{
    auto code = getAttributeCode();
    const auto contextIndex = local.getContext();
    *code
        << code->LoadReference(contextIndex) // ..., LuaContext
        << code->InvokeVirtual(luaContext.method.getParent()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void BytecodeBuilder::emitFunctionCallExpr(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    emitFunctionCallExprList(node);
    *code
        << code->PushInt(0)
        << code->InvokeVirtual(luaList.method.get());
}


void BytecodeBuilder::emitFunctionCallExprList(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    if (node.getWithSelf())
    {
        // The function is a table method, i.e. the self parameter exists only for TableField, so the static_cast is used.
        auto tableFunc = static_cast<TableFieldExprNode*>(node.getFunctionExpression());
        buildBytecode(tableFunc->getTable()); // ..., self
        *code << code->Duplicate(); // ..., self, self
        buildBytecode(tableFunc->getKey()); // ..., self, self, key
        emitBinaryGetFieldByKey(); // ..., self, LuaValue

        *code << code->Swap(); // ..., LuaValue, self
        emitNewLuaList(); // ..., LuaValue, self, LuaList
        *code
            << code->DuplicateBeforeOne() // ..., LuaValue, LuaList, self, LuaList
            << code->Swap(); // .., LuaValue, LuaList, LuaList, self
        emitAddToLuaList(); // ..., LuaValue, LuaList
    }
    else
    {
        buildBytecode(node.getFunctionExpression()); // ..., LuaValue
        emitNewLuaList(); // ..., LuaValue, LuaList
    }

    emitLoadArgumentsToLuaList(node.getFunctionArguments(), false);

    emitCall(); // ..., LuaList
}

void BytecodeBuilder::emitFunctionCallStmt(const FunctionCallStmtNode& node)
{
    auto* code = getAttributeCode();
    buildBytecode(node.getExpression());
    *code << code->PopOne();
}

void BytecodeBuilder::emitAssigment(const AssignmentStmtNode& node)
{
    auto* code = getAttributeCode();

    emitNewLuaList(); // ..., LuaList

    if (node.getScope() == Scope::Global)
    {
        for (auto* exprNode : node.getNameList())
        {
            *code << code->Duplicate(); // ..., LuaList, LuaList
            if (exprNode->getType() == ExpressionNode::Type::Id)
            {
                auto castExpr = static_cast<IdExprNode*>(exprNode);
                *code
                    << code->LoadReference(local.getContext()) // ..., LuaList, LuaList, LuaContext
                    << code->PushString(castExpr->getValue()) // ..., LuaList, LuaList, LuaContext, StringId
                    << code->InvokeVirtual(luaContext.method.getByIdOrCreateNewGlobal());
                // ..., LuaList, LuaList, LuaValue
            }
            else
            {
                buildBytecode(exprNode); // ..., LuaList, LuaList, LuaValue
            }
            emitAddToLuaList(); // ..., LuaList
        }
    }
    else
    {
        for (auto* exprNode : node.getNameList())
        {
            *code << code->Duplicate(); // ..., LuaList, LuaList

            assert(exprNode->getType() == ExpressionNode::Type::Id);
            auto* idExprNode = static_cast<IdExprNode*>(exprNode);
            *code
                << code->LoadReference(local.getContext()) // ..., LuaList, LuaList, LuaContext
                << code->PushString(idExprNode->getValue()) // ..., LuaList, LuaList, LuaContext, string
                << code->InvokeVirtual(luaContext.method.declareLocalId()); // ..., LuaList, LuaList, LuaValue

            emitAddToLuaList(); // ..., LuaList
        }
    }

    emitLoadArgumentsToLuaList(node.getValues()); // ..., LuaList, LuaList

    *code << code->InvokeStatic(luaValue.method.assigment()); // ...
}

void BytecodeBuilder::emitLoadArgumentsToLuaList(const ExpressionNodeList& nodes, bool createListBeforeSet)
{
    auto* code = getAttributeCode();

    if (createListBeforeSet)
    {
        emitNewLuaList();
    }
    // ..., LuaList

    auto it = nodes.begin();
    while (it != nodes.end())
    {
        *code << code->Duplicate(); // ..., LuaList, LuaList
        auto next = std::next(it);
        if (next == nodes.end())
        {
            switch ((*it)->getType())
            {
            case ExpressionNode::Type::Vararg:
                emitLoadVarargList(); // ..., LuaList, LuaList, LuaList
                emitAddAllToLuaList();
                break;
            case ExpressionNode::Type::FunctionCall:
                emitFunctionCallExprList(*static_cast<FunctionCallExprNode*>(*it)); // ..., LuaList, LuaList, LuaList
                emitAddAllToLuaList();
                break;
            default:
                buildBytecode(*it); // ..., LuaList, LuaList, LuaValue
                emitAddToLuaList(); // ..., LuaList
            }
        }
        else
        {
            buildBytecode(*it); // ..., LuaList, LuaList, LuaValue
            emitAddToLuaList(); // ..., LuaList
        }
        it = next;
    }
}

void BytecodeBuilder::emitNewLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaList.classConstant()) // ..., objectref(LuaList)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(luaList.constructor.base()); // ..., objectref
}

void BytecodeBuilder::emitAddToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(luaList.method.add())
        << code->PopOne(); // отбросить bool
}

void BytecodeBuilder::emitAddAllToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(luaList.method.addAll())
        << code->PopOne();
}

void BytecodeBuilder::emitDeclareLocalIds(ExpressionNodeList* ids)
{
    auto* code = getAttributeCode();
    for (auto id : *ids)
    {
        *code << code->LoadReference(local.getContext());
        buildBytecode(id);
        *code << code->InvokeVirtual(luaContext.method.declareLocalId());
    }
}
