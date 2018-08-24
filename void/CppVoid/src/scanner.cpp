/**
 * |--------------|
 * | Void Scanner |
 * |--------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/scanner.hpp"
#include "../include/logger.hpp"
#include <string.h>
#include <unordered_map>

#define ADD_TOKEN(token) printf("Add...\n"); (tokens.push_back(makeToken(token)))
#define TOK_LENGTH() ((int) (scanner->current - scanner->start))
#define IS_AT_END() (*scanner->current == '\0')
#define NEXT() (*(scanner->current++))
#define PEEK() (*scanner->current)
#define PEEK_ON(offset) (*(scanner->current + offset))
// #define CHECK(c) (*(scanner->current + 1) == c)
#define IS_DIGIT(character) (character >= '0' && character <= '9')
#define IS_ALPHA(character) (character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z' || character == '_')
#define IS_ALPHANUM(character) (IS_ALPHA(character) || IS_DIGIT(character))

Scanner *scanner = new Scanner;

static const std::unordered_map<std::string, TokenType> reservedWords = {
    { "true", TOKEN_TRUE },
    { "false", TOKEN_FALSE },
    { "or", TOKEN_OR },
    { "and", TOKEN_AND },
    { "if", TOKEN_IF },
    { "else", TOKEN_ELSE },
    { "for", TOKEN_FOR },
    { "while", TOKEN_WHILE },
    { "nil", TOKEN_NIL },
    { "class", TOKEN_CLASS },
    { "self", TOKEN_SELF },
};

void initScanner(const char *source)
{
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}

static const std::string token_error()
{
    char e[255];
    sprintf(e, "Unexpected token '%c'", *scanner->start);
    return std::string(e);
}

static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = TOK_LENGTH();
    token.line = scanner->line;

    return token;
}

static bool match(const char c)
{
    if (IS_AT_END() || PEEK() != c) return false;
    scanner->current++;

    return true;
}

static TokenType is_string()
{
    while (PEEK() != '"' && !IS_AT_END()) {
        if (PEEK() == '\n') scanner->line++;
        NEXT();
    }

    if (IS_AT_END()) error("Unterminated string literal", scanner->line);

    NEXT();
    return TOKEN_STRING;
}

static TokenType isNumber()
{
    while (IS_DIGIT(PEEK())) NEXT();

    if (PEEK() == '.' && IS_DIGIT(PEEK_ON(1))) {
        NEXT(); // The . itelf
        while (IS_DIGIT(PEEK())) NEXT();
    }

    return TOKEN_NUMBER;
}

static TokenType isIdentifier()
{
    while (IS_ALPHANUM(PEEK())) NEXT();

    char * key = (char *) malloc(TOK_LENGTH() + 1);
    memcpy(key, scanner->start, TOK_LENGTH());
    key[TOK_LENGTH()] = '\0';

    return reservedWords.find(key) != reservedWords.end() ? reservedWords.at(key) : TOKEN_IDENTIFIER;
}

std::vector<Token> scan()
{
    std::vector<Token> tokens;
    for (;;) {
        if (IS_AT_END()) {
            tokens.push_back(makeToken(TOKEN_EOF));
            break;
        }
        switch (char c = NEXT()) {
            case ' ': case '\r': case '\t': { break; }
            case '\n': { scanner->line++; ADD_TOKEN(TOKEN_NEW_LINE); break; }
            case '#': { while (PEEK() != '\n' && !IS_AT_END()) NEXT(); break; }
            case '(': { ADD_TOKEN(TOKEN_LEFT_PAREN); break; }
            case ')': { ADD_TOKEN(TOKEN_RIGHT_PAREN); break; }
            case '{': { ADD_TOKEN(TOKEN_LEFT_BRACE); break; }
            case '}': { ADD_TOKEN(TOKEN_RIGHT_BRACE); break; }
            case ',': { ADD_TOKEN(TOKEN_COMMA); break; }
            case '.': { ADD_TOKEN(TOKEN_DOT); break; }
            case '-': {
                if (match('>')) {
                    if (match('>')) {
                        ADD_TOKEN(TOKEN_DOUBLE_RIGHT_ARROW);
                        break;
                    }
                    ADD_TOKEN(TOKEN_RIGHT_ARROW);
                    break;
                }
                ADD_TOKEN(TOKEN_MINUS);
                break;
            }
            case '+': { ADD_TOKEN(TOKEN_PLUS); break; }
            case '/': { ADD_TOKEN(TOKEN_SLASH); break; }
            case '*': { ADD_TOKEN(TOKEN_STAR); break; }
            case '=': { ADD_TOKEN(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL); break; }
            case '"': { ADD_TOKEN(is_string()); break; }
            case '<': {
                if (match('-')) { ADD_TOKEN(TOKEN_LEFT_ARROW); break; }
                ADD_TOKEN(match('=') ? TOKEN_LOWER_EQUAL : TOKEN_LOWER); break;
            }
            case '>': { ADD_TOKEN(match('=') ? TOKEN_HIGHER_EQUAL : TOKEN_HIGHER); break; }
            default: {
                if (IS_DIGIT(c)) { ADD_TOKEN(isNumber()); break; }
                if (IS_ALPHA(c)) { ADD_TOKEN(isIdentifier()); break; }
                error(token_error(), scanner->line);
            }
        }
        printf("Next\n");
    }
    return tokens;
}
