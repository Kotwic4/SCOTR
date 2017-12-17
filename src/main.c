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
#define N 10 //case number
#define M 10 //iteration number
    char buff[255];
    char buff2[255];
    TestCase testCase[N];
    file = fopen("results.txt", "r");
    for(int i = 0; i < N; i++){
        fscanf(file,"%s %s\n",buff,buff2);
        Tensor * in = readImagineToTensor(buff);
        int k = strlen(buff2);
        Tensor * back = returnOutputTensor(10,k-1);
        testCase[i].input = in;
        testCase[i].expected = back;
    }
    fclose(file);
    for(int i = 0; i < M; i++){
        printf("%d\n", i);
        for(int j = 0; j < N; j++){
            printf("%d %d\n", i, j);
            train(cnn,&testCase[j]);
        }
        Tensor * in = testCase[0].input;
        Tensor * out = getForward(cnn,in);
        for(int k = 0; k < 10; k++){
            printf("[%d] : %lf ", k+1, *getFasterTensorField(out,k));
        }
        printf("\n");
    }
    for(int i = 0; i < N; i++){
        printf("\n%d ", i);
        Tensor * in = testCase[0].input;
        Tensor * out = getForward(cnn,in);
        for(int k = 0; k < 10; k++){
            printf("[%d] : %lf ", k+1, *getFasterTensorField(out,k));
        }
    }
    for(int i = 0; i< N; i++){
        freeTensor(testCase[i].input);
        freeTensor(testCase[i].expected);
    }
    return 0;
}
