#include "program.h"

Program* programCreate() {
    Program* program = malloc(sizeof(Program));

    if(program == NULL) {
        puts("Failed to allocate memory for Program");
        return NULL;
    }

    program->states = vectorCreate();

    if(program->states == NULL) {
        programDelete(program);
        return NULL;
    }

    program->transitions = vectorCreate();

    if(program->transitions == NULL) {
        programDelete(program);
        return NULL;
    }

    return program;
}

void programDelete(Program* program) {
    if(program == NULL) {
        return;
    }

    for(int i = 0; i < program->states->size; i++) {
        free(vectorGet(program->states, i));
    }

    vectorDelete(program->states);

    for(int i = 0; i < program->transitions->size; i++) {
        transitionDelete(vectorGet(program->transitions, i));
    }

    vectorDelete(program->transitions);

    free(program);
}

void programAddTransition(Program* program, char* state, char input, char output, char direction, char* next) {
    Transition* transition = programFindTransition(program, state);

    if(transition == NULL) {
        transition = transitionCreate(state);

        if(transition == NULL) {
            return;
        }

        vectorAdd(program->transitions, transition);

        vectorAdd(program->states, stringCopy(state));
    }

    transitionAddAction(transition, input, output, direction, next);
}

void transitionAddAction(Transition* transition, char input, char output, char direction, char* next) {
    Action* action = actionCreate(input, output, direction, next);

    if(action == NULL) {
        return;
    }

    vectorAdd(transition->actions, action);
}

Transition* programFindTransition(Program* program, char* state) {
    for(int i = 0; i < program->transitions->size; i++) {
        Transition* transition = vectorGet(program->transitions, i);

        if(strcmp(transition->state, state) == 0) {
            return transition;
        }
    }

    return NULL;
}

Action* transitionFindAction(Transition* transition, char input) {
    for(int i = 0; i < transition->actions->size; i++) {
        Action* action = vectorGet(transition->actions, i);

        if(action->input == input) {
            return action;
        }
    }

    return NULL;
}

Action* programFindAction(Program* program, char* state, char input) {
    Transition* transition = programFindTransition(program, state);

    if(transition != NULL) {
        return transitionFindAction(transition, input);
    }

    return NULL;
}

Transition* transitionCreate(char* state) {
    Transition* transition = malloc(sizeof(Transition));

    if(transition == NULL) {
        puts("Failed to allocate memory for Transition");
        return NULL;
    }

    transition->state = stringCopy(state);

    if(transition->state == NULL) {
        puts("Failed to copy string for Transition");
        transitionDelete(transition);
        return NULL;
    }

    transition->actions = vectorCreate();

    if(transition->actions == NULL) {
        puts("Failed to create Transition.actions");
        transitionDelete(transition);
        return NULL;
    }

    return transition;
}

void transitionDelete(Transition* transition) {
    if(transition == NULL) {
        return;
    }

    for(int i = 0; i < transition->actions->size; i++) {
        actionDelete(vectorGet(transition->actions, i));
    }

    vectorDelete(transition->actions);

    free(transition);
}

Action* actionCreate(char input, char output, char direction, char* next) {
    Action* action = malloc(sizeof(Action));

    if(action == NULL) {
        puts("Failed to allocate memory for Action");
        return NULL;
    }

    action->input = input;
    action->output = output;
    action->direction = direction;

    action->next = stringCopy(next);

    if(action->next == NULL) {
        actionDelete(action);
        return NULL;
    }

    return action;
}

void actionDelete(Action* action) {
    if(action == NULL) {
        return;
    }

    free(action);
}

bool programLinkStates(Program* program) {
    bool success = true;

    for(int i = 0; i < program->transitions->size; i++) {
        Transition* transition = vectorGet(program->transitions, i);

        char* state = programFindState(program, transition->state);

        if(state == NULL) {
            printf("Can't find state \"%s\"\n", transition->state);
            success = false;
        }

        free(transition->state);

        transition->state = state;

        for(int j = 0; j < transition->actions->size; j++) {
            Action* action = vectorGet(transition->actions, j);

            char* next = programFindState(program, action->next);

            if(next == NULL) {
                printf("Can't find state \"%s\"\n", action->next);
                success = false;
            }

            free(action->next);

            action->next = next;
        }
    }

    return success;
}

char* programFindState(Program* program, char* state) {
    for(int i = 0; i < program->states->size; i++) {
        char* result = vectorGet(program->states, i);

        if(strcmp(state, result) == 0) {
            return result;
        }
    }

    return NULL;
}

void programPrint(Program* program) {
    printf("states:");
    for(int i = 0; i < program->states->size; i++) {
        printf(" %s", vectorGet(program->states, i));
    }
    printf("\n");

    printf("transitions:\n");
    for(int i = 0; i < program->transitions->size; i++) {
        Transition* transition = vectorGet(program->transitions, i);

        for(int j = 0; j < transition->actions->size; j++) {
            Action* action = vectorGet(transition->actions, j);

            printf("  %s %c %c %c %s\n", transition->state, action->input, action->output, action->direction, action->next);
        }
    }
}

int programGetMaxStateLabelLength(Program* program) {
    int maxLength = 0;
    const int stateCount = program->states->size;

    for(int i = 0; i < stateCount; i++) {
        const int labelLength = strlen(vectorGet(program->states, i));
        if(labelLength > maxLength) {
            maxLength = labelLength;
        }
    }

    return maxLength;
}
