import tokens, rules, strutils, console

type
    Parser* = ref object
        tokens*: seq[Token]
        current: int

proc previous(parser: Parser): Token =
    return parser.tokens[parser.current - 1]

proc peek(parser: Parser): Token =
    return parser.tokens[parser.current]

proc isAtEnd(parser: Parser): bool =
    return parser.peek.kind == EOF

proc advance(parser: Parser): Token =
    if not parser.isAtEnd:
        parser.current.inc # Increment the current position
    return parser.previous

proc check(parser: Parser, token: Tokens): bool =
    if parser.isAtEnd:
        return false
    return parser.peek.kind == token

proc match(parser: Parser, tokens: varargs[Tokens]): bool =
    for token in tokens:
        if parser.check(token):
            discard parser.advance
            return true
    return false

proc consume(parser: Parser, kind: Tokens, message: string): Token =
    if parser.check(kind):
        return parser.advance
    error(message)
    quit()

proc expression(parser: Parser): Expr

proc primary(parser: Parser): Expr =
    if parser.match(FALSE):
        return Literal(
            kind: lkTruth,
            truthValue: false
        )
    if parser.match(TRUE):
        return Literal(
            kind: lkTruth,
            truthValue: true
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
        var expression = parser.expression
        discard parser.consume(RIGHT_PAREN, "Expected ')' after the expression")
        return Grouping(expression: expression)

    error("Expected an expression. Failed with the lexeme " & parser.peek.lexeme & " at line " & $parser.peek.line)
    quit()

proc unary(parser: Parser): Expr =
    if parser.match(BANG, MINUS):
        return Unary(
            operator: parser.previous,
            right: parser.unary
        )
    return parser.primary

proc multiplication(parser: Parser): Expr =
    result = parser.unary
    while parser.match(SLASH, STAR):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.unary
        )

proc addition(parser: Parser): Expr =
    result = parser.multiplication
    while parser.match(MINUS, PLUS):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.multiplication
        )

proc comparison(parser: Parser): Expr =
    result = parser.addition
    while parser.match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.addition
        )

proc equality(parser: Parser): Expr =
    result = parser.comparison
    while parser.match(BANG_EQUAL, EQUAL_EQUAL):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.comparison()
        )

proc expression(parser: Parser): Expr =
    return parser.equality

proc statement(parser: Parser): Stmt

proc expressionStatement(parser: Parser): Stmt =
    var expression = parser.expression
    discard parser.consume(DOT, "Expect '.' after statement")
    return ExprStmt(expression: expression)

proc showStatement(parser: Parser): Stmt =
    var expression = parser.expression
    discard parser.consume(DOT, "Expect '.' after statement")
    return ShowStmt(expression: expression)

proc ifStatement(parser: Parser): Stmt =
    discard parser.consume(LEFT_PAREN, "Expect a '(' after the 'if' condition")
    var
        condition = parser.expression
        res = IfStmt(condition: condition)
    discard parser.consume(RIGHT_PAREN, "Expect a ')' after the 'if' condition")
    res.thenBranch = parser.statement
    res.elseBranch = nil
    if parser.match(ELSE):
        res.elseBranch = parser.statement
    return res

proc statement(parser: Parser): Stmt =
    if parser.match(IF):
        return parser.ifStatement
    if parser.match(SHOW):
        return parser.showStatement
    return parser.expressionStatement

proc parse*(parser: Parser): seq[Stmt] =
    result = @[]
    while not parser.isAtEnd:
        result.add(parser.statement)