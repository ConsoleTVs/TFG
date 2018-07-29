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
#include <string>
#include <vector>

void compile(const char *source);

class Expression {
    public:
        unsigned int line;

        unsigned int virtual compile();
};
class Statement {
    public:
        unsigned int line;

        unsigned int virtual compile();
};

class Number : Expression
{
    public:
        double value;

        unsigned int compile();
};

class String : Expression
{
    public:
        std::string value;

        unsigned int compile();
};

class Boolean : Expression
{
    public:
        bool value;

        unsigned int compile();
};

class List : Expression
{
    public:
        std::vector<Expression *> value;

        unsigned int compile();
};

class None : Expression {
    public:
        unsigned int compile();
};

class Group : Expression
{
    public:
        Expression *expression;

        unsigned int compile();
};

class Unary : Expression
{
    public:
        std::string op; //! This should be changed to a TOKEN type
        Expression *right;

        unsigned int compile();
};

class Binary : Expression
{
    public:
        std::string op;
        Expression* left;
        Expression* right;

        unsigned int compile();
};

class Variable : Expression
{
    public:
        std::string name;

        unsigned int compile();
};

class Assign : Expression
{
    public:
        std::string name;

        unsigned int compile();
};

class AssignAccess : Expression
{
    public:
        std::string name;
        Expression *index;
        Expression *value;

        unsigned int compile();
};

class Logical : Expression
{
    public:
        std::string op;
        Expression *index;
        Expression *value;

        unsigned int compile();
};

class Call : Expression
{
    public:
        Expression *callee;
        std::vector<Expression *> *arguments;

        unsigned int compile();
};

class Access : Expression
{
    public:
        std::string *name;
        Expression *index;

        unsigned int compile();
};

#endif