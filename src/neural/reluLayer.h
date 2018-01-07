#ifndef SCOTR_RELULAYER_H
#define SCOTR_RELULAYER_H

#include "layer.h"

typedef struct {
    LayerType type; // relu
    Tensor *back, *in, *out;
} ReluLayer;

ReluLayer *initReluLayer(Point *inSize);

void activateReluLayer(ReluLayer *reluLayer, Tensor *in);

void backPropReluLayer(ReluLayer *reluLayer, Tensor *nextLayerBack);

void freeReluLayer(ReluLayer *reluLayer);

ReluLayer *readReluLayerFile(FILE *file);

void saveReluLayerFile(FILE *file, ReluLayer *reluLayer);

#endif //SCOTR_RELULAYER_H
