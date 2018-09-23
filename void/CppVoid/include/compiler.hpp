/**
 * |---------------|
 * | Void Compiler |
 * |---------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#ifndef compiler_hpp
#define compiler_hpp

#include "program.hpp"
#include "token.hpp"
#include <string>
#include <vector>

typedef enum {
    RULE_EXPRESSION,
    RULE_STATEMENT,
    RULE_EXPRESSION_STATEMENT,
    RULE_NUMBER,
    RULE_STRING,
    RULE_BOOLEAN,
    RULE_LIST,
    RULE_NONE,
    RULE_GROUP,
    RULE_UNARY,
    RULE_BINARY,
    RULE_VARIABLE,
    RULE_ASSIGN,
    RULE_ASSIGN_ACCESS,
    RULE_LOGICAL,
    RULE_CALL,
    RULE_ACCESS,
    RULE_IF,
    RULE_WHILE,
} Rule;

class Expression
{
    public:
        unsigned int line;
        Rule type;

        Expression(Rule type = RULE_EXPRESSION) : type(type) {};
        unsigned int virtual compile();
};

class Statement
{
    public:
        unsigned int line;
        Rule type;

        Statement(Rule type = RULE_STATEMENT)
            : type(type) {};
        unsigned int virtual compile();
};

class ExpressionStatement : public Statement
{
    public:
        Expression *expression;

        ExpressionStatement(Expression *expression)
            : Statement(RULE_EXPRESSION_STATEMENT), expression(expression) {}
        unsigned int compile() override;
};

class Number : public Expression
{
    public:
        double value;

        Number(double value)
            : Expression(RULE_NUMBER), value(value) {};
        unsigned int compile() override;
};

class String : public Expression
{
    public:
        std::string value;

        String(std::string value)
            : Expression(RULE_STRING), value(value) {};
        unsigned int compile() override;
};

class Boolean : public Expression
{
    public:
        bool value;

        Boolean(bool value)
            : Expression(RULE_BOOLEAN), value(value) {};
        unsigned int compile() override;
};

class List : public Expression
{
    public:
        std::vector<Expression *> value;

        List(std::vector<Expression *> value)
            : Expression(RULE_LIST), value(value) {};
        unsigned int compile() override;
};

class None : public Expression
{
    public:
        None()
            : Expression(RULE_NONE) {};
        unsigned int compile() override;
};

class Group : public Expression
{
    public:
        Expression *expression;

        Group(Expression *value)
            : Expression(RULE_GROUP), expression(value) {};
        unsigned int compile() override;
};

class Unary : public Expression
{
    public:
        Token op; //! This should be changed to a TOKEN type
        Expression *right;

        Unary(Token op, Expression *right)
            : Expression(RULE_UNARY), op(op), right(right) {};
        unsigned int compile() override;
};

class Binary : public Expression
{
    public:
        Expression* left;
        Token op;
        Expression* right;

        Binary(Expression *left, Token op, Expression *right)
            : Expression(RULE_BINARY), left(left), op(op), right(right) {};
        unsigned int compile() override;
};

class Variable : public Expression
{
    public:
        std::string name;

        Variable(std::string name)
            : Expression(RULE_VARIABLE), name(name) {};
        unsigned int compile() override;
};

class Assign : public Expression
{
    public:
        std::string name;
        Expression *value;

        Assign(std::string name, Expression *value)
            : Expression(RULE_ASSIGN), name(name), value(value) {};
        unsigned int compile() override;
};

class AssignAccess : public Expression
{
    public:
        std::string name;
        Expression *index;
        Expression *value;

        AssignAccess(std::string name, Expression *index, Expression *value)
            : Expression(RULE_ASSIGN_ACCESS), name(name), index(index), value(value) {};
        unsigned int compile() override;
};

class Logical : public Expression
{
    public:
        Expression *left;
        Token op;
        Expression *right;

        Logical(Expression *left, Token op, Expression *right)
            : Expression(RULE_LOGICAL), left(left),  op(op), right(right) {};
        unsigned int compile() override;
};

class Call : public Expression
{
    public:
        Expression *callee;
        std::vector<Expression *> arguments;

        Call(Expression *callee, std::vector<Expression *> arguments)
            : Expression(RULE_CALL), callee(callee), arguments(arguments) {};
        unsigned int compile() override;
};

class Access : public Expression
{
    public:
        std::string name;
        Expression *index;

        Access(std::string name, Expression *index)
            : Expression(RULE_ACCESS), name(name), index(index) {};
        unsigned int compile() override;
};

/* Statements */
class If : public Statement
{
    public:
        Expression *condition;
        std::vector<Statement *> thenBranch;
        std::vector<Statement *> elseBranch;

        If(Expression *condition, std::vector<Statement *> thenBranch, std::vector<Statement *> elseBranch)
            : Statement(RULE_IF), condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {};
        unsigned int compile() override;
};

class While : public Statement
{
    public:
        Expression *condition;
        std::vector<Statement *> body;

    While(Expression *condition, std::vector<Statement *> body)
        : Statement(RULE_WHILE), condition(condition), body(body) {};
    unsigned int compile() override;
};

void compile(const char *source);
void debug_rules(std::vector<Rule> rules);
void debug_rules(std::vector<Statement *> rules);

#endif