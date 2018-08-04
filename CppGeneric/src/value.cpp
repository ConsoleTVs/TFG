#include <iostream>
#include "../include/value.hpp"
#include <vector>

Value createValue(const double value)
{
    Value rval;
    rval.kind = KIND_FLOAT;
    rval.val.fvalue = value;
    return rval;
}

Value createValue(const bool value)
{
    Value rval;
    rval.kind = KIND_BOOL;
    rval.val.bvalue = value;
    return rval;
}

Value createValue(const std::string value)
{
    Value rval;
    rval.kind = KIND_STRING;
    rval.val.svalue = new std::string(value);
    return rval;
}

void printValue(Value value)
{
    switch (value.kind) {
        case KIND_FLOAT:
            printf("%g", value.val.fvalue);
            break;
        case KIND_BOOL:
            printf("%s", value.val.bvalue ? "true" : "false");
            break;
        case KIND_STRING:
            printf("%s", value.val.svalue->c_str());
            break;
        default:
            printf("Unknown");
            break;
    }
}