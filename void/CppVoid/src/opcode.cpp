/**
 * |-------------------------------|
 * | Void Bytecode Pperation Codes |
 * |-------------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/opcode.hpp"

static double numberCast(Value a)
{
    switch (a.kind) {
        case VALUE_NUMBER: return a.nvalue;
        case VALUE_BOOLEAN: return (double) a.bvalue ? 1 : 0;
        case VALUE_STRING: return (double) a.svalue->length();
        case VALUE_LIST: return (double) a.lvalues->size();
        case VALUE_NONE: return (double) 0;
    }
}

static bool booleanCast(Value a)
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

bool isTrue(Value a)
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

Value minusInst(Value a)
{
    if (a.kind == VALUE_STRING) {
        reverse(a.svalue->begin(), a.svalue->end());
        return createValue(*a.svalue);
    }
    return createValue(-numberCast(a));
}

Value notInst(Value a)
{
    return createValue(!booleanCast(a));
}

Value addInst(Value a, Value b)
{
    return createValue(numberCast(a) + numberCast(b));
}

Value subInst(Value a, Value b)
{
    return createValue(numberCast(a) - numberCast(b));
}

Value mulInst(Value a, Value b)
{
    return createValue(numberCast(a) * numberCast(b));
}

Value divInst(Value a, Value b)
{
    double bn = numberCast(b);
    if (bn == 0) { printf("Division by zero."); exit(0); }
    return createValue(numberCast(a) / bn);
}

Value eqInst(Value a, Value b)
{
    if (a.kind == VALUE_STRING && b.kind == VALUE_STRING) return createValue(*a.svalue == *b.svalue);
    return createValue(numberCast(a) == numberCast(b));
}

Value neqInst(Value a, Value b)
{
    if (a.kind == VALUE_STRING && b.kind == VALUE_STRING) return createValue(*a.svalue != *b.svalue);
    return createValue(numberCast(a) != numberCast(b));
}

Value ltInst(Value a, Value b)
{
    return createValue(numberCast(a) < numberCast(b));
}

Value lteInst(Value a, Value b)
{
    return createValue(numberCast(a) <= numberCast(b));
}

Value htInst(Value a, Value b)
{
    return createValue(numberCast(a) > numberCast(b));
}

Value hteInst(Value a, Value b)
{
    return createValue(numberCast(a) >= numberCast(b));
}

Value lenInst(Value a)
{
    return createValue(numberCast(a));
}