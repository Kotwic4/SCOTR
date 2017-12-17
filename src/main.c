#include <stdio.h>
#include <time.h>
#include <mem.h>
#include "IOlib/tensor_procesing.h"
#include "neural/cnn.h"

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
    file = fopen("results.txt", "r");
    char buff[255];
    char buff2[255];
    while(fscanf(file,"%s %s\n",buff,buff2) == 2){
        printf("%s, %s\n", buff,buff2);
        Tensor * in = readImagineToTensor(buff);
        int k = strlen(buff2);
        Tensor * back = returnOutputTensor(10,k-1);
        TestCase testCase = {in,back};
        train(cnn,&testCase);
        freeTensor(in);
        freeTensor(back);
    }
    fclose(file);
    file = fopen("results.txt","r");
    fscanf(file,"%s %s\n",buff,buff2);
    printf("%s, %s\n", buff,buff2);
    Tensor * in = readImagineToTensor(buff);
    int k = strlen(buff2);
    Tensor * out = getForward(cnn,in);
    for(int i = 0; i < 10; i++){
        printf("%lf\n", *getFasterTensorField(out,i));
    }
    freeTensor(in);
    fclose(file);
//
    return 0;
}
