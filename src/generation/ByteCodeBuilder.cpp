#include "generation/ByteCodeBuilder.h"

#include <optional>

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

void ByteCodeBuilder::build(const BlockStmtNode& node)
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

void ByteCodeBuilder::buildBytecode(const ExpressionNode* node)
{
    switch (node->getType())
    {
    case ExpressionNode::Type::Integer:
        {
            auto castNode = static_cast<const IntegerExprNode*>(node);
            pushInt(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Float:
        {
            auto castNode = static_cast<const FloatExprNode*>(node);
            pushFloat(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::String:
        {
            auto castNode = static_cast<const StringExprNode*>(node);
            pushString(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Boolean:
        {
            auto castNode = static_cast<const BoolExprNode*>(node);
            pushBool(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::Nil:
        pushNull();
        break;
    case ExpressionNode::Type::Vararg:
        pushVararg();
        break;
    case ExpressionNode::Type::Id:
        {
            auto castNode = static_cast<const IdExprNode*>(node);
            id(castNode->getValue());
            break;
        }
    case ExpressionNode::Type::TableField:
        {
            auto castField = static_cast<const TableFieldExprNode*>(node);
            buildBytecode(castField->getTable());
            buildBytecode(castField->getKey());
            getFieldByKey();
            break;
        }
    case ExpressionNode::Type::TableConstructor:
        {
            auto* castValue = static_cast<const TableConstructorExprNode*>(node);
            tableConstructor(castValue->getTableFields());
            break;
        }
    case ExpressionNode::Type::FunctionCall:
        functionCallExpr(*static_cast<const FunctionCallExprNode*>(node));
        break;
    case ExpressionNode::Type::FunctionLiteral:
        // ToDo
        break;
    case ExpressionNode::Type::Summation:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            sum();
            break;
        }
    case ExpressionNode::Type::Subtraction:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            sub();
            break;
        }
    case ExpressionNode::Type::Multiplication:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            mul();
            break;
        }
    case ExpressionNode::Type::Division:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            div();
            break;
        }
    case ExpressionNode::Type::Modulo:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            mod();
            break;
        }
    case ExpressionNode::Type::IntegerDivision:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            idiv();
            break;
        }
    case ExpressionNode::Type::Exponentiation:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            pow();
            break;
        }
    case ExpressionNode::Type::Less:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            lessThan();
            break;
        }
    case ExpressionNode::Type::Greater:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            greaterThan();
            break;
        }
    case ExpressionNode::Type::Equality:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            equal();
            break;
        }
    case ExpressionNode::Type::Unequality:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            notEqual();
            break;
        }
    case ExpressionNode::Type::LessEqual:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            lessEqual();
            break;
        }
    case ExpressionNode::Type::GreaterEqual:
        {
            auto* castValue = static_cast<const SummationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            greaterEqual();
            break;
        }
    case ExpressionNode::Type::Or:
        {
            auto* castValue = static_cast<const OrExprNode*>(node);
            buildOr(castValue->getLeft(), castValue->getRight());
            break;
        }
    case ExpressionNode::Type::And:
        {
            auto* castValue = static_cast<const AndExprNode*>(node);
            buildAnd(castValue->getLeft(), castValue->getRight());
            break;
        }
    case ExpressionNode::Type::Concatenation:
        {
            auto* castValue = static_cast<const ConcatenationExprNode*>(node);
            buildBytecode(castValue->getLeft());
            buildBytecode(castValue->getRight());
            concat();
            break;
        }
    case ExpressionNode::Type::Length:
        {
            auto* castValue = static_cast<const LengthExprNode*>(node);
            buildBytecode(castValue->getOperand());
            len();
            break;
        }
    case ExpressionNode::Type::Negation:
        {
            auto* castValue = static_cast<const NegationExprNode*>(node);
            buildBytecode(castValue->getOperand());
            booleanNot();
            break;
        }
    case ExpressionNode::Type::UnaryMinuses:
        {
            auto* castValue = static_cast<const UnaryMinusExprNode*>(node);
            buildBytecode(castValue->getOperand());
            unm();
            break;
        }
    }
}

