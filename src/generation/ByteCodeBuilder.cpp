#include "generation/ByteCodeBuilder.h"

#include <optional>

#include "node/NodeExpressionModule.h"


#include "jvm/descriptor-method.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/DeclarationStmtNode.h"
#include "node/statement/StatementNode.h"

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
        assigment(*static_cast<const AssignmentStmtNode*>(node));
        break;
    case StatementNode::Type::FunctionCall:
        {
            functionCallStmt(*static_cast<const FunctionCallStmtNode*>(node));
        }
        break;
    case StatementNode::Type::Branching:
        {
            auto* code = getAttributeCode();
            auto* castNode = static_cast<const BranchingStmtNode*>(node);
            auto* L_else = code->CodeLabel();
            auto* L_end = code->CodeLabel();

            buildBytecode(castNode->getCondition()); // ..., LuaValue
            *code
                << code->InvokeVirtual(getBoolValueFromLuaValue()) // ..., bool
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
        break;
    case StatementNode::Type::RepeatLoop:
        break;
    case StatementNode::Type::Block:
        {
            auto* castValue = static_cast<const BlockStmtNode*>(node);
            for (auto* stmt : *castValue->getList())
            {
                buildBytecode(stmt);
            }
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
    *code << code->InvokeVirtual(getBoolValueFromLuaValue()); // ..., left, bool
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
    *code << code->InvokeVirtual(getBoolValueFromLuaValue()); // ..., left, bool
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
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushLong(value)
        << code->InvokeSpecial(getIntConstructorForLuaValue());
}

void ByteCodeBuilder::pushFloat(double value)
{
    auto* code = getAttributeCode();
    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushDouble(value)
        << code->InvokeSpecial(getFloatConstructorForLuaValue());
}

void ByteCodeBuilder::pushBool(bool value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushInt(value)
        << code->InvokeSpecial(getBoolConstructorForLuaValue());
}

void ByteCodeBuilder::pushString(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->PushString(value)
        << code->InvokeSpecial(getStringConstructorForLuaValue());
}

void ByteCodeBuilder::pushNull()
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaValueClass())
        << code->Duplicate()
        << code->InvokeSpecial(getNilConstructorForLuaValue());
}

void ByteCodeBuilder::id(const std::string& value)
{
    auto* code = getAttributeCode();

    *code
        << code->LoadReference(getContextIndexInLocals())
        << code->PushString(value)
        << code->InvokeVirtual(getLuaValueByIdMethodFromContext());
}

void ByteCodeBuilder::sum()
{
    emitStaticCall(getAddMethodFromLuaValue());
}

void ByteCodeBuilder::sub()
{
    emitStaticCall(getSubMethodFromLuaValue());
}

void ByteCodeBuilder::mul()
{
    emitStaticCall(getMulMethodFromLuaValue());
}

void ByteCodeBuilder::div()
{
    emitStaticCall(getDivMethodFromLuaValue());
}

void ByteCodeBuilder::idiv()
{
    emitStaticCall(getIntegerDivMethodFromLuaValue());
}

void ByteCodeBuilder::mod()
{
    emitStaticCall(getModMethodFromLuaValue());
}

void ByteCodeBuilder::pow()
{
    emitStaticCall(getPowMethodFromLuaValue());
}

void ByteCodeBuilder::concat()
{
    emitStaticCall(getConcatMethodFromLuaValue());
}

void ByteCodeBuilder::equal()
{
    emitStaticCall(getEqualMethodFromLuaValue());
}

void ByteCodeBuilder::notEqual()
{
    equal();
    booleanNot();
}

void ByteCodeBuilder::lessThan()
{
    emitStaticCall(getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::lessEqual()
{
    emitStaticCall(getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::greaterThan()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(getLessThenMethodFromLuaValue());
}

void ByteCodeBuilder::greaterEqual()
{
    auto* code = getAttributeCode();
    *code << code->Swap();
    emitStaticCall(getLessEqualMethodFromLuaValue());
}

void ByteCodeBuilder::getFieldByKey()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(getFieldByKeyMethodFromLuaValue());
}

void ByteCodeBuilder::call()
{
    auto* code = getAttributeCode();
    *code
        << code->InvokeVirtual(getCallMethodFromLuaValue());
}

void ByteCodeBuilder::unm()
{
    emitStaticCall(getUnMinusMethodFromLuaValue());
}

void ByteCodeBuilder::len()
{
    emitStaticCall(getLengthMethodFromLuaValue());
}

void ByteCodeBuilder::booleanNot()
{
    emitStaticCall(getNotMethodFromLuaValue());
}

void ByteCodeBuilder::tableConstructor(TableFieldList* fieldList)
{
    auto code = getAttributeCode();
    int64_t index = 0;

    *code
        << code->New(getLuaValueClass()) // ..., ref(LuaValue)
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

        *code << code->InvokeVirtual(getPutMethodFromHashMap());
        // ..., ref(LuaValue), ref(LuaValue), ref(HashMap)
    }

    *code << code->InvokeVirtual(getTableConstructorForLuaValue()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVararg()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(getGetMethodFromList()); // ..., ref(LuaValue)
}

void ByteCodeBuilder::pushVarargList()
{
    auto code = getAttributeCode();
    *code
        << code->LoadReference(getArgsIndexInLocals()) // ..., ref(List of args)
        << code->PushInt(getStartIndexForVarargInListArgs()) // ..., ref(List of args), int
        << code->InvokeVirtual(getSubListMethodFromLuaList()); // ..., ref(List of vararg)
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
        << code->New(getHashMapClass()) // ..., objectref(HashMap)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(getHashMapConstructor()); // ..., objectref
}

void ByteCodeBuilder::functionCallExpr(const FunctionCallExprNode& node)
{
    auto* code = getAttributeCode();

    functionCallExprList(node);
    *code
        << code->PushInt(0)
        << code->InvokeVirtual(getGetMethodFromList());
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
            buildBytecode(exprNode); // ..., LuaList, LuaList, LuaValue
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
                << code->InvokeVirtual(getDeclareLocalByIdMethodFromContext()); // ..., LuaList, LuaList, LuaValue

            addToLuaList(); // ..., LuaList
        }
    }

    createLuaList(); // ..., LuaList, LuaList
    pushArgumentsList(node.getValues()); // ..., LuaList, LuaList

    *code << code->InvokeStatic(getAssignmentMethodFromLuaValue()); // ...
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
        if (std::next(it) == nodes.end())
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
    }
}

void ByteCodeBuilder::createLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->New(getLuaListClass()) // ..., objectref(LuaList)
        << code->Duplicate() // ..., objectref, objectref
        << code->InvokeSpecial(getLuaListConstructor()); // ..., objectref
}

void ByteCodeBuilder::addToLuaList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(getAddMethodFromList())
        << code->PopOne(); // отбросить bool
}

void ByteCodeBuilder::addAllToList()
{
    auto* code = getAttributeCode();

    *code
        << code->InvokeVirtual(getAddAllMethodFromList())
        << code->PopOne();
}

void ByteCodeBuilder::declareIds(ExpressionNodeList* ids)
{
    auto* code = getAttributeCode();
    for (auto id : *ids)
    {
        *code << code->LoadReference(getContextIndexInLocals());
        buildBytecode(id);
        *code << code->InvokeVirtual(getDeclareLocalByIdMethodFromContext());
    }
}
