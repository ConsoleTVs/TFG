import tokens

type
    Lexer* = object
        source*: string
        tokens: seq[Token]
        start, current, line: int

proc isAtEnd(lexer: Lexer): bool =
    return lexer.current >= lexer.source.len

proc advance(lexer: var Lexer): char =
    lexer.current += 1
    return lexer.source[lexer.current - 1]

proc addToken(lexer: var Lexer, token: Tokens) =
    lexer.tokens.add(Token(
        tType: token,
        tLexeme: lexer.source[lexer.start..lexer.current - 1],
        tLine: lexer.line
    ))

proc scanToken(lexer: var Lexer) =
    var c = lexer.advance
    case c
        of '(': lexer.addToken(LEFT_PAREN)
        of ')': lexer.addToken(RIGHT_PAREN)
        of '\n': lexer.line += 1
        else: echo "Unknown character '" & c & "' found at line " & $lexer.line

proc scan*(lexer: var Lexer): seq[Token] =
    # Reset the variables
    lexer.line = 1
    lexer.start = 0
    lexer.current = 0
    lexer.tokens = @[]

    # Lexical analysis
    while not lexer.isAtEnd:
        lexer.start = lexer.current
        lexer.scanToken
    
    # Add the end of file token
    lexer.tokens.add(Token(
        tType: EOF,
        tLexeme: "",
        tLine: lexer.line
    ))

    # Return the lexical analysis result tokens
    return lexer.tokens