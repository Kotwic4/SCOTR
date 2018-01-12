#include "tensor.h"
#include <stdio.h>
#include <malloc.h>
#include <memory.h>


Tensor *initTensor(const Point *size) {
    Tensor *thisTensor = malloc(sizeof(Tensor));
    thisTensor->data = calloc((size_t) multiplePointParameters(size), sizeof(double));
//    if (!thisTensor->data) {
//        fprintf(stderr, "initTensor error: calloc for data error\n");
//        return NULL;
//    }
    thisTensor->size = copyPoint(size);
    return thisTensor;
}

Tensor *copyTensor(const Tensor *tensor) {
    Tensor *thisTensor = initTensor(tensor->size);
    memcpy(thisTensor->data, tensor->data, sizeof(double) * multiplePointParameters(tensor->size));
//    memcpy(thisTensor->size, tensor->size, sizeof(Point));
    return thisTensor;
}

Tensor *addTensor(const Tensor *a, const Tensor *b) {
    int Ia = multiplePointParameters(a->size);
    int Ib = multiplePointParameters(b->size);
//    if (Ia != Ib) {
//        fprintf(stderr, "addTensor error: size of tensor a is not equal size of tensor b\n");
//        return NULL;
//    }
    Tensor *thisTensor = initTensor(a->size);
    for (int i = 0; i < Ia; ++i) {
        thisTensor->data[i] = a->data[i] + b->data[i];
    }
    return thisTensor;
}

Tensor *subTensor(const Tensor *a, const Tensor *b) {
    int Ia = multiplePointParameters(a->size);
    int Ib = multiplePointParameters(b->size);
//    if (Ia != Ib) {
//        fprintf(stderr, "subTensor error: size of tensor a is not equal size of tensor b\n");
//        return NULL;
//    }
    Tensor *thisTensor = initTensor(a->size);
    for (int i = 0; i < Ia; ++i) {
        thisTensor->data[i] = a->data[i] - b->data[i];
    }
    return thisTensor;
}


double *getTensorField(const Tensor *tensor, const Point *index) {
    int inx = convertPointToIndex(index, tensor->size);
    return getFasterTensorField(tensor, inx);
}


double *getFasterTensorField(const Tensor *tensor, const int index) {
    return tensor->data + index;
}

void freeTensor(Tensor *tensor) {
//    if (tensor != NULL) {
//        free(tensor->data);
//        free(tensor->size);
//    }
    free(tensor->data);
    free(tensor->size);
    free(tensor);
}

Tensor *initTensorArray(const Point *inPoint, const double *array) {
    Tensor *result = initTensor(inPoint);
    for (int i = 0; i < multiplePointParameters(inPoint); ++i) {
        *getFasterTensorField(result, i) = array[i];
    }
    return result;
}
