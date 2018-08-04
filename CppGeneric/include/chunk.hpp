#ifndef chunk_hpp
#define chunk_hpp

#include "base.hpp"
#include "value.hpp"

typedef enum {
    OP_CONSTANT,
    OP_NEGATE,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_RETURN
} OpCode;

typedef struct {
    std::vector<uint8_t> code;
    ValuePool constants;
    std::vector<unsigned int> lines;
} Chunk;

void addInstruction(Chunk* chunk, uint8_t instruction, unsigned int line);
int addConstant(Chunk* chunk, Value value);

#endif