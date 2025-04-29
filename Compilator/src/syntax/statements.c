// ✅ statements.c - versiune COMPLETĂ cu suport total pentru arrays și apeluri funcție

#include "syntax/statements.h"
#include "syntax/utils.h"
#include "syntax/expressions.h"
#include "syntax/ast.h"
#include <stdio.h>
#include <string.h>

ASTNode* parseStatement() {
    Token t = peek();

    if (t.type == TOKEN_KEYWORD) {
        if (strcmp(t.lexeme, "struct") == 0) {
            Token next = peekAhead(2);
            if (strcmp(next.lexeme, "{") == 0) {
                return parseStructDefinition();
            } else {
                return parseDeclaration();
            }
        } else if (strcmp(t.lexeme, "int") == 0 || strcmp(t.lexeme, "float") == 0 ||
                   strcmp(t.lexeme, "char") == 0 || strcmp(t.lexeme, "bool") == 0) {
            return parseDeclaration();
        } else if (strcmp(t.lexeme, "if") == 0) {
            return parseIf();
        } else if (strcmp(t.lexeme, "while") == 0) {
            return parseWhile();
        } else if (strcmp(t.lexeme, "for") == 0) {
            return parseFor();
        } else if (strcmp(t.lexeme, "return") == 0) {
            return parseReturn();
        }
    }

    if (t.type == TOKEN_IDENTIFIER) {
        Token next = peekAhead(1);
        if (strcmp(next.lexeme, "(") == 0) {
            ASTNode* call = parseFunctionCall(t.lexeme);
            if (!matchLexeme(";")) syntaxError("Expected ';' after function call");
            return call;
        } else {
            return parseAssignment();
        }
    }

    syntaxError("Unrecognized statement");
    return NULL;
}

ASTNode* parseFor() {
    match(TOKEN_KEYWORD); // "for"
    if (!matchLexeme("(")) syntaxError("Expected '(' after 'for'");

    ASTNode* init = NULL;
    if (!matchLexeme(";")) {
        init = parseExpression();
        if (!matchLexeme(";")) syntaxError("Expected ';' after initialization");
    }

    ASTNode* cond = NULL;
    if (!matchLexeme(";")) {
        cond = parseExpression();
        if (!matchLexeme(";")) syntaxError("Expected ';' after condition");
    }

    ASTNode* update = NULL;
    if (!matchLexeme(")")) {
        update = parseExpression();
        if (!matchLexeme(")")) syntaxError("Expected ')' after update");
    }

    ASTNode* body;
if (matchLexeme("{")) {
    body = createNode("Block", NULL);
    while (!matchLexeme("}")) {
        addChild(body, parseStatement());
    }
} else {
    body = parseStatement();
}


    ASTNode* node = createNode("For", NULL);
    if (init) addChild(node, init);
    if (cond) addChild(node, cond);
    if (update) addChild(node, update);
    addChild(node, body);
    return node;
}

ASTNode* parseDeclaration() {
    Token typeToken = peek();
    match(TOKEN_KEYWORD);

    Token typeName = typeToken;

    if (strcmp(typeToken.lexeme, "struct") == 0) {
        Token structName = peek();
        match(TOKEN_IDENTIFIER);
        typeName = structName;
    }

    ASTNode* decl = createNode("Declaration", NULL);
    addChild(decl, createNode("Type", typeToken.lexeme));
    if (strcmp(typeToken.lexeme, "struct") == 0) {
        addChild(decl, createNode("StructType", typeName.lexeme));
    }

    do {
        Token idToken = peek();
        match(TOKEN_IDENTIFIER);

        ASTNode* idNode = createNode("Identifier", idToken.lexeme);

        if (matchLexeme("[")) {
            ASTNode* sizeExpr = parseExpression();
            if (!matchLexeme("]")) syntaxError("Expected ']' after array size");
            ASTNode* arrayDecl = createNode("Array", NULL);
            addChild(arrayDecl, idNode);
            addChild(arrayDecl, sizeExpr);
            addChild(decl, arrayDecl);
        } else {
            addChild(decl, idNode);
        }
    } while (matchLexeme(","));

    if (!matchLexeme(";")) syntaxError("Expected ';' after declaration");

    return decl;
}

