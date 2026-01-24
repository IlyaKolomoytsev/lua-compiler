#ifndef LUA_COMPILER_METHOD_CODE_GEN_CONTEXT_H
#define LUA_COMPILER_METHOD_CODE_GEN_CONTEXT_H
#include "CodeGenContext.h"

class MethodCodeGenContext : public CodeGenContext, protected LocalsManager
{
public:
    MethodCodeGenContext(Class* currentClass) : CodeGenContext(currentClass)
    {
    }

protected:
    [[nodiscard]] Method* getMethod() const { return currentMethod_; }
    [[nodiscard]] AttributeCode* getAttributeCode() const { return currentAttributeCode_; }

    void updateContext(Method* newMethod);

private:
    Method* currentMethod_ = nullptr;
    AttributeCode* currentAttributeCode_ = nullptr;
};

#endif //LUA_COMPILER_METHOD_CODE_GEN_CONTEXT_H
