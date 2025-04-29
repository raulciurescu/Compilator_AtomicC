#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "syntax/ast.h"

ASTNode* parseExpression();
ASTNode* parseLogicalOr();
ASTNode* parseLogicalAnd();
ASTNode* parseEquality();
ASTNode* parseRelational();
ASTNode* parseAdditive();
ASTNode* parseMultiplicative();
ASTNode* parseAccess();
ASTNode* parsePrimary();

#endif
