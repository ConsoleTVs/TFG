#ifndef value_hpp
#define value_hpp

#include "base.hpp"
#include <string>

typedef enum {
    KIND_FLOAT,
    KIND_BOOL,
    KIND_STRING,
} ValueKind;

typedef struct {
    ValueKind kind;
    union {
        float fvalue;
        bool bvalue;
        std::string* svalue;
    } val;
} Value;

typedef std::vector<Value> ValuePool;

Value createValue(double value);
Value createValue(bool value);
Value createValue(std::string value);
void printValue(Value value);

#endif