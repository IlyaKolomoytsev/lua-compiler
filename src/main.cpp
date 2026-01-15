#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "lua_parser.tab.h"
#include "Program.h"
#include <filesystem>

yyFlexLexer* lexer;

namespace fs = std::filesystem;

struct Config {
    fs::path inputPath;
    fs::path outputDir;
    std::string prefix; // stem от входного файла
};

void print_usage(const char* exe) {
    std::cerr
        << "Usage:\n"
        << "  " << exe << " -i <input_file> [-o <output_dir>]\n\n"
        << "Options:\n"
        << "  -i   Path to input file (required)\n"
        << "  -o   Output directory (default: current '.')\n";
}

static bool parse_args(int argc, char* argv[], Config& cfg) {
    // default output dir - current directory
    cfg.outputDir = fs::current_path();

    // for each parameter
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-i") && (i + 1 < argc)) {
            cfg.inputPath = fs::path(argv[++i]);
        } else if ((arg == "-o") && (i + 1 < argc)) {
            cfg.outputDir = fs::path(argv[++i]);
        } else {
            // error (unknown key or value does not exist)
            return false;
        }
    }

    // input path must be set, otherwise error
    if (cfg.inputPath.empty())
        return false;

    // set input file name like prefix for output files
    cfg.prefix = cfg.inputPath.stem().string();
    return true;
}

bool validate_input_file(const fs::path& inputPath) {
    if (!fs::exists(inputPath) || !fs::is_regular_file(inputPath)) {
        std::cerr << "Error: input file not found or inaccessible: " << inputPath << "\n";
        return false;
    }
    return true;
}

bool ensure_output_dir(const fs::path& outDir) {
    std::error_code ec;
    if (!fs::exists(outDir)) {
        if (!fs::create_directories(outDir, ec)) {
            std::cerr << "Error: Failed to create directory: " << outDir
                      << (ec ? (std::string(" (") + ec.message() + ")") : std::string()) << "\n";
            return false;
        }
    } else if (!fs::is_directory(outDir)) {
        std::cerr << "Error: the path specified via -o is not a directory: " << outDir << "\n";
        return false;
    }
    return true;
}

bool run_frontend(const fs::path& inputPath) {
    std::ifstream inFile(inputPath);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << inputPath << "\n";
        return false;
    }
    lexer = new yyFlexLexer();
    lexer->switch_streams(&inFile, &std::cout);
    yyparse();
    return true;
}

int run_graphviz_dot(const fs::path& dotPath, const fs::path& svgPath) {
    const std::string command =
        std::string("dot -Tsvg \"") + dotPath.string() + "\" -o \"" + svgPath.string() + "\"";
    int rc = std::system(command.c_str());
    if (rc != 0) {
        std::cerr << "Error: Graphviz exited with code " << rc
                  << ". Command: " << command << "\n";
    }
    return rc;
}

bool write_dot_file(std::ostream& dst, const std::string& graphName, StatementNode* chunk) {
    // Шапка
    dst << "digraph " << graphName << " {\n";
    // Тело графа (как в исходнике: << **it)
    dst << *chunk;
    // Хвост
    dst << "}\n";
    return static_cast<bool>(dst);
}

int generate_outputs(const Config& cfg) {
    auto chunks = Program::getChunks();
    if (!chunks) {
        std::cerr << "Error: Program::getChunks() вернул nullptr\n";
        return 1;
    }

    int chunkNumber = 0;
    for (auto it = chunks->begin(); it != chunks->end(); ++it, ++chunkNumber) {
        const std::string baseName = cfg.prefix + "_" + std::to_string(chunkNumber);
        const fs::path dotPath = cfg.outputDir / (baseName + ".dot");
        const fs::path svgPath = cfg.outputDir / (baseName + ".svg");

        std::ofstream dotFile(dotPath);
        if (!dotFile.is_open()) {
            std::cerr << "Can't open file for writing: " << dotPath << "\n";
            return 1;
        }

        if (!write_dot_file(dotFile, baseName, *it)) {
            std::cerr << "Error: writing to dot file failed: " << dotPath << "\n";
            return 1;
        }
        dotFile.close();

        int rc = run_graphviz_dot(dotPath, svgPath);
        if (rc != 0) return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    Config cfg;
    if (!parse_args(argc, argv, cfg)) {
        print_usage(argv[0]);
        return 1;
    }

    if (!validate_input_file(cfg.inputPath))
        return 1;

    if (!ensure_output_dir(cfg.outputDir))
        return 1;

    if (!run_frontend(cfg.inputPath))
        return 1;

    return generate_outputs(cfg);
}
