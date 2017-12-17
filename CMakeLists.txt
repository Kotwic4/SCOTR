cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_CXX_FLAGS_DEBUG "-O2")

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        src/math/vector.h
        src/math/tensor.h
        src/math/point.h
        src/neural/testCase.h
        src/neural/layer.h
        src/neural/cnn.h
        src/neural/convLayer.h
        src/neural/fcLayer.h
        src/neural/poolLayer.h
        src/neural/reluLayer.h
        src/neural/cnn.c
        src/neural/layer.c
        src/neural/reluLayer.c
        src/math/vector.c
        src/math/tensor.c
        src/math/point.c
        src/neural/poolLayer.c
        src/util/debugAssert.h
        src/neural/convLayer.c
        src/neural/fcLayer.c
        src/neural/grad.c
        src/neural/grad.h
        test/math/pointTest.c
        test/math/pointTest.h
        test/math/mathTest.c
        test/math/mathTest.h
        test/tests.c
        test/tests.h
        test/math/vectorTest.c
        test/math/vectorTest.h
        test/math/tensorTest.c
        test/math/tensorTest.h
        test/neural/cnnTest.c
        test/neural/cnnTest.h
        test/neural/fcLayerTest.c
        test/neural/fcLayerTest.h
        test/neural/poolLayerTest.c
        test/neural/poolLayerTest.h
        test/neural/neuralTest.c
        test/neural/neuralTest.h
        test/neural/convLayerTest.c
        test/neural/convLayerTest.h
        test/neural/gradTest.c
        test/neural/gradTest.h
        test/neural/layerTest.c
        test/neural/layerTest.h
        test/neural/reluLayerTest.c
        test/neural/reluLayerTest.h
        src/IOlib/tensor_procesing.h
        src/IOlib/tensor_procesing.c
        src/IOlib/stb_image.h)
add_executable(SCOTR ${SOURCE_FILES} src/main.c)
target_link_libraries(SCOTR m)