#include "subtape.h"

Subtape* subtapeCreate(char blank) {
    Subtape* subtape = malloc(sizeof(Subtape));

    if(subtape == NULL) {
        puts("Failed to allocate memory for Subtape");
        return NULL;
    }

    subtape->blank = blank;
    subtape->next = NULL;

    return subtape;
}

void subtapeDelete(Subtape* subtape) {
    if(subtape == NULL) {
        return;
    }

    subtapeNodeDelete(subtape->next);

    free(subtape);
}

void subtapePush(Subtape* subtape, char c) {
    SubtapeNode* subtapeNode = subtapeNodeCreate(c);

    if(subtapeNode == NULL) {
        return;
    }

    subtapeNode->next = subtape->next;

    subtape->next = subtapeNode;
}

void subtapeReplaceTop(Subtape* subtape, char c) {
    if(subtape->next == NULL) {
        subtapePush(subtape, c);
    } else {
        subtape->next->value = c;
    }
}

char subtapePop(Subtape* subtape) {
    if(subtape->next == NULL) {
        return subtape->blank;
    }

    SubtapeNode* subtapeNode = subtape->next;

    char result = subtapeNode->value;

    subtape->next = subtapeNode->next;

    subtapeNode->next = NULL;

    subtapeNodeDelete(subtapeNode);

    return result;
}

char subtapePeek(Subtape* subtape) {
    if(subtape->next == NULL) {
        return subtape->blank;
    }

    return subtape->next->value;
}

void subtapePrint(Subtape* subtape) {
    subtapeNodePrint(subtape->next, subtape->blank);
}

void subtapeReversePrint(Subtape* subtape) {
    subtapeReverseNodePrint(subtape->next, subtape->blank);
}

int subtapeSize(Subtape* subtape) {
    int size = 0;

    SubtapeNode* subtapeNode = subtape->next;

    while(subtapeNode != NULL) {
        subtapeNode = subtapeNode->next;
        size++;
    }

    return size;
}

SubtapeNode* subtapeNodeCreate(char c) {
    SubtapeNode* subtapeNode = malloc(sizeof(SubtapeNode));

    if(subtapeNode == NULL) {
        puts("Failed to allocate memory for SubtapeNode");
        return NULL;
    }

    subtapeNode->value = c;
    subtapeNode->next = NULL;

    return subtapeNode;
}

void subtapeNodeDelete(SubtapeNode* subtapeNode) {
    if(subtapeNode == NULL) {
        return;
    }

    subtapeNodeDelete(subtapeNode->next);

    subtapeNode->next = NULL;

    free(subtapeNode);
}

void subtapeNodePrint(SubtapeNode* subtapeNode, char blank) {
    if(subtapeNode != NULL) {
        putchar(subtapeNode->value);

        subtapeNodePrint(subtapeNode->next, blank);
    }
}

void subtapeReverseNodePrint(SubtapeNode* subtapeNode, char blank) {
    if(subtapeNode != NULL) {
        subtapeReverseNodePrint(subtapeNode->next, blank);

        putchar(subtapeNode->value);
    }
}
