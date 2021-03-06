#include "pointTest.h"

void testMultiplePointParameters() {
    Point point1 = {1, 2, 3};
    assert(multiplePointParameters(&point1) == 6);
    Point point2 = {100, 10, 1000};
    assert(multiplePointParameters(&point2) == 1000000);
}

void testCopyPoint() {
    Point point1 = {15, 24, 38};
    Point *point2 = copyPoint(point1);
    assert(point1.height == point2->height);
    assert(point1.width == point2->width);
    assert(point1.depth == point2->depth);
    free(point2);
}

void testConvertPointToIndex() {
    Point range = {3, 3, 3};
    Point point1 = {0, 0, 0};
    Point point2 = {1, 1, 1};
    Point point3 = {2, 2, 2};
    assert(convertPointToIndex(point1, range) == 0);
    assert(convertPointToIndex(point2, range) == 13);
    assert(convertPointToIndex(point3, range) == 26);
    assert(convertPointToIndex(range, range) == -1);
}

void testConvertIndexToPoint() {
    int inx = 21;
    Point range = {3, 3, 3};
    Point point = convertIndexToPoint(inx, range);
    assert(point.height == 1);
    assert(point.width == 0);
    assert(point.depth == 2);

    point = convertIndexToPoint(300, range);
    assert(point.height == point.width == point.depth == 0);

    assert(convertPointToIndex(convertIndexToPoint(21, range), range) == 21);
}

void testPointAll() {
    testMultiplePointParameters();
    testCopyPoint();
    testConvertPointToIndex();
    testConvertIndexToPoint();
}
