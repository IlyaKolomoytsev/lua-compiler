#include "generation/MethodCodeGenContext.h"

#include "jvm/method.h"

void MethodCodeGenContext::updateContext(Method* newMethod)
{
    currentMethod_ = newMethod;
    currentAttributeCode_ = newMethod->getCodeAttribute();
    freeAllLocals();
}
