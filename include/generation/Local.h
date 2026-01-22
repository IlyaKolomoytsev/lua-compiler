#ifndef LUA_COMPILER_LOCAL_H
#define LUA_COMPILER_LOCAL_H
#include <cstdint>

class LocalsManager;

class Local
{
    friend class LocalsManager;

public:
    ~Local();

    enum class Size
    {
        one = 1,
        two = 2,
    };

    [[nodiscard]] uint16_t getIndex() const { return index_; };
    [[nodiscard]] Size getSize() const { return size_; };

private:
    Local(uint16_t index, Size size, LocalsManager* owner) : index_(index), size_(size), owner_(owner)
    {
    }

    uint16_t index_;
    Size size_;
    LocalsManager* owner_;
};

#endif //LUA_COMPILER_LOCAL_H
