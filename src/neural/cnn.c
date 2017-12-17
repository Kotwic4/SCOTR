#include "cnn.h"

Cnn *initCnn(Point *inSize) {
    Cnn *cnn = malloc(sizeof(Cnn));
    cnn->inSize = copyPoint(*inSize);
    cnn->layers = initVector(0);
    return cnn;
}

void train(Cnn *cnn, TestCase *testCase) {
    Tensor *result = getForward(cnn, testCase->input);
    backPropCnn(cnn, result, testCase->expected);
}

Tensor *getForward(Cnn *cnn, Tensor *input) {
    Layer *previousLayer;
    Layer *layer = *(Layer **)getVectorField(cnn->layers, 0);
    activateLayer(layer, input);
    for (int i = 1; i < cnn->layers->size; i++) {
        previousLayer = layer;
        layer = *(Layer **)getVectorField(cnn->layers, i);
        input = previousLayer->out;
        activateLayer(layer, input);
    }
    return layer->out;
}

void backPropCnn(Cnn *cnn, Tensor *result, Tensor *expected) {

    Layer *nextLayer;
    Tensor *back = subTensor(result, expected);
    Layer *layer = *(Layer **)getVectorField(cnn->layers, cnn->layers->size - 1);
    backPropLayer(layer, back);
    freeTensor(back);

    for (int i = cnn->layers->size - 2; i >= 0; i--) {
        nextLayer = layer;
        layer = *(Layer **)getVectorField(cnn->layers, i);
        back = nextLayer->back;
        backPropLayer(layer, back);
    }

}

Point *getCnnOutSize(Cnn *cnn) {
    if (cnn->layers->size == 0) {
        return cnn->inSize;
    } else {
        Layer *lastLayer = *(Layer **)getVectorField(cnn->layers, cnn->layers->size - 1);
        return lastLayer->out->size;
    }
}

void addLayer(Cnn *cnn, Layer *layer) {
    pushBackVector(cnn->layers, layer);
}

void addConvLayer(Cnn *cnn, int stride, int spatialExtent, int filtersNumber, int padding) {
    ConvLayer *convLayer = initConvLayer(stride, spatialExtent, padding, filtersNumber, getCnnOutSize(cnn));
    addLayer(cnn, (Layer *) convLayer);
}

void addFcLayer(Cnn *cnn, int out_size) {
    FcLayer *fcLayer = initFcLayer(getCnnOutSize(cnn), out_size);
    addLayer(cnn, (Layer *) fcLayer);
}

void addPoolLayer(Cnn *cnn, int stride, int spatialExtent) {
    PoolLayer *poolLayer = initPoolLayer(stride, spatialExtent, getCnnOutSize(cnn));
    addLayer(cnn, (Layer *) poolLayer);
}

void addReluLayer(Cnn *cnn) {
    ReluLayer *reluLayer = initReluLayer(getCnnOutSize(cnn));
    addLayer(cnn, (Layer *) reluLayer);
}

void freeCnn(Cnn *cnn) {
    for (int i = 0; i < cnn->layers->size; i++) {
        Layer *layer = *(Layer **)getVectorField(cnn->layers, i);
        freeLayer(layer);
    }
    freeVector(cnn->layers);
    free(cnn->inSize);
    free(cnn);
}
