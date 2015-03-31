#include "machine.h"

Machine* machineCreate(FILE* file) {
    Machine* machine = malloc(sizeof(Machine));

    if(machine == NULL) {
        puts("Failed to allocate memory for Machine");
        return NULL;
    }

    machine->alphabet = NULL;

    machine->tape = NULL;

    machine->program = programCreate();

    if(machine->program == NULL) {
        machineDelete(machine);
        return NULL;
    }

    if(file != NULL) {
        machineParseFile(machine, file);
    }

    if(!programLinkStates(machine->program)) {
        machineDelete(machine);
        return NULL;
    }

    char* initial = programFindState(machine->program, machine->initial);

    if(initial == NULL) {
        printf("Can't find initial state \"%s\"\n", machine->initial);
        machineDelete(machine);
        return NULL;
    }

    free(machine->initial);

    machine->initial = initial;

    machine->end = programFindState(machine->program, "End");

    machine->state = initial;

    return machine;
}

void machineDelete(Machine* machine) {
    if(machine == NULL) {
        return;
    }

    free(machine->alphabet);

    free(machine->initial);

    tapeDelete(machine->tape);

    programDelete(machine->program);

    free(machine);
}

// TODO Return false on ERROR.
void machineParseFile(Machine* machine, FILE* file) {
    bool moreToDo = true;

    while(moreToDo) {
        Token* token = tokenGetNext(file);

        switch(token->type) {
        case ALPHABET:
            machineSetAlphabet(machine, token->value);
            break;
        case BLANK:
            machineSetBlank(machine, token->value[0]);
            break;
        case INITIAL:
            machineSetInitial(machine, token->value);
            break;
        case TRANSITION:
            programAddTransition(machine->program, token->value, token->input, token->output, token->direction, token->next);
            break;
        case ERROR:
            break;
        case T_EOF:
            moreToDo = false;
            break;
        }

        tokenDelete(token);
    }
}

void machineSetAlphabet(Machine* machine, char* alphabet) {
    if(machine->alphabet != NULL) {
        printf("Can't set alphabet to %s. Already set to %s.", alphabet, machine->alphabet);
        return;
    }

    machine->alphabet = calloc(strlen(alphabet) + 1, sizeof(char));

    if(machine->alphabet == NULL) {
        puts("Failed to allocate memory for Machine.alphabet");
        return;
    }

    strcpy(machine->alphabet, alphabet);
}

void machineSetBlank(Machine* machine, char blank) {
    if(machine->blank != '\0') {
        printf("Can't set blank to %c. Already set to %c.", blank, machine->blank);
        return;
    }

    machine->blank = blank;
}

void machineSetInitial(Machine* machine, char* initial) {
    if(machine->initial != NULL) {
        printf("Can't set initial to %s. Already set to %s.", initial, machine->initial);
        return;
    }

    machine->initial = calloc(strlen(initial) + 1, sizeof(char));

    if(machine->initial == NULL) {
        puts("Failed to allocate memory for Machine.alphabet");
        return;
    }

    strcpy(machine->initial, initial);
}

void machineSetTape(Machine* machine, Tape* tape) {
    free(machine->tape);
    machine->tape = tape;
}

bool machineStep(Machine* machine) {
    // TODO Remove tape from Machine and pass in here as argument.

    if(machine->state == machine->end) {
        return false;
    }

    char input = tapeRead(machine->tape);

    Action* action = programFindAction(machine->program, machine->state, input);

    if(action != NULL) {
/*        printf("%s %c %c %c %s\n", machine->state, action->input, action->output, action->direction, action->next);*/
        tapeWrite(machine->tape, action->output);
        tapeMove(machine->tape, action->direction);

        machine->state = action->next;

        return (machine->state != machine->end);
    } else {
        machine->state = machine->end;
        return false;
    }
}

void machineReset(Machine* machine) {
    machine->state = machine->initial;
}

void machinePrint(Machine* machine) {
    printf("alphabet: %s\n", machine->alphabet);
    printf("blank: %c\n", machine->blank);
    printf("initial: %s\n", machine->initial);
    printf("end: %s\n", machine->end);
    tapePrint(machine->tape);
    programPrint(machine->program);
    printf("state: %s\n", machine->state);
}
