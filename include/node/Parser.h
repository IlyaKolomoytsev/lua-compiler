#ifndef LUA_COMPILER_PARSER_H
#define LUA_COMPILER_PARSER_H
#include "NodeExpressionModule.h"
#include "NodeStatementModule.h"

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

    inline BlockStmtNode* Block(StatementNodeList* statements, StatementNode* optionalFinishStatement)
    {
        if (optionalFinishStatement != nullptr)
        {
            statements->push_back(optionalFinishStatement);
        }
        return new BlockStmtNode(statements);
    }

    inline BranchingStmtNode* IfElseifChainElse(ExpressionNode* condition, BlockStmtNode* successBlock,
                                                    BranchingStmtNode* elseifChain, BlockStmtNode* elseBlock)
    {
        elseifChain->appendElseToDeepestIf(elseBlock);
        return new BranchingStmtNode(condition, successBlock, elseifChain);
    }

    inline BranchingStmtNode* ContinueElseifBranching(BranchingStmtNode* elseIfChain, BranchingStmtNode* newChain)
    {
        elseIfChain->appendElseToDeepestIf(newChain);
        return elseIfChain;
    }

    inline AssignmentStmtNode* FunctionDeclaration(Scope scope,
                                                   ExpressionNode* functionName,
                                                   ExpressionNodeList* parameters,
                                                   BlockStmtNode* body)
    {
        auto inputValues = new ExpressionNodeList();
        auto outputValues = new ExpressionNodeList();
        inputValues->push_back(functionName);
        outputValues->push_back(new FunctionExprNode(parameters, body));
        return new AssignmentStmtNode(scope, inputValues, outputValues);
    }

    inline AssignmentStmtNode* MethodDeclaration(ExpressionNode* tableExpr,
                                                 std::string* methodName,
                                                 ExpressionNodeList* parameters,
                                                 BlockStmtNode* body)
    {
        auto functionName = new TableFieldExprNode(tableExpr, new IdExprNode(methodName));
        parameters->push_front(new IdExprNode("self"));
        return FunctionDeclaration(Scope::Global, functionName, parameters, body);
    }
} // parser

#endif //LUA_COMPILER_PARSER_H
