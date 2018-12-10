cmake_minimum_required(VERSION 3.7)
project(binarization)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        image/Image.h
        algorithms/BradleyAlgorithm.h algorithms/BradleyAlgorithm.cpp)

include_directories(.)

add_executable(binarization ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(binarization ${OpenCV_LIBS})

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
