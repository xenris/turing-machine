#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "util.h"

typedef enum {
    ALPHABET,
    BLANK,
    INITIAL,
    TRANSITION,
    T_EOF,
    ERROR,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    char input;
    char output;
    char direction;
    char* next;
} Token;

Token* tokenGetNext(FILE* file);
Token* tokenCreate(TokenType type, char* value);
void tokenDelete(Token* token);

#endif
