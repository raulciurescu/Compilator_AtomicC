#ifndef OPERATORS_H
#define OPERATORS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"


/*
 * Listă de operatori comuni:
 * ADD:        '+'
 * SUB:        '-'
 * MUL:        '*'
 * DIV:        '/'
 * DOT:        '.'
 * AND:        '&&'
 * OR:         '||'
 * NOT:        '!'
 * ASSIGN:     '='
 * EQUAL:      '=='
 * NOTEQ:      '!='
 * LESS:       '<'
 * LESSEQ:     '<='
 * GREATER:    '>'
 * GREATEREQ:  '>='
 */

 bool checkOperator(FILE* f, char firstChar, int line);

#endif // OPERATORS_H