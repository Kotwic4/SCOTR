#ifndef SCOTR_FCLAYER_H
#define SCOTR_FCLAYER_H

#include "layer.h"
#include "../math/vector.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "grad.h"

typedef struct {
    LayerType type; // fc
    Tensor *back, *in, *out, *weights, *grad, *oldGrad, *input;
} FcLayer;

FcLayer *initFcLayer(Point *inSize, int outSize);

void activateFcLayer(FcLayer *fcLayer, Tensor *in);

void backPropFcLayer(FcLayer *fcLayer, Tensor *nextLayerBack);

void freeFcLayer(FcLayer *fcLayer);

#endif //SCOTR_FCLAYER_H
