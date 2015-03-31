#include "vector.h"

#define INITIAL_SIZE 8

Vector* vectorCreate() {
    Vector* vector = malloc(sizeof(Vector));

    if(vector == NULL) {
        puts("Failed to allocate memory for Vector");
        return NULL;
    }

    vector->data = malloc(INITIAL_SIZE * sizeof(void*));

    if(vector->data == NULL) {
        puts("Failed to allocate memory for Vector.data");
        vectorDelete(vector);
        return NULL;
    }

    vector->dataSize = INITIAL_SIZE;
    vector->size = 0;

    return vector;
}

void vectorDelete(Vector* vector) {
    if(vector == NULL) {
        return;
    }

    free(vector->data);

    free(vector);
}

void vectorAdd(Vector* vector, void* p) {
    if(vector->size == vector->dataSize) {
        if(!vectorDoubleSize(vector)) {
            return;
        }
    }

    vector->data[vector->size] = p;
    vector->size++;
}

void* vectorGet(Vector* vector, int i) {
    if((i < 0) || (i >= vector->size)) {
        return NULL;
    }

    return vector->data[i];
}

bool vectorDoubleSize(Vector* vector) {
    int newDataSize = vector->dataSize * 2;
    void* newData = realloc(vector->data, newDataSize * sizeof(void*));

    if(newData == NULL) {
        puts("failed to double Vector size");
        return false;
    }

    vector->data = newData;
    vector->dataSize = newDataSize;

    return true;
}
