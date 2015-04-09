#ifndef TAPE_H
#define TAPE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "subtape.h"

typedef struct {
    Subtape* left;
    Subtape* right;
    char blank;
} Tape;

Tape* tapeCreate(char* line, char blank);
void tapeDelete(Tape* tape);
char tapeRead(Tape* tape);
void tapeWrite(Tape* tape, char c);
bool tapeMove(Tape* tape, char direction);
void tapePrint(Tape* tape, bool detailed);

#endif
