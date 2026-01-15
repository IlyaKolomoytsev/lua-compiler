#include "ExpressionNode.h"

#include <cassert>
#include <stdexcept>

#include "DotMacros.h"
#include "StatementNode.h"

ExpressionNode* ExpressionNode::Int(integer_t value)
{
    ExpressionNode* node = new ExpressionNode(Type::Integer);
    node->value_.integer_v = value;
    return node;
}

ExpressionNode* ExpressionNode::Float(float_t value)
{
    ExpressionNode* node = new ExpressionNode(Type::Float);
    node->value_.float_v = value;
    return node;
}

ExpressionNode* ExpressionNode::String(string_t* string)
{
    ExpressionNode* node = new ExpressionNode(Type::String);
    node->value_.string_v = string;
    return node;
}

ExpressionNode* ExpressionNode::Bool(bool value)
{
    ExpressionNode* node = new ExpressionNode(Type::Boolean);
    node->value_.boolean_v = value;
    return node;
}

ExpressionNode* ExpressionNode::Nil()
{
    ExpressionNode* node = new ExpressionNode(Type::Nil);
    return node;
}

ExpressionNode* ExpressionNode::Vararg()
{
    ExpressionNode* node = new ExpressionNode(Type::Vararg);
    return node;
}

ExpressionNode* ExpressionNode::Id(token_id_t value)
{
    ExpressionNode* node = new ExpressionNode(Type::Id);
    node->value_.id_v = value;
    return node;
}

ExpressionNode* ExpressionNode::TableField(ExpressionNode* table, ExpressionNode* key)
{
    ExpressionNode* node = new ExpressionNode(Type::TableField);
    table_field_t* tableField = &node->value_.tableField_v;
    tableField->table = table;
    tableField->key = key;
    return node;
}

ExpressionNode* ExpressionNode::TableFieldByIndex(ExpressionNode* table, ExpressionNode* index)
{
    ExpressionNode* node = new ExpressionNode(Type::TableFieldByIndex);
    table_field_by_index_t* tableFieldByIndex = &node->value_.tableFieldByIndex_v;
    tableFieldByIndex->table = table;
    tableFieldByIndex->index = index;
    return node;
}

ExpressionNode* ExpressionNode::TableConstructor(TableFieldList* fields)
{
    ExpressionNode* node = new ExpressionNode(Type::TableConstructor);
    node->value_.tableConstructor_v = fields;
    return node;
}

ExpressionNode* ExpressionNode::FunctionCall(ExpressionNode* functionId, arguments_list_t* arguments)
{
    ExpressionNode* node = new ExpressionNode(Type::FunctionCall);
    function_call_t* functionCall = &node->value_.functionCall_v;
    functionCall->functionId = functionId;
    functionCall->arguments = arguments;
    return node;
}

ExpressionNode* ExpressionNode::TableFunctionCall(
    ExpressionNode* table,
    ExpressionNode* key,
    arguments_list_t* arguments
)
{
    ExpressionNode* functionIdNode = TableField(table, key);
    return FunctionCall(functionIdNode, arguments);
}

ExpressionNode* ExpressionNode::FunctionLiteral(NameList* params, StatementNode* body)
{
    ExpressionNode* node = new ExpressionNode(Type::FunctionLiteral);
    auto literal = &node->value_.functionLiteral_v;
    literal->parameters = params;
    literal->body = body;
    return node;
}


ExpressionNode* ExpressionNode::Summation(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Summation);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Subtraction(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Subtraction);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Multiplication(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Multiplication);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Division(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Division);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Modulo(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Modulo);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::IntegerDivision(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::IntegerDivision);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Exponentiation(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Exponentiation);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Less(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Less);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Greater(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Greater);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Equality(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Equality);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Unequality(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Unequality);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::LessEqual(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::LessEqual);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::GreaterEqual(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::GreaterEqual);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Or(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Or);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::And(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::And);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Concatenation(ExpressionNode* left, ExpressionNode* right)
{
    ExpressionNode* node = new ExpressionNode(Type::Concatenation);
    expression_two_operands_t* operands = &node->value_.twoOperands_v;
    operands->left = left;
    operands->right = right;
    return node;
}

