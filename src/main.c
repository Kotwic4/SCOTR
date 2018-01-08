#include <stdio.h>
#include <time.h>
#include <string.h>
#include "IOlib/tensor_procesing.h"
#include "neural/cnn.h"


Tensor *initTensorArray(Point *inPoint, const double *array) {
    Tensor *result = initTensor(inPoint);
    for (int i = 0; i < multiplePointParameters(inPoint); i++) {
        *getFasterTensorField(result, i) = array[i];
    }
    return result;
}

void printForwad(Cnn *cnn, Tensor *in) {
    Tensor *out = getForward(cnn, in);
    for (int i = 0; i < multiplePointParameters(out->size); i++) {
        printf("[%d] : %f", i, *getFasterTensorField(out, i));
    }
    printf("\n");
}

void trainCnnTestCases(Cnn *cnn, TestCase *testCases, int caseNumber, int iterationNumber) {
    for (int i = 0; i < iterationNumber; i++) {
        if(i%10 == 0){
            printf("%d\n", i);
        }
        for (int j = 0; j < caseNumber; j++) {
            train(cnn, &testCases[j]);
        }
    }
}


void simpleCnnMain() {
    Point inSize = {3, 1, 1};
    Point outSize = {2, 1, 1};

    Cnn *cnn = initCnn(&inSize);
    addFcLayer(cnn, 2);

    double array0[] = {0, 0, 1};
    double array1[] = {1, 1, 1};
    double array2[] = {1, 0, 1};
    double array3[] = {0, 1, 1};
    double arrayN[] = {1, 0, 0};

    double arrayO0[] = {0, 0};
    double arrayO1[] = {1, 1};
    double arrayO2[] = {1, 0};
    double arrayO3[] = {0, 1};
    //double arrayON[] = {1, 0};

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

//    trainCnnTestCases(cnn, testCase, 4, 10000);
    trainCnnTestCases(cnn, testCase, 4, 10);

    printForwad(cnn, in0);
    printForwad(cnn, in1);
    printForwad(cnn, in2);
    printForwad(cnn, in3);
    printForwad(cnn, inN);

    FILE *file = fopen("cnn.txt", "w");
    saveCnnFile(file,cnn);
    fclose(file);
    freeCnn(cnn);

    file = fopen("cnn.txt", "r");
    cnn = readCnnFile(file);
    fclose(file);
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

Tensor *getMnist(char *filename) {
    Point point = {28, 28, 1};
    Tensor *tensor = initTensor(&point);
    FILE *file = fopen(filename, "r");
    if (file) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                int x;
                fscanf(file, "%d", &x);
                *getFasterTensorField(tensor, i * 28 + j) = x / 255;
            }
        }
        fclose(file);
    } else {
        printf("ERROR: Can't open file %s", filename);
    }
    return tensor;
}

TestCase *mintReadTestCases(char *filename, int caseNumber) {
    char imageFileName[255];
    TestCase *testCases = calloc(sizeof(TestCase), (size_t) caseNumber);
    FILE *file = fopen(filename, "r");
    if (file) {
        for (int i = 0; i < caseNumber; i++) {
            int k;
            fscanf(file, "%s %d\n", imageFileName, &k);
            Tensor *in = getMnist(imageFileName);
            Tensor *back = returnOutputTensor(10, k);
            testCases[i].input = in;
            testCases[i].expected = back;
        }
        fclose(file);
    } else {
        printf("ERROR: Can't open file %s", filename);
    }
    return testCases;
}

void mintTrain(Cnn *cnn, int caseNumber, int iterationNumber) {
    TestCase *testCases = mintReadTestCases("test.txt", caseNumber);
    trainCnnTestCases(cnn, testCases, caseNumber, iterationNumber);
    for (int i = 0; i < caseNumber; i++) {
        freeTensor(testCases[i].input);
        freeTensor(testCases[i].expected);
    }
    free(testCases);
}

void mintRepl(Cnn *cnn) {
    printf("Welcome to MINT repl mode\n");
    char buff[255];
    while (scanf("%s", buff)) {
        if (strcmp(buff, "quit") == 0) {
            break;
        }
        Tensor *in = getMnist(buff);
        printForwad(cnn, in);
        freeTensor(in);
    }
}

void mintMain() {
    Point inSize = {28, 28, 1};
    Cnn *cnn = initCnn(&inSize);
    addConvLayer(cnn, 1, 5, 8, 0);
    addReluLayer(cnn);
    addPoolLayer(cnn, 2, 2);
    addFcLayer(cnn, 10);
    mintTrain(cnn, 20, 1000);
    mintRepl(cnn);
//    FILE *file = fopen("cnn.txt", "w");
//    saveCnnFile(file,cnn);
//    fclose(file);
//    freeCnn(cnn);
//    file = fopen("cnn.txt", "r");
//    cnn = readCnnFile(file);
//    fclose(file);
//    mintRepl(cnn);
    freeCnn(cnn);
}

void mintMainRepl() {
    Cnn *cnn;
    FILE *file;
    file = fopen("cnn.txt", "r");
    cnn = readCnnFile(file);
    fclose(file);
    mintRepl(cnn);
    freeCnn(cnn);
}

void mintMainTrain() {
    Point inSize = {28, 28, 1};
    Cnn *cnn = initCnn(&inSize);
    addConvLayer(cnn, 1, 5, 8, 0);
    addReluLayer(cnn);
    addPoolLayer(cnn, 2, 2);
    addFcLayer(cnn, 10);
    mintTrain(cnn, 20, 200);
    FILE *file = fopen("cnn.txt", "w");
    saveCnnFile(file,cnn);
    fclose(file);
    freeCnn(cnn);
}



int main() {
    srand((unsigned int) time(NULL));
//    simpleCnnMain();
//    mintMain();
    mintMainTrain();
    mintMainRepl();
    return 0;
}