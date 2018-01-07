#ifndef SCOTR_CONVLAYER_H
#define SCOTR_CONVLAYER_H

#include "layer.h"
#include "../math/vector.h"

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

ConvLayer *readConvLayerFile(FILE *file);

void saveConvLayerFile(FILE *file, ConvLayer *layer);

#endif //SCOTR_CONVLAYER_H
