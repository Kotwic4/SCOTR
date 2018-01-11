#include "point.h"

int multiplePointParameters(Point *point) {
    return point->H * point->W * point->D;
}

Point *copyPoint(Point point) {
    Point *newPoint = malloc(sizeof(Point));
    *newPoint = point;
    return newPoint;
}

int convertPointToIndex(Point point, Point range) {
    if (!(point.H < range.H && point.W < range.W && point.D < range.D)) {
        fprintf(stderr, "convertPointToIndex error: one of point value is out of range\n");
        return -1;
    }
    return point.D * range.W * range.H + point.H * range.W + point.W;
}

Point convertIndexToPoint(int index, Point range) {
    if (index >= multiplePointParameters(&range)) {
        fprintf(stderr, "convertIndexToPoint error: index is out of range");
        return (Point) {0, 0, 0};
    }
    Point point;
    point.D = index / (range.W * range.H);
    index = index - point.D * range.W * range.H;
    point.H = index / range.W;
    index = index - point.H * range.W;
    point.W = index;
    return point;
}
