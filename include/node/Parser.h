#ifndef LUA_COMPILER_PARSER_H
#define LUA_COMPILER_PARSER_H
#include "NodeExpressionModule.h"

namespace parser
{
    inline FunctionCallExprNode* FunctionCallWithArgs(ExpressionNode* function, ExpressionNodeList* arguments)
    {
        return new FunctionCallExprNode(function, arguments, false);
    }

    inline FunctionCallExprNode* TableMethodCall(ExpressionNode* table,
                                                 std::string* methodName,
                                                 ExpressionNodeList* arguments)
    {
        auto tableField = new TableFieldExprNode(table, new IdExprNode(methodName));
        return new FunctionCallExprNode(tableField, arguments, true);
    }
} // parser

#endif //LUA_COMPILER_PARSER_H
