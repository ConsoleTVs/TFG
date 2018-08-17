/**
 * |-------------------|
 * | Void Error Logger |
 * |-------------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/logger.hpp"
#include "../include/rang.hpp"

void error(const std::string error, unsigned int line)
{
    std::cout
        << rang::style::bold
        << rang::fg::red
        << "[Error] "
        << rang::fg::yellow
        << error
        << rang::style::reset
        << rang::style::bold
        << " [Line " << line << "]"
        << rang::style::reset
        << std::endl;
    exit(1);
}

void info(const std::string error, int line)
{
    std::cout
        << rang::style::bold
        << rang::fg::cyan
        << "[Info] "
        << rang::fg::yellow
        << error
        << rang::style::reset
        << rang::style::bold;
    if (line < 0) std::cout << " [Line " << line << "]";
    std::cout << rang::style::reset << std::endl;
}