#ifndef SCOTR_CNNUTIL_H
#define SCOTR_CNNUTIL_H

#include "../neural/cnn.h"

/*
 * Process input tensor by neural network and prints result.
 */
void printForwad(Cnn *neuralNetwork, Tensor *input);


/*
 * Train neural network using test cases.
 * Every 100 iteration there is information about progress.
 */
void trainCnnTestCases(Cnn *neuralNetwork, TestCase *testCases, int caseNumber, int iterationNumber);

#endif //SCOTR_CNNUTIL_H
