import tokens, rules, strutils

type
    Parser* = ref tuple
        tokens: seq[Token]
        current: int

#[
    PARSER HELPERS
]#

proc newParser*(tokens: seq[Token]): Parser =
    new result
    result.tokens = tokens
    result.current = 0

proc previous(parser: Parser): Token = parser.tokens[parser.current - 1]

proc peek(parser: Parser, offset: int = 0): Token = parser.tokens[parser.current + offset]

proc isAtEnd(parser: Parser): bool = parser.peek.kind == TOK_EOF

proc advance(parser: Parser): Token =
    if not parser.isAtEnd:
        parser.current.inc
    return parser.previous

proc check(parser: Parser, token: Kinds): bool =
    if parser.isAtEnd:
        return false
    return parser.peek.kind == token

proc match(parser: Parser, tokens: varargs[Kinds]): bool =
    for token in tokens:
        if parser.check(token):
            discard parser.advance
            return true
    return false

proc consume(parser: Parser, kind: Kinds, message: string): Token =
    if parser.check(kind):
        return parser.advance
    echo message
    quit()

#[
    GRAMMAR RULES
]#
proc statement(parser: Parser): Statement
proc expression(parser: Parser): Expression
proc blockStatement(parser: Parser): Block

proc isFunction(parser: Parser): bool =
    ## This function is used to determine if a group is a function
    var
        current = 0
        skip = 0
    while skip == 0 and parser.peek(current).kind != TOK_RIGHT_PAREN:
        if parser.peek(current).kind == TOK_EOF:
            echo "Unterminated grouping or function. Did you close the parenthesis?"
            quit()
        elif parser.peek(current).kind == TOK_LEFT_PAREN:
            skip.inc
        elif parser.peek(current).kind == TOK_RIGHT_PAREN:
            skip.dec
        current.inc
    if parser.peek(current + 1).kind == TOK_EOF:
        return false
    return parser.peek(current + 1).kind == TOK_ARROW or parser.peek(current + 1).kind == TOK_SIMPLE_ARROW

proc function(parser: Parser): Expression =
    var arguments: seq[Token] = @[]
    if not parser.check(TOK_RIGHT_PAREN):
        if arguments.len >= 32:
            echo "Function cannot have more than 32 arguments"
            quit()
        arguments.add(parser.consume(TOK_IDENTIFIER, "Expected a parameter name"))
        while parser.match(TOK_COMMA):
            if arguments.len >= 32:
                echo "Action cannot have more than 32 arguments"
                quit()
            arguments.add(parser.consume(TOK_IDENTIFIER, "Expected a parameter name"))
    discard parser.consume(TOK_RIGHT_PAREN, "Expected ')' after arguments.")
    case parser.peek.kind:
        of TOK_SIMPLE_ARROW:
            discard parser.advance
            return SimpleFunction(
                arguments: arguments,
                expression: parser.expression
            )
        of TOK_ARROW:
            discard parser.advance
            discard parser.consume(TOK_LEFT_BRACE, "Expected '{' after arrow '=>' function.")
            return Function(
                arguments: arguments,
                body: parser.blockStatement
            )
        else:
            echo "Expected arrow '=>' or simple arrow '->' after function arguments."
            quit()

proc primary(parser: Parser): Expression =
    ##[
        primary  "true" | "false" | "none" | "this"
            | NUMBER | STRING | IDENTIFIER | "(" expression ")"
            | "super" "." IDENTIFIER
            ;
    ]##
    if parser.match(TOK_FALSE):
        return Boolean(value: false)
    if parser.match(TOK_TRUE):
        return Boolean(value: true)
    if parser.match(TOK_NONE):
        return None()
    if parser.match(TOK_NUMBER):
        return Number(value: parser.previous.value.parseFloat)
    if parser.match(TOK_STRING):
        return String(value: parser.previous.value)
    if parser.match(TOK_IDENTIFIER):
        return Variable(name: parser.previous)
    if parser.match(TOK_NONE):
        return None()
    if parser.match(TOK_LEFT_PAREN):
        if parser.isFunction:
            return parser.function
        else:
            var expression = parser.expression
            discard parser.consume(TOK_RIGHT_PAREN, "Expected ')' after the expression")
            return Group(expression: expression)

    echo "Expected an expression. Failed with the lexeme " & parser.peek.lexeme & " at line " & $parser.peek.line
    quit()

proc finishCall(parser: Parser, callee: Expression): Expression =
    var arguments: seq[Expression] = @[]
    if not parser.check(TOK_RIGHT_PAREN):
        arguments.add(parser.expression)
        if arguments.len >= 32:
            echo $parser.peek, "Cannot have more than 32 acall rguments."
            quit()
        while parser.match(TOK_COMMA):
            arguments.add(parser.expression)
            if arguments.len >= 32:
                echo $parser.peek, "Cannot have more than 32 call arguments."
                quit()
    return Call(
        callee: callee,
        paren: parser.consume(TOK_RIGHT_PAREN, "Expect ')' after call arguments."),
        arguments: arguments
    );

proc call(parser: Parser): Expression =
    ##[
        call: primary ( "(" arguments? ")" | "." IDENTIFIER )* ;
            | call
            ;
    ]##
    result = parser.primary
    while true:
        if parser.match(TOK_LEFT_PAREN):
            result = parser.finishCall(result)
        else:
            break

proc unary(parser: Parser): Expression =
    ##[
        unary: ("!" | "-") unary
            | call
            ;
    ]##
    if parser.match(TOK_BANG, TOK_MINUS):
        return Unary(
            operator: parser.previous,
            right: parser.unary
        )
    return parser.call

