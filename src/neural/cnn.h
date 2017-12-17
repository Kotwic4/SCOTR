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

typedef struct {
    Vector *layers;
    Point *inSize;
} Cnn;

Cnn *initCnn(Point *inSize);

void train(Cnn *cnn, TestCase *testCase);

Tensor *getForward(Cnn *cnn, Tensor *input);

void backPropCnn(Cnn *cnn, Tensor *result, Tensor *expected);

Point *getCnnOutSize(Cnn *cnn);

void addLayer(Cnn *cnn, Layer *layer);

void addConvLayer(Cnn *cnn, int stride, int spatialExtent, int filtersNumber, int padding);

void addFcLayer(Cnn *cnn, int out_size);

void addPoolLayer(Cnn *cnn, int stride, int spatialExtent);

void addReluLayer(Cnn *cnn);

void freeCnn(Cnn *cnn);

#endif //SCOTR_CNN_H
