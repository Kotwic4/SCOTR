#ifndef SCOTR_CONVLAYER_H
#define SCOTR_CONVLAYER_H

#include "layer.h"
#include "../math/vector.h"

typedef struct{
    LayerType type; // conv
    Tensor *back,*in,*out;
    int stride, spatialExtent, padding;
    Vector *filters, *filtersGrad, *filtersOldGrad;
}ConvLayer;

ConvLayer* initConvLayer(int stride, int spatialExtent,int padding, int filtersNumber, Point* inSize);
void activateConvLayer(ConvLayer* convLayer, Tensor* in);
void backPropConvLayer(ConvLayer* convLayer, Tensor* nextLayerBack);
void freeConvLayer(ConvLayer* convLayer);

#endif //SCOTR_CONVLAYER_H
