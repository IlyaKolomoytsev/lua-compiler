#ifndef LUA_COMPILER_PROGRAM_H
#define LUA_COMPILER_PROGRAM_H
#include "node/StatementNode.h"

class Program {
public:
  static void addChunk(StatementNode *chunk);
  static const std::vector<StatementNode *> *getChunks();

private:
  static std::vector<StatementNode *> chunks;
};

#endif // LUA_COMPILER_PROGRAM_H
