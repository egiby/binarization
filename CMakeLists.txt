cmake_minimum_required(VERSION 3.7)
project(binarisation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2 -Wall")

set(SOURCE_FILES main.cpp image/Image.h algorithms/IAlgorithm.h algorithms/BradleyBinarisationAlgorithm.h)
add_executable(binarisation ${SOURCE_FILES})

find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(binarisation ${ImageMagick_LIBRARIES})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

configure_file(data/01.jpg 01.jpg COPYONLY)