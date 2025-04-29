#ifndef UTILS_H
#define UTILS_H

#include "Token.h"

extern int currentToken;

Token peek();
Token peekAhead(int k);
void advance();
int match(TokenType type);
int matchLexeme(const char* lexeme);
void backtrack(int k);
int isAtEnd();
void syntaxError(const char* message);

#endif
