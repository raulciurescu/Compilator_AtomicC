#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "syntax/ast.h"

ASTNode* parseStatement();
ASTNode* parseDeclaration();
ASTNode* parseAssignment();
ASTNode* parseIf();
ASTNode* parseWhile();
ASTNode* parseFor();
ASTNode* parseReturn();
ASTNode* parseFunctionCall(const char* name);
ASTNode* parseStructDefinition();


#endif
