#include "generation/ByteCodeBuilder.h"

#include <optional>

#include "node/NodeExpressionModule.h"


#include "jvm/descriptor-method.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/BlockStmtNode.h"
#include "node/statement/BranchingStmtNode.h"
#include "node/statement/DeclarationStmtNode.h"
#include "node/statement/StatementNode.h"
#include "node/statement/WhileLoopStmtNode.h"

void ByteCodeBuilder::build(const BlockStmtNode& node)
{
    auto* code = getAttributeCode();
    constexpr uint16_t contextIndex = 0;

    // create new context
    *code
        << code->New(LuaContext.getLuaContextClass())
        << code->Duplicate()
        << code->InvokeSpecial(LuaContext.constructor.getConstructorForLuaContext())
        << code->StoreReference(contextIndex);
    setContextIndexInLocals(contextIndex);

    for (auto* stmt : *node.getList())
    {
        buildBytecode(stmt);
    }
    *code << code->ReturnVoid();
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
            sum();
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
            idiv();
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
                << code->InvokeVirtual(LuaValue.method.getBoolValueFromLuaValue()) // ..., bool
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
        break;
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
                << code->InvokeVirtual(LuaValue.method.getBoolValueFromLuaValue()) // ..., bool
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
                << code->InvokeVirtual(LuaValue.method.getBoolValueFromLuaValue()) // ..., bool
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
        break;
    }
}

void ByteCodeBuilder::buildAnd(const ExpressionNode* left, const ExpressionNode* right)
{
    auto* code = getAttributeCode();

    auto* L_end = code->CodeLabel();

    buildBytecode(left); // ..., left
    *code << code->Duplicate(); // ..., left, left
    *code << code->InvokeVirtual(LuaValue.method.getBoolValueFromLuaValue()); // ..., left, bool
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
    *code << code->InvokeVirtual(LuaValue.method.getBoolValueFromLuaValue()); // ..., left, bool
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
        << code->New(LuaValue.getLuaValueClass())
        << code->Duplicate()
        << code->PushLong(value)
        << code->InvokeSpecial(LuaValue.constructor.getIntConstructorForLuaValue());
}

