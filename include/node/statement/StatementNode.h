#ifndef LUA_COMPILER_STATEMENT_NODE_H
#define LUA_COMPILER_STATEMENT_NODE_H
#include <cassert>
#include <functional>
#include <vector>

#include "node/expression/ExpressionNode.h"
#include "node/NodeExpressionModule.h"

class StatementNode;

using StatementNodeList = std::list<StatementNode*>;

enum class Scope
{
    Global,
    Local,
};

class StatementNode : public Node
{
    using label_t = std::string*;

    struct assignment_t
    {
        Scope scope;
        ExpressionNodeList* names;
        ExpressionNodeList* values;
    };

    struct declaration_t
    {
        Scope scope;
        ExpressionNodeList* names;
    };

    using function_call_t = ExpressionNode*;

    struct branching_t
    {
        ExpressionNode* condition;
        StatementNode* successBlock;
        StatementNode* failureBlock;
    };

    struct simple_loop
    {
        ExpressionNode* condition;
        StatementNode* block;
    };

    using while_loop_t = simple_loop;
    using repeat_loop_t = simple_loop;
    using block_t = StatementNodeList*;
    using do_block_t = StatementNode*;
    using return_t = ExpressionNodeList*;

    union Value
    {
        declaration_t declaration_v;
        assignment_t assignment_v;
        function_call_t functionCall_v;
        branching_t branching_v;
        while_loop_t whileLoop_v;
        repeat_loop_t repeatLoop_v;
        block_t block_v;
        do_block_t doBlock_v;
        label_t goTo_v;
        label_t label_v;
        return_t return_v;
    };

public:
    enum class Type
    {
        Declaration,
        Assignment,
        FunctionCall,
        Branching,
        ForLoopClassic,
        ForLoopIterator,
        WhileLoop,
        RepeatLoop,
        Block,
        DoBlock,
        GoTo,
        Label,
        Break,
        Return,
    };

    static StatementNode* Declaration(Scope scope, ExpressionNodeList* names);

    static StatementNode* BranchingChain(StatementNode* elseifChain, StatementNode* elseIfOrElseBlock);

    static StatementNode* ForLoop(ExpressionNodeList* names, ExpressionNodeList* iterator, StatementNode* block);

    static StatementNode* WhileLoop(ExpressionNode* condition, StatementNode* block);

    static StatementNode* RepeatLoop(StatementNode* block, ExpressionNode* condition);

    static StatementNode* GoTo(label_t label);

    static StatementNode* Label(label_t label);

    static StatementNode* Return(ExpressionNodeList* values);

    Type getType() const;

    /* Overridden methods */

    void writeNodeInfoToDot(std::ostream& os) const override;

protected:
    explicit StatementNode(Type type);

private:
    /**
     * Class interpret this statement
     * @code
     * for var_1, ···, var_n in explist do block end
     * @endcode
     * to this statement
     * @code
     * do
     *     local f, s, var = explist
     *     while true do
     *         local var_1, ···, var_n = f(s, var)
     *         if var_1 == nil then break end
     *         var = var_1
     *         block
     *     end
     * end
     * @endcode
     */
    class ForLoopIteratorConverter
    {
    public:
        /**
         * Create converter class and validate input parameters.
         * @param names name list of: "var_1, ···, var_n".
         * @param explist expression list.
         * @param block for body block statement.
         */
        ForLoopIteratorConverter(ExpressionNodeList* names, ExpressionNodeList* explist, StatementNode* block);

        /**
         * Generate converted for loop statement node.
         * @return Converted for loop.
         */
        StatementNode* generate();

    private:
        /**
         * Generate expression list assigment statement node:
         * @code
         * local f, s, var = explist
         * @endcode
         *
         * @return Expression list assigment.
         */
        StatementNode* getExplistAssigment();

        /**
         * Generate while loop statement node:
         * @code
         * while true do
         *     local var_1, ···, var_n = f(s, var)
         *     if var_1 == nil then break end
         *     var = var_1
         *     block
         * end
         * @endcode
         *
         * @return While loop.
         */
        StatementNode* getWhileLoop();

        /**
         * Generate iterator function result assigment statement node:
         * @code
         * local var_1, ···, var_n = f(s, var)
         * @endcode
         *
         * @return Iterator result assigment.
         */
        StatementNode* getInteratorResultAssigment();

        /**
         * Generate exit branching statement node:
         * @code
         * if var_1 == nil then break end
         * @endcode
         *
         * @return Exit branching.
         */
        StatementNode* getExitBranching();

        /**
         * Generate var assigment statement node:
         * @code
         * var = var_1
         * @endcode
         *
         * @return
         */
        StatementNode* getVarAssigment();

        /**
         * @brief Generate f variable expression node.
         * @return F variable.
         */
        ExpressionNode* getF();

        /**
         * @brief Generate s variable expression node.
         * @return S variable.
         */
        ExpressionNode* getS();

        /**
         * @brief Generate var variable expression node.
         * @return Var variable.
         */
        ExpressionNode* getVar();

        ExpressionNode* getFirstName();

        ExpressionNodeList* names_;
        ExpressionNodeList* explist_;
        StatementNode* block_;
    };

    Type type_;
    Value value_;
};

std::string to_string(Scope scope);

std::string to_string(StatementNode::Type type);


#endif //LUA_COMPILER_STATEMENT_NODE_H
