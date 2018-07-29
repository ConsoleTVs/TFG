/**
 * |---------------|
 * | Void Compiler |
 * |---------------|
 *
 * Copyright 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 */

#include "../include/compiler.hpp"
#include "../include/scanner.hpp"

void compile(const char *source)
{
    initScanner(source);
}

unsigned int Expression::compile()
{
    printf("Unknown expression to compile\n");
    exit(0);
}

unsigned int Statement::compile()
{
    printf("Unknown expression to compile\n");
    exit(0);
}

unsigned int Number::compile()
{
    addOpCode(&program, OP_CONSTANT, this->line);
    addOpCode(&program, addConstant(&program, createValue(this->value)), this->line);
    return 2;
}

unsigned int String::compile()
{
    addOpCode(&program, OP_CONSTANT, this->line);
    addOpCode(&program, addConstant(&program, createValue(this->value)), this->line);
    return 2;
}

unsigned int Boolean::compile()
{
    addOpCode(&program, OP_CONSTANT, this->line);
    addOpCode(&program, addConstant(&program, createValue(this->value)), this->line);
    return 2;
}

unsigned int List::compile()
{
    unsigned int instructions = 0;
    for (unsigned int i = this->value.size() - 1; i >= 0; i--) {
        instructions += this->value[i]->compile();
    }
    addOpCode(&program, OP_LIST, this->line);
    return instructions + 1;
}

unsigned int None::compile()
{
    addOpCode(&program, OP_CONSTANT, this->line);
    addOpCode(&program, addConstant(&program, createValue()), this->line);
    return 2;
}

unsigned int Group::compile()
{
    return this->expression->compile();
}

static unsigned int compileOperator(std::string op) //! THIS NEEDS TO BE WRITTEN!!
{
    return 0;
}

unsigned int Unary::compile()
{
    return this->right->compile() + compileOperator(this->op);
}

unsigned int Binary::compile()
{
    return this->left->compile() + this->right->compile() + compileOperator(this->op);
}

unsigned int Variable::compile()
{
    addOpCode(&program, OP_LOAD, this->line);
    addOpCode(&program, addConstant(&program, createValue(this->name)), this->line);
    return 2;
}

unsigned int Assign::compile()
{
    addOpCode(&program, OP_STORE, this->line);
    addOpCode(&program, addConstant(&program, createValue(this->name)), this->line);
    return 2;
}