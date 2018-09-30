/**
 * |-------------|
 * | Nuua Parser |
 * |-------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
 */

#ifndef parser_hpp
#define parser_hpp

#include "token.hpp"
#include "compiler.hpp"
#include <vector>

typedef struct {
    Token *current;
} Parser;

void initParser(std::vector<Token> tokens);
std::vector<Statement *> *parse(const char *source);

#endif
