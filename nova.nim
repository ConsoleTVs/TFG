import parseopt, lexer

proc run(source: string) =
    # The magic starts here
    var
        lexer = Lexer(source: source)
        tokens = lexer.scan
    for token in tokens:
        echo $token

proc prompt() =
    echo "Promp not yet done :c"
    quit()

proc file(path: string) =
    # The main program will be loaded over a file located in the path
    var source: string
    try:
        source = readFile(path)
    except:
        source = ""
        echo "There was an error reading the file '" & path & "'"
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