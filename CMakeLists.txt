cmake_minimum_required (VERSION 3.10)
project (WinnowingAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -Wextra -pedantic -g -fopenmp")
set(BINARY_FILE "find-pattern")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable("${BINARY_FILE}" "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_link_libraries("${BINARY_FILE}" SOURCE_OBJS OpenCL)

add_subdirectory(src)
