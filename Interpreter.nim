import rules, tokens, console

type
    Interpreter* = ref object

    Value = ref object
        case kind*: LiteralKind
        of lkNumber: numValue*: float
        of lkText: textValue*: string
        of lkBoolean: boolValue*: bool
        of lkNone: discard

proc `-`(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkNumber: result.numValue = -value.numValue
        else:
            error("The unary '-' operand must be followed by a number")
            quit()

proc `!`(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkBoolean: result.boolValue = not value.boolValue
        else: discard

template `+`(left, right: Value): float = left.numValue + right.numValue

template `-`(left, right: Value): float = left.numValue - right.numValue

template `*`(left, right: Value): float = left.numValue * right.numValue

template `/`(left, right: Value): float = left.numValue / right.numValue

template `==`(left, right: Value): bool = left.numValue == right.numValue

template `!=`(left, right: Value): bool = left.numValue != right.numValue

template `>`(left, right: Value): bool = left.numValue > right.numValue

template `>=`(left, right: Value): bool = left.numValue <= right.numValue

template `<`(left, right: Value): bool = left.numValue < right.numValue

template `<=`(left, right: Value): bool = left.numValue <= right.numValue

method evaluate(interpreter: Interpreter, expression: Expr): Value {.base.} = Value(kind: lkNone)

method evaluate(interpreter: Interpreter, expression: Literal): Value =
    result = Value(kind: expression.kind)
    case expression.kind:
        of lkNumber: result.numValue = expression.numValue
        of lkText: result.textValue = expression.textValue
        of lkBoolean: result.boolValue = expression.boolValue
        else: discard

method evaluate(interpreter: Interpreter, expression: Unary): Value =
    case expression.operator.kind:
        of MINUS: return -(interpreter.evaluate(expression.right))
        of BANG: return !(interpreter.evaluate(expression.right))
        else: return Value()

method evaluate(interpreter: Interpreter, expression: Binary): Value =
    let
        left = interpreter.evaluate(expression.left)
        right = interpreter.evaluate(expression.right)
    case expression.operator.kind:
        of PLUS: return Value(kind: lkNumber, numValue: left + right)
        of MINUS: return Value(kind: lkNumber, numValue: left - right)
        of STAR: return Value(kind: lkNumber, numValue: left * right)
        of SLASH: return Value(kind: lkNumber, numValue: left / right)
        of EQUAL_EQUAL: return Value(kind: lkBoolean, boolValue: left == right)
        of BANG_EQUAL: return Value(kind: lkBoolean, boolValue: left != right)
        of LESS: return Value(kind: lkBoolean, boolValue: left < right)
        of LESS_EQUAL: return Value(kind: lkBoolean, boolValue: left <= right)
        of GREATER: return Value(kind: lkBoolean, boolValue: left > right)
        of GREATER_EQUAL: return Value(kind: lkBoolean, boolValue: left >= right)
        else: discard

method evaluate(interpreter: Interpreter, expression: Grouping): Value =
    return interpreter.evaluate(expression.expression)

proc `$`*(value: Value): string =
    case value.kind:
        of lkNumber: return $value.numValue
        of lkText: return value.textValue
        of lkBoolean: return $value.boolValue
        else: return ""

proc interpret*(interpreter: Interpreter, expression: Expr): Value =
    result = interpreter.evaluate(expression)
    try:
        result = interpreter.evaluate(expression)
    except:
        error("The expression result can't be interpreted")
        quit()