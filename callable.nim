import times, rules, environment, backend_types, tables, os, logs, strutils, math

method call*(callable: Callable, interpreter: Interpreter, arguments: seq[Value]): Value {.base.}

import interpreter

method call*(callable: Callable, interpreter: Interpreter, arguments: seq[Value]): Value {.base.} = Value()

method call*(callable: ActionCallable, interpreter: Interpreter, arguments: seq[Value]): Value =
    var previous: Environment = interpreter.environment
    interpreter.environment = Environment(values: initTable[string, Value](), enclosing: previous)
    for i in 0..callable.declaration.parameters.len - 1:
        interpreter.environment.define(callable.declaration.parameters[i].lexeme, arguments[i])
    try:
        interpreter.evaluateBlock(callable.declaration.body)
    except ReturnException:
        interpreter.environment = previous
        return ReturnException(getCurrentException()).value
    interpreter.environment = previous
    return Value(kind: lkNone)

#[
    System function
]#
type
    Time* = ref object of Callable
    CpuTime* = ref object of Callable
    Sleep* = ref object of Callable

method call*(callable: Time, interpreter: Interpreter, arguments: seq[Value]): Value =
    return Value(
        kind: lkNumber,
        numValue: epochTime()
    )

method call*(callable: CpuTime, interpreter: Interpreter, arguments: seq[Value]): Value =
    return Value(
        kind: lkNumber,
        numValue: cpuTime()
    )

method call*(callable: Sleep, interpreter: Interpreter, arguments: seq[Value]): Value =
    if arguments[0].kind != lkNumber:
        logger.error(
            message = "Sleep expects parameter 1 to be a number",
            halt = true
        )
    var ar: string = $round(arguments[0].numValue)
    trimZeros(ar)
    sleep(parseInt(ar))
    return Value(
        kind: lkNone
    )