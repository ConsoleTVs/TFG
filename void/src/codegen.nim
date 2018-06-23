import rules, instructions, values, tokens, vm, typetraits

method codegen*(vm: VM, e: Expression) {.base.} = vm.program.add(Instruction())
method codegen*(vm: VM, e: Statement) {.base.} = vm.program.add(Instruction())
method codegen*(vm: VM, e: Print) =
    vm.codegen(e.expression)
    vm.program.add(PrintInst())
method codegen*(vm: VM, e: ExpressionStatement) = vm.codegen(e.expression)
method codegen*(vm: VM, e: Number) = vm.program.add(PushInst(value: NumberValue(value: e.value)))
method codegen*(vm: VM, e: Group) = vm.codegen(e.expression)
method codegen*(vm: VM, e: Assign) =
    vm.codegen(e.value)
    vm.program.add(AssignInst(name: e.name.lexeme))
method codegen*(vm: VM, e: Variable) = vm.program.add(VariableInst(name: e.name.lexeme))
method codegen*(vm: VM, e: Block) =
    vm.program.add(PushScopeInst())
    for i in e.body:
        vm.codegen(i)
    vm.program.add(PopScopeInst())
method codegen*(vm: VM, e: Binary) =
    vm.codegen(e.left)
    vm.codegen(e.right)
    case e.operator.kind:
        of TOK_PLUS: vm.program.add(AdditionInst())
        of TOK_MINUS: vm.program.add(SubtractionInst())
        of TOK_STAR: vm.program.add(MultiplicationInst())
        of TOK_SLASH: vm.program.add(DivisionInst())
        of TOK_EQUAL_EQUAL: vm.program.add(EqualInst())
        of TOK_BANG_EQUAL: vm.program.add(NotEqualInst())
        of TOK_GREATER: vm.program.add(GreaterInst())
        of TOK_GREATER_EQUAL: vm.program.add(GreaterEqualInst())
        of TOK_LESS: vm.program.add(LessInst())
        of TOK_LESS_EQUAL: vm.program.add(LessEqualInst())
        else:
            echo "Error generating code for a binary operator"
            quit()
method codegen*(vm: VM, e: SimpleIf) =
    let (marker, markerNumber) = vm.createMarker
    vm.codegen(e.condition)
    vm.program.add(BranchNotInstruction(marker: markerNumber))
    vm.codegen(e.expression)
    vm.pushMarker(marker)

method codegen*(vm: VM, e: If) =
    if e.elseBranch != nil:
        # That means the if have then and else branch
        let
            (thenMarker, thenMarkerNumber) = vm.createMarker
            (endMarker, endMarkerNumber) = vm.createMarker
        vm.codegen(e.condition)
        vm.program.add(BranchInstruction(marker: thenMarkerNumber))
        vm.codegen(e.elseBranch)
        vm.program.add(JumpInst(marker: endMarkerNumber))
        vm.pushMarker(thenMarker)
        vm.codegen(e.thenBranch)
        vm.pushMarker(endMarker)
    else:
        # That means the if have only a then branch
        let
            (endMarker, endMarkerNumber) = vm.createMarker
        vm.codegen(e.condition)
        vm.program.add(BranchNotInstruction(marker: endMarkerNumber))
        vm.codegen(e.thenBranch)
        vm.pushMarker(endMarker)

method codegen*(vm: VM, e: While) =
    let
        (startMarker, startMarkerNumber) = vm.createMarker
        (endMarker, endMarkerNumber) = vm.createMarker
    vm.pushMarker(startMarker)
    vm.codegen(e.condition)
    vm.program.add(BranchNotInstruction(marker: endMarkerNumber))
    vm.codegen(e.body)
    vm.program.add(JumpInst(marker: startMarkerNumber))
    vm.pushMarker(endMarker)