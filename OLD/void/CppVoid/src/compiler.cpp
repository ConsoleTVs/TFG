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
#include "../include/parser.hpp"
#include "../include/logger.hpp"
#include "../include/token.hpp"

static std::vector<std::string> RuleNames = {
    "RULE_EXPRESSION",
    "RULE_STATEMENT",
    "RULE_EXPRESSION_STATEMENT",
    "RULE_NUMBER",
    "RULE_STRING",
    "RULE_BOOLEAN",
    "RULE_LIST",
    "RULE_NONE",
    "RULE_GROUP",
    "RULE_UNARY",
    "RULE_BINARY",
    "RULE_VARIABLE",
    "RULE_ASSIGN",
    "RULE_ASSIGN_ACCESS",
    "RULE_LOGICAL",
    "RULE_CALL",
    "RULE_ACCESS",
    "RULE_IF",
    "RULE_WHILE",
};

void compile(const char *source)
{
    auto code = parse(source);

    info("Started compiling...");

    for (auto node : *code) {
        node->compile();
    }

    addOpCode(OP_EXIT, 0);

    // debug_program();

    success("Compiling completed");
}

void debug_rules(std::vector<Rule> rules)
{
    for (auto rule : rules) {
        printf("%s\n", RuleNames[rule].c_str());
    }
}

void debug_rules(std::vector<Statement *> rules)
{
    for (auto stmt : rules) {
        printf("%s\n", RuleNames[stmt->type].c_str());
    }
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

unsigned int ExpressionStatement::compile()
{
    return this->expression->compile();
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

static unsigned int compileOperator(Token op, unsigned int line)
{
    switch (op.type) {
        case TOKEN_PLUS: { addOpCode(OP_ADD, line); break; }
        case TOKEN_MINUS: { addOpCode(OP_MINUS, line); break; }
        case TOKEN_STAR: { addOpCode(OP_MUL, line); break; }
        case TOKEN_SLASH: { addOpCode(OP_DIV, line); break; }
        case TOKEN_BANG: { addOpCode(OP_NOT, line); break; }
        case TOKEN_EQUAL: { addOpCode(OP_STORE, line); break; }
        case TOKEN_EQUAL_EQUAL: { addOpCode(OP_EQ, line); break; }
        case TOKEN_BANG_EQUAL: { addOpCode(OP_NEQ, line); break; }
        case TOKEN_LOWER: { addOpCode(OP_LT, line); break; }
        case TOKEN_LOWER_EQUAL: { addOpCode(OP_LTE, line); break; }
        case TOKEN_HIGHER: { addOpCode(OP_HT, line); break; }
        case TOKEN_HIGHER_EQUAL: { addOpCode(OP_HTE, line); break; }
        default: { debug_token(op); error("Unknown operation token in binary instruction"); }
    }

    return 1;
}

unsigned int Unary::compile()
{
    return this->right->compile() + compileOperator(this->op, this->line);
}

unsigned int Binary::compile()
{
    return this->left->compile() + this->right->compile() + compileOperator(this->op, this->line);
}

unsigned int Variable::compile()
{
    addOpCode(OP_LOAD, this->line);
    addOpCode(addConstant(createValue(this->name)), this->line);

    return 2;
}

unsigned int Assign::compile()
{
    unsigned int instructions = this->value->compile();
    addOpCode(OP_STORE, this->line);
    addOpCode(addConstant(createValue(this->name)), this->line);

    return instructions + 2;
}

unsigned int AssignAccess::compile()
{
    unsigned int instructions = this->value->compile() + this->index->compile();
    addOpCode(OP_STORE_ACCESS, this->line);
    addOpCode(addConstant(createValue(this->name)), this->line);

    return instructions + 2;
}

unsigned int Logical::compile()
{
    return 0;
}

unsigned int Call::compile()
{
    return 0;
}

unsigned int Access::compile()
{
    return 0;
}

unsigned int If::compile() //! Still needs to finish what happens if the else branch is present!!
{
    unsigned int instructions = 0;

    if (this->elseBranch.size() == 0) {
        instructions = this->condition->compile() + 2; // +2 of the OP_BRANCH_FALSE and CONSTANT

        addOpCode(OP_BRANCH_FALSE, this->line);
        unsigned int constantIndex = addConstant(createValue(0.0)), afterCondition = 0;
        addOpCode(constantIndex, this->line);

        for (auto stmt : this->thenBranch) {
            afterCondition += stmt->compile();
        }

        modifyConstant(constantIndex, createValue((double) (afterCondition + 1)));
        instructions += afterCondition;
    }

    return instructions;
}

unsigned int While::compile()
{
    int instructions = 0;
    instructions = this->condition->compile() + 4; // +4 of the OP_BRANCH_FALSE and CONSTANT + Rjump and constant

    addOpCode(OP_BRANCH_FALSE, this->line);
    int constantIndex = addConstant(createValue(0.0)), afterCondition = 0;
    addOpCode(constantIndex, this->line);

    for (auto stmt : this->body) {
        afterCondition += stmt->compile();
    }

    addOpCode(OP_RJUMP, this->line);
    addOpCode(addConstant(createValue((double) -(instructions + afterCondition - 1))), this->line);

    modifyConstant(constantIndex, createValue((double) (afterCondition + 3)));

    return instructions + afterCondition;
}