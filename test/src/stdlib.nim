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
        newInstruction(VALUEINST, "e".newStringValue),
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
        vm.add(VALUEINST, startLabel.newStringValue)
        vm.add(PUSHINST)
        vm.add(VALUEINST, endLabel.newStringValue)
        vm.add(PUSHINST)
        vm.add(VALUEINST, newNumberValue(float(lib[k].arguments.len))) # The number of arguments
        vm.add(FUNINST) # This will pop last 3 values to know the startLabel and theEndLabel and the number of arguments
        vm.add(LABELINST, startLabel.newStringValue)
        # Function start
        # We first get the arguments and we assign them to the variables
        for v in lib[k].arguments:
            vm.add(STOREINST)
            vm.add(VALUEINST, v.newStringValue)
        for i in lib[k].instructions:
            vm.program.add(i)
        vm.add(PUSHINST)
        vm.add(VALUEINST, newNoneValue())
        vm.add(RETURNINST)
        # Function end
        vm.add(LABELINST, endLabel.newStringValue)

        #[
            We then add the variable that hold that function
        ]#
        let frame = vm.frames[vm.frames.len - 1]
        frame.heap[k] = newFunctionValue(startLabel, frame, lib[k].arguments.len)