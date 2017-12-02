#ifndef SCOTR_TESTS_H
#define SCOTR_TESTS_H

//POINT
void TEST_multiplePointParameters();
void TEST_copyPoint();
void TEST_convertPointToIndex();
void TEST_convertIndexToPoint();
void TEST_POINT_ALL();

//VECTOR
void TEST_initVector();
void TEST_freeVector();
void TEST_pushBackVector();
void TEST_getVectorField();
void TEST_VECTOR_ALL();

//TENSOR
void TEST_initTensor();
void TEST_freeTensor();
void TEST_copyTensor();
void TEST_addTensor();
void TEST_subTensor();
void TEST_getTensorField();
void TEST_getFasterTensorField();
void TEST_TENSOR_ALL();

#endif //SCOTR_TESTS_H
