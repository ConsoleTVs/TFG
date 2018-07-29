/**
 * |------------------------|
 * | Void Program structure |
 * |------------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/scanner.hpp"

void initScanner(const char *source)
{
    scanner.start = source;
    scanner.current = scanner.start;
    scanner.line = 1;
}