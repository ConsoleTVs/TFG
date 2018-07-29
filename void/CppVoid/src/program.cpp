/**
 * |------------------------|
 * | Void Program structure |
 * |------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/program.hpp"

void addOpCode(Program *program, uint8_t opcode, const unsigned int line)
{
    program->code.push_back(opcode);
    program->lines.push_back(line);
}

int addConstant(Program* program, Value value)
{
    program->constants.push_back(value);
    return program->constants.size() - 1;
}