#include <malloc.h>
#include "vector.h"

Vector* initVector(int size){
    Vector* thisVector;
    thisVector->size = size;
    thisVector->data = malloc(sizeof(void*) * thisVector->size);
    return thisVector;
}

//add element at the end of vector
void pushBackVector(Vector* vector, void* x){
    int size = vector->size + 1;
    void ** data = realloc(vector->data, sizeof(void*) * size);
    if (data) {
        vector->size = size;
        vector->data = data;
        vector->data[size-1] = x;
    } else {
        printf("pushBackVector error, realloc data failure\n");
    }
}

//get the value without deleting; chose by index
void* getVectorField(Vector* vector, int index){
    if(vector->size <= index){
        printf("getVectorField error, index out of size\n");
        return NULL;
    }
    return vector->data[index];
}

void freeVector(Vector* vector){
    free(vector->data);
}