import parseopt, lexer, rules, parser, vm, instructions, values, codegen, bytecode, tables

# Void standard library
import lib.std

#[
    Void Programming Language
    Copyright 2018 Erik Campobadal Forés <soc@erik.cat>
    All rights reserved
]#

proc run(input: string) =

    # Initialize all variables
    var
        lexer = input.newLexer
        tokens = lexer.scan
        parser = tokens.newParser
        ast = parser.parse
        vm = @[].newVM
        bytecode = vm.newBytecode

    # Add the void standard library
    vm.addStdLib

    # Add the program instructions
    for i in ast:
        vm.codegen(i)

    # Add the HALT instruction to determine end of program
    vm.program.add(HALTINST.newInstruction)

    # Find labels and optimize
    vm.findLabels
    vm.replaceLabelJumps

    # Save the bytecode to output.vovm to see how it's structured
    bytecode.save

    # Run the virtual machine
    vm.run

    # Dump the stack for debug purposes
    # vm.dumpStack

proc file(sourceFile: string) =
    var source: string
    try:
        source = sourceFile.readFile
    except:
        source = ""
        echo "There was an error reading the file '" & sourceFile & "'"
    if source != "":
        source.run
    else:
        quit()

proc prompt() =
    var ask: string
    while true:
        stdout.write ">>> "
        ask = stdin.readLine
        if ask == ".exit":
            quit()
        ask.run

when isMainModule:
    var
        params = initOptParser()
        sourceFile = ""

    for kind, key, val in params.getopt:
        if sourceFile == "" and kind == cmdArgument:
            sourceFile = key

    if sourcefile != "":
        file(sourceFile)
    else:
        prompt()
