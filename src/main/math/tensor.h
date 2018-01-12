#ifndef SCOTR_TENSOR_H
#define SCOTR_TENSOR_H

#include "point.h"

typedef struct {
    double *data;
    Point *size;
} Tensor;

Tensor *initTensor(const Point *size);

Tensor *copyTensor(const Tensor *tensor);

Tensor *addTensor(const Tensor *a, const Tensor *b);

Tensor *subTensor(const Tensor *a, const Tensor *b);

double *getTensorField(const Tensor *tensor, const Point* index);

//warning: index range isn't checked (fast function)
double *getFasterTensorField(const Tensor *tensor, int index);

void freeTensor(Tensor *tensor);

Tensor *initTensorArray(const Point *inPoint, const double *array);

#endif //SCOTR_TENSOR_H
