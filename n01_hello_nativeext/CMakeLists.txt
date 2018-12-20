cmake_minimum_required(VERSION 3.8)
PROJECT(hello)

set(CMAKE_VERBOSE_MAKEFILE on)
include_directories(./)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -undefined dynamic_lookup")
set(CMAKE_VERBOSE_MAKEFILE on)
add_library(hello SHARED libhello.cpp)
