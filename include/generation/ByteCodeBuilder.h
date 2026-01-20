#ifndef LUA_COMPILER_BYTE_CODE_BUILDER_H
#define LUA_COMPILER_BYTE_CODE_BUILDER_H

#include "generation/CodeGenContext.h"

class ByteCodeBuilder
{
public:
    ByteCodeBuilder(CodeGenContext* context)
        : context_(context){}

    [[nodiscard]] const CodeGenContext* getContext() const { return context_; }

protected:
    CodeGenContext* context_;
};

#endif //LUA_COMPILER_BYTE_CODE_BUILDER_H