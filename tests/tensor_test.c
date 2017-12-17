#include <assert.h>
#include <wchar.h>
#include <malloc.h>
#include "../math/tensor.h"
#include "../math/point.h"

void TEST_freeTensor(){
    for (int i = 0; i < 10000; i++){
        Point point = {100, 100, 100};
        Tensor* tensor1 = initTensor(&point);
        freeTensor(tensor1);
    }
}

void TEST_initTensor(){
    Point p1 = {1, 2, 3};
    Tensor* tensor1 = initTensor( &p1 );
    assert( tensor1->size->H == p1.H );
    assert( tensor1->size->D == p1.D );
    assert( tensor1->size->W == p1.W );
    assert(tensor1->data != NULL);
    freeTensor(tensor1);
}

void TEST_copyTensor(){
    Point point = {1, 2, 3};
    Tensor* tensor1 = initTensor( &point );
    tensor1->data[0] = 1.0;
    tensor1->data[3] = 12.1;
    tensor1->data[5] = 8.3;
    Tensor* tensor2 = copyTensor(tensor1);
    assert(tensor1 != NULL);
    assert(tensor1->size->H == tensor2->size->H);
    assert(tensor1->size->D == tensor2->size->D);
    assert(tensor1->size->W == tensor2->size->W);
    assert(tensor1->data[0] == tensor2->data[0]);
    assert(tensor1->data[1] == tensor2->data[1]);
    assert(tensor1->data[2] == tensor2->data[2]);
    assert(tensor1->data[3] == tensor2->data[3]);
    assert(tensor1->data[5] == tensor2->data[5]);
    freeTensor(tensor1);
    freeTensor(tensor2);
}

void TEST_addTensor() {
    Point p1 = {2, 2, 2};
    Tensor* summand1 = initTensor( &p1);
    Point p2 = {4, 4, 4};
    Tensor* summand2 = initTensor( &p2 );
    Tensor* sum = addTensor(summand1, summand2);
    assert(sum == NULL);
    freeTensor(summand1);
    freeTensor(summand2);
    freeTensor(sum);

    Point p3 = {10, 10, 10};
    Tensor* summand3 = initTensor( &p3 );
    Tensor* summand4 = initTensor( &p3 );
    for (int i = 0; i < 1000; i++){
        summand3->data[i] = i;
        summand4->data[i] = 999 - i;
    }
    Tensor* sumb = addTensor(summand3, summand4);
    for (int i = 0; i < 1000; i++){
        assert(sumb->data[i] == 999);
    }
    freeTensor(summand3);
    freeTensor(summand4);
    freeTensor(sumb);
}

void TEST_subTensor(){
    Point p1 = {2, 2, 2};
    Tensor* minuend = initTensor( &p1 );
    Point p2 = {4, 4, 4};
    Tensor* subtrahend = initTensor( &p2 );
    Tensor* subtraction = subTensor(minuend, subtrahend);
    assert(subtraction == NULL);
    freeTensor(minuend);
    freeTensor(subtrahend);
    freeTensor(subtraction);

    Point p3 = {10, 10, 10};
    Tensor* minuend1 = initTensor( &p3 );
    Tensor* subtrahend1 = initTensor( &p3 );
    for (int i = 0; i < 1000; i++){
        minuend1->data[i] = i;
        subtrahend1->data[i] = i;
    }
    Tensor* subtraction1 = subTensor(minuend1, subtrahend1);
    for (int i = 0; i < 1000; i++){
        assert(subtraction1->data[i] == 0);
    }
    freeTensor(minuend1);
    freeTensor(subtrahend1);
    freeTensor(subtraction1);
}

void TEST_getTensorField(){
    Point p1 = {1, 2, 3};
    Tensor* tensor1 = initTensor( &p1 );
    tensor1->data[1] = 16.7;
    Point p2 = {0, 1, 0};
    double* num = getTensorField( tensor1, p2 );
    assert(*num == 16.7);
    freeTensor(tensor1);
}

void TEST_getFasterTensorField(){
    Point p1 = {1, 2, 3};
    Tensor* tensor1 = initTensor( &p1 );
    tensor1->data[1] = 19.1;
    Point p2 = {0, 1, 0};
    double* num = getTensorField( tensor1, p2 );
    assert( *num == 19.1);
    freeTensor(tensor1);
}

void TEST_TENSOR_ALL(){
    TEST_freeTensor();
    TEST_initTensor();
    TEST_copyTensor();
    TEST_addTensor();
    TEST_subTensor();
    TEST_getTensorField();
    TEST_getFasterTensorField();
}

