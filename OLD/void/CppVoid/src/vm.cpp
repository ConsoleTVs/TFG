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
#include "../include/logger.hpp"

#define PUSH(value) *vm.topStack = (value); vm.topStack++
#define POP() (--vm.topStack)

/* Helpers defined for the operations performed by the virtual machine */
#define READ_INSTRUCTION() (*vm.pc++)
#define READ_CONSTANT() (vm.program->constants[READ_INSTRUCTION()])
#define READ_INT() ((int) (READ_CONSTANT().nvalue))
#define READ_VARIABLE() (*(READ_CONSTANT().svalue))
#define BINARY_POP() Value *b = POP(); Value *a = POP()

/* Push a constant into the stack */
#define DO_OP_CONSTANT() { PUSH(READ_CONSTANT()); break; }

/* Unary minus operation: -a */
#define DO_OP_MINUS() { PUSH(minusInst(POP())); break; }

/* Unary not operation: !a */
#define DO_OP_NOT() { PUSH(notInst(POP())); break; }

/* Binary addition operation: a + b */
#define DO_OP_ADD() { BINARY_POP(); PUSH(addInst(a, b)); break; }

/* Binary subtraction operation: a - b */
#define DO_OP_SUB() { BINARY_POP(); PUSH(subInst(a, b)); break; }

/* Binary multiplication operation: a * b */
#define DO_OP_MUL() { BINARY_POP(); PUSH(mulInst(a, b)); break; }

/* Binary division operation: a / b */
#define DO_OP_DIV() { BINARY_POP(); PUSH(divInst(a, b)); break; }

/* Binary equal operation: a == b */
#define DO_OP_EQ() { BINARY_POP(); PUSH(eqInst(a, b)); break; }

/* Binary not equal operation: a != b */
#define DO_OP_NEQ() { BINARY_POP(); PUSH(neqInst(a, b)); break; }

/* Binary lower than operation: a < b */
#define DO_OP_LT() { BINARY_POP(); PUSH(ltInst(a, b)); break; }

/* Binary lower than or equal to operation: a <= b */
#define DO_OP_LTE() { BINARY_POP(); PUSH(lteInst(a, b)); break; }

/* Binary higher than operation: a > b */
#define DO_OP_HT() { BINARY_POP(); PUSH(htInst(a, b)); break; }

/* Binary higher than or equal to operation: a >= b */
#define DO_OP_HTE() { BINARY_POP(); PUSH(hteInst(a, b)); break; }

/* Relative jump from the current position */
#define DO_OP_RJUMP() { vm.pc += READ_INT() - 1; break; }

/* Branch (RJUMP) if the top of the stack is true */
#define DO_OP_BRANCH_TRUE() { int position = READ_INT() - 1; vm.pc += isTrue(POP()) ? position : 0; break; }

/* Branch (RJUMP) if the top of the stack is false */
#define DO_OP_BRANCH_FALSE() { int position = READ_INT() - 1; vm.pc += isTrue(POP()) ? 0 : position; break; }

/* Store value to a variable from the frame heap: variable = expression */
#define DO_OP_STORE() { vm.topFrame->heap[READ_VARIABLE()] = *POP(); break; }

/* Store to an accessed field: variable[index] = expression*/
#define DO_OP_STORE_ACCESS() { auto v = POP(); (*vm.topFrame->heap[READ_VARIABLE()].lvalues)[POP()->nvalue] = *v; break; }

/* Load a value from a variable from the frame heap */
#define DO_OP_LOAD() { PUSH((*vm.topFrame).heap[READ_VARIABLE()]); break; }

/* Push a new list value from N elements in the stack */
#define DO_OP_LIST() { std::vector<Value> v; for (int pops = READ_INT(); pops > 0; pops--) v.push_back(*POP()); PUSH(createValue(v)); }

/* Push a value from a list item: variable[index] */
#define DO_OP_ACCESS() { PUSH((*vm.topFrame->heap[READ_VARIABLE()].lvalues)[POP()->nvalue]); break; }

/* pushes the value length of the top of the stack */
#define DO_OP_LEN() { PUSH(lenInst(POP())); break; }

/* Exit and dump */
#define DO_OP_EXIT() { for(auto i = vm.stack; i < vm.topStack; i++) { printValue(*i); printf("\n"); }; return; }

/* Unknown OP code found */
#define DO_OP_UNKNOWN() { printf("Unknown instruction at line %u\n", vm.program->lines[(int) (vm.pc - &vm.program->code[0])]); break; }

static VM vm;

static void resetStack() { vm.topStack = vm.stack; }
static void resetFrames() { vm.topFrame = vm.frames; }

void initVM()
{
    resetStack();
    resetFrames();
}

/* Typical push and pop instructions. Replaced by the macros. */
// void push(Value value) { *vm.topStack = value; vm.topStack++; }
// Value* pop() { return --vm.topStack; }

void run()
{
    for (uint8_t instruction;;) {
        instruction = READ_INSTRUCTION();
        #ifdef DEBUG
            printf(
                "Inst: %d - Offset: %d - Line: %u\n",
                instruction,
                (int)(vm.pc - &vm.program->code[0]),
                vm.program->lines[(int)(vm.pc - &vm.program->code[0])]
            );
            printf("Stack: -> ");
            for (Value* slot = vm.stack; slot < vm.topStack; slot++) {
                printf("[ "); printValue(*slot); printf(" ]");
            }
            printf(" <- \n");
        #endif
        switch (instruction) {
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
            case OP_EXIT: DO_OP_EXIT()
            default: DO_OP_UNKNOWN()
        }
    }
}

void interpret()
{
    vm.program = program;
    vm.pc = &vm.program->code[0];
    run();
}

void interpret(const char *source)
{
    compile(source);

    info("Started interpreting...");

    vm.program = program;
    vm.pc = &vm.program->code[0];

    run();

    success("Finished interpreting");
}