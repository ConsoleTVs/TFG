import tokens

#[
    Base declaraions
]#
type
    Expression* = ref object of RootObj
    Statement* = ref object of RootObj

#[
    Expression rules
]#

type
    Number* = ref object of Expression
        value*: float

    String* = ref object of Expression
        value*: string

    Boolean* = ref object of Expression
        value*: bool

    List* = ref object of Expression
        values*: seq[Expression]

    None* = ref object of Expression

    Group* = ref object of Expression
        expression*: Expression

    Unary* = ref object of Expression
        operator*: Token
        right*: Expression

    Binary* = ref object of Expression
        operator*: Token
        left*, right*: Expression

    Variable* = ref object of Expression
        name*: Token

    Assign* = ref object of Expression
        name*: Token
        value*: Expression

    Logical* = ref object of Expression
        operator*: Token
        left*, right*: Expression

    Call* = ref object of Expression
        callee*: Expression
        paren*: Token
        arguments*: seq[Expression]

method `$`*(t: Expression): string {.base.} = "Expression()"

method `$`*(t: Number): string = "Number(" & $t.value & ")"

method `$`*(t: String): string = "String(" & $t.value & ")"

method `$`*(t: Boolean): string = "Boolean(" & $t.value & ")"

method `$`*(t: List): string =
    result = "List("
    for i in t.values:
        result &= $i & ", "
    result &= ")"

method `$`*(t: None): string = "None()"

method `$`*(t: Group): string = "Group(" & $t.expression & ")"

method `$`*(t: Unary): string = "Unary(" & $t.operator.lexeme & ", " & $t.right & ")"

method `$`*(t: Binary): string = "Binary(" & $t.left & ", " & $t.operator.lexeme & ", " & $t.right & ")"

method `$`*(t: Variable): string = "Variable(" & $t.name.lexeme & ")"

method `$`*(t: Assign): string = "Assign(" & $t.name.lexeme & ", " & $t.value & ")"

method `$`*(t: Logical): string = "Logical(" & $t.left & ", " & $t.operator.lexeme & ", " & $t.right & ")"

method `$`*(t: Call): string =
    result = "Call(" & $t.callee & ", ["
    for i in t.arguments:
        result &= $i & ", "
    result &= "])"

#[
    Statemets
]#

type

    ExpressionStatement* = ref object of Statement
        expression*: Expression

    Print* = ref object of Statement
        expression*: Expression

    Block* = ref object of Statement
        body*: seq[Statement]

    If* = ref object of Statement
        condition*: Expression
        thenBranch*, elseBranch*: Block

    SimpleIf* = ref object of Statement
        condition*: Expression
        expression*: Expression

    While* = ref object of Statement
        condition*: Expression
        body*: Block

    Return* = ref object of Statement
        keyword*: Token
        value*: Expression

method `$`*(t: Statement): string {.base.} = "Statement()"

method `$`*(t: ExpressionStatement): string = "ExpressionStatement(" & $t.expression & ")"

method `$`*(t: Print): string = "Print(" & $t.expression & ")"

method `$`*(t: Block): string =
    result = "Block("
    for i in t.body:
        result &= $i & ", "
    result &= ")"

method `$`*(t: If): string =
    result = "If(" & $t.condition & ", " & $t.thenBranch
    if t.elseBranch != nil:
        result &= ", " & $t.elseBranch
    result &= ")"

method `$`*(t: SimpleIf): string = "SimpleIf(" & $t.condition & ", " & $t.expression & ")"

method `$`*(t: While): string = "While(" & $t.condition & ", " & $t.body & ")"

method `$`*(t: Return): string = "Return(" & $t.value & ")"

#[
    Special expressions
]#
type
    Function* = ref object of Expression
        arguments*: seq[Token]
        body*: Block

    SimpleFunction* = ref object of Expression
        arguments*: seq[Token]
        expression*: Expression

method `$`*(t: Function): string =
    result = "Function(["
    for i in t.arguments:
        result &= i.lexeme & ", "
    result &= "], " & $t.body & ")"

method `$`*(t: SimpleFunction): string =
    result = "SimpleFunction(["
    for i in t.arguments:
        result &= i.lexeme & ", "
    result &= "], " & $t.expression & ")"