#include <printf.h>
#include "point.h"

void copyPoint(Point newpoint, Point oldpoint) {
    newpoint = (Point) {oldpoint.H, oldpoint.W, oldpoint.D};
}

int convertPointToIndex(Point point, Point range){
    // Index = d*(W+1)*(H+1) + h*(W+1) + w
    // where:
    // point = {h, d, w} each from 0 to N-1
    // range = {H, D, W} each from 1 to N
    return point.D * (range.W+1) * (range.H+1) + point.H * (range.W+1) + point.W;
}

Point convertIndexToPoint(int index, Point range){
    Point point;
    point.D = index / ((range.W+1)*(range.H+1));
    index = index - point.D * (range.W+1)*(range.H+1);
    point.H = index / (range.W+1);
    index = index - point.H * (range.W+1);
    point.W = index;
    return point;
}