void ByteCodeBuilder::pushFloat(double value)
{
    auto* code = getAttributeCode();
    *code
        << code->New(LuaValue.getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(LuaValue.constructor.getFloatConstructorForLuaValue());
}

void ByteCodeBuilder::pushBool(bool value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(LuaValue.getLuaValueClass())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(LuaValue.constructor.getBoolConstructorForLuaValue());
}

void ByteCodeBuilder::pushString(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(LuaValue.getLuaValueClass())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(LuaValue.constructor.getStringConstructorForLuaValue());
}

void ByteCodeBuilder::pushNull()
{
    auto* code = getAttributeCode();

    *code
        << code->New(LuaValue.getLuaValueClass())
        << code->Duplicate()
        << code->InvokeSpecial(LuaValue.constructor.getNilConstructorForLuaValue());
}

void ByteCodeBuilder::id(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->LoadReference(getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(LuaContext.method.getLuaValueByIdMethodFromContext());
}

void ByteCodeBuilder::sum()
{
    emitStaticCall(LuaValue.method.getAddMethodFromLuaValue());
}

void ByteCodeBuilder::sub()
{
    emitStaticCall(LuaValue.method.getSubMethodFromLuaValue());
}

void ByteCodeBuilder::mul()
{
    emitStaticCall(LuaValue.method.getMulMethodFromLuaValue());
}

void ByteCodeBuilder::div()
{
    emitStaticCall(LuaValue.method.getDivMethodFromLuaValue());
}

void ByteCodeBuilder::idiv()
{
    emitStaticCall(LuaValue.method.getIntegerDivMethodFromLuaValue());
}

void ByteCodeBuilder::mod()
{
    emitStaticCall(LuaValue.method.getModMethodFromLuaValue());
}

void ByteCodeBuilder::pow()
{
    emitStaticCall(LuaValue.method.getPowMethodFromLuaValue());
}

void ByteCodeBuilder::concat()
{
    emitStaticCall(LuaValue.method.getConcatMethodFromLuaValue());
}

void ByteCodeBuilder::equal()
{
    emitStaticCall(LuaValue.method.getEqualMethodFromLuaValue());
}

void ByteCodeBuilder::notEqual()
{
    equal();
    booleanNot();
}

void ByteCodeBuilder::lessThan()
{
    emitStaticCall(LuaValue.method.getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::lessEqual()
{
    emitStaticCall(LuaValue.method.getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::greaterThan()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(LuaValue.method.getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::greaterEqual()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(LuaValue.method.getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::getFieldByKey()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(LuaValue.method.getFieldByKeyMethodFromLuaValue());
}

void ByteCodeBuilder::call()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(LuaValue.method.getCallMethodFromLuaValue());
}

void ByteCodeBuilder::unm()
{
    emitStaticCall(LuaValue.method.getUnMinusMethodFromLuaValue());
}

void ByteCodeBuilder::len()
{
    emitStaticCall(LuaValue.method.getLengthMethodFromLuaValue());
}

void ByteCodeBuilder::booleanNot()
{
    emitStaticCall(LuaValue.method.getNotMethodFromLuaValue());
}

void ByteCodeBuilder::tableConstructor(TableFieldList* fieldList)
{
    auto code = getAttributeCode();
    int64_t index = 0;

    *code
        << code->New(LuaValue.getLuaValueClass()) // ..., ref(LuaValue)
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

        *code << code->InvokeVirtual(HashMap.method.getPutMethodFromHashMap());
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    }

    *code << code->InvokeSpecial(LuaValue.constructor.getTableConstructorForLuaValue()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVararg()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(LuaList.method.getGetMethodFromLuaList()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVarargList()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(LuaList.method.getSubListMethodFromLuaList()); // ..., ref(List of vararg)
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
        << code->New(HashMap.getHashMapClass()) // ..., objectref(HashMap)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(HashMap.constructor.getHashMapConstructor()); // ..., objectref
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
        << code->New(LuaContext.getLuaContextClass()) // ..., LuaContext
        << code->Duplicate() // ..., LuaContext, LuaContext
        << code->LoadReference(contextIndex) // ..., LuaContext, LuaContext, LuaContext
        << code->InvokeSpecial(LuaContext.constructor.getConstructorForLuaContextWithParent()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void ByteCodeBuilder::getParentContext()
{
    auto code = getAttributeCode();
    const auto contextIndex = getContextIndexInLocals();
    *code
        << code->LoadReference(contextIndex) // ..., LuaContext
        << code->InvokeVirtual(LuaContext.method.getParentContextMethodFromContext()) // ..., LuaContext
        << code->StoreReference(contextIndex); // ...
}

void ByteCodeBuilder::functionCallExpr(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    functionCallExprList(node);
    *code
        << code->PushInt(0)
        << code->InvokeVirtual(LuaList.method.getGetMethodFromLuaList());
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
                    << code->InvokeVirtual(LuaContext.method.getLuaValueByIdOrCreateNewMethodFromContext());
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
                << code->InvokeVirtual(LuaContext.method.getDeclareLocalByIdMethodFromContext()); // ..., LuaList, LuaList, LuaValue

            addToLuaList(); // ..., LuaList
        }
    }

    pushArgumentsList(node.getValues()); // ..., LuaList, LuaList

    *code << code->InvokeStatic(LuaValue.method.getAssignmentMethodFromLuaValue()); // ...
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
        << code->New(LuaList.getLuaListClass()) // ..., objectref(LuaList)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(LuaList.constructor.getLuaListConstructor()); // ..., objectref
}

void ByteCodeBuilder::addToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(LuaList.method.getAddMethodFromLuaList())
        << code->PopOne(); // отбросить bool
}

void ByteCodeBuilder::addAllToList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(LuaList.method.getAddAllMethodFromLuaList())
        << code->PopOne();
}

void ByteCodeBuilder::declareIds(ExpressionNodeList* ids)
{
    auto* code = getAttributeCode();
    for (auto id : *ids)
    {
        *code << code->LoadReference(getContextIndexInLocals());
        buildBytecode(id);
        *code << code->InvokeVirtual(LuaContext.method.getDeclareLocalByIdMethodFromContext());
    }
}
