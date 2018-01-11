#include <time.h>
#include <stdlib.h>
#include "examples/simpleExample.h"

int main() {
    srand((unsigned int) time(NULL));
    simpleCnnMain();
//    mintMain();
//    mintMainTrain();
//    mintMainRepl();
    return 0;
}