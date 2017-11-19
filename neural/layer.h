#ifndef SCOTR_LAYER_H
#define SCOTR_LAYER_H

#include "../util/debugAssert.h"
#include <malloc.h>
#include "../math/tensor.h"

typedef enum {conv, fc, relu, pool} LayerType;

typedef struct{
    LayerType type;
    Tensor *back,*in,*out;
}Layer;

void activateLayer(Layer* layer, Tensor* in);
void backPropLayer(Layer* layer, Tensor* nextLayerBack);
void freeLayer(Layer* layer);
int normalizeValue(double x, int max, int flag);
#endif //SCOTR_LAYER_H
