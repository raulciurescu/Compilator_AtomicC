#include "syntax/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern Token tokenList[1000];
extern int tokenCount;
// extern – definit în alt fișier (parser.c)
extern int currentToken;

Token peek() {
    return tokenList[currentToken];
}

Token peekAhead(int k) {
    if (currentToken + k < tokenCount)
        return tokenList[currentToken + k];
    Token t = {TOKEN_UNKNOWN, "EOF", -1};
    return t;
}

void advance() {
    if (currentToken < tokenCount)
        currentToken++;
}

int match(TokenType type) {
    if (peek().type == type) {
        advance();
        return 1;
    }
    return 0;
}

int matchLexeme(const char* lexeme) {
    if (strcmp(peek().lexeme, lexeme) == 0) {
        advance();
        return 1;
    }
    return 0;
}

void backtrack(int k) {
    currentToken -= k;
    if (currentToken < 0) currentToken = 0;
}

int isAtEnd() {
    return currentToken >= tokenCount;
}

void syntaxError(const char* message) {
    Token t = peek();
    printf("[Syntax Error] at token %d (line %d): %s → '%s'\n",
           currentToken, t.line, message, t.lexeme);
    exit(1);
}
