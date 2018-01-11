#include "simpleExample.h"

void simpleCnnMain() {
    Point inSize = {3, 1, 1};
    Point outSize = {1, 1, 1};

    Cnn *cnn = initCnn(&inSize);
    addFcLayer(cnn, 1);

    double array0[] = {0, 1, 0};
    double array1[] = {1, 1, 1};
    double array2[] = {1, 1, 0};
    double array3[] = {0, 0, 1};
    double arrayN[] = {1, 0, 0};

    double arrayO0[] = {0};
    double arrayO1[] = {1};
    double arrayO2[] = {1};
    double arrayO3[] = {0};
    //double arrayON[] = {1};

    Tensor *in0 = initTensorArray(&inSize, array0);
    Tensor *in1 = initTensorArray(&inSize, array1);
    Tensor *in2 = initTensorArray(&inSize, array2);
    Tensor *in3 = initTensorArray(&inSize, array3);
    Tensor *inN = initTensorArray(&inSize, arrayN);

    Tensor *out0 = initTensorArray(&outSize, arrayO0);
    Tensor *out1 = initTensorArray(&outSize, arrayO1);
    Tensor *out2 = initTensorArray(&outSize, arrayO2);
    Tensor *out3 = initTensorArray(&outSize, arrayO3);

    TestCase testCase[4];
    testCase[0] = (TestCase) {in0, out0};
    testCase[1] = (TestCase) {in1, out1};
    testCase[2] = (TestCase) {in2, out2};
    testCase[3] = (TestCase) {in3, out3};

    trainCnnTestCases(cnn, testCase, 4, 10000);

    printForwad(cnn, in0);
    printForwad(cnn, in1);
    printForwad(cnn, in2);
    printForwad(cnn, in3);
    printForwad(cnn, inN);

    freeCnn(cnn);
    freeTensor(in0);
    freeTensor(in1);
    freeTensor(in2);
    freeTensor(in3);
    freeTensor(inN);
    freeTensor(out0);
    freeTensor(out1);
}