#ifndef SUBTAPE_H
#define SUBTAPE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct SubtapeNode {
    char value;
    struct SubtapeNode* next;
} SubtapeNode;

typedef struct {
    char blank;
    SubtapeNode* next;
} Subtape;

Subtape* subtapeCreate(char blank);
void subtapeDelete(Subtape* subtape);
void subtapePush(Subtape* subtape, char c);
void subtapeReplaceTop(Subtape* subtape, char c);
char subtapePop(Subtape* subtape);
char subtapePeek(Subtape* subtape);
void subtapePrint(Subtape* subtape);
void subtapeReversePrint(Subtape* subtape);
int subtapeSize(Subtape* subtape);
SubtapeNode* subtapeNodeCreate(char c);
void subtapeNodeDelete(SubtapeNode* subtapeNode);
void subtapeNodePrint(SubtapeNode* subtapeNode, char blank);
void subtapeReverseNodePrint(SubtapeNode* subtapeNode, char blank);

#endif
