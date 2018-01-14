#include "cnnUtil.h"

Tensor *printForwad(Cnn *neuralNetwork, Tensor *input) {
    Tensor *out = getForward(neuralNetwork, input);
    for (int i = 0; i < multiplePointParameters(out->size); i++) {
        printf("[%d] : %f", i, *getFasterTensorField(out, i));
    }
    printf("\n");
    return out;
}

int getResultFromTensor(Tensor *out) {
    int answer = 0;
    double max = 0;
    for (int i = 0; i < multiplePointParameters(out->size); i++) {
        double value = *getFasterTensorField(out, i);
        if (value >= max) {
            answer = i;
            max = value;
        }
    }
    return answer;
}

int getResult(Cnn *neuralNetwork, Tensor *input) {
    Tensor *out = getForward(neuralNetwork, input);
    return getResultFromTensor(out);
}

void trainCnnTestCases(Cnn *neuralNetwork, TestCase *testCases, int caseNumber, int iterationNumber) {
    for (int i = 0; i < iterationNumber; i++) {
//        printf("Done: %d iterations from %d [%f %%]\n", i, iterationNumber, i * 100.0 / iterationNumber);
//        FILE *file = fopen("tempCnn.txt", "w");
//        if (file) {
//            saveCnnFile(file,neuralNetwork);
//            fclose(file);
//        } else {
//            printf("ERROR: Can't open file temp");
//        }
        for (int j = 0; j < caseNumber; j++) {
            if (j % 1000 == 0) {
                printf("Done: %d testCases from %d [%f %%]\n", j, caseNumber, j * 100.0 / caseNumber);
            }
            train(neuralNetwork, &testCases[j]);
        }
    }
    printf("Done!\n");
}
