/**
 * |-------------|
 * | Void Parser |
 * |-------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef parser_hpp
#define parser_hpp

#include "token.hpp"
#include "compiler.hpp"
#include <vector>

typedef struct {
    std::vector<Token> tokens;
    Token *current;
} Parser;

void initParser(std::vector<Token> tokens);
std::vector<Statement> parse();

#endif
