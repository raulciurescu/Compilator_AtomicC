#include "syntax/functions.h"
#include "syntax/utils.h"
#include "syntax/statements.h"
#include "syntax/ast.h"
#include <stdio.h>
#include <string.h>

ASTNode* parseFunctionDefinition() {
    Token returnType = peek();     // ex: int
    match(TOKEN_KEYWORD);

    Token funcName = peek();       // ex: main
    match(TOKEN_IDENTIFIER);

    if (!matchLexeme("(")) syntaxError("Expected '(' in function definition");

    // Ignorăm parametrii pentru moment
    while (!matchLexeme(")")) {
        advance();
    }

    if (!matchLexeme("{")) syntaxError("Expected '{' in function definition");

    ASTNode* block = createNode("Block", NULL);
    while (!matchLexeme("}")) {
        addChild(block, parseStatement());
    }

    ASTNode* funcNode = createNode("Function", funcName.lexeme);
    addChild(funcNode, createNode("ReturnType", returnType.lexeme));
    addChild(funcNode, block);

    return funcNode;
}