ASTNode* parseAssignment() {
    Token idToken = peek();
    match(TOKEN_IDENTIFIER);

    ASTNode* target;

    if (matchLexeme("[")) {
        ASTNode* array = createNode("ArrayAccess", NULL);
        ASTNode* id = createNode("Identifier", idToken.lexeme);
        ASTNode* index = parseExpression();
        if (!matchLexeme("]")) syntaxError("Expected ']' after array index");
        addChild(array, id);
        addChild(array, index);
        target = array;
    } else {
        target = createNode("Identifier", idToken.lexeme);
    }

    if (!matchLexeme("=")) syntaxError("Expected '='");

    ASTNode* node = createNode("Assignment", NULL);
    addChild(node, target);
    addChild(node, parseExpression());

    if (!matchLexeme(";")) syntaxError("Expected ';'");
    return node;
}

ASTNode* parseIf() {
    match(TOKEN_KEYWORD);
    if (!matchLexeme("(")) syntaxError("Expected '(' after if");
    ASTNode* condition = parseExpression();
    if (!matchLexeme(")")) syntaxError("Expected ')' after condition");

    ASTNode* thenBranch;
    if (matchLexeme("{")) {
        ASTNode* block = createNode("Block", NULL);
        while (!matchLexeme("}")) {
            addChild(block, parseStatement());
        }
        thenBranch = block;
    } else {
        thenBranch = parseStatement();
    }

    ASTNode* elseBranch = NULL;
    if (matchLexeme("else")) {
        if (matchLexeme("{")) {
            ASTNode* block = createNode("Block", NULL);
            while (!matchLexeme("}")) {
                addChild(block, parseStatement());
            }
            elseBranch = block;
        } else {
            elseBranch = parseStatement();
        }
    }

    ASTNode* node = createNode("If", NULL);
    addChild(node, condition);
    addChild(node, thenBranch);
    if (elseBranch) addChild(node, elseBranch);
    return node;
}

ASTNode* parseWhile() {
    match(TOKEN_KEYWORD);
    if (!matchLexeme("(")) syntaxError("Expected '('");
    ASTNode* cond = parseExpression();
    if (!matchLexeme(")")) syntaxError("Expected ')'");

    if (!matchLexeme("{")) syntaxError("Expected '{'");
    ASTNode* body = createNode("Block", NULL);
    while (!matchLexeme("}")) {
        addChild(body, parseStatement());
    }

    ASTNode* node = createNode("While", NULL);
    addChild(node, cond);
    addChild(node, body);
    return node;
}

ASTNode* parseReturn() {
    match(TOKEN_KEYWORD);
    ASTNode* expr = parseExpression();
    if (!matchLexeme(";")) syntaxError("Expected ';'");

    ASTNode* node = createNode("Return", NULL);
    addChild(node, expr);
    return node;
}

ASTNode* parseFunctionCall(const char* name) {
    matchLexeme("(");

    ASTNode* func = createNode("FunctionCall", name);

    if (!matchLexeme(")")) {
        do {
            ASTNode* arg = parseExpression();
            addChild(func, arg);
        } while (matchLexeme(","));

        if (!matchLexeme(")")) syntaxError("Expected ')' after function arguments");
    }

    return func;
}

ASTNode* parseStructDefinition() {
    match(TOKEN_KEYWORD);
    Token name = peek();
    match(TOKEN_IDENTIFIER);

    if (!matchLexeme("{")) syntaxError("Expected '{' in struct definition");

    ASTNode* structNode = createNode("Struct", name.lexeme);

    while (!matchLexeme("}")) {
        Token type = peek();
        match(TOKEN_KEYWORD);

        ASTNode* declList = createNode("FieldList", NULL);

        do {
            Token id = peek();
            match(TOKEN_IDENTIFIER);
            addChild(declList, createNode("Field", id.lexeme));
        } while (matchLexeme(","));

        if (!matchLexeme(";")) syntaxError("Expected ';' in struct field list");

        ASTNode* fieldType = createNode("Type", type.lexeme);
        addChild(fieldType, declList);
        addChild(structNode, fieldType);
    }

    if (!matchLexeme(";")) syntaxError("Expected ';' after struct definition");

    return structNode;
}
