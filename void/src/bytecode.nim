import instructions, values, vm

type
    Bytecode* = ref object
        vm*: VM

proc newBytecode*(vm: VM): Bytecode = Bytecode(vm: vm)

method format*(b: Bytecode, i: Instruction): string {.base.}

proc save*(b: Bytecode, file = "output.vovm") =
    var contents = ""
    for i in b.vm.program:
        contents &= b.format(i) & "\n"
    file.writeFile(contents)

method format*(b: Bytecode, i: Instruction): string {.base.} =
    echo "Unknown instruction found"
    quit()

method format*(b: Bytecode, i: Marker): string = "__MARKER_" & $i.pc
method format*(b: Bytecode, i: PushInst): string = "PUSH " & $i.value
method format*(b: Bytecode, i: PopInst): string = "POP"
method format*(b: Bytecode, i: JumpInst): string = "JUMP " & $b.vm.markers[i.marker].pc
method format*(b: Bytecode, i: PrintInst): string = "PRINT"
method format*(b: Bytecode, i: AdditionInst): string = "ADDITION"
method format*(b: Bytecode, i: SubtractionInst): string = "SUBTRACTION"
method format*(b: Bytecode, i: MultiplicationInst): string = "MULTIPLICATION"
method format*(b: Bytecode, i: DivisionInst): string = "DIVISION"
method format*(b: Bytecode, i: EqualInst): string = "EQUAL"
method format*(b: Bytecode, i: NotEqualInst): string = "NOTEQUAL"
method format*(b: Bytecode, i: GreaterInst): string = "GREATER"
method format*(b: Bytecode, i: GreaterEqualInst): string = "GREATEROREQUAL"
method format*(b: Bytecode, i: LessInst): string = "LESS"
method format*(b: Bytecode, i: LessEqualInst): string = "LESSOREQUAL"
method format*(b: Bytecode, i: BranchInstruction): string = "BRANCH " & $b.vm.markers[i.marker].pc
method format*(b: Bytecode, i: BranchNotInstruction): string = "BRANCHNOT " & $b.vm.markers[i.marker].pc
method format*(b: Bytecode, i: PushScopeInst): string = "PUSHSCOPE"
method format*(b: Bytecode, i: PopScopeInst): string = "POPSCOPE"
method format*(b: Bytecode, i: AssignInst): string = "ASSIGN " &  i.name
method format*(b: Bytecode, i: VariableInst): string = "VARIABLE " & i.name