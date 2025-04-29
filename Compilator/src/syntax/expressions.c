#include "syntax/expressions.h"
#include "syntax/utils.h"
#include "syntax/ast.h"
#include <string.h>

ASTNode* parseExpression() {
    ASTNode* left = parseLogicalOr();

    while (matchLexeme("=")) {
        ASTNode* right = parseExpression();
        ASTNode* assign = createNode("=", NULL);
        addChild(assign, left);
        addChild(assign, right);
        left = assign;
    }

    return left;
}

ASTNode* parseLogicalOr() {
    ASTNode* node = parseLogicalAnd();

    while (matchLexeme("||")) {
        ASTNode* right = parseLogicalAnd();
        ASTNode* orNode = createNode("||", NULL);
        addChild(orNode, node);
        addChild(orNode, right);
        node = orNode;
    }

    return node;
}

ASTNode* parseLogicalAnd() {
    ASTNode* node = parseEquality();

    while (matchLexeme("&&")) {
        ASTNode* right = parseEquality();
        ASTNode* andNode = createNode("&&", NULL);
        addChild(andNode, node);
        addChild(andNode, right);
        node = andNode;
    }

    return node;
}



ASTNode* parseEquality() {
    ASTNode* node = parseRelational();

    while (peek().type == TOKEN_OPERATOR &&
          (strcmp(peek().lexeme, "==") == 0 || strcmp(peek().lexeme, "!=") == 0)) {
        Token op = peek();
        match(TOKEN_OPERATOR);
        ASTNode* right = parseRelational();
        ASTNode* newNode = createNode(op.lexeme, NULL);
        addChild(newNode, node);
        addChild(newNode, right);
        node = newNode;
    }

    return node;
}

ASTNode* parseRelational() {
    ASTNode* node = parseAdditive();

    while (peek().type == TOKEN_OPERATOR &&
          (strcmp(peek().lexeme, "<") == 0 || strcmp(peek().lexeme, "<=") == 0 ||
           strcmp(peek().lexeme, ">") == 0 || strcmp(peek().lexeme, ">=") == 0)) {
        Token op = peek();
        match(TOKEN_OPERATOR);
        ASTNode* right = parseAdditive();
        ASTNode* newNode = createNode(op.lexeme, NULL);
        addChild(newNode, node);
        addChild(newNode, right);
        node = newNode;
    }

    return node;
}

ASTNode* parseAdditive() {
    ASTNode* node = parseMultiplicative();

    while (peek().type == TOKEN_OPERATOR &&
          (strcmp(peek().lexeme, "+") == 0 || strcmp(peek().lexeme, "-") == 0)) {
        Token op = peek();
        match(TOKEN_OPERATOR);
        ASTNode* right = parseMultiplicative();
        ASTNode* newNode = createNode(op.lexeme, NULL);
        addChild(newNode, node);
        addChild(newNode, right);
        node = newNode;
    }

    return node;
}

ASTNode* parseMultiplicative() {
    ASTNode* node = parseAccess();

    while (peek().type == TOKEN_OPERATOR &&
          (strcmp(peek().lexeme, "*") == 0 || strcmp(peek().lexeme, "/") == 0)) {
        Token op = peek();
        match(TOKEN_OPERATOR);
        ASTNode* right = parseAccess();
        ASTNode* newNode = createNode(op.lexeme, NULL);
        addChild(newNode, node);
        addChild(newNode, right);
        node = newNode;
    }

    return node;
}

// 🔗 Accesare a.b, a[i], apel funcție
ASTNode* parseAccess() {
    ASTNode* node = parsePrimary();

    while (1) {
        if (matchLexeme(".")) {
            Token field = peek();
            match(TOKEN_IDENTIFIER);
            ASTNode* access = createNode("Access", field.lexeme);
            addChild(access, node);
            node = access;
        } else if (matchLexeme("[")) {
            ASTNode* index = parseExpression();
            if (!matchLexeme("]")) syntaxError("Expected ']'");
            ASTNode* array = createNode("ArrayAccess", NULL);
            addChild(array, node);
            addChild(array, index);
            node = array;
        } else if (matchLexeme("(")) {
            ASTNode* call = createNode("FuncCall", node->value);
            while (!matchLexeme(")")) {
                addChild(call, parseExpression());
                if (!matchLexeme(",")) break;
            }
            node = call;
        } else {
            break;
        }
    }

    return node;
}

ASTNode* parsePrimary() {
    Token t = peek();

    if (t.type == TOKEN_IDENTIFIER) {
        return parseAccess();
    } else if (match(TOKEN_CONSTANT_DECIMAL) || match(TOKEN_CONSTANT_REAL) ||
               match(TOKEN_CONSTANT_CHAR) || match(TOKEN_CONSTANT_STRING)) {
        return createNode("Constant", t.lexeme);
    } else if (matchLexeme("(")) {
        ASTNode* node = parseExpression();
        if (!matchLexeme(")")) syntaxError("Expected ')'");
        return node;
    }

    syntaxError("Invalid expression");
    return NULL;
}
