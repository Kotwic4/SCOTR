#include <mem.h>
#include "mnistExample.h"

#define MNIST_CNN "mnistCnn.txt"
#define MNIST_TRAIN_FILE "./mnist/train/train.txt"
//#define MNIST_TRAIN_FILE "./results.txt"
#define MNIST_TEST_FILE "./mnist/test/test.txt"

Tensor *getMnistFile(FILE * file) {
    Point point = {28, 28, 1};
    Tensor *tensor = initTensor(&point);
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            int x;
            fscanf(file, "%d", &x);
            *getFasterTensorField(tensor, i * 28 + j) = x / 255.0;
        }
    }
    return tensor;
}

Tensor *getMnist(char * filename) {
    Tensor *tensor = NULL;
    FILE* file = fopen(filename,"r");
    if (file) {
        tensor = getMnistFile(file);
        fclose(file);
    } else {
        printf("ERROR: Can't open file %s", filename);
    }
    return tensor;
}

TestCase *mnistReadTestCasesFile(FILE * file, int caseNumber) {
    TestCase *testCases = calloc((size_t) caseNumber, sizeof(TestCase));
    for (int i = 0; i < caseNumber; i++) {
        int expected;
        fscanf(file, "%d\n", &expected);
        Tensor *in = getMnistFile(file);
        Tensor *back = returnOutputTensor(10, expected);
        testCases[i].input = in;
        testCases[i].expected = back;
    }
    return testCases;
}

TestCase *mnistReadTestCasesFiles(FILE * file, int caseNumber) {
    char buffor[255];
    TestCase *testCases = calloc((size_t) caseNumber, sizeof(TestCase));
    for (int i = 0; i < caseNumber; i++) {
        int expected;
        fscanf(file, "%s %d\n", buffor, &expected);
        FILE * file2 = fopen(buffor, "r");
        if (file2) {
            Tensor *in = getMnistFile(file2);
            Tensor *back = returnOutputTensor(10, expected);
            testCases[i].input = in;
            testCases[i].expected = back;
            fclose(file2);
        } else {
            printf("ERROR: Can't open file %s", buffor);
        }
    }
    return testCases;
}

TestCase *mnistReadTestCases(char *filename) {
    int caseNumber;
    TestCase *testCases = NULL;
    FILE *file = fopen(filename, "r");
    if (file) {
        fscanf(file,"%d",&caseNumber);
        testCases = mnistReadTestCasesFile(file,caseNumber);
        fclose(file);
    } else {
        printf("ERROR: Can't open file %s", filename);
    }
    return testCases;
}

void mnistTrain(Cnn *cnn, int iterationNumber) {
    FILE *file = fopen(MNIST_TRAIN_FILE, "r");
    if (file) {
        int caseNumber;
        fscanf(file,"%d",&caseNumber);
        TestCase *testCases = mnistReadTestCasesFile(file, caseNumber);
        fclose(file);
        trainCnnTestCases(cnn, testCases, caseNumber, iterationNumber);
        for (int i = 0; i < caseNumber; i++) {
            freeTensor(testCases[i].input);
            freeTensor(testCases[i].expected);
        }
        free(testCases);
    } else {
        printf("ERROR: Can't open file %s", MNIST_TRAIN_FILE);
    }
}

void mnistTest(Cnn *cnn) {
    FILE *file = fopen(MNIST_TEST_FILE, "r");
    if (file) {
        int caseNumber;
        int wrong = 0;
        fscanf(file,"%d",&caseNumber);
        for(int i = 0; i < caseNumber; i++){
            if(i % 1000 == 0){
                printf("Done: %d testCases from %d [wrongs: %d]\n", i, caseNumber, wrong);
            }
            int expected;
            fscanf(file, "%d\n", &expected);
            Tensor *in = getMnistFile(file);
            int actual = getResult(cnn,in);
            if(expected != actual){
                wrong++;
            }
            freeTensor(in);
        }
        fclose(file);
        printf("Bledy na %d z %d", wrong, caseNumber);
    } else {
        printf("ERROR: Can't open file %s", MNIST_TRAIN_FILE);
    }
}

void mnistRepl(Cnn *cnn) {
    printf("Welcome to MNIST repl mode\n");
    char buff[255];
    while (scanf("%s", buff)) {
        if (strcmp(buff, "quit") == 0) {
            break;
        }
        Tensor *in = getMnist(buff);
        Tensor *out = printForwad(cnn, in);
        int result = getResultFromTensor(out);
        printf("%d\n", result);
        freeTensor(in);
    }
}

Cnn* getMnistCnn(){
    Point inSize = {28, 28, 1};
    Cnn *cnn = initCnn(&inSize);
    addConvLayer(cnn, 1, 5, 8, 0);
    addReluLayer(cnn);
    addPoolLayer(cnn, 2, 2);
    addFcLayer(cnn, 10);
    return cnn;
}

void mnistMain() {
    Cnn * cnn = getMnistCnn();
    mnistTrain(cnn, 1);
    mnistRepl(cnn);
    freeCnn(cnn);
}

void mnistMainRepl() {
    Cnn *cnn;
    FILE *file;
    file = fopen(MNIST_CNN, "r");
    cnn = readCnnFile(file);
    fclose(file);
    mnistRepl(cnn);
    freeCnn(cnn);
}

void mnistMainTest() {
    Cnn *cnn;
    FILE *file;
    file = fopen(MNIST_CNN, "r");
    cnn = readCnnFile(file);
    fclose(file);
    mnistTest(cnn);
    freeCnn(cnn);
}

void mnistMainTrain() {
    Cnn *cnn = getMnistCnn();
    mnistTrain(cnn, 40);
    FILE *file = fopen(MNIST_CNN, "w");
    saveCnnFile(file, cnn);
    fclose(file);
    freeCnn(cnn);
}
