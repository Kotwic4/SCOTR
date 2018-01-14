#include "cnnProcesing.h"
#include <mem.h>

ReluLayer *readReluLayerFile(FILE *file) {
    Point point = readPointFile(file);
    return initReluLayer(&point);
}

void saveReluLayerFile(FILE *file, ReluLayer *layer) {
    savePointFile(file, *layer->back->size);
}

PoolLayer *readPoolLayerFile(FILE *file) {
    Point point = readPointFile(file);
    int stride, spatialExtent;
    fscanf(file, "%d %d", &stride, &spatialExtent);
    return initPoolLayer(stride, spatialExtent, &point);
}

void savePoolLayerFile(FILE *file, PoolLayer *layer) {
    savePointFile(file, *layer->back->size);
    fprintf(file, "%d %d\n", layer->stride, layer->spatialExtent);
}

Layer *readLayerFile(FILE *file) {

    char buff[255];
    fscanf(file, "%s", buff);
    if (strcmp(buff, "conv") == 0) {
        return (Layer *) readConvLayerFile(file);
    }
    if (strcmp(buff, "fc") == 0) {
        return (Layer *) readFcLayerFile(file);
    }
    if (strcmp(buff, "relu") == 0) {
        return (Layer *) readReluLayerFile(file);
    }
    if (strcmp(buff, "pool") == 0) {
        return (Layer *) readPoolLayerFile(file);
    }
    return NULL;
}

void saveLayerFile(FILE *file, Layer *layer) {

    switch (layer->type) {
        case conv:
            fprintf(file, "conv\n");
            saveConvLayerFile(file, (ConvLayer *) layer);
            break;
        case fc:
            fprintf(file, "fc\n");
            saveFcLayerFile(file, (FcLayer *) layer);
            break;
        case relu:
            fprintf(file, "relu\n");
            saveReluLayerFile(file, (ReluLayer *) layer);
            break;
        case pool:
            fprintf(file, "pool\n");
            savePoolLayerFile(file, (PoolLayer *) layer);
            break;
    }
}

FcLayer *readFcLayerFile(FILE *file) {
    Point inSize = readPointFile(file);
    Point outPoint = readPointFile(file);
    FcLayer *fcLayer = malloc(sizeof(FcLayer));
    fcLayer->type = fc;
    fcLayer->in = NULL;
    fcLayer->back = initTensor(&inSize);
    fcLayer->grad = readTensorFromFile(file);
    fcLayer->oldGrad = readTensorFromFile(file);
    fcLayer->out = initTensor(&outPoint);
    fcLayer->input = initTensor(&outPoint);
    fcLayer->weights = readTensorFromFile(file);
    return fcLayer;
}

void saveFcLayerFile(FILE *file, FcLayer *layer) {
    savePointFile(file, *layer->back->size);
    savePointFile(file, *layer->out->size);
    writeTensorToFile(layer->grad, file);
    writeTensorToFile(layer->oldGrad, file);
    writeTensorToFile(layer->weights, file);
}

Cnn *readCnnFile(FILE *file) {
    Cnn *cnn = malloc(sizeof(Cnn));
    Point point = readPointFile(file);
    cnn->inSize = copyPoint(&point);
    int layersNumber;
    fscanf(file, "%d", &layersNumber);
    cnn->layers = calloc((size_t) layersNumber, sizeof(Tensor *));
    cnn->layersNumber = 0;
    cnn->arraySize = layersNumber;
    for (int i = 0; i < layersNumber; i++) {
        addLayer(cnn, readLayerFile(file));
    }
    return cnn;
}

void saveCnnFile(FILE *file, Cnn *cnn) {
    savePointFile(file, *cnn->inSize);
    int layersNumber = cnn->layersNumber;
    fprintf(file, "%d\n", layersNumber);
    for (int i = 0; i < layersNumber; i++) {
        saveLayerFile(file, cnn->layers[i]);
    }
}

ConvLayer *readConvLayerFile(FILE *file) {
    int stride, spatialExtent, padding, filtersNumber;
    Point outSize = readPointFile(file);
    Point inSize = readPointFile(file);
    fscanf(file, "%d %d %d %d", &stride, &spatialExtent, &padding, &filtersNumber);
    ConvLayer *convLayer = malloc(sizeof(ConvLayer));
    convLayer->type = conv;
    convLayer->in = NULL;
    convLayer->out = initTensor(&outSize);
    convLayer->back = initTensor(&inSize);
    convLayer->stride = stride;
    convLayer->spatial = spatialExtent;
    convLayer->padding = padding;
    convLayer->filterNumber = filtersNumber;
    convLayer->filt = calloc((size_t) filtersNumber, sizeof(Tensor *));
    convLayer->oldGrad = calloc((size_t) filtersNumber, sizeof(Tensor *));
    convLayer->grad = calloc((size_t) filtersNumber, sizeof(Tensor *));
    for (int i = 0; i < filtersNumber; i++) {
        Tensor *filter = readTensorFromFile(file);
        Tensor *filterGrad = readTensorFromFile(file);
        Tensor *filterOldGrad = readTensorFromFile(file);
        convLayer->filt[i] = filter;
        convLayer->oldGrad[i] = filterOldGrad;
        convLayer->grad[i] = filterGrad;
    }
    return convLayer;
}

void saveConvLayerFile(FILE *file, ConvLayer *layer) {
    int filtersNumber = layer->filterNumber;
    savePointFile(file, *layer->out->size);
    savePointFile(file, *layer->back->size);
    fprintf(file, "%d %d %d %d\n", layer->stride, layer->spatial, layer->padding, filtersNumber);
    for (int i = 0; i < filtersNumber; i++) {
        writeTensorToFile(layer->filt[i], file);
        writeTensorToFile(layer->grad[i], file);
        writeTensorToFile(layer->oldGrad[i], file);
    }
}
