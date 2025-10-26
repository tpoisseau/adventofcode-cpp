cmake_minimum_required(VERSION 4.0)
project(advent_of_code_cpp)

set(CMAKE_CXX_STANDARD 26)

file(GLOB SRC_FILES_2022 ${PROJECT_SOURCE_DIR}/2022/*.h ${PROJECT_SOURCE_DIR}/2022/*.cpp)
add_executable(advent_of_code_cpp main.cpp ${SRC_FILES_2022}
        shared/iterators.h)
