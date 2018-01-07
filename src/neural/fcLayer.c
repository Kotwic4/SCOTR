#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "fcLayer.h"
#include "grad.h"
#include "testCase.h"


FcLayer *initFcLayer(Point *inSize, int outSize) {
    debugAssert(inSize != NULL);
    FcLayer *fcLayer = malloc(sizeof(FcLayer));
    Point outPoint = {outSize, 1, 1};
    Point weightSize = {multiplePointParameters(inSize), outSize, 1};
    fcLayer->type = fc;
    fcLayer->in = NULL;
    fcLayer->back = initTensor(inSize);
    fcLayer->grad = initTensor(&outPoint);
    fcLayer->oldGrad = initTensor(&outPoint);
    fcLayer->out = initTensor(&outPoint);
    fcLayer->input = initTensor(&outPoint);
    fcLayer->weights = initTensor(&weightSize);

    for (int i = 0; i < multiplePointParameters(&outPoint); i++) {
        *getFasterTensorField(fcLayer->grad, i) = 0;
        *getFasterTensorField(fcLayer->oldGrad, i) = 0;
    }

    int max = multiplePointParameters(inSize);
    double maxVal = 2.19722f / max;

    for (int i = 0; i < outSize; i++) {
        for (int j = 0; j < max; j++) {
            *getTensorField(fcLayer->weights, (Point) {j, i, 0}) = maxVal * rand() / (double) RAND_MAX;
        }
    }

    return fcLayer;
}

double activatorFunction(double value) {
    return 1.0f / (1.0f + exp(-value));
}

double activatorDerivative(double value) {
    double sig = activatorFunction(value);
    return sig * (1 - sig);
}

void activateFcLayer(FcLayer *fcLayer, Tensor *in) {
    fcLayer->in = in;
    for (int n = 0; n < fcLayer->out->size->H; n++) {
        double inputValue = 0;
        for (int i = 0; i < fcLayer->in->size->H; i++) {
            for (int j = 0; j < fcLayer->in->size->W; j++) {
                for (int k = 0; k < fcLayer->in->size->D; k++) {
                    Point point = {i, j, k};
                    double inValue = *getTensorField(fcLayer->in, point);
                    int index = convertPointToIndex(point, *in->size);
                    double weight = *getTensorField(fcLayer->weights, (Point) {index, n, 0});
                    inputValue += inValue * weight;
                }
            }
        }
        *getTensorField(fcLayer->input, (Point) {n, 0, 0}) = inputValue;
        *getTensorField(fcLayer->out, (Point) {n, 0, 0}) = activatorFunction(inputValue);
    }
}

void backPropFcLayer(FcLayer *fcLayer, Tensor *nextLayerBack) {

    for (int i = 0; i < fcLayer->in->size->H; i++) {
        for (int j = 0; j < fcLayer->in->size->W; j++) {
            for (int k = 0; k < fcLayer->in->size->D; k++) {
                *getTensorField(fcLayer->back, (Point) {i, j, k}) = 0;
            }
        }
    }

    for (int n = 0; n < fcLayer->out->size->H; n++) {
        double inputValue = *getTensorField(fcLayer->input, (Point) {n, 0, 0});
        double grad = *getTensorField(nextLayerBack, (Point) {n, 0, 0}) * activatorDerivative(inputValue);
        *getTensorField(fcLayer->grad, (Point) {n, 0, 0}) = grad;
        for (int i = 0; i < fcLayer->in->size->H; i++) {
            for (int j = 0; j < fcLayer->in->size->W; j++) {
                for (int k = 0; k < fcLayer->in->size->D; k++) {
                    Point point = {i, j, k};
                    int index = convertPointToIndex(point, *fcLayer->in->size);
                    double weight = *getTensorField(fcLayer->weights, (Point) {index, n, 0});
                    *getTensorField(fcLayer->back, point) += grad * weight;
                }
            }
        }

    }


    for (int n = 0; n < fcLayer->out->size->H; n++) {
        double grad = *getTensorField(fcLayer->grad, (Point) {n, 0, 0});
        double oldGrad = *getTensorField(fcLayer->oldGrad, (Point) {n, 0, 0});
        for (int i = 0; i < fcLayer->in->size->H; i++) {
            for (int j = 0; j < fcLayer->in->size->W; j++) {
                for (int k = 0; k < fcLayer->in->size->D; k++) {
                    Point point = {i, j, k};
                    double inValue = *getTensorField(fcLayer->in, point);
                    int index = convertPointToIndex(point, *fcLayer->in->size);
                    double weight = *getTensorField(fcLayer->weights, (Point) {index, n, 0});
                    *getTensorField(fcLayer->weights, (Point) {index, n, 0}) = updateWeight(weight, grad, oldGrad,
                                                                                            inValue);
                }
            }
        }
        *getTensorField(fcLayer->oldGrad, (Point) {n, 0, 0}) = updateGradient(grad, oldGrad);
    }
}

void freeFcLayer(FcLayer *fcLayer) {
    debugAssert(fcLayer != NULL);
    freeTensor(fcLayer->back);
    freeTensor(fcLayer->out);
    freeTensor(fcLayer->weights);
    freeTensor(fcLayer->grad);
    freeTensor(fcLayer->oldGrad);
    freeTensor(fcLayer->input);
    free(fcLayer);
}