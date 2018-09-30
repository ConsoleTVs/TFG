#include <iostream>
#include "../include/operation.hpp"
#include "../include/debug.hpp"

static float floatCast(Value value)
{
    switch (value.kind) {
        case KIND_FLOAT: return value.val.fvalue;
        case KIND_BOOL: return value.val.bvalue ? 1.0 : 0.0;
        case KIND_STRING: return (float) value.val.svalue->length();
        default:
            std::cerr << "Cannot convert value to number" << std::endl;
            exit(0);
    }
}

Value negInst(Value a)
{
    switch (a.kind) {
        case KIND_FLOAT: return createValue(-a.val.fvalue);
        case KIND_BOOL: return createValue(-floatCast(a));
        default:
            std::cerr << "Invalid operand type for unary negation." << std::endl;
            exit(1);
    }
}

Value addInst(Value a, Value b)
{
    switch (a.kind) {
        case KIND_FLOAT:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(a.val.fvalue + b.val.fvalue);
                case KIND_BOOL: return createValue(a.val.fvalue + floatCast(b));
                default: /* Invalid operands */;
            }
        case KIND_BOOL:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(floatCast(a) + b.val.fvalue);
                case KIND_BOOL: return createValue(floatCast(a) + floatCast(b));
                default: /* Invalid operands */;
            }
        default: /* Invalid operands */;
    }
    std::cerr << "Invalid operand type for binary addition." << std::endl;
    exit(0);
}

Value subInst(Value a, Value b)
{
    switch (a.kind) {
        case KIND_FLOAT:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(a.val.fvalue - b.val.fvalue);
                case KIND_BOOL: return createValue(a.val.fvalue - floatCast(b));
                default: /* Invalid operands */;
            }
        case KIND_BOOL:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(floatCast(a) - b.val.fvalue);
                case KIND_BOOL: return createValue(floatCast(a) - floatCast(b));
                default: /* Invalid operands */;
            }
        default: /* Invalid operands */;
    }
    std::cerr << "Invalid operand type for binary substraction." << std::endl;
    exit(0);
}

Value mulInst(Value a, Value b)
{
    switch (a.kind) {
        case KIND_FLOAT:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(a.val.fvalue * b.val.fvalue);
                case KIND_BOOL: return createValue(a.val.fvalue + floatCast(b));
                case KIND_STRING: {
                    std::string* val = b.val.svalue;
                    std::string* result = new std::string("");
                    for (int i = 0; i < a.val.fvalue; i++) {
                        result->append(*val);
                    }
                    return createValue(*result);
                }
                default: /* Invalid operands */;
            }
        case KIND_BOOL:
            switch (b.kind) {
                case KIND_FLOAT: return createValue(floatCast(a) * b.val.fvalue);
                case KIND_BOOL: return createValue(floatCast(a) * floatCast(b));
                case KIND_STRING: return createValue(a.val.bvalue ? *b.val.svalue : std::string(""));
                default: /* Invalid operands */;
            }
        case KIND_STRING:
            switch (b.kind) {
                case KIND_FLOAT: {
                    std::string* val = a.val.svalue;
                    std::string* result = new std::string("");
                    for (int i = 0; i < b.val.fvalue; i++) {
                        result->append(*val);
                    }
                    return createValue(*result);
                }
                case KIND_BOOL: return createValue(b.val.bvalue ? *a.val.svalue : std::string(""));
                default: /* Invalid operands */;
            }
        default: /* Invalid operands */;
    }
    std::cerr << "Invalid operand type for binary multiplication." << std::endl;
    exit(0);
}

Value divInst(Value a, Value b)
{
    switch (a.kind) {
        case KIND_FLOAT:
            switch (b.kind) {
                case KIND_FLOAT: {
                    if (b.val.fvalue == 0) {
                        std::cerr << "Division by zero cannot be performed." << std::endl;
                        exit(0);
                    }
                    return createValue(a.val.fvalue / b.val.fvalue);
                }
                case KIND_BOOL: {
                    if (floatCast(b) == 0) {
                        std::cerr << "Division by zero cannot be performed." << std::endl;
                        exit(0);
                    }
                    // Considering b will always be true, divide by 1, same as fvalue.
                    return createValue(a.val.fvalue);
                }
                default: /* Invalid operands */;
            }
        case KIND_BOOL:
            switch (b.kind) {
                case KIND_FLOAT: {
                    if (b.val.fvalue == 0) {
                        std::cerr << "Division by zero cannot be performed." << std::endl;
                        exit(0);
                    }
                    return createValue(floatCast(a) - b.val.fvalue);
                }
                case KIND_BOOL: {
                    if (floatCast(b) == 0) {
                        std::cerr << "Division by zero cannot be performed." << std::endl;
                        exit(0);
                    }
                    return createValue(floatCast(a) / floatCast(b));
                }
                default: /* Invalid operands */;
            }
        default: /* Invalid operands */;
    }
    std::cerr << "Invalid operand type for binary division." << std::endl;
    exit(0);
}