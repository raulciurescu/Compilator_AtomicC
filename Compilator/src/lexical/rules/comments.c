#include "lexical/rules/comments.h"
#include <string.h>

extern Token tokenList[];
extern int tokenCount;

bool checkComment(FILE* f, char firstChar, int* line) {
    if (firstChar != '/')
        return false;

    int ch = fgetc(f);
    if (ch == '/') {
        // LINE COMMENT
        char buffer[512];
        int idx = 0;
        buffer[idx++] = '/';
        buffer[idx++] = '/';

        while ((ch = fgetc(f)) != EOF && ch != '\n' && ch != '\r') {
            buffer[idx++] = ch;
        }

        buffer[idx] = '\0';
        if (ch == '\n') (*line)++;  // contează linia

        Token t;
        strcpy(t.lexeme, buffer);
        t.type = TOKEN_LINE_COMMENT;
        t.line = *line;
        tokenList[tokenCount++] = t;
        return true;
    } else if (ch == '*') {
        // BLOCK COMMENT
        char buffer[1024];
        int idx = 0;
        buffer[idx++] = '/';
        buffer[idx++] = '*';

        int prev = 0;
        while ((ch = fgetc(f)) != EOF) {
            buffer[idx++] = ch;

            if (ch == '\n') (*line)++;

            if (prev == '*' && ch == '/') {
                buffer[idx] = '\0';
                Token t;
                strcpy(t.lexeme, buffer);
                t.type = TOKEN_COMMENT;
                t.line = *line;
                tokenList[tokenCount++] = t;
                return true;
            }

            prev = ch;
        }

        return false; // dacă nu se închide
    } else {
        // Not a comment: dă ch înapoi
        if (ch != EOF) ungetc(ch, f);
        return false;
    }
}
