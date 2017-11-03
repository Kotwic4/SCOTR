#ifndef SCOTR_LAYER_H
#define SCOTR_LAYER_H

#include "testCase.h"

typedef enum {conv, fc, relu, pool} LayerType;

typedef struct{
    LayerType type;
    Tensor *back,*in,*out;
}Layer;

void activateLayer(Layer* layer, Tensor* in);
void backPropLayer(Layer* layer, Tensor* nextLayerBack);
#endif //SCOTR_LAYER_H
