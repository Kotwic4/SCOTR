#include "cnn.h"

Cnn *initCnn(const Point *inSize) {
    return initCnnWithSize(inSize,0);
}

Cnn *initCnnWithSize(const Point *inSize, unsigned int arraySize) {
    Cnn *cnn = malloc(sizeof(Cnn));
    cnn->inSize = copyPoint(inSize);
    cnn->layers = calloc(arraySize, sizeof(Layer *));
    cnn->layersNumber = 0;
    cnn->arraySize = arraySize;
    return cnn;
}

void train(const Cnn *cnn, const TestCase *testCase) {
    Tensor *result = getForward(cnn, testCase->input);
    backPropCnn(cnn, result, testCase->expected);
}

Tensor *getForward(const Cnn *cnn, Tensor *input) {
    Layer *previousLayer;
//    Layer *layer = *(Layer **) getVectorField(cnn->layers, 0);
    Layer *layer = cnn->layers[0];
    activateLayer(layer, input);
    for (int i = 1; i < cnn->layersNumber; ++i) {
        previousLayer = layer;
//        layer = *(Layer **) getVectorField(cnn->layers, i);
        layer = cnn->layers[i];
        input = previousLayer->out;
        activateLayer(layer, input);
    }
    return layer->out;
}

void backPropCnn(const Cnn *cnn, const Tensor *result, const Tensor *expected) {

    Layer *nextLayer;
    Tensor *back = subTensor(result, expected);
//    Layer *layer = *(Layer **) getVectorField(cnn->layers, cnn->layers->size - 1);
    Layer *layer = cnn->layers[cnn->layersNumber-1];
    backPropLayer(layer, back);
    freeTensor(back);
//    for (int i = cnn->layers->size - 2; i >= 0; i--) {
    for (int i = cnn->layersNumber-1; i >= 0; --i) {
        nextLayer = layer;
//        layer = *(Layer **) getVectorField(cnn->layers, i);
        layer = cnn->layers[i];
        back = nextLayer->back;
        backPropLayer(layer, back);
    }

}

Point *getCnnOutSize(const Cnn *cnn) {
//    if (cnn->layers->size == 0) {
    if (cnn->layersNumber == 0) {
        return cnn->inSize;
    } else {
//        Layer *lastLayer = *(Layer **) getVectorField(cnn->layers, cnn->layers->size - 1);
        Layer *lastLayer = cnn->layers[cnn->layersNumber-1];
        return lastLayer->out->size;
    }
}

void addLayer(Cnn *cnn, Layer *layer) {
//    pushBackVector(cnn->layers, layer);
    if(cnn->layersNumber == cnn->arraySize){
        cnn->arraySize = cnn->arraySize * 2 + 1;
        cnn->layers = realloc(cnn->layers, sizeof(Layer *) * cnn->arraySize);
    }
    cnn->layers[cnn->layersNumber] = layer;
    ++cnn->layersNumber;
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
//    for (int i = 0; i < cnn->layers->size; i++) {
    for (int i = 0; i < cnn->layersNumber; i++) {
//        Layer *layer = *(Layer **) getVectorField(cnn->layers, i);
        Layer *layer = cnn->layers[i];
        freeLayer(layer);
    }
//    freeVector(cnn->layers);
    free(cnn->layers);
    free(cnn->inSize);
    free(cnn);
}
