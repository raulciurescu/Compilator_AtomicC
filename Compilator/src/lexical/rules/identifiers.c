#include "lexical/rules/identifiers.h"

extern Token tokenList[];
extern int tokenCount;

bool checkIdentifier(FILE* f, char firstChar, int line) {
    char buffer[256];
    int idx = 0;

    if (!isalpha(firstChar) && firstChar != '_')
        return false;

    buffer[idx++] = firstChar;

    int ch;
    while ((ch = fgetc(f)) != EOF && (isalnum(ch) || ch == '_')) {
        buffer[idx++] = ch;
    }

    buffer[idx] = '\0';

    if (ch != EOF)
        ungetc(ch, f); // pune caracterul înapoi

    // adaugă în tokenList[]
    Token t;
    strcpy(t.lexeme, buffer);
    t.type = TOKEN_IDENTIFIER;
    t.line = line;
    tokenList[tokenCount++] = t;

    return true;
}
