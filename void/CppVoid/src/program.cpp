/**
 * |------------------------|
 * | Void Program structure |
 * |------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/program.hpp"

Program *program = new Program;

void debug_program()
{
    printf("OPCODES: (size: %zu)\n",  program->code.size());
    for (unsigned long long i = 0; i < program->code.size(); i++) {
        auto opcode = program->code.at(i);
        if (
            opcode == OP_CONSTANT
            || opcode == OP_LOAD
            || opcode == OP_STORE
            || opcode == OP_BRANCH_FALSE
            || opcode == OP_BRANCH_TRUE
            || opcode == OP_RJUMP
        ) {
            // It's a constant load
            debug_opcode(program->code.at(i++));
            printf(" ");
            printValue(program->constants.at(program->code.at(i)));
            printf("\n");
            continue;
        }
        debug_opcode(program->code.at(i));
        printf("\n");
    }

    printf("\nCONSTANTS: (size: %zu)\n", program->constants.size());
    for (auto c : program->constants) {
        printValue(c);
        printf("\n");
    }
    printf("\nLITERAL OPCODE NUMBERS: (size: %zu)\n", program->code.size());
    for (auto c : program->code) {
        printf("%d ", c);
    }
    printf("\n");
}

void resetProgram()
{
    program->code.clear();
    program->lines.clear();
    program->constants.clear();
}

void addOpCode(uint8_t opcode, const unsigned int line)
{
    program->code.push_back(opcode);
    program->lines.push_back(line);
}

int addConstant(Value value)
{
    program->constants.push_back(value);

    return program->constants.size() - 1;
}

void modifyConstant(unsigned int index, Value value)
{
    program->constants[index] = value;
}