#ifndef COMMENTS_H
#define COMMENTS_H

#include <stdbool.h>
#include <stdio.h>
#include "token.h"

bool checkComment(FILE* f, char firstChar, int* line);  // line e pointer pt update la \n

#endif
