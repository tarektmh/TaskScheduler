cmake_minimum_required(VERSION 3.30)
project(TaskScheduler)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskScheduler main.cpp Task.cpp Scheduler.cpp)

# Conan integration
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()