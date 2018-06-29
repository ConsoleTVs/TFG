import rules
type
    Value* = ref object of RootObj ## Base value definition

    NumberValue* = ref object of Value ## Value to represent numbers
        value*: float

    BooleanValue* = ref object of Value ## Value to represent booleans
        value*: bool

    StringValue* = ref object of Value ## Value to represent strings
        value*: string

    FunctionValue* = ref object of Value ## Value to represent functions
        arguments*, scope*: int # Number of arguments, Frame pointer
        label*: string # Label of the function

    NoneValue* = ref object of Value ## Value to represent no value.

method `$`*(value: Value): string {.base.} = "Unknown"
method `$`*(value: NumberValue): string = $value.value
method `$`*(value: BooleanValue): string = $value.value
method `$`*(value: StringValue): string = value.value
method `$`*(value: FunctionValue): string = "<function " & value.label & ">"
method `$`*(value: NoneValue): string = "none"