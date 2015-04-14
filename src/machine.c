#include "machine.h"

Machine* machineCreate(FILE* file) {
    if(file == NULL) {
        return NULL;
    }

    Machine* machine = malloc(sizeof(Machine));

    if(machine == NULL) {
        puts("Failed to allocate memory for Machine");
        return NULL;
    }

    machine->alphabet = NULL;
    machine->blank = -1;
    machine->initial = NULL;
    machine->end = NULL;
    machine->program = NULL;
    machine->state = NULL;

    machine->program = programCreate();

    if(machine->program == NULL) {
        return NULL;
    }

    if(!machineParseFile(machine, file)) {
        machineDelete(machine);
        return NULL;
    }

    if(!programLinkStates(machine->program)) {
        return NULL;
    }

    if(machine->initial == NULL) {
        puts("Error: initial state not specified");
        return NULL;
    }

    char* initial = programFindState(machine->program, machine->initial);

    if(initial == NULL) {
        printf("Can't find initial state \"%s\"\n", machine->initial);
        return NULL;
    }

    free(machine->initial);

    machine->initial = initial;

    machine->end = programFindState(machine->program, "End");

    machine->state = initial;

    if(machine->alphabet == NULL) {
        puts("Error: alphabet not specified");
        return NULL;
    }

    if(machine->blank == -1) {
        puts("Error: blank character not specified");
        return NULL;
    }

    return machine;
}

void machineDelete(Machine* machine) {
    if(machine == NULL) {
        return;
    }

    free(machine->alphabet);

    programDelete(machine->program);

    free(machine);
}

bool machineParseFile(Machine* machine, FILE* file) {
    bool moreToDo = true;
    bool success = true;

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
            success = false;
            moreToDo = false;
            break;
        case T_EOF:
            moreToDo = false;
            break;
        }

        tokenDelete(token);
    }

    return success;
}

void machineSetAlphabet(Machine* machine, char* alphabet) {
    if(machine->alphabet != NULL) {
        printf("Can't set alphabet to %s. Already set to %s.\n", alphabet, machine->alphabet);
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
    if(machine->blank != -1) {
        printf("Can't set blank to %c. Already set to %c\n.", blank, machine->blank);
        return;
    }

    machine->blank = blank;
}

void machineSetInitial(Machine* machine, char* initial) {
    if(machine->initial != NULL) {
        printf("Can't set initial to %s. Already set to %s.\n", initial, machine->initial);
        return;
    }

    machine->initial = calloc(strlen(initial) + 1, sizeof(char));

    if(machine->initial == NULL) {
        puts("Failed to allocate memory for Machine.alphabet");
        return;
    }

    strcpy(machine->initial, initial);
}

bool machineStep(Machine* machine, Tape* tape) {
    if(machine->state == machine->end) {
        return false;
    }

    char input = tapeRead(tape);

    Action* action = programFindAction(machine->program, machine->state, input);

    if(action != NULL) {
/*        printf("%s %c %c %c %s\n", machine->state, action->input, action->output, action->direction, action->next);*/
        tapeWrite(tape, action->output);
        tapeMove(tape, action->direction);

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
    programPrint(machine->program);
    printf("state: %s\n", machine->state);
}
