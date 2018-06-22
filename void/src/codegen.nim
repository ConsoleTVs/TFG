import rules, instructions, values, tokens, vm, typetraits

method codegen*(vm: VM, e: Expression) {.base.} = vm.program.add(Instruction())
method codegen*(vm: VM, e: Statement) {.base.} = vm.program.add(Instruction())
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
        of TOK_MINUS: vm.program.add(SubstractionInst())
        of TOK_STAR: vm.program.add(MultiplicationInst())
        of TOK_SLASH: vm.program.add(DivisionInst())
        else :
            echo "Error generating code for a binary operator"
            quit()