void ByteCodeBuilder::buildBytecode(const StatementNode* node)
{
    switch (node->getType())
    {
    case StatementNode::Type::Declaration:
        {
            auto* castNode = static_cast<const DeclarationStmtNode*>(node);
            declareIds(castNode->getNames());
            break;
        }
    case StatementNode::Type::Assignment:
        {
            assigment(*static_cast<const AssignmentStmtNode*>(node));
            break;
        }
    case StatementNode::Type::FunctionCall:
        {
            functionCallStmt(*static_cast<const FunctionCallStmtNode*>(node));
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
            pushInt(0);
            lessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, stepLessThanZeroPrepare);

            // if finish < start goto end
            *code
                << code->LoadReference(finishLocal->getIndex())
                << code->LoadReference(currentLocal->getIndex());
            lessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, EndLoop_L)
                << code->GoTo(StartLoop_L);

            *code << stepLessThanZeroPrepare;

            // if finish > start goto end
            *code
                << code->LoadReference(finishLocal->getIndex())
                << code->LoadReference(currentLocal->getIndex());
            lessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::Equal, EndLoop_L);



            *code << StartLoop_L;

            // prepare block context
            createChildrenContext();
            *code
                << code->LoadReference(getContextIndexInLocals()) // ..., LuaContext
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
            sum(); // ..., LuaValue
            *code << code->StoreReference(currentLocal->getIndex()); // ...

            // if step < 0 goto stepLessThanZeroContinue
            *code
                << code->LoadReference(stepLocal->getIndex());
            pushInt(0);
            lessThan();
            *code
                << code->InvokeVirtual(luaValue.method.toBool())
                << code->If(Instruction::Compare::NotEqual, stepLessThanZeroContinue);

            // if current <= finish goto start
            *code
                << code->LoadReference(finishLocal->getIndex()) // ..., LuaValue
                << code->LoadReference(currentLocal->getIndex()); // ..., LuaValue, LuaValue
            lessThan(); // ..., LuaValue
            *code
                << code->InvokeVirtual(luaValue.method.toBool()) // ..., boolean
                << code->If(Instruction::Equal, StartLoop_L) // ...
                << code->GoTo(EndLoop_L);


            *code << stepLessThanZeroContinue;

            // if current >= finish goto start
            *code
                << code->LoadReference(finishLocal->getIndex()) // ..., LuaValue
                << code->LoadReference(currentLocal->getIndex()); // ..., LuaValue, LuaValue
            lessEqual(); // ..., LuaValue
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

            pushArgumentsList(*castNode->getReturnExprList()); // ..., LuaList

            *code << code->ReturnReference();
            break;
        }
    }
}

void ByteCodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
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

void ByteCodeBuilder::buildOr(const ExpressionNode* left, const ExpressionNode* right)
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

void ByteCodeBuilder::pushInt(int64_t value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushLong(value)
        << code->InvokeSpecial(luaValue.constructor.integer());
}

void ByteCodeBuilder::pushFloat(double value)
{
    auto* code = getAttributeCode();
    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(luaValue.constructor.floatNumber());
}

void ByteCodeBuilder::pushBool(bool value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(luaValue.constructor.boolean());
}

void ByteCodeBuilder::pushString(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(luaValue.constructor.string());
}

void ByteCodeBuilder::pushNull()
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaValue.classConstant())
        << code->Duplicate()
        << code->InvokeSpecial(luaValue.constructor.nil());
}

void ByteCodeBuilder::id(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->LoadReference(getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(luaContext.method.getById());
}

void ByteCodeBuilder::sum()
{
    emitStaticCall(luaValue.method.add());
}

void ByteCodeBuilder::sub()
{
    emitStaticCall(luaValue.method.sub());
}

void ByteCodeBuilder::mul()
{
    emitStaticCall(luaValue.method.mul());
}

void ByteCodeBuilder::div()
{
    emitStaticCall(luaValue.method.div());
}

void ByteCodeBuilder::idiv()
{
    emitStaticCall(luaValue.method.idiv());
}

void ByteCodeBuilder::mod()
{
    emitStaticCall(luaValue.method.mod());
}

void ByteCodeBuilder::pow()
{
    emitStaticCall(luaValue.method.pow());
}

void ByteCodeBuilder::concat()
{
    emitStaticCall(luaValue.method.concat());
}

void ByteCodeBuilder::equal()
{
    emitStaticCall(luaValue.method.equal());
}

void ByteCodeBuilder::notEqual()
{
    equal();
    booleanNot();
}

void ByteCodeBuilder::lessThan()
{
    emitStaticCall(luaValue.method.lessThan());
}

void ByteCodeBuilder::lessEqual()
{
    emitStaticCall(luaValue.method.lessEqual());
}

void ByteCodeBuilder::greaterThan()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(luaValue.method.lessThan());
}

