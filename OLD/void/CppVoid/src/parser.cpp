/**
 * |-------------|
 * | Void Parser |
 * |-------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/compiler.hpp" //! Possibly removable after testing
#include "../include/parser.hpp"
#include "../include/logger.hpp"
#include "../include/scanner.hpp"
#include <typeinfo>

#define CURRENT() (*(parser->current))
#define PREVIOUS() (*(parser->current - 1))
#define CHECK(token) (token == CURRENT().type)
#define NEXT() (*(parser->current++))
#define IS_AT_END() (parser->current->type == TOKEN_EOF)
#define LOOKAHEAD(n) (*(parser->current + n))

static Parser *parser = new Parser;

static Token advance()
{
    if (!IS_AT_END()) {
        return NEXT();
    }

    return *(parser->current);
}

static Token consume(TokenType type, const char* message) {
    if (parser->current->type == type) {
        return NEXT();
    }

    error(std::string(message), parser->current->line);
}

static bool match(TokenType token)
{
    if (CHECK(token)) {
        if (token != TOKEN_EOF) {
            NEXT();
        }
        return true;
    }

    return false;
}

static bool matchAny(std::vector<TokenType> tokens)
{
    for (auto token : tokens) {
        if (CHECK(token)) {
            if (token != TOKEN_EOF) {
                NEXT();
            }
            return true;
        }
    }

    return false;
}

std::string toString(Token token)
{
    //printf("Trying to convert to string the token (Length: %d)... ", token.length);
    std::string s;
    for (unsigned int i = 0; i < token.length; i++) {
        s += *(token.start + i);
    }
    //printf("%s\n", s.c_str());

    return s;
}

static Expression *expression();
static Statement *statement();

static bool isFunction()
{
    return false;
}

static Expression *function()
{

}

static Expression *primary()
{
    // debug_token(CURRENT());
    if (match(TOKEN_FALSE)) return new Boolean(false);
    if (match(TOKEN_TRUE)) return new Boolean(true);
    if (match(TOKEN_NONE)) return new None();
    if (match(TOKEN_NUMBER)) return new Number(std::stof(toString(PREVIOUS())));
    if (match(TOKEN_STRING)) return new String(toString(PREVIOUS()));
    if (match(TOKEN_IDENTIFIER)) return new Variable(toString(PREVIOUS()));
    if (match(TOKEN_LEFT_SQUARE)) {
        std::vector<Expression *> values;
        if (match(TOKEN_RIGHT_SQUARE)) {
            return new List(values);
        }
        for (;;) {
            if (IS_AT_END()) {
                error("Unfinished list, Expecting ']' after the last list element.");
            }
            values.push_back(expression());
            if (match(TOKEN_RIGHT_SQUARE)) {
                break;
            }
            consume(TOKEN_COMMA, "Expected ',' after list element");
        }

        return new List(values);
    }
    if (match(TOKEN_LEFT_PAREN)) {
        if (isFunction()) {
            return function();
        }
        auto value = expression();
        consume(TOKEN_RIGHT_PAREN, "Expected ')' after a group expression");
        return new Group(value);
    }
    // printf("FAILED AT: ");
    // debug_token(CURRENT());
    error("Expected an expression");
}

static Expression *finishCall(Expression *callee)
{
    std::vector<Expression *> arguments;
    if (!CHECK(TOKEN_RIGHT_PAREN)) {
        arguments.push_back(expression());
        while (match(TOKEN_COMMA) && !IS_AT_END()) {
            arguments.push_back(expression());
        }
    }
    consume(TOKEN_RIGHT_PAREN, "Expected ')' after call arguments");

    return new Call(callee, arguments);
}

static Expression *finishAccess(Expression *item)
{
    auto index = expression();
    consume(TOKEN_RIGHT_SQUARE, "Expected ']' after index access");

    return new Access(static_cast<Variable *>(item)->name, index);
}

static Expression *call()
{
    auto result = primary();
    for (;;) {
        if (match(TOKEN_LEFT_PAREN)) {
            result = finishCall(result);
        } else if (match(TOKEN_LEFT_SQUARE)) {
            result = finishAccess(result);
        } else {
            break;
        }
    }

    return result;
}

static Expression *unary()
{
    if (matchAny(std::vector<TokenType>({ TOKEN_BANG, TOKEN_MINUS }))) {
        auto op = PREVIOUS();
        return new Unary(op, unary());
    }

    return call();
}

static Expression *mulDivMod()
{
    auto result = unary();
    while (matchAny(std::vector<TokenType>({ TOKEN_SLASH, TOKEN_STAR, TOKEN_PERCENT }))) {
        auto op = PREVIOUS();
        result = new Binary(result, op, unary());
    }

    return result;
}

static Expression *addition()
{
    auto result = mulDivMod();
    while (matchAny(std::vector<TokenType>({ TOKEN_MINUS, TOKEN_PLUS }))) {
        auto op = PREVIOUS();
        result = new Binary(result, op, mulDivMod());
    }

    return result;
}

static Expression *comparison()
{
    auto result = addition();
    while (matchAny(std::vector<TokenType>({ TOKEN_HIGHER, TOKEN_HIGHER_EQUAL, TOKEN_LOWER, TOKEN_LOWER_EQUAL }))) {
        auto op = PREVIOUS();
        result = new Binary(result, op, addition());
    }

    return result;
}

static Expression *equality()
{
    auto result = comparison();
    while (matchAny(std::vector<TokenType>({ TOKEN_BANG_EQUAL, TOKEN_EQUAL_EQUAL }))) {
        auto op = PREVIOUS();
        result = new Binary(result, op, comparison());
    }

    return result;
}

static Expression *andOperator()
{
    auto result = equality();
    while (match(TOKEN_AND)) {
        auto op = PREVIOUS();
        result = new Logical(result, op, equality());
    }

    return result;
}

static Expression *orOperator()
{
    auto result = andOperator();
    while (match(TOKEN_AND)) {
        auto op = PREVIOUS();
        result = new Logical(result, op, andOperator());
    }

    return result;
}

static Expression *assignment()
{
    auto result = orOperator();
    if (match(TOKEN_EQUAL)) {
        switch (result->type) {
            case RULE_VARIABLE: { return new Assign(static_cast<Variable *>(result)->name, expression()); }
            case RULE_ACCESS: {
                auto res = static_cast<Access *>(result);
                return new AssignAccess(res->name, res->index, expression());
            }
            default: { error("Invalid assignment target", parser->current->line); };
        }
    }
    return result;
}

static Expression *expression()
{
    return assignment();
}

static Statement *expressionStatement()
{
    auto expr = expression();
    // printf("BEFORE: ");
    // debug_token(CURRENT());
    if (!matchAny(std::vector<TokenType>({ TOKEN_NEW_LINE, TOKEN_EOF }))) {
        error("Expected a new line or EOF after expression statement");
    }
    // printf("AFTER: ");
    // debug_token(CURRENT());
    return new ExpressionStatement(expr);
}

static std::vector<Statement *> getBockBody()
{
    std::vector<Statement *> body;
    while (!CHECK(TOKEN_RIGHT_BRACE) && !IS_AT_END()) {
        body.push_back(statement());
    }
    return body;
}

static Statement *ifStatement()
{
    consume(TOKEN_LEFT_PAREN, "Expected a '(' after 'if'");
    auto condition = expression();
    consume(TOKEN_RIGHT_PAREN, "Expected a ')' after 'if' condition");
    consume(TOKEN_LEFT_BRACE, "Expected a '{' after the ')'");
    consume(TOKEN_NEW_LINE, "Expected a new line after the '{'");
    auto thenBranch = getBockBody();
    consume(TOKEN_RIGHT_BRACE, "Unterminated block. Expected '}'");
    if (!matchAny(std::vector<TokenType>({ TOKEN_NEW_LINE, TOKEN_EOF }))) {
        error("Expected a new line after the '}'", parser->current->line);
    }

    return new If(condition, thenBranch, std::vector<Statement *>({}));
}

static Statement *whileStatement()
{
    consume(TOKEN_LEFT_PAREN, "Expected '(' after 'while'");
    auto condition = expression();
    consume(TOKEN_RIGHT_PAREN, "Expected ')' after 'while' condition");
    consume(TOKEN_LEFT_BRACE, "Expected a '{' after the ')'");
    consume(TOKEN_NEW_LINE, "Expected a new line after the '{'");
    auto body = getBockBody();
    consume(TOKEN_RIGHT_BRACE, "Unterminated block. Expected '}'");
    if (!matchAny(std::vector<TokenType>({ TOKEN_NEW_LINE, TOKEN_EOF }))) {
        error("Expected a new line after the '}'", parser->current->line);
    }
    return new While(condition, body);
}

static Statement *statement()
{
    if (match(TOKEN_IF)) {
        return ifStatement();
    } else if (match(TOKEN_WHILE)) {
        return whileStatement();
    }
    return expressionStatement();
}

std::vector<Statement *> *parse(const char *source)
{
    std::vector<Token> *tokens = scan(source);

    info("Started parsing...");

    parser->current = &tokens->front();

    auto code = new std::vector<Statement *>;

    while (!IS_AT_END()) {
        //printf("Looking for statement... Starting at ");
        //debug_token(CURRENT());
        code->push_back(statement());
    }

    // debug_rules(*code);

    success("Parsing completed");

    return code;
}

#undef CURRENT
#undef PREVIOUS
#undef CHECK
#undef NEXT
#undef IS_AT_END
#undef LOOKAHEAD