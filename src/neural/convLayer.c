#include <stdio.h>
#include <stdlib.h>
#include "convLayer.h"
#include "grad.h"
#include "../IOlib/tensor_procesing.h"

ConvLayer *initConvLayer(int stride, int spatialExtent, int padding, int filtersNumber, Point *inSize) {
    debugAssert(inSize != NULL);
    debugAssert((inSize->H - spatialExtent + 2 * padding) % stride == 0);
    debugAssert((inSize->W - spatialExtent + 2 * padding) % stride == 0);
    Point outSize;
    outSize.W = (inSize->W - spatialExtent + 2 * padding) / stride + 1;
    outSize.H = (inSize->H - spatialExtent + 2 * padding) / stride + 1;
    outSize.D = filtersNumber;
    ConvLayer *convLayer = malloc(sizeof(ConvLayer));
    convLayer->type = conv;
    convLayer->in = NULL;
    convLayer->out = initTensor(&outSize);
    convLayer->back = initTensor(inSize);
    convLayer->stride = stride;
    convLayer->spatial = spatialExtent;
    convLayer->padding = padding;
    convLayer->filt = initVector(0);
    convLayer->oldGrad = initVector(0);
    convLayer->grad = initVector(0);
    for (int i = 0; i < filtersNumber; i++) {
        Point filterSize = {spatialExtent, spatialExtent, inSize->D};
        Tensor *filter = initTensor(&filterSize);
        Tensor *filterGrad = initTensor(&filterSize);
        Tensor *filterOldGrad = initTensor(&filterSize);
        int max = multiplePointParameters(&filterSize);
        for (int index = 0; index < max; index++) {
            *getFasterTensorField(filter, index) = 1 / (double) max * rand() / (double) (RAND_MAX);
            *getFasterTensorField(filterGrad, index) = 0;
            *getFasterTensorField(filterOldGrad, index) = 0;
        }
        pushBackVector(convLayer->filt, filter);
        pushBackVector(convLayer->oldGrad, filterOldGrad);
        pushBackVector(convLayer->grad, filterGrad);
    }
    return convLayer;
}


int checkIndex(Point point, int padding, Point max) {
    if (point.H < padding || max.H + padding <= point.H) return 0;
    if (point.W < padding || max.W + padding <= point.W) return 0;
    return 1;
}

void activateConvLayer(ConvLayer *convLayer, Tensor *in) {
    convLayer->in = in;
    for (int f_i = 0; f_i < convLayer->filt->size; f_i++) {
        Tensor *filter = *(Tensor **) getVectorField(convLayer->filt, f_i);
        for (int i = 0; i < convLayer->out->size->H; i++) {
            for (int j = 0; j < convLayer->out->size->W; j++) {
                double sum = 0;
                for (int x = 0; x < convLayer->spatial; x++) {
                    for (int y = 0; y < convLayer->spatial; y++) {
                        for (int z = 0; z < in->size->D; z++) {
                            double weight = *getTensorField(filter, (Point) {x, y, z});
                            Point index = {x + i * convLayer->stride, y + j * convLayer->stride, z};
                            double val = 0;
                            if (checkIndex(index, convLayer->padding, *in->size)) {
                                Point newIndex = {index.H - convLayer->padding, index.W - convLayer->padding, index.D};
                                val = *getTensorField(in, newIndex);
                            }
                            sum += val * weight;
                        }
                    }
                }
                *getTensorField(convLayer->out, (Point) {i, j, f_i}) = sum;
            }
        }
    }
}


