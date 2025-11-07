#include "StatementNode.h"

#include <assert.h>
#include "DotMacros.h"

StatementNode* StatementNode::Declaration(NameList* names)
{
    StatementNode* node = new StatementNode(Type::Declaration);
    node->value_.declaration_v = names;
    return node;
}

StatementNode* StatementNode::Assignment(Scope scope, NameList* names, ExpressionNodeList* values)
{
    StatementNode* node = new StatementNode(Type::Assignment);
    assignment_t* assignment = &node->value_.assignment_v;
    assignment->scope = scope;
    assignment->names = names;
    assignment->values = values;
    return node;
}

StatementNode* StatementNode::FunctionCall(ExpressionNode* callExpr)
{
    StatementNode* node = new StatementNode(Type::FunctionCall);
    node->value_.functionCall_v = callExpr;
    return node;
}

StatementNode* StatementNode::Branching(
    ExpressionNode* condition,
    StatementNode* successBlock,
    StatementNode* failureBlock
)
{
    StatementNode* node = new StatementNode(Type::Branching);
    branching_t* branching = &node->value_.branching_v;
    branching->condition = condition;
    branching->successBlock = successBlock;
    branching->failureBlock = failureBlock;
    return node;
}

StatementNode* StatementNode::ForLoop(ExpressionNode* id, ForRangeStruct range, StatementNode* block)
{
    StatementNode* node = new StatementNode(Type::ForLoop);
    for_loop_t* loop = &node->value_.forLoop_v;
    loop->iteratorVariable = id;
    loop->range = range;
    loop->block = block;
    return node;
}

StatementNode* StatementNode::ForLoop(NameList* names, ExpressionNodeList* explist, StatementNode* block)
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

StatementNode* StatementNode::Block(StatementNodeList* statements, StatementNode* finishStatement)
{
    StatementNode* node = new StatementNode(Type::Block);
    if (finishStatement != nullptr)
    {
        statements->push_back(finishStatement);
    }
    node->value_.block_v = statements;
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

StatementNode* StatementNode::Break()
{
    StatementNode* node = new StatementNode(Type::Break);
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
            for (auto node : *declaration)
                os << DOT_ARC_THIS_OTHER_LABEL(node, "declare");
            // write nodes recursively
            for (auto node : *declaration)
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
            os << DOT_ARC_THIS_OTHER_LABEL(branching.failureBlock, "failure");
            // write nodes recursively
            os << *branching.condition;
            os << *branching.successBlock;
            os << *branching.failureBlock;
            break;
        }
    case Type::ForLoop:
        {
            auto loop = value_.forLoop_v;
            auto range = loop.range;
            // write arcs
            os << DOT_ARC_THIS_OTHER_LABEL(loop.iteratorVariable, "variable");
            os << DOT_ARC_THIS_OTHER_LABEL(range.start, "range start value");
            os << DOT_ARC_THIS_OTHER_LABEL(range.finish, "range start finish");
            os << DOT_ARC_THIS_OTHER_LABEL(range.step, "range start step");
            os << DOT_ARC_THIS_OTHER_LABEL(loop.block, "block");
            // write nodes recursively
            os << *loop.iteratorVariable;
            os << *range.start;
            os << *range.finish;
            os << *range.step;
            os << *loop.block;
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
    case Type::GoTo:
        {
            auto goTo = value_.goTo_v;
            // ToDo: need change goTo type
            assert(false);
            break;
        }
    case Type::Label:
        {
            auto label = value_.label_v;
            // ToDo: need change label type
            assert(false);
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
    NameList* names, ExpressionNodeList* explist, StatementNode* block
) : names_(names), explist_(explist), block_(block)
{
    // assert for name list
    bool correctNameListSize = names->size() > 0;
    assert(correctNameListSize);

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
    StatementNode* result = StatementNode::Block(statements);
    return result;
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getExplistAssigment()
{
    return StatementNode::Assignment(
        Scope::Local,
        new NameList{
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
        ExpressionNode::Bool(true),
        StatementNode::Block(statements)
    );
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getInteratorResultAssigment()
{
    ExpressionNode* fCall = ExpressionNode::FunctionCall(
        getF(),
        new ExpressionNodeList{
            getS(),
            getVar(),
        }
    );

    StatementNode* assignment = StatementNode::Assignment(
        Scope::Local,
        names_,
        new ExpressionNodeList{fCall}
    );

    return assignment;
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getExitBranching()
{
    ExpressionNode* condition = ExpressionNode::Equality(
        getFirstName(),
        ExpressionNode::Nil()
    );
    StatementNode* successBlock = StatementNode::Block(
        new StatementNodeList{
            StatementNode::Break()
        }
    );
    return StatementNode::Branching(
        condition,
        successBlock
    );
}

inline StatementNode* StatementNode::ForLoopIteratorConverter::getVarAssigment()
{
    return StatementNode::Assignment(
        Scope::Global,
        new NameList{getVar()},
        new ExpressionNodeList{getFirstName()}
    );
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getF()
{
    return ExpressionNode::Id(new std::string("f"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getS()
{
    return ExpressionNode::Id(new std::string("s"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getVar()
{
    return ExpressionNode::Id(new std::string("var"));
}

ExpressionNode* StatementNode::ForLoopIteratorConverter::getFirstName()
{
    std::string* firstName = names_->front()->getId();
    std::string* nameCopy = new std::string(*firstName);
    return ExpressionNode::Id(nameCopy);
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
    case StatementNode::Type::ForLoop:
        return "ForLoop";
    case StatementNode::Type::WhileLoop:
        return "WhileLoop";
    case StatementNode::StatementNode::Type::RepeatLoop:
        return "RepeatLoop";
    case StatementNode::StatementNode::Type::Block:
        return "Block";
    case StatementNode::Type::GoTo:
        return "GoTo";
    case StatementNode::Type::Label:
        return "Label";
    case StatementNode::Type::Break:
        return "Break";
    default:
        assert(false);
        return "Unknown";
    }
}
