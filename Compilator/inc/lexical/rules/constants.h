#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "token.h"


/*
 * Lista de constante:
 * CT_INT:     [1-9][0-9]*        // zecimal
 *             | '0'[0-7]*        // octal
 *             | '0x'[0-9a-fA-F]+ // hexazecimal
 *
 * fragment EXP:     ( 'e' | 'E' ) ( '-' | '+' )? [0-9]+
 * CT_REAL:          [0-9]+ ( '.' [0-9]+ EXP? | ( '.' [0-9]+ )? EXP )
 *
 * fragment ESC:     '\\' [abfnrtv'?"\\0]
 * CT_CHAR:          ['] ( ESC | [^'\\] ) [']
 * CT_STRING:        ["] ( ESC | [^"\\] )* ["]
 */

 bool checkConstant(FILE* f, char firstChar, int line);

#endif // CONSTANTS_H