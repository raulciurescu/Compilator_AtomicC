#include "lexical/rules/operators.h"
#include <string.h>

extern Token tokenList[];
extern int tokenCount;

bool checkOperator(FILE* f, char firstChar, int line) {
    char buffer[3] = {0};
    buffer[0] = firstChar;

    int ch2 = fgetc(f);
    if (ch2 != EOF) {
        buffer[1] = ch2;
        buffer[2] = '\0';
    }

    const char* multiCharOperators[] = {
        "==", "!=", "<=", ">=", "&&", "||"
    };

    for (int i = 0; i < sizeof(multiCharOperators) / sizeof(multiCharOperators[0]); i++) {
        if (strcmp(buffer, multiCharOperators[i]) == 0) {
            Token t;
            strcpy(t.lexeme, buffer);
            t.type = TOKEN_OPERATOR;
            t.line = line;
            tokenList[tokenCount++] = t;
            return true;
        }
    }

    // Dacă nu e compus, verificăm doar primul caracter
    if (ch2 != EOF) ungetc(ch2, f);
    buffer[1] = '\0';

    const char* singleCharOperators = "+-*/.=!<>";
    if (strchr(singleCharOperators, firstChar)) {
        Token t;
        strcpy(t.lexeme, buffer);
        t.type = TOKEN_OPERATOR;
        t.line = line;
        tokenList[tokenCount++] = t;
        return true;
    }

    return false;
}
