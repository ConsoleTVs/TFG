import tokens, typetraits

type
    LiteralKind* = enum
        lkNumber, lkText, lkBoolean, lkNone

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
        of lkBoolean: boolValue*: bool
        else: discard

method `$`*(expression: Expr): string {.base.} = return "(Expression)"

method `$`*(expression: Binary): string =
    return "(" & $expression.left & " " & expression.operator.lexeme & " " & $expression.right & ")"

method `$`*(expression: Unary): string =
    return "(" & expression.operator.lexeme & " " & $expression.right & ")"

method `$`*(expression: Grouping): string =
    return "(" & $expression.expression & ")"

method `$`*(expression: Literal): string =
    result = "("
    case expression.kind
    of lkNumber: result &= $expression.numValue
    of lkText: result &= expression.textValue
    of lkBoolean: result &= $expression.boolValue
    else: discard
    result &= ")"