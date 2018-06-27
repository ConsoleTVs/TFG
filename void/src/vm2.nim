import tables, values, instructions2

const
    vm_label_prefix* = "*"
    vm_temp_label_prefix* = "*_"

type
    VM* = ref tuple
        program: seq[Instruction] # Program instructions
        stack: seq[Value] # Program instructions
        heap: seq[Table[string, Value]] # VM Heap
        labels: Table[string, int] # Labels (label -> pc)
        pc, fp, temp_label_num: int # Program Counter, Frame Pointer, Helper to prefix temp labels and don't repeat any

proc newVM*(program: seq[Instruction]): VM =
    new result
    result.program = program
    result.stack = @[]
    result.pc = -1 # It increments on the first run to 0
    result.fp = 0
    result.temp_label_num = 0
    result.heap = @[initTable[string, Value]()]
    result.labels = initTable[string, int]()

proc tempLabel*(vm: VM): string = vm.temp_label_num.inc; vm_temp_label_prefix & $(vm.temp_label_num - 1)

proc advance(vm: VM): Instruction =  vm.pc.inc; return vm.program[vm.pc]

proc jump(vm: VM, i: Instruction) = vm.pc = int(NumberValue(i.value).value)
proc labelJump(vm: VM, i: Instruction) = vm.pc = vm.labels[StringValue(i.value).value]

proc push(vm: VM, value: Value) = vm.stack.add(value)

proc pop(vm: VM): Value =
    if vm.stack.len == 0:
        echo "Empty stack, can't pop"
        quit()
    var value = vm.stack[vm.stack.len - 1]
    vm.stack.delete(vm.stack.len - 1)
    return value

proc findLabels(vm: VM) =
    for i,e in vm.program:
        if e.kind == LABELINST:
            vm.labels[$e.value] = i

proc run*(vm: VM) =
    vm.findLabels
    while vm.pc < vm.program.len:
        vm.pc.inc
        case vm.program[vm.pc].kind:
            of HALTINST: return
            of NOPINST, LABELINST: discard # No Operation Instruction
            of PRINTINT: echo vm.pop
            of PUSHINST: vm.push(vm.advance.value)
            of VALUEINST: discard # Values are used with the advance() proc and not as an instruction.
            of POPINST: discard vm.pop # Kinda useless to pop without a reason tho...
            of NEGINST: vm.push(negInst(vm.pop))
            of NOTINST: vm.push(notInst(vm.pop))
            of ORINST: vm.push(orInst(vm.pop, vm.pop))
            of ANDINST: vm.push(andInst(vm.pop, vm.pop))
            of ADDINST: vm.push(addInst(vm.pop, vm.pop))
            of SUBINST: vm.push(subInst(vm.pop, vm.pop))
            of MULINST: vm.push(mulInst(vm.pop, vm.pop))
            of DIVINST: vm.push(divInst(vm.pop, vm.pop))
            of MODINST: vm.push(modInst(vm.pop, vm.pop))
            of EQINST: vm.push(eqInst(vm.pop, vm.pop))
            of NEQINST: vm.push(neqInst(vm.pop, vm.pop))
            of GTINST: vm.push(gtInst(vm.pop, vm.pop))
            of GTEINST: vm.push(gteInst(vm.pop, vm.pop))
            of LTINST: vm.push(ltInst(vm.pop, vm.pop))
            of LTEINST: vm.push(lteInst(vm.pop, vm.pop))
            of JUMPINST: vm.labelJump(vm.advance)
            of RJUMPINST: vm.jump(vm.advance)
            of BRANCHTINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchtInst:
                    vm.labelJump(inst)
            of BRANCHFINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchfInst:
                    vm.labelJump(inst)
            of STOREINST: vm.heap[vm.fp][StringValue(vm.advance.value).value] = vm.pop
            of LOADINST: vm.push(vm.heap[vm.fp][StringValue(vm.advance.value).value])
            else:
                echo "Unknown operation " & $vm.program[vm.pc].kind
                quit()

proc dumpStack*(vm: VM) =
    echo ""
    echo "STACK: "
    var current = vm.stack.len - 1
    while current >= 0:
        echo $current & " -> " & $vm.stack[current]
        current.dec