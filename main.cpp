#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "lua_parser.tab.h"
#include "nodes/Program.h"

yyFlexLexer* lexer;

int main(int argc, char* argv[])
{
    // Проверка на наличие аргумента командной строки (пути к файлу)
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    // Открываем файл по пути, переданному в аргументе
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    lexer = new yyFlexLexer(); // создаём объект лексера
    lexer->switch_streams(&file, &std::cout); // Передаем файл для анализа
    yyparse();

    // for all chunks in program
    auto chunks = Program::getChunks();
    int chunkNumber = 0;
    for (auto chunk = chunks->begin(); chunk != chunks->end(); ++chunk)
    {
        // crate string variables for chunk name and filenames
        std::string name{"chunk_" + std::to_string(chunkNumber)};
        std::string dotFilename{name + ".dot"};
        std::string svgFilename{name + ".svg"};

        // open ".dot" file for writing
        std::ofstream file(dotFilename);
        if (!file.is_open())
        {
            std::cerr << "Can't open file";
            return 1;
        }

        // write chunk info to wile
        file << "digraph " << name << " {" << std::endl << "node [shape=plaintext];" << std::endl;
        file << **chunk;
        file << "}";

        // close file
        file.close();

        // generate svg image
        std::string command{"dot -Tsvg " + dotFilename + " -o " + svgFilename};
        system(command.c_str());
    }
    return 0;
}
