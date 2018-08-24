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
    auto tokens = scan();
    #ifdef DEBUG
        debug_tokens(tokens);
    #endif
    // initParser(tokens);
    // auto program = parse();
    // program.compile();
    printf("COMPILE DONE\n");
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
    addOpCode(OP_CONSTANT, this->line);
    addOpCode(addConstant(createValue(this->value)), this->line);
    return 2;
}

unsigned int String::compile()
{
    addOpCode(OP_CONSTANT, this->line);
    addOpCode(addConstant(createValue(this->value)), this->line);
    return 2;
}

unsigned int Boolean::compile()
{
    addOpCode(OP_CONSTANT, this->line);
    addOpCode(addConstant(createValue(this->value)), this->line);
    return 2;
}

unsigned int List::compile()
{
    unsigned int instructions = 0;
    for (auto value : this->value) {
        instructions += value->compile();
    }
    addOpCode(OP_LIST, this->line);
    return instructions + 1;
}

unsigned int None::compile()
{
    addOpCode(OP_CONSTANT, this->line);
    addOpCode(addConstant(createValue()), this->line);
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
    addOpCode(OP_LOAD, this->line);
    addOpCode(addConstant(createValue(this->name)), this->line);
    return 2;
}

unsigned int Assign::compile()
{
    addOpCode(OP_STORE, this->line);
    addOpCode(addConstant(createValue(this->name)), this->line);
    return 2;
}

unsigned int AssignAccess::compile()
{
    unsigned int instructions = this->value->compile() + this->index->compile();
    addOpCode(OP_STORE_ACCESS, this->line);
    return instructions + 1;
}