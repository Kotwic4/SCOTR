cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c math/vector.h
        math/tensor.h
        math/point.h
        math/vector.c
        math/tensor.c
        math/point.c
        tests/tests.h
        tests/point_test.c
        tests/vector_tests.c
        tests/tensor_test.c)
add_executable(SCOTR ${SOURCE_FILES} math/vector.h)