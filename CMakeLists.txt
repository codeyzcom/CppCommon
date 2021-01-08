cmake_minimum_required(VERSION 3.17)
project(CppRepo)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(
        CppRepo
        main.cpp
        lib/multithreading/simple_worker_thread/worker.cpp
        lib/multithreading/simple_worker_thread/worker.h
)