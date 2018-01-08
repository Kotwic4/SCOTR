#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

#include <stdio.h>
#include <malloc.h>

//height, width, depth
typedef struct {
    int H, W, D;
} Point;

int multiplePointParameters(Point *point);

Point *copyPoint(Point point);

// Index = d*W*H + h*W + w
// where:
// point = {h, d, w} each from 0 to N-1
// range = {H, D, W} each from 1 to N
int convertPointToIndex(Point point, Point range);

Point convertIndexToPoint(int index, Point range);

#endif //SCOTR_POINT_H
