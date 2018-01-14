#ifndef SCOTR_GRAD_H
#define SCOTR_GRAD_H

#include <math.h>

double updateWeight(double weight, double grad, double oldGrad, double multp);

double updateGradient(double grad, double oldGrad);

int normalizeValue(double x, int max, int flag);

#endif //SCOTR_GRAD_H
