import values

type
    Instruction* = ref object of RootObj

    PushInst* = ref object of Instruction
        value*: Value

    PopInst* = ref object of Instruction

    PrintInst* = ref object of Instruction

    AdditionInst* = ref object of Instruction

    SubstractionInst* = ref object of Instruction

    MultiplicationInst* = ref object of Instruction

    DivisionInst* = ref object of Instruction

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