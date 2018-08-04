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
        PRINTINST = "PRINT" # Print
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
        LISTINST = "LIST"
        ACCESSINST = "ACCESS"
        LENINST = "LEN"

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
proc both(a, b: Value, kind: ValueKind): bool = a.kind == kind and b.kind == kind
#[
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
]#
proc addInst*(a, b: Value): Value =
    if both(a, b, NUMBERVALUE):
        return newNumberValue(b.numberValue + a.numberValue)
    "Invalid add instruction".abort

proc subInst*(a, b: Value): Value =
    if both(a, b, NUMBERVALUE):
        return newNumberValue(b.numberValue - a.numberValue)
    "Invalid sub instruction".abort

proc ltInst*(a, b: Value): Value =
    if both(a, b, NUMBERVALUE):
        return newBooleanValue(b.numberValue < a.numberValue)
    "Invalid lt instruction".abort

proc branchfInst*(a: Value): bool =
    if a.kind == BOOLEANVALUE:
        return not a.booleanValue
    "Invalid branchf instruction".abort

proc funInst*(startLabel: Value, frame: Frame, arguments: int): Value =
    if startLabel.kind ==  STRINGVALUE:
        return newFunctionValue(startLabel.stringValue, frame, arguments)
    "Invalid fun instruction".abort