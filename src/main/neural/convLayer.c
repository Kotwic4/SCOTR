#include "convLayer.h"

ConvLayer *initConvLayer(int stride, int spatialExtent, int padding, int filtersNumber, Point *inSize) {
    debugAssert(inSize != NULL);
    debugAssert((inSize->height - spatialExtent + 2 * padding) % stride == 0);
    debugAssert((inSize->width - spatialExtent + 2 * padding) % stride == 0);
    Point outSize;
    outSize.width = (inSize->width - spatialExtent + 2 * padding) / stride + 1;
    outSize.height = (inSize->height - spatialExtent + 2 * padding) / stride + 1;
    outSize.depth = filtersNumber;
    ConvLayer *convLayer = malloc(sizeof(ConvLayer));
    convLayer->type = conv;
    convLayer->in = NULL;
    convLayer->out = initTensor(&outSize);
    convLayer->back = initTensor(inSize);
    convLayer->stride = stride;
    convLayer->spatial = spatialExtent;
    convLayer->padding = padding;
    convLayer->filt = calloc((size_t) filtersNumber, sizeof(Tensor *));
    convLayer->oldGrad = calloc((size_t) filtersNumber, sizeof(Tensor *));
    convLayer->grad = calloc((size_t) filtersNumber, sizeof(Tensor *));
    convLayer->filterNumber = filtersNumber;
    for (int i = 0; i < filtersNumber; ++i) {
        Point filterSize = {spatialExtent, spatialExtent, inSize->depth};
        Tensor *filter = initTensor(&filterSize);
        Tensor *filterGrad = initTensor(&filterSize);
        Tensor *filterOldGrad = initTensor(&filterSize);
        int max = multiplePointParameters(&filterSize);
        for (int index = 0; index < max; ++index) {
            *getFasterTensorField(filter, index) = 1 / (double) max * rand() / (double) (RAND_MAX);
            *getFasterTensorField(filterGrad, index) = 0;
            *getFasterTensorField(filterOldGrad, index) = 0;
        }
        convLayer->filt[i] = filter;
        convLayer->oldGrad[i] = filterOldGrad;
        convLayer->grad[i] = filterGrad;
    }
    return convLayer;
}


int checkIndex(Point *point, int padding, Point *max) {
    if (point->height < padding || max->height + padding <= point->height) return 0;
    if (point->width < padding || max->width + padding <= point->width) return 0;
    return 1;
}

void activateConvLayer(ConvLayer *convLayer, Tensor *in) {
    convLayer->in = in;
    for (int f_i = 0; f_i < convLayer->filterNumber; ++f_i) {
        Tensor *filter = convLayer->filt[f_i];
        for (int i = 0; i < convLayer->out->size->height; ++i) {
            for (int j = 0; j < convLayer->out->size->width; ++j) {
                double sum = 0;
                Point outIndex = {i, j, f_i};
                for (int x = 0; x < convLayer->spatial; x++) {
                    for (int y = 0; y < convLayer->spatial; y++) {
                        for (int z = 0; z < in->size->depth; z++) {
                            Point weightIndex = {x, y, z};
                            double weight = *getTensorField(filter, &weightIndex);
                            Point index = {x + i * convLayer->stride, y + j * convLayer->stride, z};
                            double val = 0;
                            if (checkIndex(&index, convLayer->padding, in->size)) {
                                Point newIndex = {index.height - convLayer->padding,
                                                  index.width - convLayer->padding,
                                                  index.depth};
                                val = *getTensorField(in, &newIndex);
                            }
                            sum += val * weight;
                        }
                    }
                }
                *getTensorField(convLayer->out, &outIndex) = sum;
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
    for (int f_i = 0; f_i < convLayer->filterNumber; ++f_i) {
        Tensor *filterGrad = convLayer->grad[f_i];
        for (int index = 0; index < multiplePointParameters(filterGrad->size); ++index) {
            *getFasterTensorField(filterGrad, index) = 0;
        }
    }

    for (int i = 0; i < inSize.height; ++i) {
        for (int j = 0; j < inSize.width; ++j) {
            for (int k = 0; k < inSize.depth; ++k) {
                int x_min = normalizeValue((i + padding - spatialExtent + 1) / stride, outSize.height - 1, 1);
                int x_max = normalizeValue((i + padding) / stride, outSize.height - 1, 0);
                int y_min = normalizeValue((j + padding - spatialExtent + 1) / stride, outSize.width - 1, 1);
                int y_max = normalizeValue((j + padding) / stride, outSize.width - 1, 0);
                Point inIndex = {i, j, k};
                double sum = 0;
                for (int x = x_min; x <= x_max; ++x) {
                    for (int y = y_min; y <= y_max; ++y) {
                        for (int z = 0; z < convLayer->filterNumber; ++z) {
                            Tensor *filter = convLayer->filt[z];
                            Tensor *filterGrad = convLayer->grad[z];
                            Point outIndex = {x, y, z};
                            Point filterIndex = {i + padding - x_min, j + padding - y_min, k};
                            double filterValue = *getTensorField(filter, &filterIndex);
                            double backValue = *getTensorField(nextLayerBack, &outIndex);
                            double inValue = *getTensorField(convLayer->in, &inIndex);
                            sum += filterValue * backValue;
                            *getTensorField(filterGrad, &filterIndex) += inValue * backValue;
                        }
                    }
                }
                *getTensorField(convLayer->back, &inIndex) = sum;
            }
        }
    }

    for (int f_i = 0; f_i < convLayer->filterNumber; ++f_i) {
        Tensor *filter = convLayer->filt[f_i];
        Tensor *filterOldGrad = convLayer->oldGrad[f_i];
        Tensor *filterGrad = convLayer->grad[f_i];
        for (int index = 0; index < multiplePointParameters(filter->size); ++index) {
            double weight = *getFasterTensorField(filter, index);
            double grad = *getFasterTensorField(filterGrad, index);
            double oldGrad = *getFasterTensorField(filterOldGrad, index);
            *getFasterTensorField(filter, index) = updateWeight(weight, grad, oldGrad, 1);
            *getFasterTensorField(filterOldGrad, index) = updateGradient(grad, oldGrad);
        }
    }
}

void freeConvLayer(ConvLayer *convLayer) {
    debugAssert(convLayer != NULL);
    freeTensor(convLayer->back);
    freeTensor(convLayer->out);
    for (int i = 0; i < convLayer->filterNumber; ++i) {
        freeTensor(convLayer->filt[i]);
        freeTensor(convLayer->grad[i]);
        freeTensor(convLayer->oldGrad[i]);
    }
    free(convLayer->filt);
    free(convLayer->grad);
    free(convLayer->oldGrad);
    free(convLayer);
}
