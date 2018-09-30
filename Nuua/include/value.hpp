/**
 * |------------------|
 * | Nuua Value Types |
 * |------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#ifndef value_hpp
#define value_hpp

#include <string>
#include <vector>

typedef enum : uint8_t {
    VALUE_NUMBER,
    VALUE_BOOLEAN,
    VALUE_STRING,
    VALUE_LIST,
    VALUE_NONE
} ValueKind;

typedef struct Value {
    ValueKind kind;
    union {
        double nvalue;
        bool bvalue;
        std::string *svalue;
        std::vector<Value> *lvalues;
    };
} Value;

Value createValue();
Value createValue(double a);
Value createValue(bool a);
Value createValue(std::string a);
Value createValue(std::vector<Value> a);
void printValue(Value *a);

#endif