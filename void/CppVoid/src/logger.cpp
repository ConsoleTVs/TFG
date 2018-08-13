/**
 * |-------------------|
 * | Void Error Logger |
 * |-------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/logger.hpp"

void error(const std::string error, unsigned int line)
{
    printf("%s [Line %u]\n", error.c_str(), line);
    exit(1);
}