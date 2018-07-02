import tables, values, instructions, frame

const
    vm_label_prefix* = "*"
    vm_temp_label_prefix* = "*_"

type
    VM* = ref tuple
        program: seq[Instruction] # Program instructions
        stack: seq[Value] # Program instructions
        # heap: seq[Table[string, Value]] # VM Heap
        frames: seq[Frame] # Current execution frame
        labels: Table[string, int] # Labels (label -> pc)
        # currentScope: int
        pc, temp_label_num: int # Program Counter, Current heap scope, Helper to prefix temp labels and don't repeat any

proc newVM*(program: seq[Instruction]): VM =
    new result
    result.program = program
    result.stack = @[]
    result.pc = -1 # It increments on the first run to 0
    # result.currentScope = 0
    result.temp_label_num = 0
    # result.heap = @[initTable[string, Value]()]
    result.frames = @[newFrame(0)]
    result.labels = initTable[string, int]()

proc dumpStack*(vm: VM) =
    echo ""
    echo "STACK: "
    var current = vm.stack.len - 1
    while current >= 0:
        echo $current & " -> " & $vm.stack[current]
        current.dec

proc tempLabel*(vm: VM): string = vm.temp_label_num.inc; vm_temp_label_prefix & $(vm.temp_label_num - 1)

# proc peek(vm: VM): Instruction = vm.program[vm.pc]
proc advance(vm: VM): Instruction =  vm.pc.inc; return vm.program[vm.pc]

proc jump(vm: VM, i: Instruction) = vm.pc = int(NumberValue(i.value).value)
proc labelJump(vm: VM, i: Instruction) = vm.pc = vm.labels[StringValue(i.value).value]
proc labelJump(vm: VM, i: StringValue) = vm.pc = vm.labels[i.value]

# proc scope(vm: VM): Table[string, Value] = vm.heap[vm.heap.len - 1]
# proc createScope(vm: VM) = vm.heap.add(vm.scope); vm.currentScope.inc

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
    while vm.pc < vm.program.len - 1:
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
            of FUNINST:
                # vm.dumpStack
                let
                    # Do not re-order theese!
                    endLabel = vm.pop
                    startLabel = vm.pop
                    fun = funInst(startLabel, vm.frames[vm.frames.len - 1])
                vm.frames[vm.frames.len - 1].heap["f"] = fun # Self reference to function
                vm.frames.add(newFrame(vm.frames[vm.frames.len - 1].return_address, vm.frames[vm.frames.len - 1].heap))
                vm.push(fun) # Push the function value to the stack
                vm.labelJump(StringValue(endLabel))
                # vm.dumpStack
            of CALLINST:
                let fun = FunctionValue(vm.pop)
                vm.frames.add(newFrame(vm.pc, fun.frame.heap))
                vm.pc = vm.labels[fun.label]
            of BRANCHTINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchtInst:
                    vm.labelJump(inst)
            of BRANCHFINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchfInst:
                    vm.labelJump(inst)
            of STOREINST: vm.frames[vm.frames.len - 1].heap[StringValue(vm.advance.value).value] = vm.pop
            of LOADINST:
                let
                    key = StringValue(vm.advance.value).value
                    frame = vm.frames[vm.frames.len - 1]
                if frame.heap.hasKey(key):
                    vm.push(frame.heap[key])
                else:
                    echo "Undefined variable " & key
                    quit()
            # of PUSHPCOFFSETINST: vm.push(NumberValue(value: float(vm.pc) + NumberValue(vm.advance.value).value))
            # of PUSHSCOPEINST: vm.push(NumberValue(value: float(vm.currentScope)))
            of POPARGUMENTSINST:
                discard
                # FUNCTION ??
                # let numArgs = NumberValue(vm.pop).value
                # while numArgs > 0:
                #    vm.heap[vm.currentScope][] = v
            of RETURNINST:
                let pc = vm.frames[vm.frames.len - 1].return_address
                vm.frames.delete(vm.frames.len - 1) # Delete the current frame, so we get back to the original
                vm.pc = pc
                vm.push(vm.pop) # Put the return value back up
            of LISTINST:
                # We create a list value with N elements
                var
                    values: seq[Value] = @[]
                    num = NumberValue(vm.advance.value).value
                while num > 0:
                    values.add(vm.pop)
                    num -= 1
                vm.push(ListValue(values: values))
            else:
                echo "Unknown operation " & $vm.program[vm.pc].kind
                quit()