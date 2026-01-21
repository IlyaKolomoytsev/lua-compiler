#include "node/expression/FunctionCallExprNode.h"
#include "node/DotMacros.h"

void FunctionCallExprNode::writeNodeInfoToDot(std::ostream& os) const
{
    // Write to dot file node info
    os << DOT_NODE_THIS_WITH_LABEL("FunctionCall");

    // Write children node info to dot file
    os << DOT_ARC_THIS_OTHER_LABEL(function_, "Function");
    int index = 0;
    for (auto* arg: *arguments_)
    {
        os << DOT_ARC_THIS_OTHER_LABEL(arg, "argument №" << index++);
    }

    os << *function_;
    for (auto* arg: *arguments_)
    {
        os << *arg;
    }
}

void FunctionCallExprNode::makeBytecode(const ByteCodeBuilder& builder) const
{
    // обработать function_
    // ..., ref(LuaValue)
    if (withSelf_)
    {
        // ..., ref(LuaValue), ref(LuaValue) "дублирование"
        // ..., ref(LuaValue), ref(LuaValue), ref(LuaList) "инициализируешь"
        // ..., ref(LuaValue), ref(LuaList), ref(LuaValue), ref(LuaList) "DuplicateBeforeOne"
        // ..., ref(LuaValue), ref(LuaList), ref(LuaList), ref(LuaValue) "swap"
        // ..., ref(LuaValue), ref(LuaList) "запись в контейнер (add)"
    }
    else
    {
        // ..., ref(LuaValue), ref(LuaList) "инициализируешь"
    }
    for (auto arg: *arguments_)
    {
        // ..., ref(LuaValue), ref(LuaList), ref(LuaList) "дублирование"
        arg->makeBytecode(builder); // ..., ref(LuaValue), ref(LuaList), ref(LuaList), ref (LuaValue) "запись в контейнер"
        // ..., ref(LuaValue), ref(LuaList)
    }
    // ..., ref(LuaList) // "вызов метаметода call()"
}
