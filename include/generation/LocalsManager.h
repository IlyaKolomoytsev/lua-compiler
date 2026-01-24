#ifndef LUA_COMPILER_LOCALS_MANAGER_H
#define LUA_COMPILER_LOCALS_MANAGER_H

#include <vector>

#include "Local.h"

class LocalsManager
{
    friend class Local;
public:
    LocalsManager() = default;

    Local* registerNewLocal(Local::Size type);

    void freeAllLocals();
private:
    void freeLocal(Local* local);

    int registerLocal(Local::Size size);

    std::vector<bool> locals_;
};

#endif //LUA_COMPILER_LOCALS_MANAGER_H
