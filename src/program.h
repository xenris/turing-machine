#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "util.h"

typedef struct {
    char input;
    char output;
    char direction;
    char* next;
} Action;

typedef struct {
    char* state;
    Vector* actions;
} Transition;

typedef struct {
    Vector* states;
    Vector* transitions;
} Program;

Program* programCreate();
void programDelete(Program* program);
void programAddTransition(Program* program, char* state, char input, char output, char direction, char* next);
void transitionAddAction(Transition* transition, char input, char output, char direction, char* next);
Transition* programFindTransition(Program* program, char* state);
Action* transitionFindAction(Transition* transition, char input);
Action* programFindAction(Program* program, char* state, char input);
Transition* transitionCreate(char* state);
void transitionDelete(Transition* transition);
Action* actionCreate(char input, char output, char direction, char* next);
void actionDelete(Action* action);
bool programLinkStates(Program* program);
char* programFindState(Program* program, char* state);
void programPrint(Program* program);
int programGetMaxStateLabelLength(Program* program);

#endif
