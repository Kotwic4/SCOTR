#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include "tensor.h"
#include "point.h"

Tensor* initTensor(Point* size){
    Tensor* thisTensor = malloc(sizeof(Tensor));
    thisTensor->data = calloc((size_t) multiplePointParameters(size), sizeof(double));
    if(!thisTensor->data){
        fprintf(stderr, "initTensor error: calloc for data error\n");
        return NULL;
    }
    thisTensor->size = copyPoint(*size);
    return thisTensor;
}

Tensor* copyTensor(Tensor* tensor){
    Tensor* thisTensor = initTensor(tensor->size);
    memcpy(thisTensor->data, tensor->data, sizeof(double)*multiplePointParameters(tensor->size));
    memcpy(thisTensor->size, tensor->size, sizeof(Point));
    return thisTensor;
}

Tensor* addTensor(Tensor* a, Tensor* b){
    int Ia = multiplePointParameters(a->size);
    int Ib = multiplePointParameters(b->size);
    if (Ia != Ib){
        fprintf(stderr, "addTensor error: size of tensor a is not equal size of tensor b\n");
        return NULL;
    }
    Tensor* thisTensor = initTensor(a->size);
    for (int i = 0; i < Ia; i++){
        thisTensor->data[i] = a->data[i] + b->data[i];
    }
    return thisTensor;
}

Tensor* subTensor(Tensor* a, Tensor* b){
    int Ia = multiplePointParameters(a->size);
    int Ib = multiplePointParameters(b->size);
    if (Ia != Ib){
        fprintf(stderr, "subTensor error: size of tensor a is not equal size of tensor b\n");
        return NULL;
    }
    Tensor* thisTensor = initTensor(a->size);
    for (int i = 0; i < Ia; i++){
        thisTensor->data[i] = a->data[i] - b->data[i];
    }
    return thisTensor;
}


double* getTensorField(Tensor* tensor, Point index){
    int inx = convertPointToIndex(index, *tensor->size);
    return tensor->data + inx;
}

//warning: index range isn't checked (fast function)
double* getFasterTensorField(Tensor* tensor, int index){
    return tensor->data + index;
}

void freeTensor(Tensor* tensor){
    if (tensor != NULL){
        free(tensor->data);
        free(tensor->size);
    }
    free(tensor);
}
