#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int dataSize;
    int size;
    void** data;
} Vector;

Vector* vectorCreate();
void vectorDelete(Vector* vector);
void vectorAdd(Vector* vector, void* p);
void* vectorGet(Vector* vector, int i);
bool vectorDoubleSize(Vector* vector);

#endif
