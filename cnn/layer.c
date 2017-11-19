#include <math.h>
#include "layer.h"
#include "convLayer.h"
#include "fcLayer.h"
#include "reluLayer.h"
#include "poolLayer.h"

void activateLayer(Layer* layer, Tensor* in){
    debugAssert(layer != NULL);
    debugAssert(in != NULL);
    switch(layer->type){
        case conv:
            activateConvLayer((ConvLayer *) layer, in);
            break;
        case fc:
            activateFcLayer((FcLayer *) layer, in);
            break;
        case relu:
            activateReluLayer((ReluLayer *) layer, in);
            break;
        case pool:
            activatePoolLayer((PoolLayer *) layer, in);
            break;
    }
}

void backPropLayer(Layer* layer, Tensor* nextLayerBack){
    debugAssert(layer != NULL);
    debugAssert(nextLayerBack != NULL);
    switch(layer->type){
        case conv:
            backPropConvLayer((ConvLayer *) layer, nextLayerBack);
            break;
        case fc:
            backPropFcLayer((FcLayer *) layer, nextLayerBack);
            break;
        case relu:
            backPropReluLayer((ReluLayer *) layer, nextLayerBack);
            break;
        case pool:
            backPropPoolLayer((PoolLayer *) layer, nextLayerBack);
            break;
    }
}


void freeLayer(Layer* layer){
    debugAssert(layer != NULL);
    switch(layer->type){
        case conv:
            freeConvLayer((ConvLayer *) layer);
            break;
        case fc:
            freeFcLayer((FcLayer *) layer);
            break;
        case relu:
            freeReluLayer((ReluLayer *) layer);
            break;
        case pool:
            freePoolLayer((PoolLayer *) layer);
            break;
    }
}

int normalizeValue(double x, int max, int flag){
    if(x <= 0) return 0;
    if(x >= max) return max;
    if(flag)return (int) ceil(x);
    return (int) floor(x);
}
