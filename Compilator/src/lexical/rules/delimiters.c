#include "lexical/rules/delimiters.h"

bool checkDelimiter(char ch, int line){
    Token t;
    t.lexeme[0] = ch;
    t.lexeme[1] = '\0';
    t.line = line;

    switch (ch) {
        case ',':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case ';':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case '(':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case ')':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case '[':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case ']':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case '{':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        case '}':
            t.type = TOKEN_DELIMITER;
            tokenList[tokenCount++] = t;
            return true;
        default:
            return false;
    }
}