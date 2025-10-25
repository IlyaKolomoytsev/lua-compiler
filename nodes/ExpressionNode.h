#ifndef LUA_COMPILER_EXPRESSION_NODE_H
#define LUA_COMPILER_EXPRESSION_NODE_H
#include <list>
#include <string>
#include <sys/types.h>

#include "Node.h"

class ExpressionNode;


using NameList = std::list<ExpressionNode*>;
using FunctionArgumentsList = std::list<ExpressionNode*>;
using ExpressionNodeList = std::list<ExpressionNode*>;
struct TableField
{
    ExpressionNode* name;
    ExpressionNode* value;
};
using TableFieldList = std::list<TableField>;

class ExpressionNode : public Node
{
    using token_id_t = std::string*;
    using integer_t = int64_t;
    using float_t = double;
    using string_t = std::string;
    using arguments_list_t = FunctionArgumentsList;

    struct table_filed_t
    {
        ExpressionNode* table;
        token_id_t key;
    };

    struct function_call_t
    {
        ExpressionNode* functionId;
        arguments_list_t* arguments;
    };

    struct expression_two_operands_t
    {
        ExpressionNode* left;
        ExpressionNode* right;
    };

    using expression_one_operand_t = ExpressionNode*;

    using table_constructor_t = TableFieldList*;

    union Value
    {
        token_id_t id_v;
        integer_t integer_v;
        float_t float_v;
        string_t* string_v;
        bool boolean_v;
        table_filed_t tableField_v;
        function_call_t functionCall_v;
        expression_two_operands_t twoOperands_v;
        expression_one_operand_t oneOperand_v;
        table_constructor_t tableConstructor_v;
    };

public:
    enum class Type
    {
        Integer,
        Float,
        String,
        Boolean,
        Nil,
        Vararg,
        Id,
        TableField,
        TableConstructor,
        FunctionCall,
        //ToDo: add function declaration
        ExpressionList,
        Summation,
        Subtraction,
        Multiplication,
        Division,
        Modulo,
        IntegerDivision,
        Exponentiation,
        Less,
        Greater,
        Equality,
        Unequality,
        LessEqual,
        GreaterEqual,
        Or,
        And,
        Concatenation,
        Length,
        Negation,
        UnaryMinuses,
    };

    /* Static constructors */

    static ExpressionNode* Int(integer_t value);

    static ExpressionNode* Float(float_t value);

    static ExpressionNode* String(string_t* string);

    static ExpressionNode* Bool(bool value);

    static ExpressionNode* Id(token_id_t value);

    static ExpressionNode* TableField(ExpressionNode* table, token_id_t key);

    static ExpressionNode* TableConstructor(TableFieldList* fields);

    static ExpressionNode* FunctionCall(ExpressionNode* functionId, arguments_list_t* arguments);

    static ExpressionNode* TableFunctionCall(ExpressionNode* table, token_id_t key, arguments_list_t* arguments);

    static ExpressionNode* Summation(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Subtraction(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Multiplication(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Division(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Modulo(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* IntegerDivision(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Exponentiation(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Less(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Greater(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Equality(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Unequality(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* LessEqual(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* GreaterEqual(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Or(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* And(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Concatenation(ExpressionNode* left, ExpressionNode* right);

    static ExpressionNode* Length(ExpressionNode* expression);

    static ExpressionNode* Negation(ExpressionNode* expression);

    static ExpressionNode* UnaryMinus(ExpressionNode* expression);

    /* Getters */

    Type getType() const;

    integer_t getInteger() const;

    float_t getFloat() const;

    std::string* getString();

    bool getBool() const;

    token_id_t getId() const;

    table_filed_t* getTableField();

    ExpressionNode* getTableId();

    token_id_t getTableFieldKey();

    function_call_t* getFunctionCall();

    ExpressionNode* getFunctionId();

    arguments_list_t* getFunctionArguments();

    expression_two_operands_t* getExpressionTwoOperands();

    ExpressionNode* getLeftOperand();

    ExpressionNode* getRightOperand();

    ExpressionNode* getOperand();

private:
    explicit ExpressionNode(Type type);

    Type type_;
    Value value_;
};


#endif
