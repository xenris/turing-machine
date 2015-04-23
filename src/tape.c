#include "tape.h"

Tape* tapeCreate(char* line, char blank) {
    Tape* tape = malloc(sizeof(Tape));

    if(tape == NULL) {
        puts("Failed to allocate memory for Tape");
        return NULL;
    }

    tape->blank = blank;

    tape->left = subtapeCreate(tape->blank);

    if(tape->left == NULL) {
        tapeDelete(tape);
        return NULL;
    }

    tape->right = subtapeCreate(tape->blank);

    if(tape->right == NULL) {
        subtapeDelete(tape->left);
        tapeDelete(tape);
        return NULL;
    }

    subtapePush(tape->right, tape->blank);

    for(int i = strlen(line) - 1; i >= 0; i--) {
        subtapePush(tape->right, line[i]);
    }

    subtapePush(tape->right, tape->blank);

    return tape;
}

void tapeDelete(Tape* tape) {
    if(tape == NULL) {
        return;
    }

    subtapeDelete(tape->left);
    subtapeDelete(tape->right);

    free(tape);
}

char tapeRead(Tape* tape) {
    return subtapePeek(tape->right);
}

void tapeWrite(Tape* tape, char c) {
    subtapeReplaceTop(tape->right, c);
}

bool tapeMove(Tape* tape, char direction) {
    switch(direction) {
    case 'l':
        subtapePush(tape->right, subtapePop(tape->left));
        break;
    case 'r':
        subtapePush(tape->left, subtapePop(tape->right));
        break;
    }

    return true;
}

void tapePrint(Tape* tape, bool detailed) {
    if(tape == NULL) {
        return;
    }

    subtapeReversePrint(tape->left);

    subtapePrint(tape->right);

    printf("\n");

    if(detailed) {
        int position = subtapeSize(tape->left);

        for(int i = 0; i < position; i++) {
            putchar(' ');
        }

        puts("^");
    }
}
