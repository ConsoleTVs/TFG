type
    Kinds* = enum
        TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT, # + - * / %
        TOK_LEFT_PAREN, TOK_RIGHT_PAREN, # ( )
        TOK_LEFT_SPAREN, TOK_RIGHT_SPAREN, # [ ]
        TOK_LEFT_BRACE, TOK_RIGHT_BRACE, # { }
        TOK_COMMA, TOK_DOT, TOK_COLON, TOK_SEMICOLON # , . : ;
        TOK_EQUAL, TOK_EQUAL_EQUAL, TOK_BANG, TOK_BANG_EQUAL, # = == ! !=
        TOK_GREATER, TOK_GREATER_EQUAL, TOK_LESS, TOK_LESS_EQUAL, # > >= < <=
        TOK_SIMPLE_ARROW, TOK_ARROW # -> =>

        TOK_IDENTIFIER, TOK_STRING, TOK_NUMBER, # [a-zA-Z][a-zA-Z0-9_]* ".*" [0-9]+(\.[0-9]*)?(e[0-9]+)?
        TOK_AND, TOK_OR, TOK_TRUE, TOK_FALSE, TOK_IF, TOK_ELSE, # and or true false if else
        TOK_NONE, TOK_RETURN, TOK_FOR, TOK_WHILE, TOK_PRINT # none return for while print

        TOK_EOF # End Of File

    Token* = tuple
        kind: Kinds
        line: int
        lexeme, value: string

proc newToken*(kind: Kinds, line: int, lexeme, value: string = nil): Token =
    result.kind = kind
    result.line = line
    result.lexeme = lexeme
    result.value = value