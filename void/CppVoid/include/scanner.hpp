/**
 * |--------------|
 * | Void Scanner |
 * |--------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef scanner_hpp
#define scanner_hpp

#include <string>

typedef struct {
    const char *start;
    const char *current;
    unsigned int line;
} Scanner;

extern Scanner *scanner;

void initScanner(const char *source);

#endif