import values

type
    Instruction* = ref object of RootObj

    Marker* = ref object of Instruction # Not really an instruction tho...
        pc*: int # Program counter where the marker is

    PushInst* = ref object of Instruction
        value*: Value

    PopInst* = ref object of Instruction

    JumpInst* = ref object of Instruction
        marker*: int # Marker to jump to

    PrintInst* = ref object of Instruction

    #Binary instructions (pop 2 from stack)
    AdditionInst* = ref object of Instruction
    SubtractionInst* = ref object of Instruction
    MultiplicationInst* = ref object of Instruction
    DivisionInst* = ref object of Instruction
    EqualInst* = ref object of Instruction
    NotEqualInst* = ref object of Instruction
    GreaterInst* = ref object of Instruction
    GreaterEqualInst* = ref object of Instruction
    LessInst* = ref object of Instruction
    LessEqualInst* = ref object of Instruction

    BranchInstruction* = ref object of Instruction
        marker*: int
    BranchNotInstruction* = ref object of Instruction
        marker*: int

    PushScopeInst* = ref object of Instruction

    PopScopeInst* = ref object of Instruction

    AssignInst* = ref object of Instruction
        name*: string

    VariableInst* = ref object of Instruction
        name*: string

method printInst*(a: Value) {.base.} = echo $a

method additionInst*(a, b: Value): Value {.base.} =
    echo "Wrong addition instruction"
    quit()
method additionInst*(a, b: NumberValue): Value = NumberValue(value: b.value + a.value)

method substractionInst*(a, b: Value): Value {.base.} =
    echo "Wrong substraction instruction"
    quit()
method substractionInst*(a, b: NumberValue): Value = NumberValue(value: b.value - a.value)

method multiplicationInst*(a, b: Value): Value {.base.} =
    echo "Wrong multiplication instruction"
    quit()
method multiplicationInst*(a, b: NumberValue): Value = NumberValue(value: b.value * a.value)

method divisionInst*(a, b: Value): Value {.base.} =
    echo "Wrong division instruction"
    quit()
method divisionInst*(a, b: NumberValue): Value = NumberValue(value: b.value / a.value)

method equalInst*(a, b: Value): Value {.base.} =
    echo "Wrong equal instruction"
    quit()
method equalInst*(a, b: NumberValue): Value = BooleanValue(value: a.value == b.value)

method notEqualInst*(a, b: Value): Value {.base.} =
    echo "Wrong not equal instruction"
    quit()
method notEqualInst*(a, b: NumberValue): Value = BooleanValue(value: a.value != b.value)

method greaterInst*(a, b: Value): Value {.base.} =
    echo "Wrong greater instruction"
    quit()
method greaterInst*(a, b: NumberValue): Value = BooleanValue(value: b.value > a.value)

method greaterEqualInst*(a, b: Value): Value {.base.} =
    echo "Wrong greater equal instruction"
    quit()
method greaterEqualInst*(a, b: NumberValue): Value = BooleanValue(value: b.value >= a.value)

method lessInst*(a, b: Value): Value {.base.} =
    echo "Wrong less instruction"
    quit()
method lessInst*(a, b: NumberValue): Value = BooleanValue(value: b.value < a.value)

method lessEqualInst*(a, b: Value): Value {.base.} =
    echo "Wrong less equal instruction"
    quit()
method lessEqualInst*(a, b: NumberValue): Value = BooleanValue(value: b.value >= a.value)

method branchInstruction*(a: Value): bool {.base.} =
    echo "Wrong branch instruction"
    quit()
method branchInstruction*(a: BooleanValue): bool = a.value

method branchNotInstruction*(a: Value): bool {.base.} =
    echo "Wrong branch not instruction"
    quit()
method branchNotInstruction*(a: BooleanValue): bool = not a.value