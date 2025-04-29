#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <stdio.h>
#include <stdbool.h>   
#include <ctype.h>
#include <string.h> 
#include "token.h"



/*
 * Regula pentru identificatori (ID):
 * ID: [a-zA-Z_] [a-zA-Z0-9_]*
 */

/**
 * @brief Testează afișarea legată de identificatori.
 *
 * @param a Valoare întreagă pentru afișare.
 */

bool checkIdentifier(FILE* f, char firstChar, int line);

#endif // IDENTIFIERS_H