ExpressionNode* ExpressionNode::Length(ExpressionNode* expression)
{
    ExpressionNode* node = new ExpressionNode(Type::Length);
    node->value_.oneOperand_v = expression;
    return node;
}

ExpressionNode* ExpressionNode::Negation(ExpressionNode* expression)
{
    ExpressionNode* node = new ExpressionNode(Type::Negation);
    node->value_.oneOperand_v = expression;
    return node;
}

ExpressionNode* ExpressionNode::UnaryMinus(ExpressionNode* expression)
{
    ExpressionNode* node = new ExpressionNode(Type::UnaryMinuses);
    node->value_.oneOperand_v = expression;
    return node;
}

inline ExpressionNode::Type ExpressionNode::getType() const
{
    return type_;
}

ExpressionNode::integer_t ExpressionNode::getInteger() const
{
    bool correctType = getType() == Type::Integer;
    assert(correctType);
    if (correctType)
    {
        return value_.integer_v;
    }
    else
    {
        throw std::runtime_error("Can't get integer value because node is of wrong type.");
    }
}

ExpressionNode::float_t ExpressionNode::getFloat() const
{
    bool correctType = getType() == Type::Float;
    assert(correctType);
    if (correctType)
    {
        return value_.float_v;
    }
    else
    {
        throw std::runtime_error("Can't get float value because node is of wrong type.");
    }
}

std::string* ExpressionNode::getString()
{
    bool correctType = getType() == Type::String;
    assert(correctType);
    if (correctType)
    {
        return value_.string_v;
    }
    else
    {
        return nullptr;
    }
}

bool ExpressionNode::getBool() const
{
    bool correctType = getType() == Type::Boolean;
    assert(correctType);
    if (correctType)
    {
        return value_.boolean_v;
    }
    else
    {
        throw std::runtime_error("Can't get bool value because node is of wrong type.");
    }
}

ExpressionNode::token_id_t ExpressionNode::getId() const
{
    bool correctType = getType() == Type::Id;
    assert(correctType);
    if (correctType)
    {
        return value_.id_v;
    }
    else
    {
        throw std::runtime_error("Can't get token id value because node is of wrong type.");
    }
}

ExpressionNode::table_field_t* ExpressionNode::getTableField()
{
    bool correctType = getType() == Type::TableField;
    assert(correctType);
    if (correctType)
    {
        return &value_.tableField_v;
    }
    else
    {
        throw std::runtime_error("Can't get table field value because node is of wrong type.");
    }
}

ExpressionNode* ExpressionNode::getTableId()
{
    return getTableField()->table;
}

ExpressionNode* ExpressionNode::getTableFieldKey()
{
    return getTableField()->key;
}

ExpressionNode::function_call_t* ExpressionNode::getFunctionCall()
{
    bool correctType = getType() == Type::TableField;
    assert(correctType);
    if (correctType)
    {
        return &value_.functionCall_v;
    }
    else
    {
        throw std::runtime_error("Can't get function call value because node is of wrong type.");
    }
}

ExpressionNode* ExpressionNode::getFunctionId()
{
    return getFunctionCall()->functionId;
}

ExpressionNode::arguments_list_t* ExpressionNode::getFunctionArguments()
{
    return getFunctionCall()->arguments;
}

ExpressionNode::expression_two_operands_t* ExpressionNode::getExpressionTwoOperands()
{
    auto type = getType();
    bool correctType =
        type == Type::Summation ||
        type == Type::Subtraction ||
        type == Type::Multiplication ||
        type == Type::Division ||
        type == Type::Modulo ||
        type == Type::IntegerDivision ||
        type == Type::Exponentiation ||
        type == Type::Less ||
        type == Type::Greater ||
        type == Type::Equality ||
        type == Type::Unequality ||
        type == Type::LessEqual ||
        type == Type::GreaterEqual ||
        type == Type::Or ||
        type == Type::And ||
        type == Type::Concatenation;
    assert(correctType);
    if (correctType)
    {
        return &value_.twoOperands_v;
    }
    else
    {
        throw std::runtime_error("Can't get two operands value because node is of wrong type.");
    }
}

ExpressionNode* ExpressionNode::getLeftOperand()
{
    return getExpressionTwoOperands()->left;
}

ExpressionNode* ExpressionNode::getRightOperand()
{
    return getExpressionTwoOperands()->right;
}

