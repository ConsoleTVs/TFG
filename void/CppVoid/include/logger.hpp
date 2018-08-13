/**
 * |-------------------|
 * | Void Error Logger |
 * |-------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef logger_hpp
#define logger_hpp

#include <string>

#define LOG_BUFFER 255

void error(const std::string error, unsigned int line);

#endif