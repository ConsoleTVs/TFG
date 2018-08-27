/**
 * |-------------|
 * | Void Parser |
 * |-------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/parser.hpp"
#include "../include/logger.hpp"

#define NEXT() (*(parser->current++))
#define IS_AT_END() (parser->current == TOKEN_EOF)
#define LOOKAHEAD(n) (*(parser->current + n))

static Parser *parser = new Parser;

void initParser(std::vector<Token> tokens)
{
    parser->tokens = tokens;
    parser->current = &tokens[0];
}

static Token consume(TokenType type, const char* message) {
    if (parser->current->type == type) {
        return NEXT();
    }

    error(std::string(message), parser->current->line);
}

std::vector<Statement> parse()
{
    return std::vector<Statement>();
}

#undef NEXT
#undef IS_AT_END
#undef LOOKAHEAD