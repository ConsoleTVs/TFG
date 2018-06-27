type
    Value* = ref object of RootObj

    NumberValue* = ref object of Value
        value*: float

    BooleanValue* = ref object of Value
        value*: bool

    StringValue* = ref object of Value
        value*: string

    NoneValue* = ref object of Value

method `$`*(value: Value): string {.base.} = "Unknown"
method `$`*(value: NumberValue): string = $value.value
method `$`*(value: BooleanValue): string = $value.value
method `$`*(value: StringValue): string = value.value
