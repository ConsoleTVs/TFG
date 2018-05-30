import tables, interpreter, tokens, console

type
    Enviroment* = ref object
        values*: Table[string, Value]

proc define*(enviroment: Enviroment, name: string, value: Value) =
    enviroment.values[name] = value

proc get*(enviroment: Enviroment, name: Token): Value =
    if not enviroment.values.hasKey(name.lexeme):
        error("Undefined variable '" & $name.lexeme & "'")
        quit()
    return enviroment.values[name.lexeme]