void backPropConvLayer(ConvLayer *convLayer, Tensor *nextLayerBack) {

    int spatialExtent = convLayer->spatial;
    double stride = convLayer->stride;
    Point inSize = *convLayer->back->size;
    Point outSize = *convLayer->out->size;
    int padding = convLayer->padding;
    for (int f_i = 0; f_i < convLayer->grad->size; f_i++) {
        Tensor *filterGrad = *(Tensor **) getVectorField(convLayer->grad, f_i);
        for (int i = 0; i < spatialExtent; i++) {
            for (int j = 0; j < spatialExtent; j++) {
                for (int k = 0; k < inSize.D; k++) {
                    *getTensorField(filterGrad, (Point) {i, j, k}) = 0;
                }
            }
        }
    }

    for (int i = 0; i < inSize.H; i++) {
        for (int j = 0; j < inSize.W; j++) {
            for (int k = 0; k < inSize.D; k++) {
                int x_min = normalizeValue((i + padding - spatialExtent + 1) / stride, outSize.H - 1, 1);
                int x_max = normalizeValue((i + padding) / stride, outSize.H - 1, 0);
                int y_min = normalizeValue((j + padding - spatialExtent + 1) / stride, outSize.W - 1, 1);
                int y_max = normalizeValue((j + padding) / stride, outSize.W - 1, 0);
                Point inIndex = {i, j, k};
                double sum = 0;
                for (int x = x_min; x <= x_max; x++) {
                    for (int y = y_min; y <= y_max; y++) {
                        for (int z = 0; z < convLayer->filt->size; z++) {
                            Tensor *filter = *(Tensor **) getVectorField(convLayer->filt, z);
                            Tensor *filterGrad = *(Tensor **) getVectorField(convLayer->grad, z);
                            Point outIndex = {x, y, z};
                            Point filterIndex = {i + padding - x_min, j + padding - y_min, k};
                            double filter_value = *getTensorField(filter, filterIndex);
                            double back_value = *getTensorField(nextLayerBack, outIndex);
                            double in_val = *getTensorField(convLayer->in, inIndex);
                            sum += filter_value * back_value;
                            *getTensorField(filterGrad, filterIndex) += in_val * back_value;
                        }
                    }
                }
                *getTensorField(convLayer->back, inIndex) = sum;
            }
        }
    }

    for (int f_i = 0; f_i < convLayer->grad->size; f_i++) {
        Tensor *filter = *(Tensor **) getVectorField(convLayer->filt, f_i);
        Tensor *filterOldGrad = *(Tensor **) getVectorField(convLayer->oldGrad, f_i);
        Tensor *filterGrad = *(Tensor **) getVectorField(convLayer->grad, f_i);
        for (int i = 0; i < spatialExtent; i++) {
            for (int j = 0; j < spatialExtent; j++) {
                for (int k = 0; k < inSize.D; k++) {
                    Point index = {i, j, k};
                    double weight = *getTensorField(filter, index);
                    double grad = *getTensorField(filterGrad, index);
                    double oldGrad = *getTensorField(filterOldGrad, index);
                    *getTensorField(filter, index) = updateWeight(weight, grad, oldGrad, 1);
                    *getTensorField(filterOldGrad, index) = updateGradient(grad, oldGrad);
                }
            }
        }
    }


}

void freeConvLayer(ConvLayer *convLayer) {
    debugAssert(convLayer != NULL);
    freeTensor(convLayer->back);
    freeTensor(convLayer->out);
    for (int i = 0; i < convLayer->filt->size; i++) {
        freeTensor(*(Tensor **) getVectorField(convLayer->filt, i));
        freeTensor(*(Tensor **) getVectorField(convLayer->grad, i));
        freeTensor(*(Tensor **) getVectorField(convLayer->oldGrad, i));
    }
    freeVector(convLayer->filt);
    freeVector(convLayer->grad);
    freeVector(convLayer->oldGrad);
    free(convLayer);
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
    convLayer->filt = initVector(0);
    convLayer->oldGrad = initVector(0);
    convLayer->grad = initVector(0);
    for (int i = 0; i < filtersNumber; i++) {
        Tensor *filter = readTensorFromFile(file);
        Tensor *filterGrad = readTensorFromFile(file);
        Tensor *filterOldGrad = readTensorFromFile(file);
        pushBackVector(convLayer->filt, filter);
        pushBackVector(convLayer->oldGrad, filterOldGrad);
        pushBackVector(convLayer->grad, filterGrad);
    }
    return convLayer;
}

void saveConvLayerFile(FILE *file, ConvLayer *layer) {
    int filtersNumber = layer->filt->size;
    savePointFile(file, *layer->out->size);
    savePointFile(file, *layer->back->size);
    fprintf(file, "%d %d %d %d\n", layer->stride, layer->spatial, layer->padding, filtersNumber);
    for (int i = 0; i < filtersNumber; i++) {
        writeTensorToFile(*(Tensor **)getVectorField(layer->filt, i), file);
        writeTensorToFile(*(Tensor **)getVectorField(layer->grad, i), file);
        writeTensorToFile(*(Tensor **)getVectorField(layer->oldGrad, i), file);
    }
}

