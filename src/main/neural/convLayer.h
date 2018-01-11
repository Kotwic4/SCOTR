#ifndef SCOTR_CONVLAYER_H
#define SCOTR_CONVLAYER_H

#include "layer.h"
#include "../math/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "grad.h"
#include "../io/mathProcesing.h"

typedef struct {
    LayerType type; // conv
    Tensor *back;
    Tensor *in;
    Tensor *out;
    Vector *filt;
    Vector *grad;
    Vector *oldGrad;
    int stride;
    int spatial;
    int padding;
} ConvLayer;

ConvLayer *initConvLayer(int stride, int spatialExtent, int padding, int filtersNumber, Point *inSize);

void activateConvLayer(ConvLayer *convLayer, Tensor *in);

void backPropConvLayer(ConvLayer *convLayer, Tensor *nextLayerBack);

void freeConvLayer(ConvLayer *convLayer);

#endif //SCOTR_CONVLAYER_H
