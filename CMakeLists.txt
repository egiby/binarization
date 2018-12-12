cmake_minimum_required(VERSION 3.7)
project(binarization)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        image/Image.h
        algorithms/BradleyAlgorithm.h algorithms/BradleyAlgorithm.cpp)

include_directories(.)

add_executable(binarization ${SOURCE_FILES})

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(binarization ${OpenCV_LIBS})

# pkg-config
find_package(PkgConfig REQUIRED)

# VIPS
pkg_check_modules(VIPS REQUIRED vips vips-cpp gobject-2.0)
include_directories(${VIPS_INCLUDE_DIRS})
target_link_libraries(binarization ${VIPS_LIBRARIES})
