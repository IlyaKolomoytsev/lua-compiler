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
        auto tableField = new TableFieldExprNode(table, new StringExprNode(methodName));
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
        if (functionName->getType() == ExpressionNode::Type::TableField)
        {
            auto tableField = static_cast<TableFieldExprNode*>(functionName);
            if (tableField->getKey()->getType() == ExpressionNode::Type::Id)
            {
                tableField->setKey(new StringExprNode(static_cast<IdExprNode*>(tableField->getKey())->getValue()));
            }
        }
        inputValues->push_back(functionName);
        outputValues->push_back(new FunctionExprNode(parameters, body));
        return new AssignmentStmtNode(scope, inputValues, outputValues);
    }

    inline AssignmentStmtNode* MethodDeclaration(ExpressionNode* tableExpr,
                                                 std::string* methodName,
                                                 ExpressionNodeList* parameters,
                                                 BlockStmtNode* body)
    {
        auto functionName = new TableFieldExprNode(tableExpr, new StringExprNode(methodName));
        parameters->push_front(new IdExprNode("self"));
        return FunctionDeclaration(Scope::Global, functionName, parameters, body);
    }
} // parser

#endif //LUA_COMPILER_PARSER_H
