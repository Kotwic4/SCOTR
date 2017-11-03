//
// Created by Radomir on 03.11.2017.
//

#ifndef SCOTR_FCLAYER_H
#define SCOTR_FCLAYER_H

#include "layer.h"

typedef struct{
    LayerType type; // fc
    Tensor *back,*in,*out,*weights;
}FcLayer;

FcLayer* initFcLayer(Point inSize, int outSize);
void activateFcLayer(FcLayer* fcLayer, Tensor* in);
void backPropFcLayer(FcLayer* fcLayer, Tensor* nextLayerBack);
#endif //SCOTR_FCLAYER_H
