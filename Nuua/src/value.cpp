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

double numberCast(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: { return a->nvalue; }
        case VALUE_BOOLEAN: { return a->bvalue ? 1.0 : 0.0; }
        case VALUE_STRING: { return (double) a->svalue->length(); }
        case VALUE_LIST: { return (double) a->lvalues->size(); }
        case VALUE_NONE: { return 0.0; }
    }
}

std::string stringCast(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: { return std::to_string(a->nvalue); }
        case VALUE_BOOLEAN: { return a->bvalue ? "true" : "false"; }
        case VALUE_STRING: { return *a->svalue; }
        case VALUE_LIST: {
            std::string list = "[";
            for (unsigned int i = 0; i < a->lvalues->size(); i++) {
                list += stringCast(&a->lvalues->at(i));
                if (i < a->lvalues->size() - 1) { list += ", "; }
            }
            return list + "]";
        }
        case VALUE_NONE: return "none";
    }
}

bool booleanCast(Value *a)
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

void printValue(Value *a)
{
    printf("%s", stringCast(a).c_str());
}