proc mulDiv(parser: Parser): Expression =
    ##[
        mulDiv: unary (("/" | "*") unary)*
            ;
    ]##
    result = parser.unary
    while parser.match(TOK_SLASH, TOK_STAR):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.unary
        )

proc addition(parser: Parser): Expression =
    ##[
        addition: mulDiv (("-" | "+") mulDiv)*
            ;
    ]##
    result = parser.mulDiv
    while parser.match(TOK_MINUS, TOK_PLUS):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.mulDiv
        )

proc comparison(parser: Parser): Expression =
    ##[
        comparison: addition ((">" | ">=" | "<" | "<=") addition)*
            ;
    ]##
    result = parser.addition
    while parser.match(TOK_GREATER, TOK_GREATER_EQUAL, TOK_LESS, TOK_LESS_EQUAL):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.addition
        )

proc equality(parser: Parser): Expression =
    ##[
        equality: comparison (("!=" | "==") comparison)*
            ;
    ]##
    result = parser.comparison
    while parser.match(TOK_BANG_EQUAL, TOK_EQUAL_EQUAL):
        result = Binary(
            left: result,
            operator: parser.previous,
            right: parser.comparison
        )

proc andOperator(parser: Parser): Expression =
    ##[
        andOperator: equality ("and" equality)*
            ;
    ]##
    result = parser.equality
    while parser.match(TOK_AND):
        result = Logical(
            left: result,
            operator: parser.previous,
            right: parser.equality
        )

proc orOperator(parser: Parser): Expression =
    ##[
        orOperator: andOperator ("or" andOperator)*
            ;
    ]##
    result = parser.andOperator
    while parser.match(TOK_OR):
        result = Logical(
            left: result,
            operator: parser.previous,
            right: parser.andOperator
        )

proc assignment(parser: Parser): Expression =
    ##[
        assignment: identifier "=" expression
            | orOperator
            ;
    ]##
    result = parser.orOperator
    if parser.match(TOK_EQUAL):
        if result of Variable:
            return Assign(
                name: cast[Variable](result).name,
                value: parser.assignment
            )
        echo "Invalid assignment target"
        quit()


proc expression(parser: Parser): Expression =
    ##[
        expression: assignment
            ;
    ]##
    return parser.assignment

proc expressionStatement(parser: Parser): Statement =
    ##[
        expressionStatement: expression ";"
            ;
    ]##
    var expression = parser.expression
    discard parser.consume(TOK_SEMICOLON, "Expected ';' after statement")
    return ExpressionStatement(expression: expression)

proc blockStatement(parser: Parser): Block =
    ##[
        blockStatement: "{" statements "}"
    ]##
    var statements: seq[Statement] = @[]
    while not parser.check(TOK_RIGHT_BRACE) and not parser.isAtEnd:
        statements.add(parser.statement)
    discard parser.consume(TOK_RIGHT_BRACE, "Unterminated block statement")
    result = Block(body: statements)

proc ifStatement(parser: Parser): Statement =
    ##[
        ifStatement: "if" expression "->" expression
            | "if" expression "=>" blockStatement ("else" -> expression)?
            | "if" expression "=>" blockStatement ("else" => blockStatement)?
            ;
    ]##
    var condition = parser.expression
    if parser.match(TOK_SIMPLE_ARROW):
        return SimpleIf(condition: condition, expression: parser.expression)
    elif parser.match(TOK_ARROW):
        var res = If(condition: condition)
        discard parser.consume(TOK_LEFT_BRACE, "Expected a block after a '=>' function")
        res.thenBranch = parser.blockStatement
        res.elseBranch = nil
        if parser.match(TOK_ELSE):
            discard parser.consume(TOK_ARROW, "Expected an arrow '=>' after an 'else'.")
            discard parser.consume(TOK_LEFT_BRACE, "Expected a block after the function 'else =>' statement")
            res.elseBranch = parser.blockStatement
        return res
    echo "Expected an arrow '=>' or a simple arrow '->' after an 'if'."
    quit()

proc whileStatement(parser: Parser): Statement =
    var condition = parser.expression
    return While(
        condition: condition,
        body: parser.blockStatement
    )

proc printStatement(parser: Parser): Statement =
    var expression = parser.expression
    discard parser.consume(TOK_SEMICOLON, "Expect ';' after statement")
    return Print(expression: expression)

proc returnStatement(parser: Parser): Statement =
    var
        keyword = parser.previous
        value: Expression = nil
    if not parser.check(TOK_SEMICOLON):
        value = parser.expression
    discard parser.consume(TOK_SEMICOLON, "Expect ';' after return value.")
    return Return(keyword: keyword, value: value)

proc statement(parser: Parser): Statement =
    ##[
        statement: ifStatement
            |   printStatement
            |   returnStatement
            |   whileStatement
            |   blockStatement
            |   expressionStatement
            ;
    ]##
    if parser.match(TOK_IF):
        return parser.ifStatement
    elif parser.match(TOK_PRINT):
        return parser.printStatement
    elif parser.match(TOK_RETURN):
        return parser.returnStatement
    elif parser.match(TOK_WHILE):
        return parser.whileStatement
    elif parser.match(TOK_LEFT_BRACE):
        return parser.blockStatement
    return parser.expressionStatement


proc parse*(parser: Parser): seq[Statement] =
    result = @[]
    while not parser.isAtEnd:
        ##[
            program: statements
                ;
        ]##
        result.add(parser.statement)