/**
 * |-------------------------------|
 * | Void Bytecode Operation Codes |
 * |-------------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/opcode.hpp"
#include "../include/logger.hpp"
#include <algorithm>

static std::string OpCodeNames[155] = {
    "OP_CONSTANT",

    // Unary operations
    "OP_MINUS",
    "OP_NOT",

    // Binary operations
    "OP_ADD",
    "OP_SUB",
    "OP_MUL",
    "OP_DIV",
    "OP_EQ",
    "OP_NEQ",
    "OP_LT",
    "OP_LTE",
    "OP_HT",
    "OP_HTE",

    // Jumps and conditional jumps
    "OP_RJUMP",
    "OP_BRANCH_TRUE",
    "OP_BRANCH_FALSE",

    // Store and load
    "OP_STORE",
    "OP_LOAD",
    "OP_STORE_ACCESS",

    // Lists and dictionaries
    "OP_LIST",
    "OP_ACCESS",

    // Others
    "OP_LEN",
    "OP_EXIT"
};

void debug_opcode(uint8_t opcode)
{
    printf("%s", OpCodeNames[opcode].c_str());
}

void debug_opcodes(std::vector<uint8_t> opcodes)
{
    for (auto opcode : opcodes) {
        printf("%s\n", OpCodeNames[opcode].c_str());
    }
}

static double numberCast(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: return a->nvalue;
        case VALUE_BOOLEAN: return a->bvalue ? 1.0 : 0.0;
        case VALUE_STRING: return (double) a->svalue->length();
        case VALUE_LIST: return (double) a->lvalues->size();
        case VALUE_NONE: return 0.0;
    }
}

static bool booleanCast(Value *a)
{
    return numberCast(a) != 0;
    /*
    switch (a.kind) {
        case VALUE_NUMBER: return a.nvalue != 0;
        case VALUE_BOOLEAN: return a.bvalue;
        case VALUE_STRING: return a.svalue->length() != 0;
    }
    */
}

bool isTrue(Value *a)
{
    return (bool) numberCast(a);
}

/*
static std::string multiplyString(std::string a, double times)
{
    std::string result = "";
    for (; times > 0; times--) result.append(a);
    return result;
}
*/

Value minusInst(Value *a)
{
    if (a->kind == VALUE_STRING) {
        std::reverse(a->svalue->begin(), a->svalue->end());
        return createValue(*a->svalue);
    }
    return createValue(-numberCast(a));
}

Value notInst(Value *a)
{
    return createValue(!booleanCast(a));
}

Value addInst(Value *a, Value *b)
{
    return createValue(numberCast(a) + numberCast(b));
}

Value subInst(Value *a, Value *b)
{
    return createValue(numberCast(a) - numberCast(b));
}

Value mulInst(Value *a, Value *b)
{
    return createValue(numberCast(a) * numberCast(b));
}

Value divInst(Value *a, Value *b)
{
    double bn = numberCast(b);
    if (bn == 0) error("Division by zero.");
    return createValue(numberCast(a) / bn);
}

Value eqInst(Value *a, Value *b)
{
    if (a->kind == VALUE_STRING && b->kind == VALUE_STRING) return createValue(*a->svalue == *b->svalue);
    return createValue(numberCast(a) == numberCast(b));
}

Value neqInst(Value *a, Value *b)
{
    if (a->kind == VALUE_STRING && b->kind == VALUE_STRING) return createValue(*a->svalue != *b->svalue);
    return createValue(numberCast(a) != numberCast(b));
}

Value ltInst(Value *a, Value *b)
{
    return createValue(numberCast(a) < numberCast(b));
}

Value lteInst(Value *a, Value *b)
{
    return createValue(numberCast(a) <= numberCast(b));
}

Value htInst(Value *a, Value *b)
{
    return createValue(numberCast(a) > numberCast(b));
}

Value hteInst(Value *a, Value *b)
{
    return createValue(numberCast(a) >= numberCast(b));
}

Value lenInst(Value *a)
{
    return createValue(numberCast(a));
}