#include "vector.h"

Vector *initVector(int size) {
    Vector *thisVector = malloc(sizeof(Vector));
//    if (size < 0) {
//        fprintf(stderr, "initVector error: size can't be negative\n");
//        return NULL;
//    }
    if (size == 0) {
        thisVector->data = NULL;
        thisVector->size = 0;
    } else {
        thisVector->data = calloc((size_t) size, sizeof(void *));
        if (!thisVector->data) {
            fprintf(stderr, "initVector error: calloc function error\n");
            thisVector->size = 0;
        } else {
            thisVector->size = size;
        }
    }
    return thisVector;
}

void pushBackVector(Vector *vector, void *value) {
    int size = vector->size + 1;
    void **data = realloc(vector->data, sizeof(void *) * size);
    if (data) {
        vector->size = size;
        vector->data = data;
        vector->data[size - 1] = value;
    } else {
        fprintf(stderr, "pushBackVector error: realloc function error\n");
    }
}

void *getVectorField(Vector *vector, int index) {
//    if (vector->size <= index) {
//        fprintf(stderr, "getVectorField error: index out of range\n");
//        return NULL;
//    }
    return vector->data + index;
}

void freeVector(Vector *vector) {
    free(vector->data);
    free(vector);
}
