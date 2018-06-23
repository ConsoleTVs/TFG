import values, instructions, tables

##[
    This module stores what's said to be an
    implementation of the void virtual machin
]##

type
    VM* = ref tuple
        program: seq[Instruction] # Instructions
        pc: int # Program counter
        stack: seq[Value] # Stack
        memory: seq[Table[string, Value]] # Program memory (scopes)
        markers: seq[Marker] # Sequence of program counters where the marker is set

proc newVM*(program: seq[Instruction]): VM =
    new result
    result.program = program
    result.pc = 0
    result.stack = @[]
    result.memory = @[]
    result.markers = @[]
    result.memory.add(initTable[string, Value]())

proc createMarker*(vm: VM): tuple[marker: Marker, markerNumber: int] =
    vm.markers.add(Marker())
    return (marker: vm.markers[vm.markers.len - 1], markerNumber: vm.markers.len - 1)

proc pushMarker*(vm: VM, marker: Marker) =
    marker.pc = vm.program.len # We set the marker program counter
    vm.program.add(marker)

proc put*(vm: VM, name: string, value: Value) =
    var current = vm.memory.len - 1
    while current >= 0:
        if vm.memory[current].hasKey(name):
            vm.memory[current][name] = value
            return
        current.dec
    vm.memory[vm.memory.len - 1][name] = value

proc get*(vm: VM, name: string): Value =
    var current = vm.memory.len - 1
    while current >= 0:
        if vm.memory[current].hasKey(name):
            return vm.memory[current][name]
        current.dec
    echo "Undefined variable " & name
    quit()

proc push*(vm: VM, value: Value) = vm.stack.add(value)

proc pop*(vm: VM): Value =
    if vm.stack.len == 0:
        echo "Empty stack, can't pop"
        quit()
    var value = vm.stack[vm.stack.len - 1]
    vm.stack.delete(vm.stack.len - 1)
    return value

proc jump(vm: VM, marker: int) = vm.pc = vm.markers[marker].pc

proc current(vm: VM): Value = vm.stack[vm.stack.len - 1]

method execute(vm: VM, instruction: Instruction) {.base.} =
    echo "Generic instruction. Something went wrong..."
    quit()
method execute(vm: VM, instruction: Marker) = discard # Discard the marker
method execute(vm: VM, instruction: PushInst) = vm.push(instruction.value)
method execute(vm: VM, instruction: PopInst) = discard vm.pop
method execute(vm: VM, instruction: JumpInst) = vm.jump(instruction.marker)
method execute(vm: VM, instruction: PrintInst) = vm.current.printInst
method execute(vm: VM, instruction: AdditionInst) = vm.push(additionInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: SubtractionInst) = vm.push(substractionInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: MultiplicationInst) = vm.push(multiplicationInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: DivisionInst) = vm.push(divisionInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: EqualInst) = vm.push(equalInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: NotEqualInst) = vm.push(notEqualInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: GreaterInst) = vm.push(greaterInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: GreaterEqualInst) = vm.push(greaterEqualInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: LessInst) = vm.push(lessInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: LessEqualInst) = vm.push(lessEqualInst(vm.pop, vm.pop))
method execute(vm: VM, instruction: BranchInstruction) =
    if vm.pop.branchInstruction:
        vm.jump(instruction.marker)
method execute(vm: VM, instruction: BranchNotInstruction) =
    if vm.pop.branchNotInstruction:
        vm.jump(instruction.marker)
method execute(vm: VM, instruction: PushScopeInst) = vm.memory.add(initTable[string, Value]())
method execute(vm: VM, instruction: PopScopeInst) =
    if vm.memory.len == 1:
        echo "Can't pop the global scope"
        quit()
    vm.memory.delete(vm.memory.len - 1)
method execute(vm: VM, instruction: AssignInst) = vm.put(instruction.name, vm.pop)
method execute(vm: VM, instruction: VariableInst) = vm.push(vm.get(instruction.name))

proc dumpStack*(vm: VM) =
    echo ""
    echo "STACK: "
    var current = vm.stack.len - 1
    while current >= 0:
        echo $current & " -> " & $vm.stack[current]
        current.dec

proc init*(vm: VM) =
    while vm.pc < vm.program.len:
        vm.execute(vm.program[vm.pc])
        vm.pc.inc