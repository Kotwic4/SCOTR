#include "point.h"
#include <stdio.h>
#include <malloc.h>

int multiplePointParameters(const Point *point) {
    return point->height * point->width * point->depth;
}

Point *copyPoint(const Point *point) {
    Point *newPoint = malloc(sizeof(Point));
    *newPoint = *point;
    return newPoint;
}

int convertPointToIndex(const Point *point, const Point *range) {
//    if (!(point.height < range.height && point.width < range.width && point.depth < range.depth)) {
//        fprintf(stderr, "convertPointToIndex error: one of point value is out of range\n");
//        return -1;
//    }
    return point->depth * range->width * range->height + point->height * range->width + point->width;
}

Point convertIndexToPoint(int index, const Point *range) {
//    if (index >= multiplePointParameters(&range)) {
//        fprintf(stderr, "convertIndexToPoint error: index is out of range");
//        return (Point) {0, 0, 0};
//    }
    Point point;
    point.depth = index / (range->width * range->height);
    index = index - point.depth * range->width * range->height;
    point.height = index / range->width;
    index = index - point.height * range->width;
    point.width = index;
    return point;
}
