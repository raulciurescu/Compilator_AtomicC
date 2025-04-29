#include "lexical/lexer.h"

void lexerPopulate(const char* filename) 
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Eroare la deschiderea fișierului");
        return;
    }

    int ch;
    int line = 1;

    while ((ch = fgetc(f)) != EOF) {
        // Ignoră spații/taburi
        if (ch == ' ' || ch == '\t' || ch == '\r')
            continue;

        // Crește linia la newline
        if (ch == '\n') {
            line++;
            continue;
        }

        // Verifică dacă e comentariu
        if (checkComment(f, ch, &line)) {
            continue;
        }

        // Verifică keyword
        if (checkKeyword(f, ch, line)) {
            continue;
        }

        // Verifică identificator
        if (checkIdentifier(f, ch, line)) {
            continue;
        }

        // Verifică constantă
        if (checkConstant(f, ch, line)) {
            continue;
        }

        // Verifică operator
        if (checkOperator(f, ch, line)) {
            continue;
        }

        // Verifică delimitator
        if (checkDelimiter(ch, line)) {
            continue;
        }

        // Dacă nimic nu s-a potrivit, e caracter necunoscut
        printf("Caracter necunoscut: '%c' (ASCII: %d) la linia %d\n", ch, ch, line);
    }

    fclose(f);
}
