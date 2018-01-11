#ifndef SCOTR_MNISTEXAMPLE_H
#define SCOTR_MNISTEXAMPLE_H

#include "../io/cnnProcesing.h"
#include "../util/cnnUtil.h"

Tensor *getMnist(char *filename);

TestCase *mnistReadTestCases(char *filename);

void mnistTrain(Cnn *cnn, int iterationNumber);

void mnistRepl(Cnn *cnn);

void mnistMain();

void mnistMainRepl();

void mnistMainTrain();

#endif //SCOTR_MNISTEXAMPLE_H
