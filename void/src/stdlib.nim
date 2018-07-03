import tables, instructions, values, vm, codegen

type
    Function = tuple
        arguments: seq[string]
        instructions: seq[Instruction]

proc createFun(arguments: seq[string], instructions: seq[Instruction]): Function = (arguments: arguments, instructions: instructions)

##[
    Standard library functions
]##
let lib*: Table[string, Function] = {
    "len": createFun(@["e"], @[
        newInstruction(LOADINST),
        newInstruction(VALUEINST, StringValue(value: "e")),
        newInstruction(LENINST),
        newInstruction(RETURNINST)
    ])
}.toTable

proc addStdLib*(vm: VM) =
    for k in lib.keys:

        #[
            We first add the code to the bytecode
        ]#
        let startLabel, endLabel = vm.tempLabel
        vm.add(PUSHINST)
        vm.add(VALUEINST, StringValue(value: startLabel))
        vm.add(PUSHINST)
        vm.add(VALUEINST, StringValue(value: endLabel))
        vm.add(PUSHINST)
        vm.add(VALUEINST, NumberValue(value: float(lib[k].arguments.len))) # The number of arguments
        vm.add(FUNINST) # This will pop last 3 values to know the startLabel and theEndLabel and the number of arguments
        vm.add(LABELINST, StringValue(value: startLabel))
        # Function start
        # We first get the arguments and we assign them to the variables
        for v in lib[k].arguments:
            vm.add(STOREINST)
            vm.add(VALUEINST, StringValue(value: v))
        for i in lib[k].instructions:
            vm.program.add(i)
        vm.add(PUSHINST)
        vm.add(VALUEINST, NoneValue())
        vm.add(RETURNINST)
        # Function end
        vm.add(LABELINST, StringValue(value: endLabel))

        #[
            We then add the variable that hold that function
        ]#
        let frame = vm.frames[vm.frames.len - 1]
        frame.heap[k] = FunctionValue(label: startLabel, frame: frame, arguments: lib[k].arguments.len)