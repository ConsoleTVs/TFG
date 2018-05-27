import rules

type
    Interpreter* = object

proc evaluate(self: Interpreter, expr: Expr): any = discard

proc evaluate(interpreter: Interpreter, literal: Literal): any =
    case literal.kind
    of lkNumber:
        return literal.numValue
    of lkText:
        return literal.textValue
    of lkBoolean:
        return literal.boolValue
    of lkNone:
        return nil

proc evaluate(interpreter: Interpreter, grouping: Grouping): any =
    return interpreter.evaluate(grouping.expression)