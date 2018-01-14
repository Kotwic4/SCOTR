#include "convLayerTest.h"
#include "../../main/math/point.h"
#include "../../main/math/tensor.h"
#include "../../main/neural/convLayer.h"

void testActivateConvLayer() {
    Point *point = copyPoint((Point) {5, 5, 3});
    Tensor *in = initTensor(point);
    ConvLayer *convLayer = initConvLayer(2, 3, 1, 2, point);
    free(point);
    double values[] = {2, 1, 2, 2, 0,
                       0, 1, 0, 0, 1,
                       2, 2, 0, 2, 1,
                       1, 0, 2, 0, 1,
                       0, 1, 2, 0, 2,

                       1, 1, 2, 1, 2,
                       2, 1, 1, 2, 2,
                       0, 2, 0, 1, 2,
                       1, 1, 1, 1, 0,
                       2, 1, 1, 2, 1,


                       1, 1, 2, 2, 1,
                       0, 1, 0, 0, 0,
                       2, 0, 0, 0, 1,
                       1, 2, 1, 0, 0,
                       2, 2, 0, 2, 2};
    double filter1[] = {-1, -1, 1, 0, 0, 0, -1, -1, 0,
                        -1, -1, 1, 1, -1, -1, 0, 0, 1,
                        1, 1, 0, 0, 1, -1, 1, 0, -1};
    double filter2[] = {1, 0, -1, -1, 1, 0, -1, 0, -1,
                        1, -1, 0, 1, -1, -1, 1, -1, 1,
                        0, -1, 1, -1, -1, 0, 0, -1, -1};
    double expected[] = {-2, 0, -1,
                         -2, 2, -6,
                         -3, -4, 1,

                         -4, -3, -6,
                         -7, 0, -2,
                         -5, -4, 0};
    for (int i = 0; i < 75; i++) {
        *getFasterTensorField(in, i) = values[i];
    }
    Tensor *filt = *(Tensor **) getVectorField(convLayer->filt, 0);
    Tensor *filt2 = *(Tensor **) getVectorField(convLayer->filt, 1);
    for (int i = 0; i < 27; i++) {
        *getFasterTensorField(filt, i) = filter1[i];
        *getFasterTensorField(filt2, i) = filter2[i];
    }
    activateLayer((Layer *) convLayer, in);
    assert(convLayer->in == in);
    for (int i = 0; i < 18; i++) {
        assert(*getFasterTensorField(convLayer->out, i) == expected[i]);
    }
    freeConvLayer(convLayer);
    freeTensor(in);
}

void testConvLayerAll() {
    testActivateConvLayer();
}
