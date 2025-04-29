#ifndef AST_H
#define AST_H

#define MAX_CHILDREN 10

typedef struct ASTNode {
    const char* type;
    const char* value;
    struct ASTNode* children[MAX_CHILDREN];
    int childCount;
} ASTNode;

ASTNode* createNode(const char* type, const char* value);
void addChild(ASTNode* parent, ASTNode* child);
void printAST(ASTNode* node, int depth);
void freeAST(ASTNode* node);
void generateDOT(ASTNode* root, const char* filename);

#endif
