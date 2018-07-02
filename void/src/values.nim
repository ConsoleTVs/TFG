import rules

type Value* = ref object of RootObj ## Base value definition

import frame

type
    NumberValue* = ref object of Value ## Value to represent numbers
        value*: float

    BooleanValue* = ref object of Value ## Value to represent booleans
        value*: bool

    ListValue* = ref object of Value ## Value to represent lists
        values*: seq[Value]

    StringValue* = ref object of Value ## Value to represent strings
        value*: string

    FunctionValue* = ref object of Value ## Value to represent functions
        arguments*: int # Number of arguments
        frame*: Frame
        label*: string # Label of the function

    NoneValue* = ref object of Value ## Value to represent no value.

method `$`*(value: Value): string {.base.} = "Unknown"
method `$`*(value: NumberValue): string = $value.value
method `$`*(value: BooleanValue): string = $value.value
method `$`*(value: StringValue): string = value.value
method `$`*(value: ListValue): string =
    result = "["
    for i,e in value.values:
        result &= $e
        if i != value.values.len - 1:
            result &= ", "
    result &= "]"
method `$`*(value: FunctionValue): string = "<function " & value.label & ">"
method `$`*(value: NoneValue): string = "none"