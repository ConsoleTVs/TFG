import bytecode, instructions, values, vm

type
    BytecodeOptimizer* = ref tuple
        bytecode: Bytecode

proc newBytecodeOptimizer*(bytecode: Bytecode): BytecodeOptimizer = new result; result.bytecode = bytecode

##[
    Theese are the real optimizations done to the bytecode before execution.
]##
proc tail_recursive(o: BytecodeOptimizer) =
    var
        program = o.bytecode.vm.program
        inFunction = false
        functionEnd = ""
    for i,e in program:
        if inFunction:
            # Search for recursive tail
            if e.kind == CALLINST and StringValue(program[i - 3].value).value == "f":
                # Recursion found
                echo "Recursion found at instruction " & $i
                discard
            elif e.kind == LABELINST and StringValue(e.value).value == functionEnd:
                inFunction = false
        elif e.kind == FUNINST:
            inFunction = true
            functionEnd = StringValue(program[i - 3].value).value # Get the end label string

##[
    The optimizations that are applied are determined in the following function.
]##
proc optimize*(o: BytecodeOptimizer) =
    o.tail_recursive ## Optimize the tail calling recursion