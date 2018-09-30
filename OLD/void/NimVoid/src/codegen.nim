import vm, instructions, values, rules, tokens
##[

    This module implements the code generation that takes place during AST to Bytecode
    transformation. This proces have some optimizations applied to it as such, called
    AST optimizations because they are done just before creating the bytecode.

    Current Optimizations:
        -   Dead code elimination (ExpressionStatement)
        -   Unreachable code elimination (Block)

]##

proc add*(vm: VM, kind: InstructionKind, value: Value = nil) = vm.program.add(newInstruction(kind, value))

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

method codegen*(vm: VM, n: ExpressionStatement) =
    # Eliminate redundant code (expressions that have no effect in the code)

    let ex = n.expression
    if ex of Number: return
    elif ex of String: return
    elif ex of Boolean: return
    elif ex of List: return
    elif ex of None: return
    elif ex of Group: return
    elif ex of Unary: return
    elif ex of Binary: return
    elif ex of Variable: return
    elif ex of Logical: return

    vm.codegen(n.expression)

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

method codegen*(vm: VM, n: AssignAccess) =
    vm.codegen(n.index)
    vm.codegen(n.value)
    vm.add(STOREACCESSINST)
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
    vm.add(PRINTINST)

method codegen*(vm: VM, n: Block) =
    for i in n.body:
        vm.codegen(i)
        if i of Return:
            break

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
    vm.add(PUSHINST)
    vm.add(VALUEINST, NumberValue(value: float(n.arguments.len))) # The number of arguments
    vm.add(FUNINST) # This will pop last 3 values to know the startLabel and theEndLabel and the number of arguments
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
    vm.add(PUSHINST)
    vm.add(VALUEINST, NumberValue(value: float(n.arguments.len)))
    vm.add(CALLINST) # Call instruction

method codegen*(vm: VM, n: SimpleFunction) =
    let startLabel, endLabel = vm.tempLabel
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: startLabel))
    vm.add(PUSHINST)
    vm.add(VALUEINST, StringValue(value: endLabel))
    vm.add(PUSHINST)
    vm.add(VALUEINST, NumberValue(value: float(n.arguments.len))) # The number of arguments
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

method codegen*(vm: VM, n: Access) =
    vm.codegen(n.index)
    vm.add(LOADINST)
    vm.add(VALUEINST, StringValue(value: n.item.lexeme))
    vm.add(ACCESSINST)
