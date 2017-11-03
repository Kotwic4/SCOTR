//
// Created by Radomir on 03.11.2017.
//

#ifndef SCOTR_POOLLAYER_H
#define SCOTR_POOLLAYER_H

#include "layer.h"

typedef struct{
    LayerType type; // pool
    Tensor *back,*in,*out;
    int stride, spatialExtent;
}PoolLayer;

PoolLayer* initPoolLayer(int stride, int spatialExtent, Point inSize);
void activatePoolLayer(PoolLayer* poolLayer, Tensor* in);
void backPropPoolLayer(PoolLayer* poolLayer, Tensor* nextLayerBack);
#endif //SCOTR_POOLLAYER_H
