#include "mintExample.h"

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
    mintTrain(cnn, 20, 100);
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
    mintTrain(cnn, 20, 10);
    FILE *file = fopen("cnn.txt", "w");
    saveCnnFile(file, cnn);
    fclose(file);
    freeCnn(cnn);
}