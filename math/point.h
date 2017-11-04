#ifndef SCOTR_POINT_H
#define SCOTR_POINT_H

typedef struct{
    int x,y,z;
}Point;

Point* copyPoint(Point* point);

#endif //SCOTR_POINT_H
