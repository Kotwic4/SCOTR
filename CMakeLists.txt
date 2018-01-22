cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_C_FLAGS_DEBUG "-O2")

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main/main.c
        src/main/math/vector.h
        src/main/math/tensor.h
        src/main/math/point.h
        src/main/neural/testCase.h
        src/main/neural/layer.h
        src/main/neural/cnn.h
        src/main/neural/convLayer.h
        src/main/neural/fcLayer.h
        src/main/neural/poolLayer.h
        src/main/neural/reluLayer.h
        src/main/neural/cnn.c
        src/main/neural/layer.c
        src/main/neural/reluLayer.c
        src/main/math/vector.c
        src/main/math/tensor.c
        src/main/math/point.c
        src/main/neural/poolLayer.c
        src/main/util/debugAssert.h
        src/main/neural/convLayer.c
        src/main/neural/fcLayer.c
        src/main/neural/grad.c
        src/main/neural/grad.h
        src/main/io/mathProcesing.h
        src/main/io/mathProcesing.c
        src/main/3rdParty/stb_image.h
        src/main/io/cnnProcesing.c
        src/main/io/cnnProcesing.h
        src/main/util/cnnUtil.c
        src/main/util/cnnUtil.h
        src/main/examples/mnistExample.c
        src/main/examples/mnistExample.h
        src/main/examples/simpleExample.c
        src/main/examples/simpleExample.h)

add_executable(SCOTR ${SOURCE_FILES} src/main/main.c)
target_link_libraries(SCOTR m)
