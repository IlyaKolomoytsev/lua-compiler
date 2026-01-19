#include "node/statement/StatementNode.h"

#include <cassert>
#include "node/DotMacros.h"
#include "node/expression/FunctionCallExprNode.h"
#include "node/NodeExpressionModule.h"
#include "node/statement/AssignmentStmtNode.h"
#include "node/statement/BlockStmtNode.h"
#include "node/statement/BranchingStmtNode.h"
#include "node/statement/BreakStmtNode.h"

StatementNode* StatementNode::Declaration(Scope scope, ExpressionNodeList* names)
{
    StatementNode* node = new StatementNode(Type::Declaration);
    declaration_t* declaration = &node->value_.declaration_v;
    declaration->names = names;
    declaration->scope = scope;
    return node;
}

StatementNode* StatementNode::BranchingChain(StatementNode* elseifChain, StatementNode* elseIfOrElseBlock)
{
    StatementNode* current = elseifChain;
    while (true)
    {
        auto& branching = current->value_.branching_v;
        if (branching.failureBlock == nullptr)
        {
            branching.failureBlock = elseIfOrElseBlock;
            break;
        }
        current = branching.failureBlock;
    }
    return elseifChain;
}

StatementNode* StatementNode::ForLoop(ExpressionNodeList* names, ExpressionNodeList* explist, StatementNode* block)
{
    auto converter = ForLoopIteratorConverter(names, explist, block);
    return converter.generate();
}

StatementNode* StatementNode::WhileLoop(ExpressionNode* condition, StatementNode* block)
{
    StatementNode* node = new StatementNode(Type::WhileLoop);
    while_loop_t* loop = &node->value_.whileLoop_v;
    loop->condition = condition;
    loop->block = block;
    return node;
}

StatementNode* StatementNode::RepeatLoop(StatementNode* block, ExpressionNode* condition)
{
    StatementNode* node = new StatementNode(Type::RepeatLoop);
    repeat_loop_t* loop = &node->value_.repeatLoop_v;
    loop->condition = condition;
    loop->block = block;
    return node;
}

StatementNode* StatementNode::GoTo(label_t label)
{
    StatementNode* node = new StatementNode(Type::GoTo);
    node->value_.goTo_v = label;
    return node;
}

StatementNode* StatementNode::Label(label_t label)
{
    StatementNode* node = new StatementNode(Type::Label);
    node->value_.label_v = label;
    return node;
}

StatementNode* StatementNode::Return(ExpressionNodeList* values)
{
    StatementNode* node = new StatementNode(Type::Return);
    node->value_.return_v = values;
    return node;
}

inline StatementNode::Type StatementNode::getType() const
{
    return type_;
}

StatementNode::StatementNode(Type type) : type_(type)
{
}

void StatementNode::writeNodeInfoToDot(std::ostream& os) const
{
    // write node information
    switch (type_)
    {
    case Type::Assignment:
        os << DOT_NODE_THIS_WITH_LABEL(to_string(type_) << "\n" << to_string(value_.assignment_v.scope));
        break;
    case Type::Declaration:
        os << DOT_NODE_THIS_WITH_LABEL(to_string(type_) << "\n" << to_string(value_.declaration_v.scope));
        break;
    default:
        os << DOT_NODE_THIS_WITH_LABEL(to_string(type_));
    }

    // write information about connections and child nodes
    switch (type_)
    {
    case Type::Declaration:
        {
            auto declaration = value_.declaration_v;
            // write arcs
            int index = 0;
            for (auto node : *declaration.names)
                os << DOT_ARC_THIS_OTHER_LABEL(node, "declare №" << index++);
            // write nodes recursively
            for (auto node : *declaration.names)
                os << *node;
            break;
        }
    case Type::Assignment:
        {
            auto assignment = value_.assignment_v;
            // write arcs
            int index = 0;
            for (auto node : *assignment.names)
                os << DOT_ARC_THIS_OTHER_LABEL(node, "variable №" << index++);
            index = 0;
            for (auto node : *assignment.values)
                os << DOT_ARC_THIS_OTHER_LABEL(node, "value №" << index++);
            // write nodes recursively
            for (auto node : *assignment.names)
                os << *node;
            for (auto node : *assignment.values)
                os << *node;
            break;
        }
    case Type::FunctionCall:
        {
            auto functionCall = value_.functionCall_v;
            os << DOT_ARC_THIS_OTHER_LABEL(functionCall, "expression");
            os << *functionCall;
            break;
        }
    case Type::Branching:
        {
            auto branching = value_.branching_v;
            // write arcs
            os << DOT_ARC_THIS_OTHER_LABEL(branching.condition, "condition");
            os << DOT_ARC_THIS_OTHER_LABEL(branching.successBlock, "success");
            if (branching.failureBlock)
            {
                os << DOT_ARC_THIS_OTHER_LABEL(branching.failureBlock, "failure");
            }
            // write nodes recursively
            os << *branching.condition;
            os << *branching.successBlock;
            if (branching.failureBlock)
            {
                os << *branching.failureBlock;
            }
            break;
        }
    case Type::WhileLoop:
        {
            auto loop = value_.whileLoop_v;
            // write arcs
            os << DOT_ARC_THIS_OTHER_LABEL(loop.condition, "condition");
            os << DOT_ARC_THIS_OTHER_LABEL(loop.block, "block");
            // write nodes recursively
            os << *loop.condition;
            os << *loop.block;
            break;
        }
    case Type::RepeatLoop:
        {
            auto loop = value_.repeatLoop_v;
            // write arcs
            os << DOT_ARC_THIS_OTHER_LABEL(loop.condition, "condition");
            os << DOT_ARC_THIS_OTHER_LABEL(loop.block, "block");
            // write nodes recursively
            os << *loop.condition;
            os << *loop.block;
            break;
        }
    case Type::Block:
        {
            auto block = value_.block_v;
            // write arcs
            int index = 0;
            for (auto statement : *block)
                os << DOT_ARC_THIS_OTHER_LABEL(statement, "element №" << index++);
            // write nodes recursively
            for (auto statement : *block)
                os << *statement;
            break;
        }
    case Type::DoBlock:
        {
            auto doBlock = value_.doBlock_v;
            os << DOT_ARC_THIS_OTHER_LABEL(doBlock, "do");
            os << *doBlock;
            break;
        }
    case Type::GoTo:
        {
            auto label = value_.goTo_v;
            os << DOT_NODE_THIS_WITH_LABEL("goto " << *label);
            break;
        }
    case Type::Label:
        {
            auto label = value_.label_v;
            os << DOT_NODE_THIS_WITH_LABEL("::" << *label << "::");
            break;
        }
    case Type::Break:
        break;
    case Type::Return:
        {
            auto return_v = value_.return_v;
            // write arcs
            int index = 0;
            for (auto statement : *return_v)
                os << DOT_ARC_THIS_OTHER_LABEL(statement, "expression №" << index++);
            // write nodes recursively
            for (auto statement : *return_v)
                os << *statement;
            break;
        }
    default:
        assert(false);
    }
}