void ByteCodeBuilder::greaterEqual()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(luaValue.method.lessEqual());
}

void ByteCodeBuilder::getFieldByKey()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(luaValue.method.fieldByKey());
}

void ByteCodeBuilder::call()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(luaValue.method.call());
}

void ByteCodeBuilder::unm()
{
    emitStaticCall(luaValue.method.unMinus());
}

void ByteCodeBuilder::len()
{
    emitStaticCall(luaValue.method.length());
}

void ByteCodeBuilder::booleanNot()
{
    emitStaticCall(luaValue.method.boolNot());
}

void ByteCodeBuilder::tableConstructor(TableFieldList* fieldList)
{
    auto code = getAttributeCode();
    int64_t index = 0;

    *code
        << code->New(luaValue.classConstant()) // ..., ref(LuaValue)
        << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue)

    createHashMap(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    for (auto field : *fieldList)
    {
        *code << code->Duplicate(); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap)
        if (field.name != nullptr)
        {
            buildBytecode(field.name); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        else
        {
            pushInt(++index); // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue)
        }
        buildBytecode(field.value);
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap), ref(HashMap), ref(LuaValue), ref(LuaValue)

        *code << code->InvokeVirtual(hashMap.method.put());
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    }

    *code << code->InvokeSpecial(luaValue.constructor.table()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVararg()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(luaList.method.get()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVarargList()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(luaList.method.subList()); // ..., ref(List of vararg)
}

void ByteCodeBuilder::emitStaticCall(ConstantMethodref* methodref)
{
    auto* code = getAttributeCode();
    *code << code->InvokeStatic(methodref);
}

void ByteCodeBuilder::createHashMap()
{
    auto* code = getAttributeCode();

    *code
        << code->New(hashMap.classConstant()) // ..., objectref(HashMap)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(hashMap.constructor.base()); // ..., objectref
}

void ByteCodeBuilder::buildBlock(const BlockStmtNode& block, bool needCreateNewContext, bool needSetParentContextAfter)
{
    if (needCreateNewContext)
    {
        createChildrenContext();
    }
    for (auto* stmt : *block.getList())
    {
        buildBytecode(stmt);
    }
    if (needSetParentContextAfter)
    {
        getParentContext();
    }
}

void ByteCodeBuilder::createChildrenContext()
{
    auto code = getAttributeCode();
    const auto contextIndex = getContextIndexInLocals();
    *code
        << code->New(luaContext.classConstant()) // ..., LuaContext
        << code->Duplicate() // ..., LuaContext, LuaContext
        << code->LoadReference(contextIndex) // ..., LuaContext, LuaContext, LuaContext
        << code->InvokeSpecial(luaContext.constructor.withParent()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void ByteCodeBuilder::getParentContext()
{
    auto code = getAttributeCode();
    const auto contextIndex = getContextIndexInLocals();
    *code
        << code->LoadReference(contextIndex) // ..., LuaContext
        << code->InvokeVirtual(luaContext.method.getParent()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void ByteCodeBuilder::functionCallExpr(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    functionCallExprList(node);
    *code
        << code->PushInt(0)
        << code->InvokeVirtual(luaList.method.get());
}


void ByteCodeBuilder::functionCallExprList(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    if (node.getWithSelf())
    {
        // The function is a table method, i.e. the self parameter exists only for TableField, so the static_cast is used.
        auto tableFunc = static_cast<TableFieldExprNode*>(node.getFunctionExpression());
        buildBytecode(tableFunc->getTable()); // ..., self
        *code << code->Duplicate(); // ..., self, self
        buildBytecode(tableFunc->getKey()); // ..., self, self, key
        getFieldByKey(); // ..., self, LuaValue

        *code << code->Swap(); // ..., LuaValue, self
        createLuaList(); // ..., LuaValue, self, LuaList
        *code
            << code->DuplicateBeforeOne() // ..., LuaValue, LuaList, self, LuaList
            << code->Swap(); // .., LuaValue, LuaList, LuaList, self
        addToLuaList(); // ..., LuaValue, LuaList
    }
    else
    {
        buildBytecode(node.getFunctionExpression()); // ..., LuaValue
        createLuaList(); // ..., LuaValue, LuaList
    }

    pushArgumentsList(node.getFunctionArguments(), false);

    call(); // ..., LuaList
}

void ByteCodeBuilder::functionCallStmt(const FunctionCallStmtNode& node)
{
    auto* code = getAttributeCode();
    buildBytecode(node.getExpression());
    *code << code->PopOne();
}

void ByteCodeBuilder::assigment(const AssignmentStmtNode& node)
{
    auto* code = getAttributeCode();

    createLuaList(); // ..., LuaList

    if (node.getScope() == Scope::Global)
    {
        for (auto* exprNode : node.getNameList())
        {
            *code << code->Duplicate(); // ..., LuaList, LuaList
            if (exprNode->getType() == ExpressionNode::Type::Id)
            {
                auto castExpr = static_cast<IdExprNode*>(exprNode);
                *code
                    << code->LoadReference(getContextIndexInLocals()) // ..., LuaList, LuaList, LuaContext
                    << code->PushString(castExpr->getValue()) // ..., LuaList, LuaList, LuaContext, StringId
                    << code->InvokeVirtual(luaContext.method.getByIdOrCreateNewGlobal());
                // ..., LuaList, LuaList, LuaValue
            }
            else
            {
                buildBytecode(exprNode); // ..., LuaList, LuaList, LuaValue
            }
            addToLuaList(); // ..., LuaList
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
                << code->LoadReference(getContextIndexInLocals()) // ..., LuaList, LuaList, LuaContext
                << code->PushString(idExprNode->getValue()) // ..., LuaList, LuaList, LuaContext, string
                << code->InvokeVirtual(luaContext.method.declareLocalId()); // ..., LuaList, LuaList, LuaValue

            addToLuaList(); // ..., LuaList
        }
    }

    pushArgumentsList(node.getValues()); // ..., LuaList, LuaList

    *code << code->InvokeStatic(luaValue.method.assigment()); // ...
}

void ByteCodeBuilder::pushArgumentsList(const ExpressionNodeList& nodes, bool createListBeforeSet)
{
    auto* code = getAttributeCode();

    if (createListBeforeSet)
    {
        createLuaList();
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
                pushVarargList(); // ..., LuaList, LuaList, LuaList
                addAllToList();
                break;
            case ExpressionNode::Type::FunctionCall:
                functionCallExprList(*static_cast<FunctionCallExprNode*>(*it)); // ..., LuaList, LuaList, LuaList
                addAllToList();
                break;
            default:
                buildBytecode(*it); // ..., LuaList, LuaList, LuaValue
                addToLuaList(); // ..., LuaList
            }
        }
        else
        {
            buildBytecode(*it); // ..., LuaList, LuaList, LuaValue
            addToLuaList(); // ..., LuaList
        }
        it = next;
    }
}

void ByteCodeBuilder::createLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->New(luaList.classConstant()) // ..., objectref(LuaList)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(luaList.constructor.base()); // ..., objectref
}

void ByteCodeBuilder::addToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(luaList.method.add())
        << code->PopOne(); // отбросить bool
}

void ByteCodeBuilder::addAllToList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(luaList.method.addAll())
        << code->PopOne();
}

void ByteCodeBuilder::declareIds(ExpressionNodeList* ids)
{
    auto* code = getAttributeCode();
    for (auto id : *ids)
    {
        *code << code->LoadReference(getContextIndexInLocals());
        buildBytecode(id);
        *code << code->InvokeVirtual(luaContext.method.declareLocalId());
    }
}
