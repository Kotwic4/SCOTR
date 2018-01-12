#ifndef SCOTR_CNN_H
#define SCOTR_CNN_H

#include "../math/vector.h"
#include "../math/point.h"
#include "testCase.h"
#include "layer.h"
#include "convLayer.h"
#include "fcLayer.h"
#include "reluLayer.h"
#include "poolLayer.h"
#include <stdio.h>

typedef struct {
//    Vector *layers;
    Layer **layers;
    int layersNumber;
    int arraySize;
    Point *inSize;
} Cnn;

Cnn *initCnn(const Point *inSize);

Cnn *initCnnWithSize(const Point *inSize, unsigned int arraySize);

void train(const Cnn *cnn, const TestCase *testCase);

Tensor *getForward(const Cnn *cnn, Tensor *input);

void backPropCnn(const Cnn *cnn, const Tensor *result, const Tensor *expected);

Point *getCnnOutSize(const Cnn *cnn);

void addLayer(Cnn *cnn, Layer *layer);

void addConvLayer(Cnn *cnn, int stride, int spatialExtent, int filtersNumber, int padding);

void addFcLayer(Cnn *cnn, int out_size);

void addPoolLayer(Cnn *cnn, int stride, int spatialExtent);

void addReluLayer(Cnn *cnn);

void freeCnn(Cnn *cnn);

#endif //SCOTR_CNN_H
