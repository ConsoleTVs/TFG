import instructions, values, vm

type
    Bytecode* = tuple
        vm: VM

proc format(b: Bytecode, n: Instruction): string =
    case n.kind:
        of LABELINST: return $n.value & ":\n"
        of VALUEINST:
            if n.value.kind == STRINGVALUE:
                return "\"" & n.value.stringValue & "\"\n"
            else:
                return $n.value & "\n"
        of BRANCHTINST, BRANCHFINST, PUSHINST, JUMPINST, STOREINST, LOADINST, PUSHPCOFFSETINST, LISTINST:
            return "\t" & $n.kind & " "
        else: return "\t" & $n.kind & "\n"

proc save*(b: Bytecode, file = "output.vovm") =
    var contents = vm_label_prefix & "main:\n"
    for i in b.vm.program:
        contents &= b.format(i)
    file.writeFile(contents)