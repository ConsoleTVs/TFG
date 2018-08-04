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

#define ADD_TOKEN(token) printf("Add...\n"); (tokens.push_back(makeToken(token)))

#define IS_AT_END() (*scanner->current == '\0')
#define NEXT() (*(scanner->current++))
#define PEEK() (*scanner->current)
// #define CHECK(c) (*(scanner->current + 1) == c)

Scanner *scanner = new Scanner;

void initScanner(const char *source)
{
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}

static const char * token_error()
{
    char e[LOG_BUFFER];
    sprintf(e, "Unexpected token %c", *scanner->start);
    return std::string(e).c_str();
}

static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int) (scanner->current - scanner->start);
    token.line = scanner->line;

    return token;
}

static bool match(const char c)
{
    if (IS_AT_END() || PEEK() != c) return false;
    scanner->current++;

    return true;
}

std::vector<Token> scan()
{
    std::vector<Token> tokens;
    for (;;) {
        if (IS_AT_END()) {
            tokens.push_back(makeToken(TOKEN_EOF));
            break;
        }
        switch (NEXT()) {
            case '#': { while (PEEK() != '\n' && !IS_AT_END()) NEXT(); break; }
            case '\n': { scanner->line++; ADD_TOKEN(TOKEN_NEW_LINE); break; }
            case '(': { ADD_TOKEN(TOKEN_LEFT_PAREN); break; }
            case ')': { ADD_TOKEN(TOKEN_RIGHT_PAREN); break; }
            case '{': { ADD_TOKEN(TOKEN_LEFT_BRACE); break; }
            case '}': { ADD_TOKEN(TOKEN_RIGHT_BRACE); break; }
            case ',': { ADD_TOKEN(TOKEN_COMMA); break; }
            case '.': { ADD_TOKEN(TOKEN_DOT); break; }
            case '-': { ADD_TOKEN(match('>') ? TOKEN_RIGHT_ARROW : TOKEN_MINUS); break; }
            case '+': { ADD_TOKEN(TOKEN_PLUS); break; }
            case '/': { ADD_TOKEN(TOKEN_SLASH); break; }
            case '*': { ADD_TOKEN(TOKEN_STAR); break; }
            case '=': { ADD_TOKEN(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL); break; }
            case '<': {
                if (match('-')) { ADD_TOKEN(TOKEN_LEFT_ARROW); break; }
                ADD_TOKEN(match('=') ? TOKEN_LOWER_EQUAL : TOKEN_LOWER); break;
            }
            case '>': { ADD_TOKEN(match('=') ? TOKEN_HIGHER_EQUAL : TOKEN_HIGHER); break; }
            default: { error(token_error(), scanner->line); }
        }
        printf("Next\n");
    }
    return tokens;
}