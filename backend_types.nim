import rules, tables, logs

type
    Value* = ref object of RootObj
        case kind*: LiteralKind
        of lkNumber: numValue*: float
        of lkText: textValue*: string
        of lkTruth: truthValue*: bool
        of lkNone: discard

    BlockValue* = ref object of Value

    Environment* = ref object
        values*: Table[string, Value]
        enclosing*: Environment

    Callable* = ref object of Value
        arity*: int

    ActionCallable* = ref object of Callable
        declaration*: ActionStmt

    Interpreter* = ref object
        environment*, globals*: Environment

    ReturnException* = ref object of Exception
        value*: Value

proc newReturnException*(value: Value): ReturnException =
    return ReturnException(value: value)

method `$`*(value: Value): string {.base.} =
    result = ""
    case value.kind:
        of lkNumber: result &= $value.numValue
        of lkText: result &= value.textValue
        of lkTruth: result &= $value.truthValue
        else: result &= "None"

proc `$`*(environment: Environment): string =
    result = "(parms: ["
    for i in environment.values.keys:
        result &= $i & ", "
    result &= "], parent: "
    if environment.enclosing != nil:
        result &= $environment.enclosing
    else:
        result &= "None"
    result &= ")"

proc `-`*(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkNumber: result.numValue = -value.numValue
        else:
            logger.error(
                message = "The unary '-' operand must be followed by a number",
                halt = true
            )

proc `!`*(value: Value): Value =
    result = Value(kind: value.kind)
    case value.kind:
        of lkTruth: result.truthValue = not value.truthValue
        else:
            logger.error(
                message = "The unary '!' operand must be followed by a truth",
                halt = true
            )

proc `+`*(left, right: Value): float = left.numValue + right.numValue

proc `-`*(left, right: Value): float = left.numValue - right.numValue

proc `*`*(left, right: Value): float = left.numValue * right.numValue

proc `/`*(left, right: Value): float = left.numValue / right.numValue

proc `==`*(left, right: Value): bool =
    if left.kind == lkNumber:
        return left.numValue == right.numValue
    elif left.kind == lkTruth:
        return left.truthValue == right.truthValue
    logger.error(
        message = "The equal == operation requires either truths or numbers on both sides",
        halt = true
    )

proc `!=`*(left, right: Value): bool =
    if left.kind == lkNumber:
        return left.numValue != right.numValue
    elif left.kind == lkTruth:
        return left.truthValue != right.truthValue
    logger.error(
        message = "The not equal != operation requires either truths or numbers on both sides",
        halt = true
    )

proc `>`*(left, right: Value): bool = left.numValue > right.numValue

proc `>=`*(left, right: Value): bool = left.numValue <= right.numValue

proc `<`*(left, right: Value): bool = left.numValue < right.numValue

proc `<=`*(left, right: Value): bool = left.numValue <= right.numValue