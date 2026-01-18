#ifndef LUA_COMPILER_FIXED_STRING_H
#define LUA_COMPILER_FIXED_STRING_H
#include <cstddef>

template <std::size_t N>
struct fixed_string
{
    char value[N];

    constexpr fixed_string(const char (&str)[N])
    {
        for (std::size_t i = 0; i < N; ++i)
            value[i] = str[i];
    }
};

#endif //LUA_COMPILER_FIXED_STRING_H
