import tables, interpreter, tokens, logs, backend_types

proc define*(environment: Environment, name: string, value: Value) =
    environment.values[name] = value

proc assign*(environment: Environment, name: string, value: Value) =
    if environment.values.hasKey(name):
        environment.values[name] = value
        return
    elif environment.enclosing != nil:
        environment.enclosing.assign(name, value)
        return
    logger.error(
        message = "Undefined variable '" & name & "'",
        halt = true
    )

proc get*(environment: Environment, name: Token): Value =
    if environment.values.hasKey(name.lexeme):
        return environment.values[name.lexeme]
    elif environment.enclosing != nil:
        return environment.enclosing.get(name)
    logger.error(
        message = "Undefined variable '" & name.lexeme & "'",
        halt = true
    )