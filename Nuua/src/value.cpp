/**
 * |------------------|
 * | Nuua Value Types |
 * |------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#include "../include/value.hpp"

Value createValue()
{
    Value value;
    value.kind = VALUE_NONE;

    return value;
}

Value createValue(double a)
{
    Value value;
    value.kind = VALUE_NUMBER;
    value.nvalue = a;

    return value;
}

Value createValue(bool a)
{
    Value value;
    value.kind = VALUE_BOOLEAN;
    value.bvalue = a;

    return value;
}

Value createValue(std::string a)
{
    Value value;
    value.kind = VALUE_STRING;
    value.svalue = new std::string(a);

    return value;
}

Value createValue(std::vector<Value> a)
{
    Value value;
    value.kind = VALUE_LIST;
    value.lvalues = new std::vector<Value>(a);
    return value;
}

void printValue(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: printf("%f", a->nvalue); break;
        case VALUE_BOOLEAN: printf(a->bvalue ? "true" : "false"); break;
        case VALUE_STRING: printf("%s", a->svalue->c_str()); break;
        case VALUE_LIST: {
            printf("[");
            unsigned int i = 0;
            for (; i < a->lvalues->size() - 1; i++) {
                //printValue((*a->lvalues)[i]);
                printf(", ");
            }
            // printValue((*a->lvalues)[i + 1]);
            printf("]");
            break;
        }
        case VALUE_NONE: printf("None"); break;
    }
}