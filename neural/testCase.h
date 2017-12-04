#ifndef SCOTR_TESTCASE_H
#define SCOTR_TESTCASE_H

#include "../math/tensor.h"

typedef struct {
    Tensor *input, *expected;
} TestCase;
#endif //SCOTR_TESTCASE_H