ExpressionNode* ExpressionNode::getOperand()
{
    auto type = getType();
    bool correctType =
        type == Type::Length ||
        type == Type::Negation ||
        type == Type::UnaryMinuses;
    assert(correctType);
    if (correctType)
    {
        return value_.oneOperand_v;
    }
    else
    {
        throw std::runtime_error("Can't get operand value because node is of wrong type.");
    }
}

void ExpressionNode::writeNodeInfoToDot(std::ostream& os) const
{
    // write node information
    switch (type_)
    {
    case Type::Integer:
        os << DOT_NODE_THIS_WITH_LABEL(value_.integer_v);
        break;
    case Type::Float:
        os << DOT_NODE_THIS_WITH_LABEL(value_.float_v);
        break;
    case Type::String:
        os << DOT_NODE_THIS_WITH_LABEL(*value_.string_v);
        break;
    case Type::Boolean:
        os << DOT_NODE_THIS_WITH_LABEL(value_.boolean_v);
        break;
    case Type::Id:
        os << DOT_NODE_THIS_WITH_LABEL(*value_.id_v);
        break;
    case Type::Summation:
        os << DOT_NODE_THIS_WITH_LABEL("+");
        break;
    case Type::Subtraction:
        os << DOT_NODE_THIS_WITH_LABEL("-");
        break;
    case Type::Multiplication:
        os << DOT_NODE_THIS_WITH_LABEL("*");
        break;
    case Type::Division:
        os << DOT_NODE_THIS_WITH_LABEL("/");
        break;
    case Type::IntegerDivision:
        os << DOT_NODE_THIS_WITH_LABEL("//");
        break;
    case Type::Modulo:
        os << DOT_NODE_THIS_WITH_LABEL("%");
        break;
    case Type::Exponentiation:
        os << DOT_NODE_THIS_WITH_LABEL("^");
        break;
    case Type::Less:
        os << DOT_NODE_THIS_WITH_LABEL("<");
        break;
    case Type::Greater:
        os << DOT_NODE_THIS_WITH_LABEL(">");
        break;
    case Type::Equality:
        os << DOT_NODE_THIS_WITH_LABEL("==");
        break;
    case Type::Unequality:
        os << DOT_NODE_THIS_WITH_LABEL("!=");
        break;
    case Type::LessEqual:
        os << DOT_NODE_THIS_WITH_LABEL("<=");
        break;
    case Type::GreaterEqual:
        os << DOT_NODE_THIS_WITH_LABEL(">=");
        break;
    default:
        os << DOT_NODE_THIS_WITH_LABEL(to_string(type_));
    }

    // write information about connections and child nodes
    switch (type_)
    {
    case Type::TableField:
        {
            auto tableField = value_.tableField_v;
            os << DOT_ARC_THIS_OTHER_LABEL(tableField.table, "table");
            os << DOT_ARC_THIS_OTHER_LABEL(tableField.key, "key");
            os << *tableField.table;
            os << *tableField.key;
            break;
        }
    case Type::TableFieldByIndex:
        {
            auto tableFieldByIndex = value_.tableFieldByIndex_v;
            os << DOT_ARC_THIS_OTHER_LABEL(tableFieldByIndex.table, "table");
            os << DOT_ARC_THIS_OTHER_LABEL(tableFieldByIndex.index, "index");
            os << *tableFieldByIndex.table;
            os << *tableFieldByIndex.index;
            break;
        }
    case Type::TableConstructor:
        {
            auto constructor = value_.tableConstructor_v;
            int index = 0;
            for (auto field : *constructor)
            {
                if (field.name)
                {
                    os << DOT_ARC_THIS_OTHER_LABEL(field.name, "key " << index);
                }
                os << DOT_ARC_THIS_OTHER_LABEL(field.value, "value " << index);
                index++;
            }
            for (auto field : *constructor)
            {
                if (field.name)
                    os << *field.name;
                os << *field.value;
            }
            break;
        }
    case Type::FunctionCall:
        {
            auto call = value_.functionCall_v;
            os << DOT_ARC_THIS_OTHER_LABEL(call.functionId, "FunctionId");
            int index = 0;
            for (auto arg : *call.arguments)
            {
                os << DOT_ARC_THIS_OTHER_LABEL(arg, "argument №" << index++);
            }
            os << *call.functionId;
            for (auto arg : *call.arguments)
            {
                os << *arg;
            }
            break;
        }
    case Type::FunctionLiteral:
        {
            auto f = value_.functionLiteral_v;
            // параметры
            int i = 0;
            for (auto p : *f.parameters)
            {
                os << DOT_ARC_THIS_OTHER_LABEL(p, "param " << i++);
                os << *p;
            }

            // тело функции
            os << DOT_ARC_THIS_OTHER_LABEL(f.body, "body");
            os << *f.body;
            break;
        }
    case Type::ExpressionList:
        {
            // ToDo: can't find expression list values
            assert(false);
            break;
        }
    case Type::Summation:
    case Type::Subtraction:
    case Type::Multiplication:
    case Type::Division:
    case Type::Modulo:
    case Type::IntegerDivision:
    case Type::Exponentiation:
    case Type::Less:
    case Type::Greater:
    case Type::Equality:
    case Type::Unequality:
    case Type::LessEqual:
    case Type::GreaterEqual:
    case Type::Or:
    case Type::And:
    case Type::Concatenation:
        {
            auto operands = value_.twoOperands_v;
            os << DOT_ARC_THIS_OTHER_LABEL(operands.left, "left");
            os << DOT_ARC_THIS_OTHER_LABEL(operands.right, "right");
            os << *operands.left;
            os << *operands.right;
            break;
        }
    case Type::Length:
    case Type::Negation:
    case Type::UnaryMinuses:
        {
            auto operand = value_.oneOperand_v;
            os << DOT_ARC_THIS_OTHER_LABEL(operand, "operand");
            os << *operand;
            break;
        }
    case Type::Vararg:
        {
            os << DOT_NODE_THIS_WITH_LABEL("...");
            break;
        }
    }
}