StatementNode::ForLoopIteratorConverter::ForLoopIteratorConverter(
    ExpressionNodeList* names, ExpressionNodeList* explist, StatementNode* block
) : names_(names), explist_(explist), block_(block)
{
    // assert for name list
    bool correctExpressionNodeListSize = names->size() > 0;
    assert(correctExpressionNodeListSize);

    // assert for expression list
    bool correctExplistSize = explist->size() > 0;
    assert(correctExplistSize);

    // assert for block
    StatementNode::Type blockType = block->getType();
    assert(blockType == StatementNode::Type::Block);
}

StatementNode* StatementNode::ForLoopIteratorConverter::generate()
{
    StatementNodeList* statements = new StatementNodeList();
    statements->push_back(getExplistAssigment());
    statements->push_back(getWhileLoop());
    StatementNode* result = new BlockStmtNode(statements);
    return result;
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getExplistAssigment()
{
    return new AssignmentStmtNode(
        Scope::Local,
        new ExpressionNodeList{
            getF(),
            getS(),
            getVar(),
        },
        explist_
    );
}

StatementNode* StatementNode::ForLoopIteratorConverter::getWhileLoop()
{
    StatementNodeList* statements = new StatementNodeList();
    statements->push_back(getInteratorResultAssigment());
    statements->push_back(getExitBranching());
    statements->push_back(getVarAssigment());
    statements->push_back(block_);
    return StatementNode::WhileLoop(
        new BoolExprNode(true),
        new BlockStmtNode(statements)
    );
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getInteratorResultAssigment()
{
    ExpressionNode* fCall = new FunctionCallExprNode(
        getF(),
        new ExpressionNodeList{
            getS(),
            getVar(),
        },
        false
    );

    StatementNode* assignment = new AssignmentStmtNode(
        Scope::Local,
        names_,
        new ExpressionNodeList{fCall}
    );

    return assignment;
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getExitBranching()
{
    ExpressionNode* condition = new EqualityExprNode(
        getFirstName(),
        new NilExprNode()
    );
    BlockStmtNode* successBlock = new BlockStmtNode(
        new StatementNodeList{
            new BreakStmtNode()
        }
    );
    return new BranchingStmtNode(
        condition,
        successBlock
    );
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getVarAssigment()
{
    return new AssignmentStmtNode(
        Scope::Global,
        new ExpressionNodeList{getVar()},
        new ExpressionNodeList{getFirstName()}
    );
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getF()
{
    return new IdExprNode(std::string("f"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getS()
{
    return new IdExprNode(std::string("s"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getVar()
{
    return new IdExprNode(std::string("var"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getFirstName()
{
    std::string firstName = static_cast<IdExprNode*>(names_->front())->getValue();
    std::string nameCopy = std::string(firstName);
    return new IdExprNode(nameCopy);
}

std::string to_string(Scope scope)
{
    switch (scope)
    {
    case Scope::Global:
        return "Global";
    case Scope::Local:
        return "Local";
    default:
        assert(false);
        return "Unknown";
    }
}

std::string to_string(StatementNode::Type type)
{
    switch (type)
    {
    case StatementNode::Type::Declaration:
        return "Declaration";
    case StatementNode::Type::Assignment:
        return "Assignment";
    case StatementNode::Type::FunctionCall:
        return "FunctionCall";
    case StatementNode::Type::Branching:
        return "Branching";
    case StatementNode::Type::ForLoopClassic:
        return "ForLoop";
    case StatementNode::Type::WhileLoop:
        return "WhileLoop";
    case StatementNode::Type::RepeatLoop:
        return "RepeatLoop";
    case StatementNode::Type::Block:
        return "Block";
    case StatementNode::Type::DoBlock:
        return "DoBlock";
    case StatementNode::Type::GoTo:
        return "GoTo";
    case StatementNode::Type::Label:
        return "Label";
    case StatementNode::Type::Break:
        return "Break";
    case StatementNode::Type::Return:
        return "Return";
    default:
        assert(false);
        return "Unknown";
    }
}
