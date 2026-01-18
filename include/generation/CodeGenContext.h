#ifndef LUA_COMPILER_CODEGEN_CONTEXT_H
#define LUA_COMPILER_CODEGEN_CONTEXT_H

#include "RuntimeRefs.h"
#include "jvm/attribute-code.h"
#include "jvm/class.h"

using namespace jvm;

class CodeGenContext
{
public:
    CodeGenContext(Class* currentClass, Method* currentMethod, AttributeCode* currentAttributeCode)
        : class_(currentClass), method_(currentMethod), attributeCode_(currentAttributeCode)
    {
        runtime_.init(class_);
    }

    [[nodiscard]] const Class* getClass() const{ return class_; }
    [[nodiscard]] const Method* getMethod() const { return method_; }
    [[nodiscard]] const AttributeCode* getAttributeCode() const { return attributeCode_; }
private:
    friend class ExpressionBytecodeBuilder;

    Class* class_;
    Method* method_;
    AttributeCode* attributeCode_;
    RuntimeRefs runtime_;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H