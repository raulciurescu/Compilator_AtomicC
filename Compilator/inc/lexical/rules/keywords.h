#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"

/*
 * Lista de cuvinte cheie:
 * BREAK:   'break'
 * CHAR:    'char'
 * DOUBLE:  'double'
 * ELSE:    'else'
 * FOR:     'for'
 * IF:      'if'
 * INT:     'int'
 * RETURN:  'return'
 * STRUCT:  'struct'
 * VOID:    'void'
 * WHILE:   'while'
 */

 extern const char* keywords[];  
 extern const int keyword_count;
 


bool checkKeyword(FILE* f, char firstChar, int line);

#endif // KEYWORDS_H