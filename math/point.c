#include <stdio.h>
#include "point.h"

int convertPointToIndex(Point point, Point range){
    // Index = d*W*H + h*W + w
    // where:
    // point = {h, d, w} each from 0 to N-1
    // range = {H, D, W} each from 1 to N
    if(!(point.H<range.H && point.W<range.W && point.D<range.D)){
        fprintf(stderr, "convertPointToIndex error: one of point value is out of range\n");
        return -1;
    }
    return point.D * range.W * range.H + point.H * range.W + point.W;
}

Point convertIndexToPoint(int index, Point range){
    if(index >= range.H * range.W * range.D){
        fprintf(stderr, "convertIndexToPoint error: index is out of range");
        return NULL;
    }
    Point point;
    point.D = index / (range.W*range.H);
    index = index - point.D * range.W*range.H;
    point.H = index / range.W;
    index = index - point.H * range.W;
    point.W = index;
    return point;
}
