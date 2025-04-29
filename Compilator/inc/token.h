#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_CONSTANT_DECIMAL,
    TOKEN_CONSTANT_OCTAL,
    TOKEN_CONSTANT_HEXADECIMAL,
    TOKEN_CONSTANT_REAL,
    TOKEN_CONSTANT_CHAR,
    TOKEN_CONSTANT_STRING,
    TOKEN_LINE_COMMENT,
    TOKEN_COMMENT,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];
    int line;
} Token;

extern Token tokenList[1000];  // vector global
extern int tokenCount;         // câți tokeni am

#endif // TOKEN_H
