#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

#include <stdio.h>
#include <malloc.h>

typedef struct {
    int height, width, depth;
} Point;

int multiplePointParameters(Point *point);

Point *copyPoint(Point point);

int convertPointToIndex(Point point, Point range);

Point convertIndexToPoint(int index, Point range);

#endif //SCOTR_POINT_H
