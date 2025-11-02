#include "StatementNode.h"

#include <assert.h>

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

StatementNode* StatementNode::FunctionCall(ExpressionNode* functionId, ExpressionNodeList* arguments)
{
    StatementNode* node = new StatementNode(Type::FunctionCall);
    node->value_.functionCall_v = ExpressionNode::FunctionCall(functionId, arguments);
    return node;
}

StatementNode* StatementNode::FunctionCall(ExpressionNode* functionId, ExpressionNode* argument)
{
    ExpressionNodeList* arguments = new ExpressionNodeList();
    arguments->push_back(argument);

    StatementNode* node = FunctionCall(functionId, arguments);
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
        statements->push_back(node);
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
    os << getNodeId() << " [label=StatementNode]" << std::endl;
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
