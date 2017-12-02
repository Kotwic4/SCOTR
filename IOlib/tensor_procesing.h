#ifndef SCOTR_TENSOR_PROCESING_H
#define SCOTR_TENSOR_PROCESING_H

#include <stdio.h>
#include "../math/tensor.h"

//using OpenCV library, IplImage structure; H and W is for image size, D is RGB
Tensor* readImagineToTensor( FILE* imgFile );

Tensor* readTensorFromFile( FILE* tensorFile );

//I could return FILE*, if U need
void writeTensorToFile( Tensor* tensor, char* filename );

//if U have a better name for that, I'm listening:
Tensor* convertFirstCNNTensorToSecondCNNTensor( Tensor* firstCNNTensor );
// ^ I wuold like to add a one dimention to depth and add only two values at the and of tensor
// it will be a bit wasting a memory, but we will be able to keep our acctual math implementation


#endif //SCOTR_TENSOR_PROCESING_H
