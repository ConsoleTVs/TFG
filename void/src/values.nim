type
    Value* = ref object of RootObj

    NumberValue* = ref object of Value
        value*: float

    BooleanValue* = ref object of Value
        value*: bool

    TextValue* = ref object of Value
        value*: string

method `$`*(value: Value): string {.base.} = "Unknown"
method `$`*(value: NumberValue): string = $value.value
method `$`*(value: BooleanValue): string = $value.value
method `$`*(value: TextValue): string = $value.value
