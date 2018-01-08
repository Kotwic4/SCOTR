#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

#include <stdio.h>

typedef struct {
    int H; //height
    int W; //width
    int D; //depth
} Point;

int multiplePointParameters(Point *point);

Point *copyPoint(Point point);

int convertPointToIndex(Point point, Point range);

Point convertIndexToPoint(int index, Point range);

Point readPointFile(FILE *file);

void savePointFile(FILE *file, Point point);

#endif //SCOTR_POINT_H
