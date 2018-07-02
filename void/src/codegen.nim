import vm, instructions, values, rules, tokens

proc add(vm: VM, kind: InstructionKind, value: Value = nil) = vm.program.add(newInstruction(kind, value))

method codegen*(vm: VM, n: Expression) {.base.} = discard
method codegen*(vm: VM, n: Statement) {.base.} = discard

method codegen*(vm: VM, n: Number) =
    vm.add(PUSHINST)
    vm.add(VALUEINST, NumberValue(value: n.value))

method codegen*(vm: VM, n: String) =
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: n.value))

method codegen*(vm: VM, n: Boolean) =
    vm.add(PUSHINST)
    vm.add(VALUEINST, BooleanValue(value: n.value))

method codegen*(vm: VM, n: List) =
    var i = n.values.len - 1
    while i >= 0:
        vm.codegen(n.values[i])
        i.dec
    vm.add(LISTINST)
    vm.add(VALUEINST, NumberValue(value: float(n.values.len)))

method codegen*(vm: VM, n: None) =
    vm.add(PUSHINST)
    vm.add(VALUEINST, NoneValue())

method codegen*(vm: VM, n: ExpressionStatement) = vm.codegen(n.expression)

method codegen*(vm: VM, n: Group) = vm.codegen(n.expression)

method codegen*(vm: VM, n: Unary) =
    vm.codegen(n.right)
    case n.operator.kind:
        of TOK_BANG: vm.add(NOTINST)
        of TOK_MINUS: vm.add(NEGINST)
        else: echo "Error generating code for unary operator"; quit()

method codegen*(vm: VM, n: Binary) =
    vm.codegen(n.left)
    vm.codegen(n.right)
    case n.operator.kind:
        of TOK_PLUS: vm.add(ADDINST)
        of TOK_MINUS: vm.add(SUBINST)
        of TOK_STAR: vm.add(MULINST)
        of TOK_SLASH: vm.add(DIVINST)
        of TOK_PERCENT: vm.add(MODINST)
        of TOK_EQUAL_EQUAL: vm.add(EQINST)
        of TOK_BANG_EQUAL: vm.add(NEQINST)
        of TOK_GREATER: vm.add(GTINST)
        of TOK_GREATER_EQUAL: vm.add(GTEINST)
        of TOK_LESS: vm.add(LTINST)
        of TOK_LESS_EQUAL: vm.add(LTEINST)
        else:
            echo "Error generating code for a binary operator"
            quit()

method codegen*(vm: VM, n: Variable) =
    vm.add(LOADINST)
    vm.add(VALUEINST, StringValue(value: n.name.lexeme))

method codegen*(vm: VM, n: Assign) =
    vm.codegen(n.value)
    vm.add(STOREINST)
    vm.add(VALUEINST, StringValue(value: n.name.lexeme))

method codegen*(vm: VM, n: Logical) =
    vm.codegen(n.left)
    vm.codegen(n.right)
    case n.operator.kind:
        of TOK_OR: vm.add(ORINST)
        of TOK_AND: vm.add(ANDINST)
        else:
            echo "Error generating code for a logical operator"
            quit()

method codegen*(vm: VM, n: Print) =
    vm.codegen(n.expression)
    vm.add(PRINTINT)

method codegen*(vm: VM, n: Block) =
    for i in n.body:
        vm.codegen(i)

method codegen*(vm: VM, n: SimpleIf) =
    vm.codegen(n.condition)
    let label = vm.tempLabel
    vm.add(BRANCHFINST)
    vm.add(VALUEINST, StringValue(value: label))
    vm.codegen(n.expression)
    vm.add(LABELINST, StringValue(value: label))

method codegen*(vm: VM, n: If) =
    if n.elseBranch == nil:
        vm.codegen(n.condition)
        let endLabel = vm.tempLabel
        vm.add(BRANCHFINST)
        vm.add(VALUEINST, StringValue(value: endLabel))
        vm.codegen(n.thenBranch)
        vm.add(LABELINST, StringValue(value: endLabel))
    else:
        vm.codegen(n.condition)
        let elseLabel, endLabel = vm.tempLabel
        vm.add(BRANCHFINST)
        vm.add(VALUEINST, StringValue(value: elseLabel))
        vm.codegen(n.thenBranch)
        vm.add(JUMPINST)
        vm.add(VALUEINST, StringValue(value: endLabel))
        vm.add(LABELINST, StringValue(value: elseLabel))
        vm.codegen(n.elseBranch)
        vm.add(LABELINST, StringValue(value: endLabel))

method codegen*(vm: VM, n: While) =
    let startLabel, endLabel = vm.tempLabel
    vm.add(LABELINST, StringValue(value: startLabel))
    vm.codegen(n.condition)
    vm.add(BRANCHFINST)
    vm.add(VALUEINST, StringValue(value: endLabel))
    vm.codegen(n.body)
    vm.add(JUMPINST)
    vm.add(VALUEINST, StringValue(value: startLabel))
    vm.add(LABELINST, StringValue(value: endLabel))

method codegen*(vm: VM, n: Function) =
    let startLabel, endLabel = vm.tempLabel
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: startLabel))
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: endLabel))
    vm.add(FUNINST) # This will pop last 2 values to know the startLabel and theEndLabel
    vm.add(LABELINST, StringValue(value: startLabel))
    # Function start
    # We first get the arguments and we assign them to the variables
    for i in n.arguments:
        vm.add(STOREINST)
        vm.add(VALUEINST, StringValue(value: i.lexeme))
    vm.codegen(n.body)
    vm.add(PUSHINST)
    vm.add(VALUEINST, NoneValue())
    vm.add(RETURNINST)
    # Function end
    vm.add(LABELINST, StringValue(value: endLabel))

method codegen*(vm: VM, n: Return) =
    vm.codegen(n.value)
    vm.add(RETURNINST)

method codegen*(vm: VM, n: Call) =
    # vm.add(PUSHPCOFFSETINST)
    # vm.add(VALUEINST, NumberValue(value: float(4 + n.arguments.len)))
    # vm.add(PUSHSCOPEINST)
    var max = n.arguments.len
    while max > 0:
        vm.codegen(n.arguments[max - 1]) # This pushes every argument into the stack
        max.dec
    # vm.add(PUSHINST) # Push the number of arguments
    # vm.add(VALUEINST, NumberValue(value: float(n.arguments.len)))
    vm.codegen(n.callee) # The caller function
    vm.add(CALLINST) # Call instruction

method codegen*(vm: VM, n: SimpleFunction) =
    let startLabel, endLabel = vm.tempLabel
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: startLabel))
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: endLabel))
    vm.add(FUNINST) # This will pop last 2 values to know the startLabel and theEndLabel
    vm.add(LABELINST, StringValue(value: startLabel))
    # Function start
    # We first get the arguments and we assign them to the variables
    for i in n.arguments:
        vm.add(STOREINST)
        vm.add(VALUEINST, StringValue(value: i.lexeme))
    vm.codegen(n.expression)
    vm.add(RETURNINST)
    # Function end
    vm.add(LABELINST, StringValue(value: endLabel))