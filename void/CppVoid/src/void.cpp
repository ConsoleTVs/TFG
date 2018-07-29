/**
 * |---------------------------|
 * | Void Programming Language |
 * |---------------------------|
 *
 * Copyright (c) 2018 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include "../include/opcode.hpp"
#include "../include/program.hpp"
#include "../include/compiler.hpp"
#include "../include/vm.hpp"

static void prompt()
{
    std::string input;
    for (;;) {
        printf("-> ");
        std::getline(std::cin, input);
        if (input == ".exit") exit(0);
        interpret(input.c_str());
    }
}

static void file(const char *file)
{
    // Load from fileW
}

int main(int argc, char *argv[])
{
    // prompt();
    // a = 0
    addOpCode(OP_CONSTANT, 1);
    addOpCode(addConstant(createValue(0.0)), 2);
    addOpCode(OP_STORE, 3);
    addOpCode(addConstant(createValue(std::string("a"))), 4);
    // b = 0
    addOpCode(OP_CONSTANT, 5);
    addOpCode(addConstant(createValue(0.0)), 6);
    addOpCode(OP_STORE, 7);
    addOpCode(addConstant(createValue(std::string("b"))), 8);
    // while (a < 6000000)
    addOpCode(OP_LOAD, 9);
    addOpCode(addConstant(createValue(std::string("a"))), 10);
    addOpCode(OP_CONSTANT, 11);
    addOpCode(addConstant(createValue(6000000.0)), 12);
    addOpCode(OP_LT, 13);
    addOpCode(OP_BRANCH_FALSE, 14);
    addOpCode(addConstant(createValue(20.0)), 15);
    // b = a - b / 2;
    addOpCode(OP_LOAD, 16);
    addOpCode(addConstant(createValue(std::string("a"))), 17);
    addOpCode(OP_LOAD, 18);
    addOpCode(addConstant(createValue(std::string("b"))), 19);
    addOpCode(OP_CONSTANT, 20);
    addOpCode(addConstant(createValue(2.0)), 21);
    addOpCode(OP_DIV, 22);
    addOpCode(OP_SUB, 23);
    addOpCode(OP_STORE, 24);
    addOpCode(addConstant(createValue(std::string("b"))), 25);
    // a = a + 1;
    addOpCode(OP_LOAD, 26);
    addOpCode(addConstant(createValue(std::string("a"))), 27);
    addOpCode(OP_CONSTANT, 28);
    addOpCode(addConstant(createValue(1.0)), 29);
    addOpCode(OP_ADD, 30);
    addOpCode(OP_STORE, 31);
    addOpCode(addConstant(createValue(std::string("a"))), 32);
    // Back to the start of the loop
    addOpCode(OP_RJUMP, 33);
    addOpCode(addConstant(createValue(-25.0)), 34);
    // End of loop
    addOpCode(OP_LOAD, 35);
    addOpCode(addConstant(createValue(std::string("b"))), 36);
    // Return the result
    addOpCode(OP_RETURN, 37);

    initVM();
    // interpret(program);
    interpret();
    //freeVM();
}