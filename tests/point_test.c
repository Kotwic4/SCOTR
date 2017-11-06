#include <assert.h>
#include <printf.h>
#include <malloc.h>
#include "../math/point.h"

void TEST_multiplePointParameters(){
    Point point1 = { 1, 2, 3};
    assert(multiplePointParameters(&point1) == 6);
    Point point2 = {100, 10, 1000};
    assert(multiplePointParameters(&point2) == 1000000);
}

void TEST_copyPoint(){
    Point point1 = {15, 24, 38};
    Point* point2 = copyPoint(point1);
    assert(point1.H == point2->H);
    assert(point1.W == point2->W);
    assert(point1.D == point2->D);
    free(point2);
}

void TEST_convertPointToIndex() {
    Point range = {3, 3, 3};
    Point point1 = {0, 0, 0};
    Point point2 = {1, 1, 1};
    Point point3 = {2, 2, 2};
    assert(convertPointToIndex(point1, range) == 0);
    assert(convertPointToIndex(point2, range) == 13);
    assert(convertPointToIndex(point3, range) == 26);
    assert(convertPointToIndex(range, range) == -1);
}

void TEST_convertIndexToPoint(){
    int inx = 21;
    Point range = {3,3,3};
    Point point = convertIndexToPoint(inx, range);
    assert(point.H == 1);
    assert(point.W == 0);
    assert(point.D == 2);

    point = convertIndexToPoint(300, range);
    assert(point.H == point.W == point.D == 0);

    assert(convertPointToIndex(convertIndexToPoint(21, range), range) == 21);
}

void TEST_POINT_ALL(){
    TEST_multiplePointParameters();
    TEST_copyPoint();
    TEST_convertPointToIndex();
    TEST_convertIndexToPoint();
}