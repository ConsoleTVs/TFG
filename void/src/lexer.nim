import tokens, tables, strutils

type
    Lexer = ref tuple
        source: string
        tokens: seq[Token]
        start, current, line: int

const keywords = {
    "and"       : TOK_AND,
    "or"        : TOK_OR,
    "true"      : TOK_TRUE,
    "false"     : TOK_FALSE,
    "if"        : TOK_IF,
    "else"      : TOK_ELSE,
    "for"       : TOK_FOR,
    "while"     : TOK_WHILE,
    "print"     : TOK_PRINT,
    "none"      : TOK_NONE,
    "return"    : TOK_RETURN,
}.toTable

proc newLexer*(source: string): Lexer =
    new result
    result.source = source
    result.tokens = @[]
    result.start = 0
    result.current = 0
    result.line = 1

proc isAtEnd(lexer: Lexer): bool = lexer.current >= lexer.source.len

proc advance(lexer: Lexer): char =
    lexer.current.inc
    return lexer.source[lexer.current - 1]

proc peek(lexer: Lexer, offset: int = 0): char =
    if lexer.isAtEnd or lexer.current + offset >= lexer.source.len:
        return '\0'
    return lexer.source[lexer.current + offset]

proc nextIs(lexer: Lexer, expected: char): bool =
    if lexer.isAtEnd or lexer.source[lexer.current] != expected:
        return false
    lexer.current.inc
    return true

proc addToken(lexer: Lexer, kind: Kinds, value: string = nil) =
    var token: Token
    token.kind = kind
    token.lexeme = lexer.source[lexer.start..lexer.current - 1]
    token.value = value
    token.line = lexer.line
    lexer.tokens.add(token)

proc text(lexer: Lexer) =
    while lexer.peek != '"' and not lexer.isAtEnd:
        if lexer.peek == '\n':
            lexer.line.inc
        discard lexer.advance
    if lexer.isAtEnd:
        echo "There's an unterminated text at line " & $lexer.line
        quit()
    discard lexer.advance # TOK_he remaining '"'
    lexer.addToken(TOK_STRING, lexer.source[lexer.start + 1..lexer.current - 2])

proc number(lexer: Lexer) =
    while lexer.peek.isDigit:
        discard lexer.advance
    if lexer.peek == '.' and lexer.peek(1).isDigit:
        discard lexer.advance
        while lexer.peek.isDigit:
            discard lexer.advance
    lexer.addToken(TOK_NUMBER, lexer.source[lexer.start..lexer.current - 1])

proc identifier(lexer: Lexer) =
    while lexer.peek.isAlphaNumeric:
        discard lexer.advance
    let text = lexer.source[lexer.start..lexer.current - 1]
    if keywords.hasKey(text):
        lexer.addToken(keywords[text])
    else:
        lexer.addToken(TOK_IDENTIFIER)

proc scanToken(lexer: Lexer) =
    let c = lexer.advance
    case c:
        of ' ', '\r', '\t': discard
        of '#':
            while lexer.peek != '\n' and not lexer.isAtEnd:
                discard lexer.advance
        of '+': lexer.addToken(TOK_PLUS)
        of '-':
            if lexer.nextIs('>'):
                lexer.addToken(TOK_SIMPLE_ARROW)
            else:
                lexer.addToken(TOK_MINUS)
        of '*': lexer.addToken(TOK_STAR)
        of '/': lexer.addToken(TOK_SLASH)
        of '(': lexer.addToken(TOK_LEFT_PAREN)
        of ')': lexer.addToken(TOK_RIGHT_PAREN)
        of '[': lexer.addToken(TOK_LEFT_SPAREN)
        of ']': lexer.addToken(TOK_RIGHT_SPAREN)
        of '{': lexer.addToken(TOK_LEFT_BRACE)
        of '}': lexer.addToken(TOK_RIGHT_BRACE)
        of ',': lexer.addToken(TOK_COMMA)
        of '.': lexer.addToken(TOK_DOT)
        of ':': lexer.addToken(TOK_COLON)
        of ';': lexer.addToken(TOK_SEMICOLON)
        of '=':
            if lexer.nextIs('='):
                lexer.addToken(TOK_EQUAL_EQUAL)
            elif lexer.nextIs('>'):
                lexer.addTOken(TOK_ARROW)
            else:
                lexer.addToken(TOK_EQUAL)
        of '!':
            if lexer.nextIs('='):
                lexer.addToken(TOK_BANG_EQUAL)
            else:
                lexer.addToken(TOK_BANG)
        of '>':
            if lexer.nextIs('='):
                lexer.addToken(TOK_GREATER_EQUAL)
            else:
                lexer.addToken(TOK_GREATER)
        of '<':
            if lexer.nextIs('='):
                lexer.addToken(TOK_LESS_EQUAL)
            else:
                lexer.addToken(TOK_LESS)
        of '\n': lexer.line.inc
        of '"': lexer.text
        else:
            if c.isDigit:
                lexer.number
            elif c.isAlphaAscii:
                lexer.identifier
            else:
                echo "Unknown character '" & c & "' found at line " & $lexer.line

proc scan*(lexer: Lexer): seq[Token] =
    while not lexer.isAtEnd:
        lexer.start = lexer.current
        lexer.scanToken
    lexer.tokens.add(newToken(kind = TOK_EOF, line = lexer.line))
    return lexer.tokens