/**
 * |----------------------------------|
 * | Void Stack Based Virtual Machine |
 * |----------------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef vm_hpp
#define vm_hpp

#define STACK_SIZE 256
#define FRAME_SIZE 256

// #define DEBUG

#include <vector>
#include <unordered_map>
#include "program.hpp"

typedef struct {
    std::unordered_map<std::string, Value> heap;
    uint8_t *return_address;
} Frame;

typedef struct {
    Program *program;
    uint8_t *pc;
    Value stack[STACK_SIZE];
    Value *topStack;
    Frame frames[FRAME_SIZE];
    Frame *topFrame;
} VM;

void initVM();
// void push(Value value);
// Value* pop();
void run();
void interpret(); // For debug purposes
void interpret(const char *source);

#endif