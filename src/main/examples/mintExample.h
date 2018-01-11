#ifndef SCOTR_MINTEXAMPLE_H
#define SCOTR_MINTEXAMPLE_H

#include "../io/cnnProcesing.h"
#include "../util/cnnUtil.h"

Tensor *getMnist(char *filename);

TestCase *mintReadTestCases(char *filename, int caseNumber);

void mintTrain(Cnn *cnn, int caseNumber, int iterationNumber);

void mintRepl(Cnn *cnn);

void mintMain();

void mintMainRepl();

void mintMainTrain();

#endif //SCOTR_MINTEXAMPLE_H
