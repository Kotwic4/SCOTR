#include <assert.h>
#include "gradTest.h"
#include "../../main/neural/grad.h"

void assertDoubleEquals(double value, double value2) {
    double e = 0.00000001;
    if (value2 > value) {
        assert(value2 - value < e);
    } else {
        assert(value - value2 < e);
    }
}

void testUpdateWeight() {
    assertDoubleEquals(updateWeight(4, 3, 2, 1), 3.957960);
}

void testUpdateGradient() {
    assertDoubleEquals(updateGradient(2, 2), 3.2);
    assertDoubleEquals(updateGradient(2, 0), 2);
    assertDoubleEquals(updateGradient(0, 2), 1.2);
}

void testNormalizeValue() {
    assert(normalizeValue(-1, 5, 0) == 0);
    assert(normalizeValue(7, 5, 0) == 5);
    assert(normalizeValue(3.5, 5, 1) == 4);
    assert(normalizeValue(3.5, 5, 0) == 3);
}

void testGradAll() {
    testUpdateWeight();
    testUpdateGradient();
    testNormalizeValue();
}
