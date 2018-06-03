import tables, interpreter, tokens, logs

type
    Enviroment* = ref object
        values*: Table[string, Value]
        enclosing*: Enviroment

proc define*(enviroment: Enviroment, name: string, value: Value) =
    enviroment.values[name] = value

proc assign*(enviroment: Enviroment, name: string, value: Value) =
    if enviroment.values.hasKey(name):
        enviroment.values[name] = value
        return
    elif enviroment.enclosing != nil:
        enviroment.enclosing.assign(name, value)
        return
    logger.error(
        message = "Undefined variable '" & name & "'",
        halt = true
    )

proc get*(enviroment: Enviroment, name: Token): Value =
    if enviroment.values.hasKey(name.lexeme):
        return enviroment.values[name.lexeme]
    elif enviroment.enclosing != nil:
        return enviroment.enclosing.get(name)
    logger.error(
        message = "Undefined variable '" & name.lexeme & "'",
        halt = true
    )