#include "lexical/rules/keywords.h"

extern Token tokenList[];
extern int tokenCount;

const char* keywords[] = {
    "break", "char", "double", "else", "for",
    "if", "int", "return", "struct", "void", "while","float","bool"
};

const int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

bool checkKeyword(FILE* f, char firstChar, int line) {
    char buffer[256];
    int idx = 0;

    if (!isalpha(firstChar))
        return false;

    buffer[idx++] = firstChar;

    int ch;
    while ((ch = fgetc(f)) != EOF && (isalnum(ch) || ch == '_')) {
        buffer[idx++] = ch;
    }

    buffer[idx] = '\0';

    if (ch != EOF)
        ungetc(ch, f);

    // verificăm dacă este keyword
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(buffer, keywords[i]) == 0) {
            Token t;
            strcpy(t.lexeme, buffer);
            t.type = TOKEN_KEYWORD;
            t.line = line;
            tokenList[tokenCount++] = t;
            return true;
        }
    }

    // ❗ Dacă NU e keyword → punem înapoi în fișier caracterele în ordine inversă
    for (int i = idx - 1; i >= 1; i--) {
        ungetc(buffer[i], f);
    }

    // returnăm false → va încerca checkIdentifier
    return false;
}
