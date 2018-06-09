import tokens, typetraits, sequtils, future

#[
    Expressions
]#
type
    LiteralKind* = enum
        lkNone, lkNumber, lkText, lkTruth

    Expr* = ref object of RootObj

    Binary* = ref object of Expr
        operator*: Token
        left*, right*: Expr

    Unary* = ref object of Expr
        operator*: Token
        right*: Expr

    Grouping* = ref object of Expr
        expression*: Expr

    Literal* = ref object of Expr
        case kind*: LiteralKind
        of lkNumber: numValue*: float
        of lkText: textValue*: string
        of lkTruth: truthValue*: bool
        else: discard

    Variable* = ref object of Expr
        name*: Token

    Assign* = ref object of Expr
        name*: Token
        value*: Expr

    Logical* = ref object of Expr
        operator*: Token
        left*, right*: Expr

    Call* = ref object of Expr
        callee*: Expr
        paren*: Token
        arguments*: seq[Expr]

method `$`*(expression: Expr): string {.base.} = "Expression()"

method `$`*(expression: Binary): string =
    return "Binary(" & $expression.left & ", " & expression.operator.lexeme & ", " & $expression.right & ")"

method `$`*(expression: Unary): string = "Unary(" & expression.operator.lexeme & ", " & $expression.right & ")"

method `$`*(expression: Grouping): string = "Grouping(" & $expression.expression & ")"

method `$`*(expression: Literal): string =
    result = "Literal("
    case expression.kind
    of lkNumber: result &= $expression.numValue
    of lkText: result &= expression.textValue
    of lkTruth: result &= $expression.truthValue
    else: discard
    result &= ")"

method `$`*(expression: Variable): string = "Var(" & $expression.name.lexeme & ")"

method `$`*(expression: Assign): string = "Assign(" & expression.name.lexeme & ", " & $expression.value & ")"

method `$`*(expression: Logical): string =
    return "Logical(" & $expression.left & ", " & expression.operator.lexeme & ", " & $expression.right & ")"

method `$`*(expression: Call): string =
    return "Call()"

#[
    Statements
]#
type
    Stmt* = ref object of RootObj

    ExprStmt* = ref object of Stmt
        expression*: Expr

    ShowStmt* = ref object of Stmt
        expression*: Expr

    VarStmt* = ref object of Stmt
        name*: Token
        initializer*: Expr

    Block* = ref object of Stmt
        statements*: seq[Stmt]

    IfStmt* = ref object of Stmt
        condition*: Expr
        thenBranch*, elseBranch*: Stmt

    WhileStmt* = ref object of Stmt
        condition*: Expr
        body*: Stmt

    ActionStmt* = ref object of Stmt
        name*: Token
        parameters*: seq[Token]
        body*: seq[Stmt]

    ReturnStmt* = ref object of Stmt
        keyword*: Token
        value*: Expr

method `$`*(statement: Stmt): string {.base.} = "Statement()"

method `$`*(statement: ExprStmt): string = "Expression(" & $statement.expression & ")"

method `$`*(statement: ShowStmt): string = "Show(" & $statement.expression & ")"

method `$`*(statement: VarStmt): string = "VarDeclaration(" & $statement.name.lexeme & ", " & $statement.initializer & ")"

method `$`*(statement: Block): string =
    result = "{"
    for s in statement.statements:
        result &= $s
    result &= "}"

method `$`*(statement: IfStmt): string =
    return "If(" & $statement.condition & ", " & $statement.thenBranch & ",  " & $statement.elseBranch & ")"

method `$`*(statement: WhileStmt): string =
    return "While(" & $statement.condition & ", " & $statement.body & ")"

method `$`*(statement: ActionStmt): string =
    return "Action(" & $statement.name.lexeme & ", " & $statement.parameters.map((p) => p.lexeme) & ")"

method `$`*(statement: ReturnStmt): string = "Return(" & $statement.keyword & ")"