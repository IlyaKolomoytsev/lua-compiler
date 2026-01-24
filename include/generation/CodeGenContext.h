#ifndef LUA_COMPILER_CODEGEN_CONTEXT_H
#define LUA_COMPILER_CODEGEN_CONTEXT_H
#include "LocalsManager.h"
#include "jvm/class.h"
#include "jvm/attribute-code.h"


#define ONE_TIME_INIT_VALUE_METHOD(pointerType, method) \
public:                                                 \
    pointerType* method()                               \
    {                                                   \
        if (method##_ == nullptr)                       \
        {                                               \
            method##_ = method##_impl();                \
        }                                               \
        return method##_;                               \
    }                                                   \
private:                                                \
    pointerType* method##_impl();                       \
    pointerType* method##_ = nullptr ;

#define METHODREF_CONSTANT_METHOD(method) ONE_TIME_INIT_VALUE_METHOD(ConstantMethodref, method)
#define FILEDREF_CONSTANT_METHOD(method) ONE_TIME_INIT_VALUE_METHOD(ConstantFieldref, method)
#define CLASS_CONSTANT_METHOD(method) ONE_TIME_INIT_VALUE_METHOD(ConstantClass, method)
#define CLASS_METHOD_METHOD(method) ONE_TIME_INIT_VALUE_METHOD(Method, method)
#define CLASS_FIELD_METHOD(method) ONE_TIME_INIT_VALUE_METHOD(Field, method)


using namespace jvm;

class CodeGenContext
{
    struct ContextProvider
    {
    protected:
        explicit ContextProvider(CodeGenContext* context) : context_(context)
        {
        }

        [[nodiscard]] Class* getClass() const { return context_->getClass(); }

    private:
        CodeGenContext* context_;
    };

public:
    CodeGenContext(Class* currentClass);

    [[nodiscard]] Class* getClass() const { return class_; }

    struct LuaValue_ : ContextProvider
    {
        explicit LuaValue_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(nil)
            METHODREF_CONSTANT_METHOD(integer)
            METHODREF_CONSTANT_METHOD(floatNumber)
            METHODREF_CONSTANT_METHOD(boolean)
            METHODREF_CONSTANT_METHOD(string)
            METHODREF_CONSTANT_METHOD(table)
            METHODREF_CONSTANT_METHOD(function)
            METHODREF_CONSTANT_METHOD(anotherLuaValue)
        } constructor;

        struct Methods_ : ContextProvider
        {
            explicit Methods_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(add)
            METHODREF_CONSTANT_METHOD(sub)
            METHODREF_CONSTANT_METHOD(mul)
            METHODREF_CONSTANT_METHOD(div)
            METHODREF_CONSTANT_METHOD(idiv)
            METHODREF_CONSTANT_METHOD(mod)
            METHODREF_CONSTANT_METHOD(pow)
            METHODREF_CONSTANT_METHOD(concat)
            METHODREF_CONSTANT_METHOD(equal)
            METHODREF_CONSTANT_METHOD(lessThan)
            METHODREF_CONSTANT_METHOD(lessEqual)
            METHODREF_CONSTANT_METHOD(boolNot)
            METHODREF_CONSTANT_METHOD(toBool)
            METHODREF_CONSTANT_METHOD(fieldByKey)
            METHODREF_CONSTANT_METHOD(call)
            METHODREF_CONSTANT_METHOD(unMinus)
            METHODREF_CONSTANT_METHOD(length)
            METHODREF_CONSTANT_METHOD(assigment)
        } method;

        CLASS_CONSTANT_METHOD(classConstant)
    } luaValue;

    struct LuaContext_ : ContextProvider
    {
        explicit LuaContext_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(root)
            METHODREF_CONSTANT_METHOD(withParent)
        } constructor;

        struct Methods_ : ContextProvider
        {
            explicit Methods_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(getParent)
            METHODREF_CONSTANT_METHOD(getById)
            METHODREF_CONSTANT_METHOD(getByIdOrCreateNewGlobal)
            METHODREF_CONSTANT_METHOD(setValue)
            METHODREF_CONSTANT_METHOD(declareLocalId)
            METHODREF_CONSTANT_METHOD(declareLocalValueById)
        } method;

        CLASS_CONSTANT_METHOD(classConstant)
    } luaContext;

    struct LuaList_ : ContextProvider
    {
        explicit LuaList_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(base)
        } constructor;

        struct Methods_ : ContextProvider
        {
            explicit Methods_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(get)
            METHODREF_CONSTANT_METHOD(subList)
            METHODREF_CONSTANT_METHOD(getFirst)
            METHODREF_CONSTANT_METHOD(add)
            METHODREF_CONSTANT_METHOD(addAll)
        } method;

        CLASS_CONSTANT_METHOD(classConstant)
    } luaList;

    struct HashMap_ : ContextProvider
    {
        explicit HashMap_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(base);
        } constructor;

        struct Methods_ : ContextProvider
        {
            explicit Methods_(CodeGenContext* context);

            METHODREF_CONSTANT_METHOD(put);
        } method;

        CLASS_CONSTANT_METHOD(classConstant)
    } hashMap;

    struct CustomFunction_
    {
        explicit CustomFunction_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);
            ConstantMethodref* base(const std::string& customFunctionClassName) const;
        } constructor;

        struct Methods_ : ContextProvider
        {
            explicit Methods_(CodeGenContext* context);
            ConstantMethodref* apply(const std::string& customFunctionClassName) const;
        } method;

        struct Fields_ : ContextProvider
        {
            explicit Fields_(CodeGenContext* context);
            ConstantFieldref* context(const std::string& customFunctionClassName) const;
        } field;
    } customFunction;

    struct Object_
    {
        explicit Object_(CodeGenContext* context);

        struct Constructors_ : ContextProvider
        {
            explicit Constructors_(CodeGenContext* context);
            METHODREF_CONSTANT_METHOD(base)
        } constructor;
    } object;

private:
    Class* class_;
};

#endif //LUA_COMPILER_CODEGEN_CONTEXT_H
