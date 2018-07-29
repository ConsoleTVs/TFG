/**
 * |----------------------------------|
 * | Void Stack Based Virtual Machine |
 * |----------------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/vm.hpp"
#include "../include/compiler.hpp"
#include <iostream>

/* Helpers defined for the operations performed by the virtual machine */
#define READ_INSTRUCTION() (*vm.pc++)
#define READ_CONSTANT() (vm.program->constants[READ_INSTRUCTION()])
#define READ_INT() ((int) (READ_CONSTANT().nvalue))
#define READ_VARIABLE() (*(READ_CONSTANT().svalue))
#define BINARY_POP() Value b = pop(); Value a = pop()

/* Push a constant into the stack */
#define DO_OP_CONSTANT() { push(READ_CONSTANT()); break; }

/* Unary minus operation: -a */
#define DO_OP_MINUS() { push(minusInst(pop())); break; }

/* Unary not operation: !a */
#define DO_OP_NOT() { push(notInst(pop())); break; }

/* Binary addition operation: a + b */
#define DO_OP_ADD() { BINARY_POP(); push(addInst(a, b)); break; }

/* Binary subtraction operation: a - b */
#define DO_OP_SUB() { BINARY_POP(); push(subInst(a, b)); break; }

/* Binary multiplication operation: a * b */
#define DO_OP_MUL() { BINARY_POP(); push(mulInst(a, b)); break; }

/* Binary division operation: a / b */
#define DO_OP_DIV() { BINARY_POP(); push(divInst(a, b)); break; }

/* Binary equal operation: a == b */
#define DO_OP_EQ() { BINARY_POP(); push(eqInst(a, b)); break; }

/* Binary not equal operation: a != b */
#define DO_OP_NEQ() { BINARY_POP(); push(neqInst(a, b)); break; }

/* Binary lower than operation: a < b */
#define DO_OP_LT() { BINARY_POP(); push(ltInst(a, b)); break; }

/* Binary lower than or equal to operation: a <= b */
#define DO_OP_LTE() { BINARY_POP(); push(lteInst(a, b)); break; }

/* Binary higher than operation: a > b */
#define DO_OP_HT() { BINARY_POP(); push(htInst(a, b)); break; }

/* Binary higher than or equal to operation: a >= b */
#define DO_OP_HTE() { BINARY_POP(); push(hteInst(a, b)); break; }

/* Relative jump from the current position */
#define DO_OP_RJUMP() { vm.pc += READ_INT() - 1; break; }

/* Branch (RJUMP) if the top of the stack is true */
#define DO_OP_BRANCH_TRUE() { int position = READ_INT() - 1; vm.pc += isTrue(pop()) ? position : 0; break; }

/* Branch (RJUMP) if the top of the stack is false */
#define DO_OP_BRANCH_FALSE() { int position = READ_INT() - 1; vm.pc += isTrue(pop()) ? 0 : position; break; }

/* Store value to a variable from the frame heap: variable = expression */
#define DO_OP_STORE() { (*vm.topFrame).heap[READ_VARIABLE()] = pop(); break; }

/* Store to an accessed field: variable[index] = expression*/
#define DO_OP_STORE_ACCESS() { (*(*vm.topFrame).heap[READ_VARIABLE()].lvalues)[pop().nvalue] = pop(); break; }

/* Load a value from a variable from the frame heap */
#define DO_OP_LOAD() { push((*vm.topFrame).heap[READ_VARIABLE()]); break; }

/* Push a new list value from N elements in the stack */
#define DO_OP_LIST() { std::vector<Value> v; for (int pops = READ_INT(); pops > 0; pops--) v.push_back(pop()); push(createValue(v)); }

/* Push a value from a list item: variable[index] */
#define DO_OP_ACCESS() { push((*(*vm.topFrame).heap[READ_VARIABLE()].lvalues)[pop().nvalue]); break; }

/* pushes the value length of the top of the stack */
#define DO_OP_LEN() { push(lenInst(pop())); break; }

/* Return */
#define DO_OP_RETURN() { printValue(pop()); printf("\n"); return; }

/* Unknown OP code found */
#define DO_OP_UNKNOWN() { printf("Unknown instruction at line %u\n", vm.program->lines[(int) (vm.pc - &vm.program->code[0])]); break; }

static VM vm;

static void resetStack()
{
    vm.topStack = vm.stack;
}

static void resetFrames()
{
    vm.topFrame = vm.frames;
}

void initVM()
{
    resetStack();
    resetFrames();
}

void push(Value value)
{
    *vm.topStack = value;
    vm.topStack++;
}

Value pop()
{
    vm.topStack--;
    return *vm.topStack;
}

void run()
{
    for (uint8_t instruction;;) {
        #ifdef DEBUG
            printf("Inst: %d - Offset: %d - Line: %u\n", instruction, (int)(vm.pc - &vm.program->code[0]), vm.program->lines[(int)(vm.pc - &vm.program->code[0])]);
            printf("Stack: -> ");
            for (Value* slot = vm.stack; slot < vm.topStack; slot++) {
                printf("[ "); printValue(*slot); printf(" ]");
            }
            printf(" <- \n");
        #endif
        switch (instruction = READ_INSTRUCTION()) {
            case OP_CONSTANT: DO_OP_CONSTANT()
            case OP_MINUS: DO_OP_MINUS()
            case OP_NOT: DO_OP_NOT()
            case OP_ADD: DO_OP_ADD()
            case OP_SUB: DO_OP_SUB()
            case OP_MUL: DO_OP_MUL()
            case OP_DIV: DO_OP_DIV()
            case OP_EQ: DO_OP_EQ()
            case OP_NEQ: DO_OP_NEQ()
            case OP_LT: DO_OP_LT()
            case OP_LTE: DO_OP_LTE()
            case OP_HT: DO_OP_HT()
            case OP_HTE: DO_OP_HTE()
            case OP_RJUMP: DO_OP_RJUMP()
            case OP_BRANCH_TRUE: DO_OP_BRANCH_TRUE()
            case OP_BRANCH_FALSE: DO_OP_BRANCH_FALSE()
            case OP_STORE: DO_OP_STORE()
            case OP_STORE_ACCESS: DO_OP_STORE_ACCESS()
            case OP_LOAD: DO_OP_LOAD()
            case OP_LIST: DO_OP_LIST()
            case OP_ACCESS: DO_OP_ACCESS()
            case OP_LEN: DO_OP_LEN()
            case OP_RETURN: DO_OP_RETURN()
            default: DO_OP_UNKNOWN()
        }
    }
}

void interpret(const char *source)
{
    compile(source);
    //vm.program = program;
    vm.pc = &vm.program->code[0];
    run();
}