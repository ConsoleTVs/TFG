import tokens

type
    Lexer* = object
        source*: string
        tokens: seq[Token]
        start, current, line: int

proc isAtEnd(lexer: Lexer): bool =
    return lexer.current >= lexer.source.len

proc scan*(lexer: var Lexer): seq[Token] =
    # Reset the variables
    lexer.line = 1
    lexer.start = 0
    lexer.current = 0

    # Lexical analysis
    while not lexer.isAtEnd:
        lexer.start = lexer.current
        lexer.scanToken
    lexer.tokens.add(Token(tType: EOF, tLexeme: "", line: lexer.line))
    return lexer.tokens