import parseopt, lexer, parser, rules, interpreter, logs, enviroment, tables, callable

proc run(source: string) =
    # The magic starts here

    logger.success("Starting lexical analysis...", debug = true)

    var
        lexer = Lexer(source: source)
        tokens = lexer.scan

    for token in tokens:
        logger.info($token, "Token Found", debug = true)

    logger.success("Lexical analysis complete", debug = true)
    logger.success("Starting syntactic analysis...", debug = true)

    var
        parser = Parser(tokens: tokens)
        statements = parser.parse

    for s in statements:
        logger.info($s, "Statement", debug = true)
    logger.success("Syntactic analysis complete", debug = true)
    logger.success("Starting semantic and code evaluation...", debug = true)

    var
        enviroment = Enviroment(values: initTable[string, Value]())
        globals = Enviroment(values: initTable[string, Value]())
        interpreter = Interpreter(
            globals: globals,
            enviroment: enviroment
        )

    # Native functions
    enviroment.define("time", Time(
        arity: 0
    ))
    enviroment.define("cpuTime", CpuTime(
        arity: 0
    ))

    interpreter.interpret(statements)

    logger.success("Finished program", debug = true)

proc prompt() =
    logger.error(
        message = "Promp not yet done :c",
        halt = true
    )

proc file(path: string) =
    # The main program will be loaded over a file located in the path
    var source: string
    try:
        source = readFile(path)
    except:
        source = ""
        logger.error("There was an error reading the file '" & path & "'")
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

    # Set the logging level
    logger.debug = false

    for kind, key, val in params.getopt:
        if sourceFile == "" and kind == cmdArgument:
            sourceFile = key
        # Do something with other command line arguments
        if kind == cmdShortOption:
            if key == "d":
                logger.debug = true

    if sourcefile != "":
        # Execute the script in the file
        file(sourceFile)
    else:
        # Execute the interpreter promp
        prompt()