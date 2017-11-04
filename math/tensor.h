#ifndef SCOTR_TENSOR_H
#define SCOTR_TENSOR_H

#include "point.h"

typedef struct{
    double* data;
    Point* size;
}Tensor;

// change int to size_t?
Tensor* initTensor(Point* size, int data_size);
Tensor* copyTensor(Tensor* tensor);
Tensor* addTensor(Tensor* a, Tensor* b);
Tensor* subTensor(Tensor* a, Tensor* b);
double* getTensorField(Tensor* tensor,Point* index);
void freeTensor(Tensor* tensor);

#endif //SCOTR_TENSOR_H
