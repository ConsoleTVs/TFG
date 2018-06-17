import tokens, rules, strutils, logs

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
    logger.error(
        message = message,
        halt = true
    )

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

    if parser.match(IDENTIFIER):
        return Variable(name: parser.previous)

    if parser.match(LEFT_PAREN):
        var expression = parser.expression
        discard parser.consume(RIGHT_PAREN, "Expected ')' after the expression")
        return Grouping(expression: expression)

    logger.error(
        message = "Expected an expression. Failed with the lexeme " & parser.peek.lexeme & " at line " & $parser.peek.line,
        halt = true
    )

proc finishCall(parser: Parser, callee: Expr): Expr =
    var arguments: seq[Expr] = @[]
    if not parser.check(RIGHT_PAREN):
        arguments.add(parser.expression)
        if arguments.len >= 32:
            logger.error($parser.peek, "Cannot have more than 32 arguments.");
        while parser.match(COMMA):
            arguments.add(parser.expression)
            if arguments.len >= 32:
                logger.error($parser.peek, "Cannot have more than 32 arguments.");
    return Call(
        callee: callee,
        paren: parser.consume(RIGHT_PAREN, "Expect ')' after arguments."),
        arguments: arguments
    );

proc call(parser: Parser): Expr =
    result = parser.primary
    while true:
        if parser.match(LEFT_PAREN):
            result = parser.finishCall(result)
        else:
            break

proc unary(parser: Parser): Expr =
    if parser.match(BANG, MINUS):
        return Unary(
            operator: parser.previous,
            right: parser.unary
        )
    return parser.call

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

proc andOperator(parser: Parser): Expr =
    result = parser.equality
    while parser.match(AND):
        result = Logical(
            left: result,
            operator: parser.previous,
            right: parser.equality
        )

proc orOperator(parser: Parser): Expr =
    result = parser.andOperator
    while parser.match(OR):
        result = Logical(
            left: result,
            operator: parser.previous,
            right: parser.andOperator
        )

proc assignment(parser: Parser): Expr =
    result = parser.orOperator
    if parser.match(EQUAL):
        if result of Variable:
            return Assign(
                name: cast[Variable](result).name,
                value: parser.assignment
            )
        logger.error(
            message = "Invalid assignment target",
            halt = true
        )

proc expression(parser: Parser): Expr =
    return parser.assignment

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

proc declaration(parser: Parser): Stmt # Forward declaration

proc blockStatement(parser: Parser): seq[Stmt] =
    result = @[]
    while not parser.check(RIGHT_BRACE) and not parser.isAtEnd:
        result.add(parser.declaration)
    discard parser.consume(RIGHT_BRACE, "Expect '}' after block")

proc returnStatement(parser: Parser): Stmt =
    var
        keyword = parser.previous
        value: Expr = nil
    if not parser.check(DOT):
        value = parser.expression
    discard parser.consume(DOT, "Expect '.' after return value.")
    return ReturnStmt(keyword: keyword, value: value)

proc whileStatement(parser: Parser): Stmt =
    discard parser.consume(LEFT_PAREN, "Expect '(' after while")
    var condition = parser.expression
    discard parser.consume(RIGHT_PAREN, "Expect ')' after condition")
    return WhileStmt(
        condition: condition,
        body: parser.statement
    )

proc statement(parser: Parser): Stmt =
    if parser.match(IF):
        return parser.ifStatement
    elif parser.match(SHOW):
        return parser.showStatement
    elif parser.match(RETURN):
        return parser.returnStatement
    elif parser.match(WHILE):
        return parser.whileStatement
    elif parser.match(LEFT_BRACE):
        return Block(statements: parser.blockStatement)
    return parser.expressionStatement

proc varDeclaration(parser: Parser): Stmt =
    var name = parser.consume(IDENTIFIER, "Expected a variable name")
    var initializer: Expr = nil
    if parser.match(EQUAL):
        initializer = parser.expression
    discard parser.consume(DOT, "Expected '.' after variable declaration")
    return VarStmt(name: name, initializer: initializer)

proc actionDeclaration(parser: Parser): Stmt =
    var name = parser.consume(IDENTIFIER, "Expect an action name")
    discard parser.consume(LEFT_PAREN, "Expect '(' after action name.")
    var parameters: seq[Token] = @[]
    if not parser.check(RIGHT_PAREN):
        if parameters.len >= 32:
            logger.error(
                message = "Action cannot have more than 32 parameters",
                halt = true
            )
        parameters.add(parser.consume(IDENTIFIER, "Expected a parameter name"))
        while parser.match(COMMA):
            if parameters.len >= 32:
                logger.error(
                    message = "Action cannot have more than 32 parameters",
                    halt = true
                )
            parameters.add(parser.consume(IDENTIFIER, "Expected a parameter name"))
    discard parser.consume(RIGHT_PAREN, "Expect ')' after parameters.")
    discard parser.consume(LEFT_BRACE, "Expect '{' before action body.")
    return ActionStmt(
        name: name,
        parameters: parameters,
        body: parser.blockStatement
    )

proc declaration(parser: Parser): Stmt =
    if parser.match(ACTION):
        return parser.actionDeclaration
    if parser.match(VAR):
        return parser.varDeclaration
    return parser.statement

proc parse*(parser: Parser): seq[Stmt] =
    result = @[]
    while not parser.isAtEnd:
        result.add(parser.declaration)