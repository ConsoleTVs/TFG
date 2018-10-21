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
#include <unordered_map>

typedef enum : uint8_t {
    VALUE_NUMBER,
    VALUE_BOOLEAN,
    VALUE_STRING,
    VALUE_LIST,
    VALUE_DICTIONARY,
    VALUE_NONE
} ValueKind;

typedef struct ValueDictionary ValueDictionary;

typedef struct Value {
    ValueKind kind;
    union {
        double nvalue;
        bool bvalue;
        std::string *svalue;
        std::vector<Value> *lvalues;
        ValueDictionary *dvalues;
    };
} Value;

typedef struct ValueDictionary {
    std::unordered_map<std::string, Value> *values;
    std::vector<std::string> *key_order;
} ValueDictionary;

Value createValue();
Value createValue(double a);
Value createValue(bool a);
Value createValue(std::string a);
Value createValue(std::vector<Value> a);
Value createValue(std::unordered_map<std::string, Value> a, std::vector<std::string> b);
double numberCast(Value *a);
std::string stringCast(Value *a);
std::string valueRepresentation(Value *a);
bool booleanCast(Value *a);
void printValue(Value *a);

#endif