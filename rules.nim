import tokens, typetraits

type
    #[
        Expressions
    ]#

    LiteralKind* = enum
        lkNumber, lkText, lkTruth, lkNone

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

    #[
        Statements
    ]#
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

method `$`*(expression: Expr): string {.base.} = "(Expression)"

method `$`*(expression: Binary): string =
    return "(" & $expression.left & " " & expression.operator.lexeme & " " & $expression.right & ")"

method `$`*(expression: Variable): string =
    return "( var " & $expression.name & ")"

method `$`*(expression: Unary): string =
    return "(" & expression.operator.lexeme & " " & $expression.right & ")"

method `$`*(expression: Grouping): string =
    return "(" & $expression.expression & ")"

method `$`*(expression: Literal): string =
    result = "("
    case expression.kind
    of lkNumber: result &= $expression.numValue
    of lkText: result &= expression.textValue
    of lkTruth: result &= $expression.truthValue
    else: discard
    result &= ")"

method `$`*(statement: Stmt): string {.base.} = "(Statement)"

method `$`*(statement: ExprStmt): string = "(" & $statement.expression & ")"

method `$`*(statement: ShowStmt): string = "(" & $statement.expression & ")"

method `$`*(statement: VarStmt): string = "(" & $statement.name.lexeme & " = " & $statement.initializer & ")"

method `$`*(statement: Block): string =
    result = "{"
    for s in statement.statements:
        result &= $s
    result &= "}"

method `$`*(statement: IfStmt): string =
    result = "(" & $statement.condition & " ? " & $statement.thenBranch & " : " & $statement.elseBranch & ")"

method `$`*(statement: WhileStmt): string =
    result = "( WHILE " & $statement.condition & " DO " & $statement.body & ")"