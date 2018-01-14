#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

typedef struct {
    int height, width, depth;
} Point;

int multiplePointParameters(const Point *point);

Point *copyPoint(const Point *point);

int convertPointToIndex(const Point *point, const Point *range);

Point convertIndexToPoint(int index, const Point *range);

#endif //SCOTR_POINT_H
