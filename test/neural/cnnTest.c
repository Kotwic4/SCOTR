#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cnnTest.h"
#include "../../src/math/point.h"
#include "../../src/neural/cnn.h"

void testCnnAll() {
    srand((unsigned int) time(NULL));
    Point point = {200, 100, 3};
    Cnn *cnn = initCnn(&point);
    addConvLayer(cnn, 1, 5, 10, 2);
    addReluLayer(cnn);
    addPoolLayer(cnn, 2, 2);
    addConvLayer(cnn, 1, 3, 10, 1);
    addReluLayer(cnn);
    addPoolLayer(cnn, 2, 2);
    addFcLayer(cnn, 80);
    addReluLayer(cnn);
    addFcLayer(cnn, 10);
    Tensor *in = initTensor(&point);
    Tensor *out = getForward(cnn, in);
    for (int i = 0; i < 10; i++) {
        printf("%lf\n", *getFasterTensorField(out, i));
    }
    freeCnn(cnn);
    freeTensor(in);
}
