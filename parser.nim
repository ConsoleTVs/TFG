import tokens, rules, strutils

type
    Parser* = object
        tokens*: seq[Token]
        current: int

proc previous(parser: Parser): Token =
    return parser.tokens[parser.current - 1]

proc peek(parser: Parser): Token =
    return parser.tokens[parser.current]

proc isAtEnd(parser: Parser): bool =
    return parser.peek.kind == EOF

proc advance(parser: var Parser): Token =
    if not parser.isAtEnd:
        parser.current.inc # Increment the current position
    return parser.previous

proc check(parser: Parser, token: Tokens): bool =
    if parser.isAtEnd:
        return false
    return parser.peek.kind == token

proc match(parser: var Parser, tokens: varargs[Tokens]): bool =
    for token in tokens:
        if parser.check(token):
            discard parser.advance
            return true
    return false

proc consume(parser: var Parser, kind: Tokens, message: string): Token =
    if parser.check(kind):
        return parser.advance
    raise newException(Exception, message)

proc expression(parser: var Parser): Expr

proc primary(parser: var Parser): Expr =
    if parser.match(FALSE):
        return Literal(
            kind: lkBoolean,
            boolValue: false
        )
    if parser.match(TRUE):
        return Literal(
            kind: lkBoolean,
            boolValue: true
        )
    if parser.match(NONE):
        return Literal(
            kind: lkNone
        )
    if parser.match(NUMBER):
        return Literal(
            kind: lkNumber,
            numValue: parseFloat(parser.previous.value)
        )
    if parser.match(TEXT):
        return Literal(
            kind: lkText,
            textValue: parser.previous.value
        )

    if parser.match(LEFT_PAREN):
        discard parser.consume(RIGHT_PAREN, "Expected ')' after the expression")
        return Grouping(expression: parser.expression)

    raise newException(Exception, "Expected expression")

proc unary(parser: var Parser): Expr =
    if parser.match(BANG, MINUS):
        echo "UNARY"
        return Unary(
            operator: parser.previous,
            right: parser.unary
        )
    return parser.primary

proc multiplication(parser: var Parser): Expr =
    result = parser.unary
    while parser.match(SLASH, STAR):
        echo "MUL"
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.unary
        )

proc addition(parser: var Parser): Expr =
    result = parser.multiplication
    while parser.match(MINUS, PLUS):
        echo "ADD"
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.multiplication
        )

proc comparison(parser: var Parser): Expr =
    result = parser.addition
    while parser.match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL):
        echo "COMP"
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.addition
        )

proc equality(parser: var Parser): Expr =
    result = parser.comparison
    while parser.match(BANG_EQUAL, EQUAL_EQUAL):
        echo "EQ"
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.comparison()
        )

proc expression(parser: var Parser): Expr =
    return parser.equality

proc parse*(parser: var Parser): Expr =
    try:
        return parser.expression
    except:
        raise
