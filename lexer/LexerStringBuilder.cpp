#include "LexerStringBuilder.h"

void LexerStringBuilder::write(const char* data, size_t size)
{
    stream_.write(data, size);
}

void LexerStringBuilder::write(char symbol)
{
    stream_ << symbol;
}

void LexerStringBuilder::writeUnicodeByCode(unsigned code)
{
    if (code <= 0x7F) {
        write((char)code);
    } else if (code <= 0x7FF) {
        write((char)(0xC0 | ((code >> 6) & 0x1F)));
        write((char)(0x80 | (code & 0x3F)));
    } else if (code <= 0xFFFF) {
        write((char)(0xE0 | ((code >> 12) & 0x0F)));
        write((char)(0x80 | ((code >> 6) & 0x3F)));
        write((char)(0x80 | (code & 0x3F)));
    } else if (code <= 0x10FFFF) {
        write((char)(0xF0 | ((code >> 18) & 0x07)));
        write((char)(0x80 | ((code >> 12) & 0x3F)));
        write((char)(0x80 | ((code >> 6) & 0x3F)));
        write((char)(0x80 | (code & 0x3F)));
    } else {
        writeUnicodeByCode(0xFFFD);
    }
}

std::string LexerStringBuilder::getString()
{
    auto newString = stream_.str();
    clear();
    return newString;
}

std::string* LexerStringBuilder::createString()
{
    return new std::string(getString());
}

void LexerStringBuilder::clear()
{
    stream_.str("");
    stream_.clear();
}
