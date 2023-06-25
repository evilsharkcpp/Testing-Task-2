cmake_minimum_required(VERSION 3.10)

project(FindSymmetry)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set (headers
#Point2.hpp
#Polygon.hpp
)

set (sources
)

add_executable(${PROJECT_NAME} main.cpp ${headers} ${sources})