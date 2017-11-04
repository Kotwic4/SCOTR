#include <malloc.h>
#include <memory.h>
#include "tensor.h"

Tensor* initTensor(Point* size){
    Tensor* thisTensor;
    thisTensor->data = calloc((size_t) size->H * size->W * size->D, sizeof(double));
    if(!thisTensor->data){
        fprintf(stderr, "initTensor error: calloc error\n");
        return NULL;
    }
    thisTensor->size = size;
    return thisTensor;
}

Tensor* copyTensor(Tensor* tensor){
    Tensor* thisTensor = initTensor(tensor->size);
    memcpy(thisTensor, tensor, sizeof(tensor));
    return thisTensor;
}

Tensor* addTensor(Tensor* a, Tensor* b){
    int Ia = a->size->H * a->size->W * a->size->D;
    int Ib = b->size->H * b->size->W * b->size->D;
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
    int Ia = a->size->H * a->size->W * a->size->D;
    int Ib = b->size->H * b->size->W * b->size->D;
    if (Ia < Ib){
        fprintf(stderr, "subTensor error: size of tensor a is not equal size of tensor b\n");
        return NULL;
    }
    Tensor* thisTensor = initTensor(a->size);
    for (int i = 0; i < Ia; i++){
        thisTensor->data[i] = a->data[i] - b->data[i];
    }
    return thisTensor;
}


void* getTensorField(Tensor* tensor, Point* index){
    int inx = convertPointToIndex(*index, *tensor->size);
    return &tensor->data[inx];
}

//warning: index range isn't checked (fast function)
void* getFasterTensorField(Tensor* tensor, int index){
    return &tensor->data[index];
}

void freeTensor(Tensor* tensor){
    free(tensor->data);
}