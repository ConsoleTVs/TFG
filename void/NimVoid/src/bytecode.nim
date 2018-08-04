import instructions, values, vm

type
    Bytecode* = ref tuple
        vm: VM

proc newBytecode*(vm: VM): Bytecode = new result; result.vm = vm

proc format(b: Bytecode, n: Instruction): string =
    case n.kind:
        of LABELINST: return $n.value & ":\n"
        of VALUEINST:
            if n.value of StringValue:
                return "\"" & $n.value & "\"\n"
            else:
                return $n.value & "\n"
        of BRANCHTINST, BRANCHFINST, PUSHINST, JUMPINST, AJUMPINST, STOREINST, LOADINST, PUSHPCOFFSETINST, LISTINST:
            return "\t" & $n.kind & " "
        else: return "\t" & $n.kind & "\n"

proc save*(b: Bytecode, file = "output.vovm") =
    var contents = vm_label_prefix & "main:\n"
    for i in b.vm.program:
        contents &= b.format(i)
    file.writeFile(contents)