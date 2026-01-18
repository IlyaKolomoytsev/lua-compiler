#include "node/Program.h"

std::vector<StatementNode *> Program::chunks{};
void Program::addChunk(StatementNode *chunk) { chunks.push_back(chunk); }
const std::vector<StatementNode *> *Program::getChunks() { return &chunks; }