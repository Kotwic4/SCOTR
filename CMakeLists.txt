cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        math/vector.h
        math/tensor.h
        math/point.h
        cnn/testCase.h
        cnn/layer.h
        cnn/cnn.h
        cnn/convLayer.h
        cnn/fcLayer.h
        cnn/poolLayer.h
        cnn/reluLayer.h
        cnn/cnn.c cnn/layer.c cnn/reluLayer.c)
add_executable(SCOTR ${SOURCE_FILES} main.c)