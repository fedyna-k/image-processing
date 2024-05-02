cmake_minimum_required(VERSION 3.5)

project(pic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_DEFINITIONS("-Wall -std=c++17 -O3" -g)

add_executable(pic main.cpp)

target_include_directories(pic PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( pic ${OpenCV_LIBS} )