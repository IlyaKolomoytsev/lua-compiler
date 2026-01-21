#include "node/expression/FunctionCallExprNode.h"

#include "generation/ByteCodeBuilder.h"
#include "node/DotMacros.h"
#include "node/expression/TableFieldExprNode.h"

void FunctionCallExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("FunctionCall");

    // Write children node info to dot file
    os << DOT_ARC_THIS_OTHER_LABEL(function_, "Function");
    int index = 0;
    for (auto* arg : *arguments_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(arg, "argument №" << index++);
    }

    os << *function_;
    for (auto* arg : *arguments_)
    {
        os << *arg;
    }
}

void FunctionCallExprNode::makeBytecode(ByteCodeBuilder& builder) const
{
    auto* code = builder.getAttributeCode();

    if (withSelf_)
    {
        // The function is a table method, i.e. the self parameter exists only for TableField, so the static_cast is used.
        auto tableFunc = static_cast<TableFieldExprNode*>(function_);
        tableFunc->getTable()->makeBytecode(builder); // ..., self
        *code << code->Duplicate(); // ..., self, self
        tableFunc->getKey()->makeBytecode(builder); // ..., self, self, key
        builder.getFieldByKey(); // ..., self, LuaValue

        *code << code->Swap(); // ..., LuaValue, self
        builder.createLuaList(); // ..., LuaValue, self, LuaList
        *code
            << code->DuplicateBeforeOne() // ..., LuaValue, LuaList, self, LuaList
            << code->Swap(); // .., LuaValue, LuaList, LuaList, self
        builder.addToLuaList(); // ..., LuaValue, LuaList
    }
    else
    {
        function_->makeBytecode(builder); // ..., LuaValue
        builder.createLuaList(); // ..., LuaValue, LuaList
    }
    for (auto arg : *arguments_)
    {
        *code << code->Duplicate(); // ..., LuaValue, LuaList, LuaList
        arg->makeBytecode(builder); // ..., LuaValue, LuaList, LuaList, LuaValue
        builder.addToLuaList(); // ..., LuaValue, LuaList
    }
    builder.call(); // ..., LuaList
}
