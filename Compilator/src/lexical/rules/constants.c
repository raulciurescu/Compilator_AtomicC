#include "lexical/rules/constants.h"
#include <string.h>
#include <ctype.h>

extern Token tokenList[];
extern int tokenCount;

bool checkConstant(FILE* f, char firstChar, int line) {
    char buffer[256];
    int idx = 0;

    // ------------------------------
    // CONSTANTĂ CHAR: 'x' sau '\n'
    // ------------------------------
    if (firstChar == '\'') {
        buffer[idx++] = firstChar;
        int ch = fgetc(f);

        if (ch == '\\') {
            buffer[idx++] = ch;
            ch = fgetc(f);
            if (ch == EOF) return false;

            // ✅ doar escape-uri valide
            if (strchr("abfnrtv'\"\\0", ch) == NULL)
                return false;

            buffer[idx++] = ch;
        } else {
            if (ch == EOF || ch == '\'') return false;
            buffer[idx++] = ch;
        }

        ch = fgetc(f);
        if (ch != '\'') return false;

        buffer[idx++] = ch;
        buffer[idx] = '\0';

        Token t;
        strcpy(t.lexeme, buffer);
        t.type = TOKEN_CONSTANT_CHAR;
        t.line = line;
        tokenList[tokenCount++] = t;
        return true;
    }

    // ------------------------------
    // CONSTANTĂ STRING: "text"
    // ------------------------------
    if (firstChar == '\"') {
        buffer[idx++] = firstChar;
        int ch;

        while ((ch = fgetc(f)) != EOF && ch != '\"') {
            buffer[idx++] = ch;
        }

        if (ch == '\"') {
            buffer[idx++] = ch;
            buffer[idx] = '\0';

            Token t;
            strcpy(t.lexeme, buffer);
            t.type = TOKEN_CONSTANT_STRING;
            t.line = line;
            tokenList[tokenCount++] = t;
            return true;
        }

        return false;
    }

    // ------------------------------
    // CONSTANTE NUMERICE
    // ------------------------------
    if (isdigit(firstChar)) {
        int ch;
        buffer[idx++] = firstChar;

        ch = fgetc(f);
        if (firstChar == '0' && (ch == 'x' || ch == 'X')) {
            // HEXADECIMAL
            buffer[idx++] = ch;
            while ((ch = fgetc(f)) != EOF && isxdigit(ch)) {
                buffer[idx++] = ch;
            }

            buffer[idx] = '\0';
            if (ch != EOF) ungetc(ch, f);

            Token t;
            strcpy(t.lexeme, buffer);
            t.type = TOKEN_CONSTANT_HEXADECIMAL;
            t.line = line;
            tokenList[tokenCount++] = t;
            return true;
        } else {
            if (ch != EOF) ungetc(ch, f);
        }

        // Citim restul cifrelor (posibil zecimal/octal)
        while ((ch = fgetc(f)) != EOF && isdigit(ch)) {
            buffer[idx++] = ch;
        }

        // Verificăm dacă e octal
        if (firstChar == '0' && idx > 1) {
            bool isOctal = true;
            for (int i = 1; i < idx; i++) {
                if (buffer[i] < '0' || buffer[i] > '7') {
                    isOctal = false;
                    break;
                }
            }

            if (isOctal) {
                buffer[idx] = '\0';
                if (ch != EOF) ungetc(ch, f);
                Token t;
                strcpy(t.lexeme, buffer);
                t.type = TOKEN_CONSTANT_OCTAL;
                t.line = line;
                tokenList[tokenCount++] = t;
                return true;
            }
        }

        // Verificăm dacă e real
        bool isReal = false;
        if (ch == '.') {
            isReal = true;
            buffer[idx++] = ch;
            while ((ch = fgetc(f)) != EOF && isdigit(ch)) {
                buffer[idx++] = ch;
            }
        }

        if (ch == 'e' || ch == 'E') {
            isReal = true;
            buffer[idx++] = ch;

            ch = fgetc(f);
            if (ch == '+' || ch == '-') {
                buffer[idx++] = ch;
                ch = fgetc(f);
            }

            while (isdigit(ch)) {
                buffer[idx++] = ch;
                ch = fgetc(f);
            }
        }

        buffer[idx] = '\0';
        if (ch != EOF) ungetc(ch, f);

        Token t;
        strcpy(t.lexeme, buffer);
        t.type = isReal ? TOKEN_CONSTANT_REAL : TOKEN_CONSTANT_DECIMAL;
        t.line = line;
        tokenList[tokenCount++] = t;
        return true;
    }

    return false;
}
