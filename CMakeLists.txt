cmake_minimum_required(VERSION 3.30)
project(TaskScheduler)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskScheduler main.cpp Task.cpp Scheduler.cpp FCFSScheduler.cpp SJNScheduler.cpp PriorityScheduler.cpp RoundRobinScheduler.cpp)