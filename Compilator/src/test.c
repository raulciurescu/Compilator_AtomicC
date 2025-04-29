#include "main.h"
#include <direct.h> // pentru _mkdir pe Windows

extern Token tokenList[1000];
extern int tokenCount;

void testLexerPopulate() {
    // Cream directoarele de output dacă nu există
    _mkdir("TesteRezultateTokeni");
    _mkdir("TesteRezultateAST");
    _mkdir("TesteRezultatePNG");

    char filename[32];
    char tokenFile[64];
    char dotFile[64];
    char pngCommand[128];

    for (int i = 0; i <= 9; i++) {
        sprintf(filename, "Teste/%d.c", i);
        sprintf(tokenFile, "TesteRezultateTokeni/tokens_%d.txt", i);
        sprintf(dotFile, "TesteRezultateAST/ast_%d.dot", i);

        printf("\n=== Procesare fisier: %s ===\n", filename);

        lexerPopulate(filename);

        FILE* fout = fopen(tokenFile, "w");
        if (!fout) {
            perror("Eroare la deschiderea fisierului Token.txt");
            return;
        }

        fprintf(fout, "\n==================== Tokeni identificati ====================\n");
        for (int j = 0; j < tokenCount; j++) {
            fprintf(fout, "Token[%d]: %-20s | Tip: %d | Linie: %d\n",
                j,
                tokenList[j].lexeme,
                tokenList[j].type,
                tokenList[j].line);
        }
        fprintf(fout, "============================================================\n");
        fclose(fout);

        printf("Tokenii au fost scrisi in: %s\n", tokenFile);

        ASTNode* root = parse();
        if (root != NULL) {
            generateDOT(root, dotFile);
            printf("  AST salvat în: %s\n", dotFile);

            // Generăm imagine PNG din DOT
            sprintf(pngCommand, "dot -Tpng %s -o TesteRezultatePNG/ast_%d.png", dotFile, i);
            system(pngCommand);
            printf("PNG generat in: TesteRezultatePNG/ast_%d.png\n", i);

            freeAST(root);
        } else {
            printf("Eroare la parsare pentru: %s\n", filename);
        }

        tokenCount = 0;
    }
}
