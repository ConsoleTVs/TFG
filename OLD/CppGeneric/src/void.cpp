#include <iostream>
#include <fstream>
#include "../include/base.hpp"
#include "../include/chunk.hpp"
#include "../include/debug.hpp"
#include "../include/value.hpp"
#include "../include/vm.hpp"


static void runPrompt()
{
    for (std::string input;;) {
        std::cout << ">>> " << std::flush;
        std::cin >> input;
        if (input == ".exit") break;
        interpret(input);
    }
}

static void runFile(const char* file)
{
    std::ifstream myfile (file);
    if (myfile.is_open()) {
        std::string content( (std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()));
        std::cout << content << std::endl;
    } else {
        std::cout << "Unable to open file '" << file << "'." << std::endl;
    }
}

int main(int argc, const char* argv[])
{
    initVM();
    if (argc == 1) {
        runPrompt();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64); // Exit status for incorrect command usage.
    }
    freeVM();
}