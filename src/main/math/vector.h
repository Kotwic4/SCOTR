#ifndef SCOTR_VECTOR_H
#define SCOTR_VECTOR_H

#include <malloc.h>
#include <stdio.h>

typedef struct {
    void **data;
    int size;
} Vector;

Vector *initVector(int size);

void pushBackVector(Vector *vector, void *value);

void *getVectorField(Vector *vector, int index);

void freeVector(Vector *vector);

#endif //SCOTR_VECTOR_H
