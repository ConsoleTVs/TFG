/**
 * |-------------------|
 * | Void Error Logger |
 * |-------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/logger.hpp"

void error(const char error[LOG_BUFFER], unsigned int line)
{
    printf("%s [Line %u]\n", error, line);
    exit(1);
}