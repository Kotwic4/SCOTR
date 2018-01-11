#ifndef SCOTR_CNNPROCESING_H
#define SCOTR_CNNPROCESING_H

#include "../neural/cnn.h"

ReluLayer *readReluLayerFile(FILE *file);

void saveReluLayerFile(FILE *file, ReluLayer *reluLayer);

Layer *readLayerFile(FILE *file);

void saveLayerFile(FILE *file, Layer *layer);

PoolLayer *readPoolLayerFile(FILE *file);

void savePoolLayerFile(FILE *file, PoolLayer *layer);

FcLayer *readFcLayerFile(FILE *file);

void saveFcLayerFile(FILE *file, FcLayer *layer);

Cnn* readCnnFile(FILE *file);

void saveCnnFile(FILE *file, Cnn *cnn);

ConvLayer *readConvLayerFile(FILE *file);

void saveConvLayerFile(FILE *file, ConvLayer *layer);

#endif //SCOTR_CNNPROCESING_H
