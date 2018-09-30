/**
 * |-------------------|
 * | Nuua Error Logger |
 * |-------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#ifndef logger_hpp
#define logger_hpp

#include <string>

void error(const std::string error, int line = -1);
void info(const std::string error, int line = -1);
void success(const std::string error, int line = -1);
void warning(const std::string error, int line = -1);

#endif
