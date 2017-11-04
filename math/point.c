#include <stdio.h>
#include "point.h"

Point copyPoint(Point point) {
    return (Point) {point.H, point.W, point.D};
}

int convertPointToIndex(Point point, Point range){
    // Index = d*(W+1)*(H+1) + h*(W+1) + w
    // where:
    // point = {h, d, w} each from 0 to N-1
    // range = {H, D, W} each from 1 to N
    if(!(point.H<range.H && point.W<range.W && point.D<range.D)){
        fprintf(stderr, "convertPointToIndex error: one of point value is out of range\n");
        return -1;
    }
    return point.D * (range.W+1) * (range.H+1) + point.H * (range.W+1) + point.W;
}

Point convertIndexToPoint(int index, Point range){
    if(index >= range.H * range.W * range.D){
        fprintf(stderr, "convertIndexToPoint error: index is out of range");
        return NULL;
    }
    Point point;
    point.D = index / ((range.W+1)*(range.H+1));
    index = index - point.D * (range.W+1)*(range.H+1);
    point.H = index / (range.W+1);
    index = index - point.H * (range.W+1);
    point.W = index;
    return point;
}