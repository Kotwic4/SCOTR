#include "reluLayerTest.h"

void testInitReluLayer() {
    Point *point = copyPoint((Point) {1, 2, 3});
    ReluLayer *reluLayer = initReluLayer(point);
    free(point);
    assert(reluLayer != NULL);
    assert(reluLayer->type == relu);
    assert(reluLayer->in == NULL);
    assert(reluLayer->back != NULL);
    assert(reluLayer->back->size->height == 1);
    assert(reluLayer->back->size->width == 2);
    assert(reluLayer->back->size->depth == 3);
    assert(reluLayer->out != NULL);
    assert(reluLayer->out->size->height == 1);
    assert(reluLayer->out->size->width == 2);
    assert(reluLayer->out->size->depth == 3);
    freeReluLayer(reluLayer);
}

void testActivateReluLayer() {
    Point *point = copyPoint((Point) {1, 2, 3});
    Tensor *in = initTensor(point);
    ReluLayer *reluLayer = initReluLayer(point);
    free(point);
    double values[] = {1.0, -1.0, 0.0, 2.0, -3.0, 3.0};
    double expected[] = {1.0, 0.0, 0.0, 2.0, 0.0, 3.0};
    for (int i = 0; i < 6; i++) {
        *getFasterTensorField(in, i) = values[i];
    }

    activateLayer((Layer *) reluLayer, in);

    assert(reluLayer->in == in);
    for (int i = 0; i < 6; i++) {
        assert(*getFasterTensorField(reluLayer->out, i) == expected[i]);
    }
    freeReluLayer(reluLayer);
    freeTensor(in);
}

void testBackPropReluLayer() {
    Point *point = copyPoint((Point) {1, 2, 3});
    Tensor *in = initTensor(point);
    Tensor *back = initTensor(point);
    ReluLayer *reluLayer = initReluLayer(point);
    free(point);
    double valuesIn[] = {1.0, -1.0, 0.0, 2.0, -3.0, 3.0};
    double valuesBack[] = {1.0, 0.0, 0.0, 2.0, 0.0, 2.0};
    double expected[] = {1.0, 0.0, 0.0, 2.0, 0.0, 2.0};
    for (int i = 0; i < 6; i++) {
        *getFasterTensorField(in, i) = valuesIn[i];
        *getFasterTensorField(back, i) = valuesBack[i];
    }
    activateReluLayer(reluLayer, in);

    backPropLayer((Layer *) reluLayer, back);

    for (int i = 0; i < 6; i++) {
        assert(*getFasterTensorField(reluLayer->back, i) == expected[i]);
    }
    freeReluLayer(reluLayer);
    freeTensor(in);
    freeTensor(back);
}

void testFreeReluLayer() {
    Point *point = copyPoint((Point) {1, 2, 3});
    for (int i = 0; i < 10000; i++) {
        ReluLayer *reluLayer = initReluLayer(point);

        freeLayer((Layer *) reluLayer);

    }
    free(point);
}

void testReluLayerAll() {
    testInitReluLayer();
    testActivateReluLayer();
    testBackPropReluLayer();
    testFreeReluLayer();
}
