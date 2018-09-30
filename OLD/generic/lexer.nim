import tokens, strutils, tables, logs

type
    Lexer* = object
        source*: string
        tokens: seq[Token]
        start, current, line: int

const keywords = {
    "and"       : AND,
    "or"        : OR,
    "true"      : TRUE,
    "false"     : FALSE,
    "if"        : IF,
    "else"      : ELSE,
    "for"       : FOR,
    "while"     : WHILE,
    "show"      : SHOW,
    "none"      : NONE,
    "action"    : ACTION,
    "return"    : RETURN,
    "var"       : VAR
}.toTable

proc isAtEnd(lexer: Lexer): bool =
    return lexer.current >= lexer.source.len

proc advance(lexer: var Lexer): char =
    lexer.current.inc # Increment the current index
    return lexer.source[lexer.current - 1]

proc peek(lexer: Lexer, offset: int = 0): char =
    if lexer.isAtEnd or lexer.current + offset >= lexer.source.len:
        return '\0'
    return lexer.source[lexer.current + offset]

proc match(lexer: var Lexer, expected: char): bool =
    if lexer.isAtEnd or lexer.source[lexer.current] != expected:
        return false
    lexer.current.inc # Increment the current index
    return true

proc addToken(lexer: var Lexer, token: Tokens, value: string = nil) =
    lexer.tokens.add(Token(
        kind: token,
        lexeme: lexer.source[lexer.start..lexer.current - 1],
        value: value,
        line: lexer.line
    ))

proc text(lexer: var Lexer) =
    while lexer.peek != '"' and not lexer.isAtEnd:
        # It can be a multi-line text, so be sure to increment
        # the line number if needed
        if lexer.peek() == '\n':
            lexer.line.inc # Increment the current line
        discard lexer.advance
    # Check if we reached the end of the file
    if lexer.isAtEnd:
        logger.error(
            message = "There's an unterminated text at line " & $lexer.line,
            halt = true
        )
    # The remaining "
    discard lexer.advance
    lexer.addToken(TEXT, lexer.source[lexer.start + 1..lexer.current - 2])

proc number(lexer: var Lexer) =
    while lexer.peek.isDigit:
        discard lexer.advance
    if lexer.peek == '.' and lexer.peek(1).isDigit:
        discard lexer.advance
        while lexer.peek.isDigit:
            discard lexer.advance
    lexer.addToken(NUMBER, lexer.source[lexer.start..lexer.current - 1])

proc identifier(lexer: var Lexer) =
    while lexer.peek.isAlphaNumeric:
        discard lexer.advance
    var text = lexer.source[lexer.start..lexer.current - 1]
    if keywords.hasKey(text):
        lexer.addToken(keywords[text])
    else:
        lexer.addToken(IDENTIFIER)

proc scanToken(lexer: var Lexer) =
    var c = lexer.advance
    # Diferent cases for the current character
    case c:
        of '"': lexer.text
        of '(': lexer.addToken(LEFT_PAREN)
        of ')': lexer.addToken(RIGHT_PAREN)
        of ',': lexer.addToken(COMMA)
        of '.': lexer.addToken(DOT)
        of '+': lexer.addToken(PLUS)
        of '-': lexer.addToken(MINUS)
        of '*': lexer.addToken(STAR)
        # of ':': lexer.addToken(COLON)
        # of ';': lexer.addToken(SEMICOLON)
        of '{': lexer.addToken(LEFT_BRACE)
        of '}': lexer.addToken(RIGHT_BRACE)
        of '=':
            if lexer.match('='):
                lexer.addToken(EQUAL_EQUAL)
            else:
                lexer.addToken(EQUAL)
        of '!':
            if lexer.match('='):
                lexer.addToken(BANG_EQUAL)
            else:
                lexer.addToken(BANG)
        of '<':
            if lexer.match('='):
                lexer.addToken(LESS_EQUAL)
            else:
                lexer.addToken(LESS)
        of '>':
            if lexer.match('='):
                lexer.addToken(GREATER_EQUAL)
            else:
                lexer.addToken(GREATER)
        of '/':
            if lexer.match('/'):
                # There's an inline comment
                while lexer.peek != '\n' and not lexer.isAtEnd:
                    # Ignore character till new line
                    discard lexer.advance
            else:
                lexer.addToken(SLASH)
        of '\n': lexer.line.inc # Increment the current line
        of ' ', '\r', '\t': discard
        else:
            if c.isDigit:
                # The begining of a number
                lexer.number
            elif c.isAlphaAscii:
                # The begining of an identifier
                lexer.identifier
            else:
                # The character is unknown
                logger.warning("Unknown character '" & c & "' found at line " & $lexer.line)

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
        kind: EOF,
        line: lexer.line
    ))

    # Return the lexical analysis result tokens
    return lexer.tokens