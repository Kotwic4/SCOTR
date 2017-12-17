#include "vectorTest.h"
#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include "../../src/math/vector.h"
#include "../../src/math/point.h"

void TEST_freeVector() {
    for (int i = 0; i < 100000; i++) {
        Vector *vector = initVector(100000);
        freeVector(vector);
    }
}

void TEST_initVector() {
    Vector *vector1 = initVector(-8);
    assert(vector1 == NULL);

    Vector *vector2 = initVector(200);
    assert(vector2->size == 200);
    freeVector(vector2);
}

void TEST_pushBackVector() {
    Vector *vector = initVector(0);
    void *element = copyPoint((Point) {1, 2, 3});
    pushBackVector(vector, element);
    assert(vector->data[0] == element);
    assert(vector->size == 1);
    freeVector(vector);
    free(element);
}

void TEST_getVectorField() {
    Vector *vector = initVector(10);
    int **field8 = (int **) getVectorField(vector, 8);
    *field8 = malloc(sizeof(int));
    **field8 = 5;
    assert(**(int **) getVectorField(vector, 8) == 5);

    void *element = copyPoint((Point) {1, 2, 3});
    pushBackVector(vector, element);
    void **field10 = getVectorField(vector, 10);
    assert(*field10 == element);
    freeVector(vector);
}

void testVectorAll() {
    TEST_freeVector();
    TEST_initVector();
    TEST_pushBackVector();
    TEST_getVectorField();
}
