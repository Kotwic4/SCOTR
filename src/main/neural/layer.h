#ifndef SCOTR_LAYER_H
#define SCOTR_LAYER_H

#include "../util/debugAssert.h"
#include <malloc.h>
#include <stdio.h>
#include "../math/tensor.h"


typedef enum {
    conv, fc, relu, pool
} LayerType;

typedef struct {
    LayerType type;
    Tensor *back, *in, *out;
} Layer;

void activateLayer(Layer *layer, Tensor *in);

void backPropLayer(Layer *layer, Tensor *nextLayerBack);

void freeLayer(Layer *layer);

#endif //SCOTR_LAYER_H
