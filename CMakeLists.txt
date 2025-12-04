cmake_minimum_required(VERSION 4.0)
project(advent_of_code_cpp)

set(CMAKE_CXX_STANDARD 26)

#file(GLOB SRC_FILES_2022 ${PROJECT_SOURCE_DIR}/2022/*.h ${PROJECT_SOURCE_DIR}/2022/*.cpp)
#file(GLOB SRC_FILES_2025 ${PROJECT_SOURCE_DIR}/2025/*.h ${PROJECT_SOURCE_DIR}/2025/*.cpp)
add_executable(advent_of_code_cpp main.cpp
        shared/iterators.h
        # ${SRC_FILES_2022}
        # ${SRC_FILES_2025}
        2025/day_01.h 2025/day_01.cpp
        2025/day_02.h 2025/day_02.cpp
        2025/day_03.h 2025/day_03.cpp
        2025/day_04.cpp
        2025/day_04.h)