ExpressionNode::ExpressionNode(Type type) : type_(type)
{
}

std::string to_string(ExpressionNode::Type type)
{
    switch (type)
    {
    case ExpressionNode::Type::Integer:
        return "Integer";
    case ExpressionNode::Type::Float:
        return "Float";
    case ExpressionNode::Type::String:
        return "String";
    case ExpressionNode::Type::Boolean:
        return "Boolean";
    case ExpressionNode::Type::Nil:
        return "Nil";
    case ExpressionNode::Type::Vararg:
        return "Vararg";
    case ExpressionNode::Type::TableField:
        return "TableField";
    case ExpressionNode::Type::TableFieldByIndex:
        return "TableFieldByIndex";
    case ExpressionNode::Type::TableConstructor:
        return "TableConstructor";
    case ExpressionNode::Type::FunctionCall:
        return "FunctionCall";
    case ExpressionNode::Type::FunctionLiteral:
        return "FunctionLiteral";
    case ExpressionNode::Type::ExpressionList:
        return "ExpressionList";
    case ExpressionNode::Type::Summation:
        return "Summation";
    case ExpressionNode::Type::Subtraction:
        return "Subtraction";
    case ExpressionNode::Type::Multiplication:
        return "Multiplication";
    case ExpressionNode::Type::Division:
        return "Division";
    case ExpressionNode::Type::Modulo:
        return "Modulo";
    case ExpressionNode::Type::IntegerDivision:
        return "IntegerDivision";
    case ExpressionNode::Type::Exponentiation:
        return "Exponentiation";
    case ExpressionNode::Type::Less:
        return "Less";
    case ExpressionNode::Type::Greater:
        return "Greater";
    case ExpressionNode::Type::Equality:
        return "Equality";
    case ExpressionNode::Type::Unequality:
        return "Unequality";
    case ExpressionNode::Type::LessEqual:
        return "LessEqual";
    case ExpressionNode::Type::GreaterEqual:
        return "GreaterEqual";
    case ExpressionNode::Type::Or:
        return "Or";
    case ExpressionNode::Type::And:
        return "And";
    case ExpressionNode::Type::Concatenation:
        return "Concatenation";
    case ExpressionNode::Type::Length:
        return "Length";
    case ExpressionNode::Type::Negation:
        return "Negation";
    case ExpressionNode::Type::UnaryMinuses:
        return "UnaryMinuses";
    default:
        assert(false);
        return "Unknown";
    }
}
