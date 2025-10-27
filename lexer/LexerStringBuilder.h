#ifndef LUA_COMPILER_LEXER_STRING_BUILDER_H
#define LUA_COMPILER_LEXER_STRING_BUILDER_H
#include <sstream>


class LexerStringBuilder
{
public:
    LexerStringBuilder() = default;

    void write(const char* data, size_t size);

    void write(char symbol);

    void writeUnicodeByCode(unsigned code);

    std::string getString();

    void clear();

private:
    std::ostringstream stream_;
};


#endif //LUA_COMPILER_LEXER_STRING_BUILDER_H