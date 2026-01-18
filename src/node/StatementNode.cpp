#include "node/StatementNode.h"

#include <cassert>
#include "node/DotMacros.h"
#include "node/expression/FunctionCallExprNode.h"
#include "node/NodeExpressionModule.h"

StatementNode* StatementNode::Declaration(Scope scope, NameList* names)
{
    StatementNode* node = new StatementNode(Type::Declaration);
    declaration_t* declaration = &node->value_.declaration_v;
    declaration->names = names;
    declaration->scope = scope;
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

StatementNode* StatementNode::FunctionDeclaration(DottedNameStruct* funcName, NameList* parList, StatementNode* block)
{
    StatementNode* node = new StatementNode(Type::FunctionDeclarationGlobal);
    function_declaration_global_t* function_declaration = &node->value_.function_declaration_global_v;
    function_declaration->funcName = funcName;

    if (funcName->isMethod())
    {
        parList->push_front(new IdExprNode("self"));
    }

    function_declaration->parList = parList;
    function_declaration->block = block;
    return node;
}

StatementNode* StatementNode::FunctionDeclaration(IdExprNode* id, NameList* parList, StatementNode* block)
{
    StatementNode* node = new StatementNode(Type::FunctionDeclarationLocal);
    function_declaration_local_t* function_declaration = &node->value_.function_declaration_local_v;
    function_declaration->id = id;
    function_declaration->parList = parList;
    function_declaration->block = block;
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

StatementNode* StatementNode::DoBlock(StatementNode* block)
{
    StatementNode* node = new StatementNode(Type::DoBlock);
    node->value_.doBlock_v = block;
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
    case Type::Declaration:
        os << DOT_NODE_THIS_WITH_LABEL(to_string(type_) << "\n" << to_string(value_.declaration_v.scope));
        break;
    case Type::FunctionDeclarationGlobal:
        {
            auto& fd = value_.function_declaration_global_v;

            std::string fullName;
            const auto& ns = fd.funcName->names();
            size_t count = ns.size();

            bool isMethod = fd.funcName->isMethod();

            size_t i = 0;
            for (const auto& name : ns)
            {
                fullName += name;
                if (i + 1 < count)
                {
                    if (isMethod && i + 1 == count - 1)
                        fullName += ":";
                    else
                        fullName += ".";
                }

                i++;
            }

            os << DOT_NODE_THIS_WITH_LABEL("FunctionDeclarationGlobal\n" << fullName);
            break;
        }

    case Type::FunctionDeclarationLocal:
        {
            auto& fd = value_.function_declaration_local_v;

            std::string localName = "<fn>";
            localName = fd.id->getValue();

            os << DOT_NODE_THIS_WITH_LABEL("FunctionDeclarationLocal\n" << localName);
            break;
        }
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
    case Type::FunctionDeclarationGlobal:
        {
            auto functionDeclaration = value_.function_declaration_global_v;

            int i = 0;
            for (auto* p : *functionDeclaration.parList)
            {
                os << DOT_ARC_THIS_OTHER_LABEL(p, "param " << i++);
            }

            os << DOT_ARC_THIS_OTHER_LABEL(functionDeclaration.block, "body");

            for (auto* p : *functionDeclaration.parList) os << *p;
            os << *functionDeclaration.block;
            break;
        }

    case Type::FunctionDeclarationLocal:
        {
            auto& fd = value_.function_declaration_local_v;

            int i = 0;
            for (auto* p : *fd.parList)
            {
                os << DOT_ARC_THIS_OTHER_LABEL(p, "param " << i++);
            }

            os << DOT_ARC_THIS_OTHER_LABEL(fd.block, "body");

            for (auto* p : *fd.parList) os << *p;
            os << *fd.block;
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
    case Type::ForLoop:
        {
            auto loop = value_.forLoop_v;
            auto range = loop.range;
            // write arcs
            os << DOT_ARC_THIS_OTHER_LABEL(loop.iteratorVariable, "variable");
            os << DOT_ARC_THIS_OTHER_LABEL(range.start, "range start");
            os << DOT_ARC_THIS_OTHER_LABEL(range.finish, "range end");
            os << DOT_ARC_THIS_OTHER_LABEL(range.step, "range step");
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
        new BoolExprNode(true),
        StatementNode::Block(statements)
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

    StatementNode* assignment = StatementNode::Assignment(
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
    case StatementNode::Type::FunctionDeclarationGlobal:
        return "FunctionDeclarationGlobal";
    case StatementNode::Type::FunctionDeclarationLocal:
        return "FunctionDeclarationLocal";
    case StatementNode::Type::Branching:
        return "Branching";
    case StatementNode::Type::ForLoop:
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
