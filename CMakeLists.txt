cmake_minimum_required(VERSION 3.17)
project(Thread_Pool)

set(CMAKE_CXX_STANDARD 17)

add_executable(Thread_Pool main.cpp ThreadPool.cpp ThreadPool.h Logger.cpp Logger.h)