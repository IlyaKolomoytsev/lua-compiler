#include "ExpressionNode.h"

#include <assert.h>
#include <stdexcept>

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

ExpressionNode* ExpressionNode::Id(token_id_t value)
{
    ExpressionNode* node = new ExpressionNode(Type::Id);
    node->value_.id_v = value;
    return node;
}

ExpressionNode* ExpressionNode::TableField(ExpressionNode* table, token_id_t key)
{
    ExpressionNode* node = new ExpressionNode(Type::TableField);
    table_filed_t* tableField = &node->value_.tableField_v;
    tableField->table = table;
    tableField->key = key;
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
    token_id_t key,
    arguments_list_t* arguments
)
{
    ExpressionNode* functionIdNode = TableField(table, key);
    arguments->push_front(table); // add table like first argument in argument list
    return FunctionCall(functionIdNode, arguments);
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
    ExpressionNode* node = new ExpressionNode(Type::Division);
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

ExpressionNode::table_filed_t* ExpressionNode::getTableField()
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

ExpressionNode::token_id_t ExpressionNode::getTableFieldKey()
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
    os << getNodeId() << " [label=ExpressionNode]" << std::endl;
}

ExpressionNode::ExpressionNode(Type type) : type_(type)
{
}
