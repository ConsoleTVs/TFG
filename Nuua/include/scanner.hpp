/**
 * |--------------|
 * | Nuua Scanner |
 * |--------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#ifndef scanner_hpp
#define scanner_hpp

#include "../include/token.hpp"
#include <vector>
#include <string>

typedef struct {
    const char *start;
    const char *current;
    unsigned int line;
} Scanner;

std::vector<Token> *scan(const char *source);

#endif