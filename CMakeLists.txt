cmake_minimum_required(VERSION 3.8)
project(SCOTR)

find_package(OpenCV REQUIRED)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c math/vector.h math/tensor.h math/point.h math/vector.c math/tensor.c math/point.c tests/point_test.c tests/tests.h IOlib/tensor_procesing.h IOlib/tensor_procesing.c)
add_executable(SCOTR ${SOURCE_FILES} math/vector.h)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(SCOTR ${OpenCV_LIBS})

add_definitions(-O4 -g)