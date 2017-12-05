cmake_minimum_required(VERSION 3.8)
project(cmsc441_proj1)

find_package(Boost 1.65.1)

include_directories(${Boost_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(cmsc441_proj1 ${SOURCE_FILES})