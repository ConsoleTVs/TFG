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

Value createValue(std::unordered_map<std::string, Value> a, std::vector<std::string> b)
{
    Value value;
    value.kind = VALUE_DICTIONARY;

    auto dictionary = new ValueDictionary;
    dictionary->values = new std::unordered_map<std::string, Value>(a);
    dictionary->key_order = new std::vector<std::string>(b);

    value.dvalues = dictionary;

    return value;
}

double numberCast(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: { return a->nvalue; }
        case VALUE_BOOLEAN: { return a->bvalue ? 1.0 : 0.0; }
        case VALUE_STRING: { return (double) a->svalue->length(); }
        case VALUE_LIST: { return (double) a->lvalues->size(); }
        case VALUE_DICTIONARY: { return (double) a->dvalues->values->size(); }
        case VALUE_NONE: { return 0.0; }
    }
}

std::string valueRepresentation(Value *a)
{
    std::string result = stringCast(a);

    if (a->kind == VALUE_STRING) {

    }

    return result;
}

std::string stringCast(Value *a)
{
    switch (a->kind) {
        case VALUE_NUMBER: { return std::to_string(a->nvalue); }
        case VALUE_BOOLEAN: { return a->bvalue ? "true" : "false"; }
        case VALUE_STRING: { return *a->svalue; }
        case VALUE_LIST: {
            std::string list = "[";
            if (a->lvalues->size() > 0) {
                for (auto element : *a->lvalues) {
                    list += (element.kind == VALUE_STRING ? '\'' + stringCast(&element) + '\'' : stringCast(&element)) + ", ";
                }
                list.pop_back(); list.pop_back(); // Pop the space and the comma
            }
            return list + "]";
        }
        case VALUE_DICTIONARY: {
            std::string dictionary = "{";
            if (a->dvalues->values->size() > 0) {
                for (auto element : *a->dvalues->key_order) {
                    auto value = a->dvalues->values->at(element);
                    dictionary += element + ": " + (value.kind == VALUE_STRING ? '\'' + stringCast(&value) + '\'' : stringCast(&value)) + ", ";
                }
                dictionary.pop_back(); dictionary.pop_back(); // Pop the space and the comma
            }
            return dictionary + "}";
        }
        case VALUE_NONE: { return "none"; }
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