#include "../include/vm.hpp"
#include "../include/compiler.hpp"
#include "../include/operation.hpp"
#include "../include/debug.hpp"

static VM vm;

static void resetStack()
{
    vm.stackTop = vm.stack;
}

void initVM()
{
    resetStack();
}

void freeVM()
{

}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

InterpretResult interpret(const std::string source)
{

}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants[READ_BYTE()])
    #define BINARY_POP() Value b = pop(); Value a = pop()

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("          ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int) (vm.ip - &vm.chunk->code[0]));
        #endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: { push(READ_CONSTANT()); break; }
            case OP_NEGATE: { push(negInst(pop())); break; }
            case OP_ADD: { BINARY_POP(); push(addInst(a, b)); break; }
            case OP_SUB: { BINARY_POP(); push(subInst(a, b)); break; }
            case OP_MUL: { BINARY_POP(); push(mulInst(a, b)); break; }
            case OP_DIV: { BINARY_POP(); push(divInst(a, b)); break; }
            case OP_RETURN: { printValue(pop()); printf("\n"); return INTERPRET_OK; }
        }
    }

    #undef READ_CONSTANT
    #undef READ_BYTE
}

InterpretResult interpret(const char* source)
{
    compile(source);
    return INTERPRET_OK;
}
