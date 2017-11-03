//
// Created by Radomir on 03.11.2017.
//

#ifndef SCOTR_CNN_H
#define SCOTR_CNN_H

#include "../math/vector.h"
#include "../math/point.h"
#include "testCase.h"
#include "layer.h"

typedef struct {
    Vector layers;
    Point inSize;
}Cnn;

Cnn* initCnn(Point inSize);
void train(Cnn* cnn, TestCase testCase);
Tensor* forward(Tensor* input);
void addLayer(Cnn* cnn, Layer* layer);
void addConvLayer(Cnn* cnn, int stride, int spatial_extent, int number_filters, int padding);
void addFcLayer(Cnn* cnn, int out_size);
void addPoolLayer(Cnn* cnn, int stride, int spatial_extent);
void addReluLayer(Cnn* cnn);
void freeCnn(Cnn* cnn);
#endif //SCOTR_CNN_H
