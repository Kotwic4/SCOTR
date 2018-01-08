#include "cnnUtil.h"

void printForwad(Cnn *neuralNetwork, Tensor *input) {
    Tensor *out = getForward(neuralNetwork, input);
    for (int i = 0; i < multiplePointParameters(out->size); i++) {
        printf("[%d] : %f", i, *getFasterTensorField(out, i));
    }
    printf("\n");
}

void trainCnnTestCases(Cnn *neuralNetwork, TestCase *testCases, int caseNumber, int iterationNumber) {
    for (int i = 0; i < iterationNumber; i++) {
        if (i % 100 == 0) {
            printf("Done: %d iterations from %d [%f %%]\n", i, iterationNumber, i * 100.0 / iterationNumber);
        }
        for (int j = 0; j < caseNumber; j++) {
            train(neuralNetwork, &testCases[j]);
        }
    }
    printf("Done!\n");
}
