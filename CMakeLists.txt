cmake_minimum_required(VERSION 3.8)
project(SCOTR)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c math/vector.h math/tensor.h math/point.h)
add_executable(SCOTR ${SOURCE_FILES} math/vector.h)