import tables, values, instructions

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

proc jump(vm: VM, i: Instruction) = vm.pc = int(i.value.numberValue)
proc labelJump(vm: VM, i: Instruction) = vm.pc = vm.labels[i.value.stringValue]
proc labelJump(vm: VM, i: string) = vm.pc = vm.labels[i]

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
        #echo vm.program[vm.pc].kind
        case vm.program[vm.pc].kind:
            of HALTINST: return
            of NOPINST, LABELINST: discard # No Operation Instruction
            of PRINTINST: echo vm.pop
            of PUSHINST: vm.push(vm.advance.value)
            of VALUEINST: discard # Values are used with the advance() proc and not as an instruction.
            of POPINST: discard vm.pop # Kinda useless to pop without a reason tho...
            #[
            of NEGINST: vm.push(negInst(vm.pop))
            of NOTINST: vm.push(notInst(vm.pop))
            of ORINST:
                let a, b = vm.pop
                vm.push(orInst(a, b))
            of ANDINST:
                let a, b = vm.pop
                vm.push(andInst(a, b))
            ]#
            of ADDINST:
                let a, b = vm.pop
                vm.push(addInst(a, b))
            of SUBINST:
                let a, b = vm.pop
                vm.push(subInst(a, b))
            #[
            of MULINST:
                let a, b = vm.pop
                vm.push(mulInst(a, b))
            of DIVINST:
                let a, b = vm.pop
                vm.push(divInst(a, b))
            of MODINST:
                let a, b = vm.pop
                vm.push(modInst(a, b))
            of EQINST:
                let a, b = vm.pop
                vm.push(eqInst(a, b))
            of NEQINST:
                let a, b = vm.pop
                vm.push(neqInst(a, b))
            of GTINST:
                let a, b = vm.pop
                vm.push(gtInst(a, b))
            of GTEINST:
                let a, b = vm.pop
                vm.push(gteInst(a, b))
            ]#
            of LTINST:
                let a, b = vm.pop
                vm.push(ltInst(a, b))
            #[
            of LTEINST:
                let a, b = vm.pop
                vm.push(lteInst(a, b))
            ]#
            of JUMPINST: vm.labelJump(vm.advance)
            of RJUMPINST: vm.jump(vm.advance)
            of FUNINST:
                # vm.dumpStack
                let
                    # Do not re-order theese!
                    arguments = vm.pop
                    endLabel = vm.pop
                    startLabel = vm.pop
                    fun = funInst(startLabel, vm.frames[vm.frames.len - 1], int(arguments.numberValue))
                vm.frames[vm.frames.len - 1].heap["f"] = fun # Self reference to function
                vm.frames.add(newFrame(vm.frames[vm.frames.len - 1].return_address, vm.frames[vm.frames.len - 1].heap))
                vm.push(fun) # Push the function value to the stack
                vm.labelJump(endLabel.stringValue)
                # vm.dumpStack
            of CALLINST:
                let
                    arguments = int(vm.pop.numberValue)
                    fun = vm.pop
                if arguments != fun.functionArguments:
                    echo "The function requires " & $fun.functionArguments & " arguments. You provided " & $arguments & "."
                    quit()
                vm.frames.add(newFrame(vm.pc, fun.functionFrame.heap))
                vm.pc = vm.labels[fun.functionLabel]
            #[
            of BRANCHTINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchtInst:
                    vm.labelJump(inst)
            ]#
            of BRANCHFINST:
                let inst = vm.advance # Always consume the next instruction
                if vm.pop.branchfInst:
                    vm.labelJump(inst)
            of STOREINST: vm.frames[vm.frames.len - 1].heap[vm.advance.value.stringValue] = vm.pop
            of LOADINST:
                let
                    key = vm.advance.value.stringValue
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
                    res: Value
                    values: seq[Value] = @[]
                    num = vm.advance.value.numberValue
                while num > 0:
                    values.add(vm.pop)
                    num -= 1
                res.listValues = values
                vm.push(res)
            #of ACCESSINST: vm.push(accessInst(vm.pop, vm.pop))
            #of LENINST: vm.push(lenInst(vm.pop))
            else:
                echo "Unknown operation " & $vm.program[vm.pc].kind
                quit()