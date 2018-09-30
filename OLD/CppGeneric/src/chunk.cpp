#include "../include/chunk.hpp"

void addInstruction(Chunk* chunk, uint8_t instruction, unsigned int line)
{
    chunk->code.push_back(instruction);
    chunk->lines.push_back(line);
}

int addConstant(Chunk* chunk, Value value)
{
    chunk->constants.push_back(value);
    return chunk->constants.size() - 1;
}