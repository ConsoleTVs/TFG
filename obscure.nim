import parseopt, lexer, parser, rules, interpreter, console

proc run(source: string) =
    # The magic starts here
    "Starting lexical analysis...".success

    var
        lexer = Lexer(source: source)
        tokens = lexer.scan

    for token in tokens:
        info($token, "Token Found")

    "Lexical analysis complete".success
    "Starting syntactic and semantic analysis...".success

    var
        parser = Parser(tokens: tokens)
        expression = parser.parse
    info($expression, "Abstract Syntax Tree")
    "Syntactic and semantic analysis complete".success
    "Starting code evaluation...".success

    var interpreter = Interpreter()
    success($interpreter.interpret(expression), "Expression Result")

proc prompt() =
    warning("Promp not yet done :c")
    quit()

proc file(path: string) =
    # The main program will be loaded over a file located in the path
    var source: string
    try:
        source = readFile(path)
    except:
        source = ""
        error("There was an error reading the file '" & path & "'")
    if source != "":
        # The source program is loaded into the source var
        run(source)
    else:
        # There was either an exception or the source is empty
        quit()

when isMainModule:
    var
        params = initOptParser()
        sourceFile = ""

    for kind, key, val in params.getopt:
        if sourceFile == "" and kind == cmdArgument:
            sourceFile = key
        # Do something with other command line arguments

    if sourcefile != "":
        # Execute the script in the file
        file(sourceFile)
    else:
        # Execute the interpreter promp
        prompt()