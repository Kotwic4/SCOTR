#include "reluLayer.h"

ReluLayer *initReluLayer(Point *inSize) {
    debugAssert(inSize != NULL);
    ReluLayer *reluLayer = malloc(sizeof(ReluLayer));
    reluLayer->type = relu;
    reluLayer->in = NULL;
    reluLayer->back = initTensor(inSize);
    reluLayer->out = initTensor(inSize);
    return reluLayer;
}

void activateReluLayer(ReluLayer *reluLayer, Tensor *in) {
    debugAssert(reluLayer != NULL);
    debugAssert(in != NULL);
    reluLayer->in = in;
    for (int i = 0; i < in->size->H; i++) {
        for (int j = 0; j < in->size->W; j++) {
            for (int k = 0; k < in->size->D; k++) {
                double x = *getTensorField(in, (Point) {i, j, k});
                if (x < 0) x = 0;
                *getTensorField(reluLayer->out, (Point) {i, j, k}) = x;
            }
        }
    }
}

void backPropReluLayer(ReluLayer *reluLayer, Tensor *nextLayerBack) {
    debugAssert(reluLayer != NULL);
    debugAssert(nextLayerBack != NULL);
    for (int i = 0; i < reluLayer->in->size->H; i++) {
        for (int j = 0; j < reluLayer->in->size->W; j++) {
            for (int k = 0; k < reluLayer->in->size->D; k++) {
                double x = *getTensorField(reluLayer->in, (Point) {i, j, k});
                if (x < 0) x = 0;
                else x = *getTensorField(nextLayerBack, (Point) {i, j, k});
                *getTensorField(reluLayer->back, (Point) {i, j, k}) = x;
            }
        }
    }
}

void freeReluLayer(ReluLayer *reluLayer) {
    debugAssert(reluLayer != NULL);
    freeTensor(reluLayer->back);
    freeTensor(reluLayer->out);
    free(reluLayer);
}
