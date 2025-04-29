#include "syntax/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode* createNode(const char* type, const char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->childCount = 0;
    return node;
}

void addChild(ASTNode* parent, ASTNode* child) {
    if (parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
    } else {
        printf("Too many children for node %s\n", parent->type);
    }
}

void printAST(ASTNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s", node->type);
    if (node->value) printf(" (%s)", node->value);
    printf("\n");

    for (int i = 0; i < node->childCount; i++) {
        printAST(node->children[i], depth + 1);
    }
}

void freeAST(ASTNode* node) {
    if (!node) return;
    for (int i = 0; i < node->childCount; i++) {
        freeAST(node->children[i]);
    }
    free((char*)node->type);
    if (node->value) free((char*)node->value);
    free(node);
}

static int nodeId = 0;

void generateDOTRec(ASTNode* node, FILE* file, int parentId) {
    if (!node) return;
    int myId = nodeId++;

    fprintf(file, "  node%d [label=\"%s", myId, node->type);
    if (node->value) fprintf(file, "\\n%s", node->value);
    fprintf(file, "\"];\n");

    if (parentId != -1) {
        fprintf(file, "  node%d -> node%d;\n", parentId, myId);
    }

    for (int i = 0; i < node->childCount; i++) {
        generateDOTRec(node->children[i], file, myId);
    }
}

void generateDOT(ASTNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Eroare la deschiderea fișierului .dot");
        return;
    }

    nodeId = 0;
    fprintf(file, "digraph AST {\n");
    fprintf(file, "  node [shape=box, style=filled, fillcolor=lightgray];\n");
    generateDOTRec(root, file, -1);
    fprintf(file, "}\n");

    fclose(file);
}
