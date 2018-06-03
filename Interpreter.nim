import rules, tokens, logs, typetraits, tables

type
    Value* = ref object
        case kind*: LiteralKind
        of lkNumber: numValue*: float
        of lkText: textValue*: string
        of lkTruth: truthValue*: bool
        of lkNone: discard

proc `$`*(value: Value): string =
    case value.kind:
        of lkNumber: return $value.numValue
        of lkText: return value.textValue
        of lkTruth: return $value.truthValue
        else: return ""

# To solve the cyclic import, we import it here
import enviroment

type
    Interpreter* = ref object
        enviroment*: Enviroment

proc `-`(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkNumber: result.numValue = -value.numValue
        else:
            logger.error(
                message = "The unary '-' operand must be followed by a number",
                halt = true
            )

proc `!`(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkTruth: result.truthValue = not value.truthValue
        else:
            logger.error(
                message = "The unary '!' operand must be followed by a truth",
                halt = true
            )

proc `+`(left, right: Value): float = left.numValue + right.numValue

proc `-`(left, right: Value): float = left.numValue - right.numValue

proc `*`(left, right: Value): float = left.numValue * right.numValue

proc `/`(left, right: Value): float = left.numValue / right.numValue

proc `==`(left, right: Value): bool =
    if left.kind == lkNumber:
        return left.numValue == right.numValue
    elif left.kind == lkTruth:
        return left.truthValue == right.truthValue
    logger.error(
        message = "The equal == operation requires either truths or numbers on both sides",
        halt = true
    )

proc `!=`(left, right: Value): bool =
    if left.kind == lkNumber:
        return left.numValue != right.numValue
    elif left.kind == lkTruth:
        return left.truthValue != right.truthValue
    logger.error(
        message = "The not equal != operation requires either truths or numbers on both sides",
        halt = true
    )

proc `>`(left, right: Value): bool = left.numValue > right.numValue

proc `>=`(left, right: Value): bool = left.numValue <= right.numValue

proc `<`(left, right: Value): bool = left.numValue < right.numValue

proc `<=`(left, right: Value): bool = left.numValue <= right.numValue

method evaluate(interpreter: Interpreter, expression: Expr): Value {.base.} = Value(kind: lkNone)

method evaluate(interpreter: Interpreter, expression: Literal): Value =
    result = Value(kind: expression.kind)
    case expression.kind:
        of lkNumber: result.numValue = expression.numValue
        of lkText: result.textValue = expression.textValue
        of lkTruth: result.truthValue = expression.truthValue
        else: discard

method evaluate(interpreter: Interpreter, expression: Unary): Value =
    case expression.operator.kind:
        of MINUS: return -interpreter.evaluate(expression.right)
        of BANG: return !interpreter.evaluate(expression.right)
        else: return Value()

proc boolValue(value: Value): bool =
    if value.kind == lkTruth:
        return value.truthValue
    elif value.kind == lkText and value.textValue != "":
        return true
    return false

method evaluate(interpreter: Interpreter, expression: Logical): Value =
    var left = interpreter.evaluate(expression.left)
    if expression.operator.kind == OR:
        if left.boolValue:
            return left
    else:
        if not left.boolValue:
            return left
    return interpreter.evaluate(expression.right)

proc matchValues(expression: Binary, left, right: Value) =
    if left.kind != right.kind:
        logger.error(
            message = "The left and right expressions for the " & expression.operator.lexeme & " operation at line " & $expression.operator.line & " are not the same type",
            halt = true
        )

proc matchNumericValues(expression: Binary, left, right: Value) =
    if left.kind != right.kind or left.kind != lkNumber :
        logger.error(
            message = "The left and right expressions for the " & expression.operator.lexeme & " operation at line " & $expression.operator.line & " are not numbers",
            halt = true
        )

method evaluate(interpreter: Interpreter, expression: Binary): Value =
    let
        left = interpreter.evaluate(expression.left)
        right = interpreter.evaluate(expression.right)
    case expression.operator.kind:
        of PLUS:
            expression.matchNumericValues(left, right)
            return Value(kind: lkNumber, numValue: left + right)
        of MINUS:
            expression.matchNumericValues(left, right)
            return Value(kind: lkNumber, numValue: left - right)
        of STAR:
            expression.matchNumericValues(left, right)
            return Value(kind: lkNumber, numValue: left * right)
        of SLASH:
            expression.matchNumericValues(left, right)
            return Value(kind: lkNumber, numValue: left / right)
        of EQUAL_EQUAL:
            expression.matchValues(left, right)
            return Value(kind: lkTruth, truthValue: left == right)
        of BANG_EQUAL:
            expression.matchValues(left, right)
            return Value(kind: lkTruth, truthValue: left != right)
        of LESS:
            expression.matchNumericValues(left, right)
            return Value(kind: lkTruth, truthValue: left < right)
        of LESS_EQUAL:
            expression.matchNumericValues(left, right)
            return Value(kind: lkTruth, truthValue: left <= right)
        of GREATER:
            expression.matchNumericValues(left, right)
            return Value(kind: lkTruth, truthValue: left > right)
        of GREATER_EQUAL:
            expression.matchNumericValues(left, right)
            return Value(kind: lkTruth, truthValue: left >= right)
        else: discard

method evaluate(interpreter: Interpreter, expression: Grouping): Value =
    return interpreter.evaluate(expression.expression)

method evaluate(interpreter: Interpreter, expression: Variable): Value =
    return interpreter.enviroment.get(expression.name)

method evaluate(interpreter: Interpreter, expression: Assign): Value =
    result = interpreter.evaluate(expression.value)
    interpreter.enviroment.assign(expression.name.lexeme, result)

method evaluate(interpreter: Interpreter, statement: Stmt): Value {.base.} = Value(kind: lkNone)

method evaluate(interpreter: Interpreter, statement: ShowStmt): Value =
    echo $interpreter.evaluate(statement.expression)
    return Value(kind: lkNone)

method evaluate(interpreter: Interpreter, statement: ExprStmt): Value =
    discard interpreter.evaluate(statement.expression)
    return Value(kind: lkNone)

method evaluate(interpreter: Interpreter, statement: VarStmt): Value =
        var value = Value(kind: lkNone)
        if statement.initializer != nil:
            value = interpreter.evaluate(statement.initializer)
        interpreter.enviroment.define(statement.name.lexeme, value)
        return Value(kind: lkNone)

method evaluate(interpreter: Interpreter, statement: Block): Value =
    result = Value(kind: lkNone)
    var
        previous = interpreter.enviroment
    interpreter.enviroment = Enviroment(values: initTable[string, Value](), enclosing: previous)
    for s in statement.statements:
        discard interpreter.evaluate(s)
    interpreter.enviroment = previous

method evaluate(interpreter: Interpreter, statement: IfStmt): Value =
    var condition = interpreter.evaluate(statement.condition)
    if condition.boolValue:
        discard interpreter.evaluate(statement.thenBranch)
    elif statement.elseBranch != nil:
        discard interpreter.evaluate(statement.elseBranch)
    return Value(kind: lkNone)

method evaluate(interpreter: Interpreter, statement: WhileStmt): Value =
    while boolValue(interpreter.evaluate(statement.condition)):
        discard interpreter.evaluate(statement.body)
    return Value(kind: lkNone)

proc interpret*(interpreter: Interpreter, statements: seq[Stmt]): void =
    try:
        for statement in statements:
            discard interpreter.evaluate(statement)
    except:
        logger.error(
            message = "Can't evaluate the statements",
            halt = true
        )