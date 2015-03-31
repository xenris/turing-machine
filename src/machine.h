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
    char* end;
    Tape* tape;
    Program* program;
    char* state;
} Machine;

Machine* machineCreate(FILE* file);
void machineDelete(Machine* machine);
void machineParseFile(Machine* machine, FILE* file);
void machineSetAlphabet(Machine* machine, char* alphabet);
void machineSetBlank(Machine* machine, char blank);
void machineSetInitial(Machine* machine, char* initial);
void machineSetTape(Machine* machine, Tape* tape);
bool machineStep(Machine* machine);
void machineReset(Machine* machine);
void machinePrint(Machine* machine);

#endif
