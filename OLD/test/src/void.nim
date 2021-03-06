import parseopt, lexer, rules, parser, vm, instructions, values, codegen, bytecode, stdlib, tables
#[
    Void Programming Language
    Copyright 2018 Erik Campobadal Forés <soc@erik.cat>
    All rights reserved
]#

proc run(input: string) =
    var
        lexer = input.newLexer
        tokens = lexer.scan
        parser = tokens.newParser
        ast = parser.parse

    #for statement in ast:
    #    echo $statement

    #[
        var instructions: seq[Instruction] = @[]
        instructions.add(PushInst(value: NumberValue(value: 500)))
        instructions.add(PushInst(value: NumberValue(value: 10)))
        instructions.add(PushInst(value: NumberValue(value: 5)))
        instructions.add(AdditionInst())
        instructions.add(PushInst(value: NumberValue(value: 10)))
        instructions.add(SubstractionInst())
        instructions.add(PrintInst())
        instructions.add(DivisionInst())
    ]#

    var
        vm: VM = newVM(@[])
        bytecode: Bytecode = (vm: vm)

    # Add the void standard library
    vm.addStdLib

    # Add the program instructions
    for i in ast:
        vm.codegen(i)

    vm.program.add(newInstruction(HALTINST))
    bytecode.save
    vm.run
    #vm.dumpStack

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
