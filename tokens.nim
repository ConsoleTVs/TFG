type
    Tokens* = enum
        # Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN,
        COMMA, DOT, COLON, SEMICOLON
        MINUS, PLUS, SLASH, STAR,

        # One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        # Literals.
        IDENTIFIER, TEXT, NUMBER,

        # Keywords.
        AND, OR, TRUE, FALSE, ACTION, IF, ELSE,
        NONE, RETURN, FOR, WHILE, SHOW, VAR

        EOF

    Token* = object of RootObj
        kind*: Tokens
        lexeme*: string
        value*: string
        line*: int