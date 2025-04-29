#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#include "token.h"
#include "rules/constants.h"
#include "rules/delimiters.h"
#include "rules/identifiers.h"
#include "rules/keywords.h"
#include "rules/operators.h"
#include "rules/comments.h"

/**
 * @brief Parcurge fișierul caracter cu caracter și afișează conținutul.
 *
 * @param filename Calea către fișierul sursă ce urmează a fi analizat.
 */
void lexerPopulate(const char* filename);

#endif // LEXER_H
