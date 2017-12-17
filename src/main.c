#include <stdio.h>
#include <time.h>
#include <string.h>
#include "IOlib/tensor_procesing.h"
#include "neural/cnn.h"
#include "neural/testCase.h"

int main() {
    srand(time(NULL));
    Point point = {200,100,3};
    Cnn* cnn = initCnn(&point);
    addConvLayer(cnn,1,5,10,2);
    addReluLayer(cnn);
    addPoolLayer(cnn,2,2);
    addConvLayer(cnn,1,3,10,1);
    addReluLayer(cnn);
    addPoolLayer(cnn,2,2);
    addFcLayer(cnn,80);
    addReluLayer(cnn);
    addFcLayer(cnn,10);
    FILE * file;
#define N  10
    char buff[N][255];
    char buff2[N][255];
    TestCase testCase[N];
    file = fopen("results.txt", "r");
    for(int i = 0; i < 1; i++){
        fscanf(file,"%s %s\n",buff[i],buff2[i]);
        Tensor * in = readImagineToTensor(buff[i]);
        int k = strlen(buff2[i]);
        printf("%d\n", k);
        Tensor * back = returnOutputTensor(10,k-1);
        for(int a = 0; a < 10; a++){
            printf("%lf ", *getFasterTensorField(back,a));
        }
        testCase[i].input = in;
        testCase[i].expected = back;
    }
    fclose(file);
    for(int i = 0; i < 10000; i++){
        printf("%d\n", i);
        for(int j = 0; j < 1; j++){
            printf("%d %d\n", i, j);
            train(cnn,&testCase[j]);
        }
        Tensor * in = testCase[0].input;
        Tensor * out = getForward(cnn,in);
        for(int k = 0; k < 10; k++){
            printf("%lf\n", *getFasterTensorField(out,k));
        }
    }
    for(int i = 0; i< 10; i++){
        freeTensor(testCase[i].input);
        freeTensor(testCase[i].expected);
    }
    return 0;
}
