#include "syntax/parser.h"
#include "syntax/utils.h"
#include "syntax/statements.h"
#include "syntax/functions.h"
#include "syntax/ast.h"
#include <stdio.h>
#include <string.h>

int currentToken = 0;

ASTNode* parse() {
    ASTNode* program = createNode("Program", NULL);

    while (!isAtEnd()) {
        Token t = peek();

        if (t.type == TOKEN_KEYWORD && (
            strcmp(t.lexeme, "int") == 0 ||
            strcmp(t.lexeme, "float") == 0 ||
            strcmp(t.lexeme, "char") == 0 ||
            strcmp(t.lexeme, "bool") == 0 ||
            strcmp(t.lexeme, "void") == 0
        )) {
            Token next = peekAhead(2);
            if (strcmp(next.lexeme, "(") == 0) {
                addChild(program, parseFunctionDefinition());
                continue;
            }
        }

        addChild(program, parseStatement());
    }

    printf("[Syntactic Analysis] Success!\n");
    return program;
}
