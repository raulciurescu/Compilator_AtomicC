#ifndef DELIMITERS_H
#define DELIMITERS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"


/*
 * Lista de delimitatori:
 * COMMA:      ','
 * SEMICOLON:  ';'
 * LPAR:       '('
 * RPAR:       ')'
 * LBRACKET:   '['
 * RBRACKET:   ']'
 * LACC:       '{'
 * RACC:       '}'
 */

 bool checkDelimiter(char ch, int line);

#endif // DELIMITERS_H
