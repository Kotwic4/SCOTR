#include "poolLayerTest.h"

void testInitPoolLayer() {
    Point *point = copyPoint((Point) {9, 3, 3});
    PoolLayer *poolLayer = initPoolLayer(3, 2, point);
    free(point);
    assert(poolLayer != NULL);
    assert(poolLayer->type == pool);
    assert(poolLayer->in == NULL);
    assert(poolLayer->back != NULL);
    assert(poolLayer->back->size->H == 9);
    assert(poolLayer->back->size->W == 3);
    assert(poolLayer->back->size->D == 3);
    assert(poolLayer->out != NULL);
    assert(poolLayer->out->size->H == 3);
    assert(poolLayer->out->size->W == 1);
    assert(poolLayer->out->size->D == 3);
    assert(poolLayer->stride == 3);
    assert(poolLayer->spatialExtent == 2);
    freePoolLayer(poolLayer);
}

void testActivatePoolLayer() {
    Point *point = copyPoint((Point) {4, 4, 2});
    Tensor *in = initTensor(point);
    PoolLayer *reluLayer = initPoolLayer(2, 2, point);
    free(point);
    double values[] = {1, 1, 2, 4, 5, 6, 7, 8, 3, 2, 1, 0, 1, 2, 3, 4,
                       1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    double expected[] = {6, 8, 3, 4,
                         6, 8, 14, 16};
    for (int i = 0; i < 32; i++) {
        *getFasterTensorField(in, i) = values[i];
    }

    activateLayer((Layer *) reluLayer, in);

    assert(reluLayer->in == in);
    for (int i = 0; i < 8; i++) {
        assert(*getFasterTensorField(reluLayer->out, i) == expected[i]);
    }
    freePoolLayer(reluLayer);
    freeTensor(in);
}

void testBackPropPoolLayer() {
    Point *point = copyPoint((Point) {4, 4, 2});
    Point *point2 = copyPoint((Point) {2, 2, 2});
    Tensor *in = initTensor(point);
    Tensor *back = initTensor(point2);
    PoolLayer *reluLayer = initPoolLayer(2, 2, point);
    free(point);
    free(point2);
    double valuesIn[] = {1, 1, 2, 4,
                         5, 6, 7, 8,
                         3, 2, 1, 0,
                         1, 2, 3, 4,

                         1, 2, 3, 4,
                         5, 6, 7, 8,
                         9, 10, 11, 12,
                         13, 14, 15, 16};
    double valuesBack[] = {5, 4,
                           3, 2,

                           1, 2,
                           3, 4};
    double expected[] = {0, 0, 0, 0,
                         0, 5, 0, 4,
                         3, 0, 0, 0,
                         0, 0, 0, 2,

                         0, 0, 0, 0,
                         0, 1, 0, 2,
                         0, 0, 0, 0,
                         0, 3, 0, 4};
    for (int i = 0; i < 32; i++) {
        *getFasterTensorField(in, i) = valuesIn[i];
    }
    for (int i = 0; i < 8; i++) {
        *getFasterTensorField(back, i) = valuesBack[i];
    }
    activatePoolLayer(reluLayer, in);

    backPropLayer((Layer *) reluLayer, back);

    assert(reluLayer->in == in);
    for (int i = 0; i < 32; i++) {
        assert(*getFasterTensorField(reluLayer->back, i) == expected[i]);
    }
    freePoolLayer(reluLayer);
    freeTensor(in);
    freeTensor(back);
}

void testFreePoolLayer() {
    Point *point = copyPoint((Point) {4, 4, 3});
    for (int i = 0; i < 10000; i++) {
        PoolLayer *poolLayer = initPoolLayer(2, 2, point);

        freeLayer((Layer *) poolLayer);

    }
    free(point);
}

void testPoolLayerAll() {
    testInitPoolLayer();
    testActivatePoolLayer();
    testBackPropPoolLayer();
    testFreePoolLayer();
}
