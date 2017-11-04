#ifndef SCOTR_CONVLAYER_H
#define SCOTR_CONVLAYER_H

#include "layer.h"

typedef struct{
    LayerType type; // conv
    Tensor *back,*in,*out;
    int stride, spatialExtent, padding;
}ConvLayer;

ConvLayer* initConvLayer(int stride, int spatialExtent, int filtersNumber, Point* inSize);
void activateConvLayer(ConvLayer* convLayer, Tensor* in);
void backPropConvLayer(ConvLayer* convLayer, Tensor* nextLayerBack);

#endif //SCOTR_CONVLAYER_H
