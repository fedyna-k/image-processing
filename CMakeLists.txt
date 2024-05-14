cmake_minimum_required(VERSION 3.5)

project(pia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_DEFINITIONS("-Wall -std=c++17 -O3" -g)

add_executable(pia main.cpp)

target_include_directories(pia PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( pia ${OpenCV_LIBS} )