#include "poolLayer.h"

PoolLayer *initPoolLayer(int stride, int spatialExtent, Point *inSize) {
    debugAssert(inSize != NULL);
    debugAssert((inSize->height - spatialExtent) % stride == 0);
    debugAssert((inSize->width - spatialExtent) % stride == 0);
    debugAssert(spatialExtent > 0);
    debugAssert(stride > 0);
    int width = (inSize->width - spatialExtent) / stride + 1;
    int height = (inSize->height - spatialExtent) / stride + 1;
    Point outSize = {height, width, inSize->depth};
    PoolLayer *poolLayer = malloc(sizeof(PoolLayer));
    poolLayer->type = pool;
    poolLayer->in = NULL;
    poolLayer->back = initTensor(inSize);
    poolLayer->out = initTensor(&outSize);
    poolLayer->stride = stride;
    poolLayer->spatialExtent = spatialExtent;
    return poolLayer;
}

double findMaxValueArea(Tensor *in, Point *index, int spatialExtent, int stride) {
    double max = -DBL_MAX;
    for (int x = 0; x < spatialExtent; x++) {
        for (int y = 0; y < spatialExtent; y++) {
            Point point = {x + index->height * stride,
                           y + index->width * stride,
                           index->depth};
            double val = *getTensorField(in, &point);
            if (val > max)
                max = val;
        }
    }
    return max;
}

void activatePoolLayer(PoolLayer *poolLayer, Tensor *in) {
    debugAssert(poolLayer != NULL);
    debugAssert(in != NULL);
    poolLayer->in = in;
    for (int i = 0; i < poolLayer->out->size->height; i++) {
        for (int j = 0; j < poolLayer->out->size->width; j++) {
            for (int k = 0; k < poolLayer->out->size->depth; k++) {
                Point point = {i, j, k};
                double max = findMaxValueArea(in, &point, poolLayer->spatialExtent, poolLayer->stride);
                *getTensorField(poolLayer->out, &point) = max;
            }
        }
    }
}

void backPropPoolLayer(PoolLayer *poolLayer, Tensor *nextLayerBack) {
    debugAssert(poolLayer != NULL);
    debugAssert(nextLayerBack != NULL);
    int spatialExtent = poolLayer->spatialExtent;
    double stride = poolLayer->stride;
    Point inSize = *poolLayer->back->size;
    Point outSize = *poolLayer->out->size;
    for (int i = 0; i < inSize.height; i++) {
        for (int j = 0; j < inSize.width; j++) {
            for (int k = 0; k < inSize.depth; k++) {
                int x_min = normalizeValue((i - spatialExtent + 1) / stride, outSize.height - 1, 1);
                int x_max = normalizeValue(i / stride, outSize.height - 1, 0);
                int y_min = normalizeValue((j - spatialExtent + 1) / stride, outSize.width - 1, 1);
                int y_max = normalizeValue(j / stride, outSize.width - 1, 0);
                Point inIndex = {i, j, k};
                double sum = 0;
                for (int x = x_min; x <= x_max; x++) {
                    for (int y = y_min; y <= y_max; y++) {
                        Point outIndex = {x, y, k};
                        if (*getTensorField(poolLayer->in, &inIndex) == *getTensorField(poolLayer->out, &outIndex)) {
                            sum += *getTensorField(nextLayerBack, &outIndex);
                        }
                    }
                }
                *getTensorField(poolLayer->back, &inIndex) = sum;
            }
        }
    }
}

void freePoolLayer(PoolLayer *poolLayer) {
    debugAssert(poolLayer != NULL);
    freeTensor(poolLayer->back);
    freeTensor(poolLayer->out);
    free(poolLayer);
}
