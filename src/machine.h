#ifndef MACHINE_H
#define MACHINE_H

#include "tape.h"
#include "program.h"
#include "token.h"
#include "vector.h"

typedef struct {
    char* alphabet;
    char blank;
    char* initial;
    Program* program;
    char* state;
} Machine;

Machine* machineCreate(FILE* file);
void machineDelete(Machine* machine);
bool machineParseFile(Machine* machine, FILE* file);
void machineSetAlphabet(Machine* machine, char* alphabet);
void machineSetBlank(Machine* machine, char blank);
void machineSetInitial(Machine* machine, char* initial);
bool machineStep(Machine* machine, Tape* tape);
void machineReset(Machine* machine);
void machinePrint(Machine* machine);

#endif
