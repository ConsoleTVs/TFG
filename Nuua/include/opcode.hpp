/**
 * |-------------------------------|
 * | Nuua Bytecode Pperation Codes |
 * |-------------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#ifndef opcode_hpp
#define opcode_hpp

#include "value.hpp"

typedef enum : uint8_t {
    OP_CONSTANT,

    // Unary operations
    OP_MINUS,
    OP_NOT,

    // Binary operations
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LTE,
    OP_HT,
    OP_HTE,

    // Jumps and conditional jumps
    OP_RJUMP,
    OP_BRANCH_TRUE,
    OP_BRANCH_FALSE,

    // Store and load
    OP_STORE,
    OP_LOAD,
    OP_STORE_ACCESS,

    // Lists and dictionaries
    OP_LIST,
    OP_ACCESS,

    // Others
    OP_LEN,
    OP_EXIT
} OpCode;

void debug_opcode(uint8_t opcode);
void debug_opcodes(std::vector<uint8_t> opcodes);
bool isTrue(Value *a);
Value minusInst(Value *a);
Value notInst(Value *a);
Value addInst(Value *a, Value *b);
Value subInst(Value *a, Value *b);
Value mulInst(Value *a, Value *b);
Value divInst(Value *a, Value *b);
Value eqInst(Value *a, Value *b);
Value neqInst(Value *a, Value *b);
Value ltInst(Value *a, Value *b);
Value lteInst(Value *a, Value *b);
Value htInst(Value *a, Value *b);
Value hteInst(Value *a, Value *b);
Value lenInst(Value *a);

#endif