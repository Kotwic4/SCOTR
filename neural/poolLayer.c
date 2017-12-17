#include "poolLayer.h"

PoolLayer *initPoolLayer(int stride, int spatialExtent, Point *inSize) {
    debugAssert(inSize != NULL);
    debugAssert((inSize->H - spatialExtent) % stride == 0);
    debugAssert((inSize->W - spatialExtent) % stride == 0);
    debugAssert(spatialExtent > 0);
    debugAssert(stride > 0);
    int w = (inSize->W - spatialExtent) / stride + 1;
    int h = (inSize->H - spatialExtent) / stride + 1;
    Point outSize = {h,w, inSize->D};
    PoolLayer *poolLayer = malloc(sizeof(PoolLayer));
    poolLayer->type = pool;
    poolLayer->in = NULL;
    poolLayer->back = initTensor(inSize);
    poolLayer->out = initTensor(&outSize);
    poolLayer->stride = stride;
    poolLayer->spatialExtent = spatialExtent;
    return poolLayer;
}

void activatePoolLayer(PoolLayer *poolLayer, Tensor *in) {
    debugAssert(poolLayer != NULL);
    debugAssert(in != NULL);
    poolLayer->in = in;
    for (int i = 0; i < poolLayer->out->size->H; i++) {
        for (int j = 0; j < poolLayer->out->size->W; j++) {
            for (int k = 0; k < poolLayer->out->size->D; k++) {
                double max = -DBL_MAX;
                for (int x = 0; x < poolLayer->spatialExtent; x++) {
                    for (int y = 0; y < poolLayer->spatialExtent; y++) {
                        Point point = {x + i * poolLayer->stride,
                                       y + j * poolLayer->stride,
                                       k};
                        double val = *getTensorField(in, point);
                        if (val > max) max = val;
                    }
                }
                *getTensorField(poolLayer->out, (Point) {i, j, k}) = max;
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
    for (int i = 0; i < inSize.H; i++) {
        for (int j = 0; j < inSize.W; j++) {
            for (int k = 0; k < inSize.D; k++) {
                int x_min = normalizeValue((i - spatialExtent + 1) / stride, outSize.H - 1, 1);
                int x_max = normalizeValue(i / stride, outSize.H - 1, 0);
                int y_min = normalizeValue((j - spatialExtent + 1) / stride, outSize.W - 1, 1);
                int y_max = normalizeValue(j / stride, outSize.W - 1, 0);
                Point inIndex = {i, j, k};
                double sum = 0;
                for (int x = x_min; x <= x_max; x++) {
                    for (int y = y_min; y <= y_max; y++) {
                        Point outIndex = {x, y, k};
                        if (*getTensorField(poolLayer->in, inIndex) == *getTensorField(poolLayer->out, outIndex)) {
                            sum += *getTensorField(nextLayerBack, outIndex);
                        }
                    }
                }
                *getTensorField(poolLayer->back, inIndex) = sum;

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


