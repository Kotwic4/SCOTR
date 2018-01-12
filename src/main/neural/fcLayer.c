#include "fcLayer.h"

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

    for (int i = 0; i < multiplePointParameters(&outPoint); ++i) {
        *getFasterTensorField(fcLayer->grad, i) = 0;
        *getFasterTensorField(fcLayer->oldGrad, i) = 0;
    }

    int max = multiplePointParameters(inSize);
    double maxVal = 2.19722 / max;

    for (int i = 0; i < outSize; ++i) {
        for (int j = 0; j < max; ++j) {
            Point index = {j, i, 0};
            *getTensorField(fcLayer->weights, &index) = maxVal * rand() / (double) RAND_MAX;
        }
    }

    return fcLayer;
}

double activatorFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}

double activatorDerivative(double value) {
    double sig = activatorFunction(value);
    return sig * (1 - sig);
}

void activateFcLayer(FcLayer *fcLayer, Tensor *in) {
    fcLayer->in = in;
    for (int n = 0; n < fcLayer->out->size->height; ++n) {
        double inputValue = 0;
        for (int inIndex = 0; inIndex < multiplePointParameters(in->size); ++inIndex) {
            double inValue = *getFasterTensorField(in, inIndex);
            Point weightIndex = {inIndex, n, 0};
            double weight = *getTensorField(fcLayer->weights, &weightIndex);
            inputValue += inValue * weight;
        }
        Point outIndex = {n, 0, 0};
        *getTensorField(fcLayer->input, &outIndex) = inputValue;
        *getTensorField(fcLayer->out, &outIndex) = activatorFunction(inputValue);
    }
}

void backPropFcLayer(FcLayer *fcLayer, Tensor *nextLayerBack) {

    for (int inIndex = 0; inIndex < multiplePointParameters(fcLayer->in->size); ++inIndex) {
        *getFasterTensorField(fcLayer->back, inIndex) = 0;
    }

    for (int n = 0; n < fcLayer->out->size->height; ++n) {
        Point outIndex = {n, 0, 0};
        double inputValue = *getTensorField(fcLayer->input, &outIndex);
        double grad = *getTensorField(nextLayerBack, &outIndex) * activatorDerivative(inputValue);
        double oldGrad = *getTensorField(fcLayer->oldGrad, &outIndex);
        *getTensorField(fcLayer->grad, &outIndex) = grad;
        for (int inIndex = 0; inIndex < multiplePointParameters(fcLayer->in->size); ++inIndex) {
            Point weightIndex = {inIndex, n, 0};
            double weight = *getTensorField(fcLayer->weights, &weightIndex);
            *getFasterTensorField(fcLayer->back, inIndex) += grad * weight;

            double inValue = *getFasterTensorField(fcLayer->in, inIndex);
            *getTensorField(fcLayer->weights, &weightIndex) = updateWeight(weight, grad, oldGrad, inValue);
        }
        *getTensorField(fcLayer->oldGrad, &outIndex) = updateGradient(grad, oldGrad);
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
