#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

typedef struct{
    int H; //height
    int W; //width
    int D; //depth
}Point;

Point* copyPoint(Point point);
int convertPointToIndex(Point point, Point range);
Point convertIndexToPoint(int index, Point range);

#endif //SCOTR_POINT_H
