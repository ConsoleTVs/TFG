/**
 * |--------------|
 * | Void Scanner |
 * |--------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/scanner.hpp"

Scanner *scanner = new Scanner;

void initScanner(const char *source)
{
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}