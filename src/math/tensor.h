#ifndef SCOTR_TENSOR_H
#define SCOTR_TENSOR_H

#include "point.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

typedef struct {
    double *data;
    Point *size;
} Tensor;

Tensor *initTensor(Point *size);

Tensor *copyTensor(Tensor *tensor);

Tensor *addTensor(Tensor *a, Tensor *b);

Tensor *subTensor(Tensor *a, Tensor *b);

double *getTensorField(Tensor *tensor, Point index);

//warning: index range isn't checked (fast function)
double *getFasterTensorField(Tensor *tensor, int index);

void freeTensor(Tensor *tensor);

Tensor *initTensorArray(Point *inPoint, const double *array);

#endif //SCOTR_TENSOR_H
