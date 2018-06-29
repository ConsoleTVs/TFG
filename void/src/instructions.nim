import values, strutils, math

##[
    This module implements all the possible instructions and the
    common operations done on them that the void programming language
    currently supports.
]##

type
    InstructionKind* = enum
        ##[
            This instructions define all the possible operations
            of the void bytecode VM. The string they are equal to
            is not the value, it's a string representation of
            the enum, same as definint each `$` operator.
        ]##
        HALTINST = "HALT" # Halt
        PUSHINST = "PUSH" # Push
        POPINST = "POP" # Pop
        NOPINST = "NOP" # No operation
        LABELINST = "" # Label
        PRINTINT = "PRINT" # Print
        VALUEINST = "" # Value representation
        NEGINST = "NEG" # Negation (numeric)
        NOTINST = "NOT" # Negation (boolean)
        ORINST = "OR" # Logic or
        ANDINST = "AND" # Logic and
        ADDINST = "ADD" # Addition
        SUBINST = "SUB" # Substraction
        MULINST = "MUL" # Multiplication
        DIVINST = "DIV" # Division
        MODINST = "MOD" # Modulo
        EQINST = "EQ" # Equal
        NEQINST = "NEQ" # Not equal
        GTINST = "GT" # Greater than
        GTEINST = "GTE" # Greater or equal than
        LTINST = "LT" # Lower than
        LTEINST = "LTE" # Lower or equal than
        JUMPINST = "JUMP" # Jump
        RJUMPINST = "RJUMP" # Relative Jump
        BRANCHTINST = "BRANCHT" # Branch if true
        BRANCHFINST = "BRANCHF" # Branch if false
        STOREINST = "STORE" # Store variable
        LOADINST = "LOAD" # Load variable
        FUNINST = "FUN" # Function definition
        CALLINST = "CALL" # Call instruction
        RETURNINST = "RETURN" # Return instruction
        PUSHPCOFFSETINST = "PUSHPCOFFSET" # Push the current program counter + offset
        PUSHSCOPEINST = "PUSHSCOPE" # Push the current scope
        POPARGUMENTSINST = "POPARGUMENTS" # Instruction to pop function arguments

    Instruction* = ref tuple
        ##[
            Representation of the instruction consists of a kind
            of instruction and a value that might be associated with it.
        ]##
        kind: InstructionKind # The instruction kind
        value: Value # The value of the instruction if any

proc newInstruction*(kind: InstructionKind, value: Value = nil): Instruction =
    new result
    result.kind = kind
    result.value = value

##[
    Instruction functions that are used during the VM running state.
    These functions will be called when needed by passing the value arguments to it.
]##

proc abort(msg: string) = echo msg; quit()

method negInst*(a: Value): Value {.base.} = "Invalid value in neg operation".abort
method negInst*(a: NumberValue): Value = NumberValue(value: -a.value)
method negInst*(a: BooleanValue): Value = NumberValue(value: -float(a.value))

method notInst*(a: Value): Value {.base.} = "Invalid value in not operation".abort
method notInst*(a: NumberValue): Value = BooleanValue(value: not bool(a.value))
method notInst*(a: BooleanValue): Value = BooleanValue(value: not a.value)

method orInst*(a, b: Value): Value {.base.} = "Invalid value in or operation".abort
method orInst*(a, b: NumberValue): Value = BooleanValue(value: bool(b.value) or bool(a.value))
method orInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value or a.value)

method andInst*(a, b: Value): Value {.base.} = "Invalid value in or operation".abort
method andInst*(a, b: NumberValue): Value = BooleanValue(value: bool(b.value) and bool(a.value))
method andInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value and a.value)

method addInst*(a, b: Value): Value {.base.} = "Invalid values in add instruction".abort
method addInst*(a, b: NumberValue): Value = NumberValue(value: b.value + a.value)
method addInst*(a, b: BooleanValue): Value = NumberValue(value: float(b.value) + float(a.value))
method addInst*(a, b: StringValue): Value = StringValue(value: b.value & a.value)

method subInst*(a, b: Value): Value {.base.} = "Invalid values in sub instruction".abort
method subInst*(a, b: NumberValue): Value = NumberValue(value: b.value - a.value)
method subInst*(a, b: BooleanValue): Value = NumberValue(value: float(b.value) - float(a.value))

method mulInst*(a, b: Value): Value {.base.} = "Invalid values in mul instruction".abort
method mulInst*(a, b: NumberValue): Value = NumberValue(value: b.value * a.value)
method mulInst*(a, b: BooleanValue): Value = NumberValue(value: float(b.value) * float(a.value))
method mulInst*(a: NumberValue, b: StringValue): Value = StringValue(value: b.value.repeat(Natural(a.value)))
method mulInst*(a: StringValue, b: NumberValue): Value = StringValue(value: a.value.repeat(Natural(b.value)))

method divInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method divInst*(a, b: NumberValue): Value = NumberValue(value: b.value / a.value)
method divInst*(a, b: BooleanValue): Value = NumberValue(value: float(b.value) / float(a.value))

method modInst*(a, b: Value): Value {.base.} = "Invalid values in mod instruction".abort
method modInst*(a, b: NumberValue): Value = NumberValue(value: b.value mod a.value)
method modInst*(a, b: BooleanValue): Value = NumberValue(value: float(b.value) mod float(a.value))

method eqInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method eqInst*(a, b: NumberValue): Value = BooleanValue(value: b.value == a.value)
method eqInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value == a.value)
method eqInst*(a, b: StringValue): Value = BooleanValue(value: b.value == a.value)

method neqInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method neqInst*(a, b: NumberValue): Value = BooleanValue(value: b.value != a.value)
method neqInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value != a.value)
method neqInst*(a, b: StringValue): Value = BooleanValue(value: b.value != a.value)

method gtInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method gtInst*(a, b: NumberValue): Value = BooleanValue(value: b.value > a.value)
method gtInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value > a.value)
method gtInst*(a, b: StringValue): Value = BooleanValue(value: b.value > a.value)

method gteInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method gteInst*(a, b: NumberValue): Value = BooleanValue(value: b.value >= a.value)
method gteInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value >= a.value)
method gteInst*(a, b: StringValue): Value = BooleanValue(value: b.value >= a.value)

method ltInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method ltInst*(a, b: NumberValue): Value = BooleanValue(value: b.value < a.value)
method ltInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value < a.value)
method ltInst*(a, b: StringValue): Value = BooleanValue(value: b.value < a.value)

method lteInst*(a, b: Value): Value {.base.} = "Invalid values in div instruction".abort
method lteInst*(a, b: NumberValue): Value = BooleanValue(value: b.value <= a.value)
method lteInst*(a, b: BooleanValue): Value = BooleanValue(value: b.value <= a.value)
method lteInst*(a, b: StringValue): Value = BooleanValue(value: b.value <= a.value)

method branchtInst*(a: Value): bool {.base.} = "Wrong branch instruction".abort
method branchtInst*(a: NumberValue): bool = bool(a.value)
method branchtInst*(a: BooleanValue): bool = a.value
method branchtInst*(a: StringValue): bool = bool(a.value.len)

method branchfInst*(a: Value): bool {.base.} = "Wrong branch not instruction".abort
method branchfInst*(a: NumberValue): bool = not bool(a.value)
method branchfInst*(a: BooleanValue): bool = not a.value
method branchfInst*(a: StringValue): bool = not bool(a.value.len)

method funInst*(startLabel: Value, scope: int): Value {.base.} = "Wrong function declaration".abort
method funInst*(startLabel: StringValue, scope: int): Value = FunctionValue(label: startLabel.value, scope: scope)