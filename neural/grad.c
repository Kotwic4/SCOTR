#include "grad.h"

#define LEARNING_RATE 0.01
#define MOMENTUM 0.6
#define WEIGHT_DECAY 0.001

double updateWeight(double weight, double grad, double oldGrad, double multp) {
    weight -= LEARNING_RATE * (updateGradient(grad, oldGrad) * multp +  WEIGHT_DECAY * weight);
    return weight;
}

double updateGradient(double grad, double oldGrad) {
    return grad + oldGrad * MOMENTUM;
}