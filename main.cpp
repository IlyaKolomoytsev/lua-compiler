#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "lua_parser.tab.h"

yyFlexLexer *lexer;

int main(int argc, char* argv[]) {
    // Проверка на наличие аргумента командной строки (пути к файлу)
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    // Открываем файл по пути, переданному в аргументе
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    lexer = new yyFlexLexer();      // создаём объект лексера
    lexer->switch_streams(&file, &std::cout);  // Передаем файл для анализа
    yyparse();

    return 0;
}
