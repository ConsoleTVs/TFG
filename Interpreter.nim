import rules, tokens, logs, tables, backend_types, environment

# Forward declaration
proc evaluateBlock*(interpreter: Interpreter, statements: seq[Stmt])

# Cyclic import
import callable

method evaluate*(interpreter: Interpreter, expression: Expr): Value {.base.} = Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, expression: Literal): Value =
    result = Value(kind: expression.kind)
    case expression.kind:
        of lkNumber: result.numValue = expression.numValue
        of lkText: result.textValue = expression.textValue
        of lkTruth: result.truthValue = expression.truthValue
        else: discard

method evaluate*(interpreter: Interpreter, expression: Unary): Value =
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

method evaluate*(interpreter: Interpreter, expression: Logical): Value =
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

method evaluate*(interpreter: Interpreter, expression: Binary): Value =
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

method evaluate*(interpreter: Interpreter, expression: Grouping): Value =
    return interpreter.evaluate(expression.expression)

method evaluate*(interpreter: Interpreter, expression: Variable): Value =
    return interpreter.environment.get(expression.name)

method evaluate*(interpreter: Interpreter, expression: Assign): Value =
    result = interpreter.evaluate(expression.value)
    interpreter.environment.assign(expression.name.lexeme, result)

method evaluate*(interpreter: Interpreter, expression: Call): Value =
    var
        callee = interpreter.evaluate(expression.callee)
        arguments: seq[Value] = @[]
    for arg in expression.arguments:
        arguments.add(interpreter.evaluate(arg))

    if not (callee of Callable):
        logger.error(
            message = "Can only call functions and classes.",
            halt = true
        )

    var function: Callable = cast[Callable](callee)
    if arguments.len != function.arity:
        logger.error(
            message = "Expected " & $function.arity & " arguments, but got " & $arguments.len,
            halt = true
        )
    return function.call(interpreter, arguments)

method evaluate*(interpreter: Interpreter, statement: Stmt): Value {.base.} = Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, statement: ShowStmt): Value =
    echo $interpreter.evaluate(statement.expression)
    return Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, statement: ExprStmt): Value =
    logger.info("Evaluating", "Expression statement", debug = true)
    discard interpreter.evaluate(statement.expression)
    logger.info("=> OK", "Expression statement", debug = true)
    return Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, statement: VarStmt): Value =
        logger.info("Evaluating " & statement.name.lexeme, "Var", debug = true)
        var value = Value(kind: lkNone)
        if statement.initializer != nil:
            value = interpreter.evaluate(statement.initializer)
        interpreter.environment.define(statement.name.lexeme, value)
        logger.info("=> " & $value, "Var", debug = true)
        return Value(kind: lkNone)

#proc isBlockValue(v: Value): bool = v of BlockValue

proc evaluateBlock*(interpreter: Interpreter, statements: seq[Stmt]) =
    logger.info("Evaluating", "Block", debug = true)
    #interpreter.environment = Environment(values: initTable[string, Value](), enclosing: environment)
    for s in statements:
        discard interpreter.evaluate(s)
    #interpreter.environment = environment

method evaluate*(interpreter: Interpreter, statement: Block): Value =
    var previous: Environment = interpreter.environment
    interpreter.environment = Environment(values: initTable[string, Value](), enclosing: previous)
    interpreter.evaluateBlock(statement.statements)
    interpreter.environment = previous

method evaluate*(interpreter: Interpreter, statement: IfStmt): Value =
    logger.info("Evaluating", "If", debug = true)
    var condition = interpreter.evaluate(statement.condition)
    if condition.boolValue:
        discard interpreter.evaluate(statement.thenBranch)
    elif statement.elseBranch != nil:
        discard interpreter.evaluate(statement.elseBranch)
    logger.info("=> OK", "If", debug = true)
    return Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, statement: WhileStmt): Value =
    logger.info("Evaluating", "While", debug = true)
    while boolValue(interpreter.evaluate(statement.condition)):
        discard interpreter.evaluate(statement.body)
    logger.info("=> OK", "While", debug = true)
    return Value(kind: lkNone)

method evaluate*(interpreter: Interpreter, statement: ActionStmt): Value =
    logger.info("Declaring " & statement.name.lexeme, "Action", debug = true)
    interpreter.environment.define(statement.name.lexeme, ActionCallable(
        declaration: statement,
        arity: statement.parameters.len
    ))
    logger.info("=> OK", "Action", debug = true)
    return Value(kind: lkNone)

proc blockValueFromValue(value: Value): BlockValue =
    case value.kind:
        of lkNone: return BlockValue(kind: lkNone)
        of lkNumber: return BlockValue(kind: lkNumber, numValue: value.numValue)
        of lkText: return BlockValue(kind: lkText, textValue: value.textValue)
        of lkTruth: return BlockValue(kind: lkTruth, truthValue: value.truthValue)

method evaluate*(interpreter: Interpreter, statement: ReturnStmt): Value =
    logger.info("Evaluating", "Return", debug = true)
    result = Value(kind: lkNone)
    if statement.value != nil:
        result = interpreter.evaluate(statement.value)
    logger.info("=> " & $result, "Return", debug = true)
    raise newReturnException(result)

proc interpret*(interpreter: Interpreter, statements: seq[Stmt]): void =
    for statement in statements:
        discard interpreter.evaluate(statement)
    try:
        discard
    except:
        logger.error(
            message = "Can't evaluate the statements",
            halt = true
        )