#include "layer.h"
#include "convLayer.h"
#include "fcLayer.h"
#include "reluLayer.h"
#include "poolLayer.h"

void activateLayer(Layer* layer, Tensor* in){
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
