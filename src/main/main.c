#include <time.h>
#include <stdlib.h>
#include "examples/simpleExample.h"
#include "examples/mnistExample.h"

int main() {
    srand((unsigned int) time(NULL));
//    simpleCnnMain();
//    mnistMain();
    mnistMainTrain();
//    mnistMainRepl();
    return 0;
}