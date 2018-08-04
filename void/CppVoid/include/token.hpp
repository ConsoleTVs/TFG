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

typedef enum {
    // Single-character tokens.
    TOKEN_NEW_LINE,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_SLASH,
    TOKEN_STAR,

    // One or two character tokens.
    TOKEN_RIGHT_ARROW,
    TOKEN_LEFT_ARROW,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_HIGHER,
    TOKEN_HIGHER_EQUAL,
    TOKEN_LOWER,
    TOKEN_LOWER_EQUAL,

    // Literals.
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,

    // Keywords.
    TOKEN_AND,
    TOKEN_CLASS,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FUN,
    TOKEN_FOR,
    TOKEN_IF,
    TOKEN_NIL,
    TOKEN_OR,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_SUPER,
    TOKEN_THIS,
    TOKEN_TRUE,
    TOKEN_VAR,
    TOKEN_WHILE,

    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    unsigned int length;
    unsigned int line;
} Token;

#endif