/**
 * |---------------------------|
 * | Nuua Programming Language |
 * |---------------------------|
 *
 * Copyright (c) 2018 Erik Campobadal <soc@erik.cat>
 * https://nuua.io
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
        if (input == ".exit" || std::cin.fail() || std::cin.eof()) {
            std::cin.clear();
            exit(1);
        }

        printf("\n ");
        for (unsigned int k = 0; k < input.length() + 4; k++) {
            printf("=");
        }
        printf("\n");
        printf(" | %s |\n ", input.c_str());
        for (unsigned int k = 0; k < input.length() + 4; k++) {
            printf("=");
        }
        printf("\n");
        printf("\n");

        input += '\n';
        interpret(input.c_str());
        resetProgram();
    }
}

static void file(const char *file)
{
    std::ifstream programFile (file);
    if (programFile.is_open()) {
        std::string content( (std::istreambuf_iterator<char>(programFile) ), (std::istreambuf_iterator<char>()));
        interpret(content.c_str());
        exit(1);
    }

    fprintf(stderr, "Unable to open file '%s'\n", file); exit(0);
}

int main(int argc, char *argv[])
{
    initVM();

    switch (argc) {
        case 1: { prompt(); break; }
        case 2: { file(argv[1]); break; }
        default: { fprintf(stderr, "Invalid usage. nuua <path_to_file>\n"); exit(64); } // Exit status for incorrect command usage.
    }
}