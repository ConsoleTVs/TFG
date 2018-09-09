/**
 * |-------------|
 * | Void Tokens |
 * |-------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef token_hpp
#define token_hpp

#include <string>
#include <vector>

typedef enum : uint8_t {
    TOKEN_NEW_LINE, // \n
    TOKEN_LEFT_PAREN, // (
    TOKEN_RIGHT_PAREN, // )
    TOKEN_LEFT_BRACE, // {
    TOKEN_RIGHT_BRACE, // }
    TOKEN_COMMA, // ,
    TOKEN_DOT, // .
    TOKEN_MINUS, // -
    TOKEN_PLUS, // +
    TOKEN_SLASH, // /
    TOKEN_STAR, // *
    TOKEN_RIGHT_ARROW, // ->
    TOKEN_DOUBLE_RIGHT_ARROW, // ->>
    TOKEN_LEFT_ARROW, // <-
    TOKEN_BANG, // !
    TOKEN_BANG_EQUAL, // !=
    TOKEN_EQUAL, // =
    TOKEN_EQUAL_EQUAL, // ==
    TOKEN_HIGHER, // >
    TOKEN_HIGHER_EQUAL, // >=
    TOKEN_LOWER, // <
    TOKEN_LOWER_EQUAL, // <=
    TOKEN_IDENTIFIER, // <identifier>
    TOKEN_STRING, // <string>
    TOKEN_NUMBER, // <number>
    TOKEN_OR, // or
    TOKEN_AND, // and
    TOKEN_CLASS, // class
    TOKEN_ELSE, // else
    TOKEN_TRUE, // true
    TOKEN_FALSE, // false
    // TOKEN_FUN, // Not really needed
    TOKEN_WHILE, // while
    TOKEN_FOR, // for
    TOKEN_IF, // if
    TOKEN_NONE, // none
    // TOKEN_RETURN, // Not really needed
    // TOKEN_SUPER,
    TOKEN_SELF, // self
    TOKEN_EOF, // \0
    TOKEN_PERCENT, // %
    TOKEN_LEFT_SQUARE, // [
    TOKEN_RIGHT_SQUARE // ]
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    unsigned int length;
    unsigned int line;
} Token;

void debug_token(Token token);
void debug_tokens(std::vector<Token> tokens);
void debug_tokens(std::vector<TokenType> tokens);

#endif
