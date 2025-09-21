#include <iostream>
#include <FlexLexer.h>

int main() {
    std::cout << "Введите текст для анализа: \n";

    yyFlexLexer lexer;       // создаём объект лексера
    lexer.yylex();           // вызываем метод yylex() класса

    return 0;
}
