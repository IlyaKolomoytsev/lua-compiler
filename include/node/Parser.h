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
} // parser

#endif //LUA_COMPILER_PARSER_H
