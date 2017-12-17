cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        math/vector.h
        math/tensor.h
        math/point.h
        neural/testCase.h
        neural/layer.h
        neural/cnn.h
        neural/convLayer.h
        neural/fcLayer.h
        neural/poolLayer.h
        neural/reluLayer.h
        neural/cnn.c
        neural/layer.c
        neural/reluLayer.c
        math/vector.c
        math/tensor.c
        math/point.c
        neural/poolLayer.c
        util/debugAssert.h
        neural/convLayer.c
        neural/fcLayer.c
        neural/grad.c
        neural/grad.h
        tests/math/pointTest.c
        tests/math/pointTest.h
        tests/math/mathTest.c
        tests/math/mathTest.h
        tests/tests.c
        tests/tests.h
        tests/math/vectorTest.c
        tests/math/vectorTest.h
        tests/math/tensorTest.c
        tests/math/tensorTest.h
        tests/neural/cnnTest.c
        tests/neural/cnnTest.h
        tests/neural/fcLayerTest.c
        tests/neural/fcLayerTest.h
        tests/neural/poolLayerTest.c
        tests/neural/poolLayerTest.h
        tests/neural/neuralTest.c
        tests/neural/neuralTest.h
        tests/neural/convLayerTest.c
        tests/neural/convLayerTest.h
        tests/neural/gradTest.c
        tests/neural/gradTest.h
        tests/neural/layerTest.c
        tests/neural/layerTest.h
        tests/neural/reluLayerTest.c
        tests/neural/reluLayerTest.h)
add_executable(SCOTR ${SOURCE_FILES} main.c)
