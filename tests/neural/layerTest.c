#include "layerTest.h"

void testNormalizeValue() {
    assert(normalizeValue(-1,5,0) == 0);
    assert(normalizeValue(7,5,0) == 5);
    assert(normalizeValue(3.5,5,1) == 4);
    assert(normalizeValue(3.5,5,0) == 3);
}

void testLayerAll() {
    testNormalizeValue();
}
