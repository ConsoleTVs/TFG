import interpreter, times, rules

type
    Callable* = ref object of Value
        arity*: int

    Time* = ref object of Callable
    CpuTime* = ref object of Callable

method call*(callable: Callable, interpreter: Interpreter, arguments: seq[Value]): Value {.base.} = Value()

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