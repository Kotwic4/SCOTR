#ifndef SCOTR_TENSOR_PROCESING_H
#define SCOTR_TENSOR_PROCESING_H

#include <stdio.h>
#include "../math/tensor.h"
#include "../math/vector.h"

Tensor* readImagineToTensor(char* filename);

Tensor* readTensorFromFile(FILE* file);

void writeTensorToFile(Tensor* tensor, FILE* file);

Tensor* addDimensionsToTensor(Tensor* oldT, int n, int k);

Vector* createParamtersTensors(Tensor* rawImage, int n);

Tensor* returnOutputTensor(int n, int k);

Point readPointFile(FILE *file);

void savePointFile(FILE *file, Point point);

#endif //SCOTR_TENSOR_PROCESING_H
