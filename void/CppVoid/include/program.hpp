/**
 * |------------------------|
 * | Void Program structure |
 * |------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef program_hpp
#define program_hpp

#include <vector>
#include "opcode.hpp"
#include "value.hpp"

typedef struct {
    std::vector<uint8_t> code;
    std::vector<Value> constants;
    std::vector<unsigned int> lines;
} Program;

extern Program *program;

void addOpCode(uint8_t opcode, const unsigned int line);
int addConstant(Value value);

#endif